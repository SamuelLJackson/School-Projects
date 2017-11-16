/* * * * * * * * * ** * ** ** ** * * * * ** *** * * * * * *  * * * * *
 * File:     myDriver.cpp
 * Project:  Project 5
 * Author:   Sam Everett
 * Date:     12/06/16
 * Section:  03
 * E-mail:   eversam1@umbc.edu
 *
 * This is the main workhorse, pumping out 150 runs of inserting things and
 * printing out data to reflect each of these.  
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <iostream>
#include <time.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pinball.h"
#include "words.h"


using namespace std;

//Get amount of user time since the program begain in milliseconds


double getmsecs() {
  struct rusage use;
  struct timeval utime;

  getrusage(RUSAGE_SELF, &use);
  utime = use.ru_utime;
  
  return ((double) utime.tv_sec)*1000.0 + ((double) utime.tv_usec)/1000.0;
  
}

// A "bug-proff" way to call rand() that preserves the state of the
// random seed between calls to rand().
// set the random seed by passing a non-zero parameter

int myRand(int seed=0) {
  // static local variables persist between calls 
  static int savedSeed;

  if (seed) savedSeed = seed;

  int othersSeed = rand(); // save other people's seed
  srand(savedSeed);           // restore my seed
  int result = rand();
  savedSeed = result;
  srand(othersSeed);
  return result;
}


//Exercies the pibball hash table with size slots
// inserting reps items

void test(int size, int reps) {

  int index;
  int slot;
  double startTime, stopTime;

  Pinball PH(size);

  startTime = getmsecs();

  //Insert reps randomly chosen itemn

  for (int i=0; i < reps; i++) {
    // don't choose items already in the hash table
    do {
      index = myRand() % numWords;
      slot = PH.find(words[index]);
    } while(slot > -1);
    try {
      PH.insert(words[index]); // might throw exception
      //double check that inserted items were store propery

    } catch (PinballHashFull &e) {
      cout << e.what() << endl;
      break;
    } catch (...) {
      cout << "Unkown error\n";
    }

  }


  stopTime = getmsecs();
  printf("Elapsed time = %.3lf milliseconds\n", stopTime - startTime);
  
  PH.printStats();
  
}

int main() {
  //set random seed to wall clock time in milliseconds
  struct timeval tp;
  gettimeofday (&tp, NULL);
  long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
  printf("Random seed set to : %ld\n\n", ms);
  myRand(ms);
  srand(ms*37); // other uses


  //perform some paltry test to chekc that basic function sare working:
  Pinball pinball(1);
  pinball.insert(words[200]);
  cout << "pinball.find(words[200]): (should be 0): " << pinball.find(words[200]) << endl;
  try {
      pinball.insert(words[11]); // should throw Hashfull exception
    } catch (PinballHashFull &e) {
      cout << e.what() << endl;
    } catch (...) {
      cout << "Unkown error\n";
    }  

  try {
    pinball.at(-333);
    } catch (out_of_range &e) {
      cout << e.what() << endl;
    } catch (...) {
      cout << "Unkown error\n";
    }

  try {
    pinball.at(2);
    } catch (out_of_range &e) {
      cout << e.what() << endl;
    } catch (...) {
      cout << "Unkown error\n";
    }



  //make all 150 trials and print them jiggas out
  int capacityArray[3] = {5003, 10037, 20101};
  int numInsertsArray[5] = {2500, 3000, 3500, 4000, 4500};
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 5; j++) {
      for (int k = 0; k < 10; k++) {
	if (i == 2) {
	  test(capacityArray[i], numInsertsArray[j] * 4);
	} else {
	  test(capacityArray[i], numInsertsArray[j] * (i+1));
	}
	cout << endl;
      }
    }
  }
  return 0;
}
