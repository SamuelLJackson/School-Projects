/* * * * * * * * * ** * ** ** ** * * * * ** *** * * * * * *  * * * * *
 * File:     Pinball.cpp
 * Project:  Project 5
 * Author:   Sam Everett
 * Date:     12/06/16
 * Section:  03
 * E-mail:   eversam1@umbc.edu
 *
 * This file is the implementation of the Pinball hashing class.  It contains
 * various methods for insertion, removal and finding chars within its midst.
 * it also includes a functino to print out the data relevant to chang's 
 * stipulations.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "Pinball.h"
#include <cstring>
#include <stdlib.h>
#include <iostream>

using namespace std;

Pinball::Pinball(int n) {
  //initilize members
  m_capacity = n;
  m_size = 0;
  m_degree = 7;
  m_ejectLimit = 20; 
  m_cuckooCount = 0;
  m_maxEjectionsInSingleInsert = 0;
  H = new char * [m_capacity];
  //initialize arrays
  m_seeds = new int[m_capacity];
  m_primarySlotsArray = new int[m_capacity];
  for (int i = 0; i < m_capacity; i++) {
    H[i] = (char*)"___";
    m_seeds[i] = rand();
    m_primarySlotsArray[i] = 0;
  }
  m_totalEjections = 0;
  m_primarySlots = 0;
  m_savedSeed = rand();
  m_didntMakeIt = 0;

  m_avgHitsToPrimarySlots = 0;
  
}
//destructor
Pinball::~Pinball() {
  //iterate over hash table to remove and free char *'s
  for (int i = 0; i < m_capacity; i++) {
    if (at(i) != NULL) {
      free(H[i]);
    }
      H[i] = NULL;
  }
  //free dynamically allocated arrays
  free(H);
  H = NULL;
  delete [] m_seeds;
  delete [] m_primarySlotsArray;

  m_seeds = NULL;
  m_primarySlotsArray = NULL;

}

//places char* in hash table, OR DOES IT DUN DUN DUUUUUUUN?????
void Pinball::insert(const char * str) {
  if (m_size == m_capacity) {//there is literally no room left
    throw PinballHashFull("Hash if full!");
  }

  //find the primary slot captain!
  unsigned int primarySlotIndex = hashCode(str) % m_capacity;
  if (at(primarySlotIndex) == NULL) {
    //place the value in its primary slot, garrrr
    H[primarySlotIndex] = strdup(str);
    
    //increment size, number of nodes in primary slot, and number of elements
    // that hash to the same primary slot
    m_size++;
    m_primarySlots++;
    m_primarySlotsArray[primarySlotIndex] += 1;
  } 
  
  else { //primary slot full
    m_primarySlotsArray[primarySlotIndex] += 1;
    srand(m_seeds[primarySlotIndex]);
    
    //create an array of auxiliary slots matey, shiver me timbers
    int auxNodes[6];
    for (int i = 0; i < 6; i++) {
      auxNodes[i] = rand() % m_capacity;
    }
    
    int indexCounter = 0;
    bool noEmptiesFound = true;
    
    while (indexCounter < 6 && noEmptiesFound) {//iterate over auxiliary nodes
      
      if (at(auxNodes[indexCounter]) == NULL) {
	noEmptiesFound = false;
	break;
      }
      indexCounter++;
    }//end while loop over auxNodes
    
    if (!noEmptiesFound) { //time to insert the node into empty auxNode
      
      H[auxNodes[indexCounter]] = strdup(str);
      //incase we are cuckooing, time to reset!
      m_cuckooCount = 0;
      m_size++;
    } else {
      
      if (m_cuckooCount < 20) {
	//hoist the mains! it's tijme to eject!
	m_totalEjections++;
	m_cuckooCount++;
	if (m_cuckooCount > m_maxEjectionsInSingleInsert)
	  m_maxEjectionsInSingleInsert = m_cuckooCount;
	
	srand(m_savedSeed);
	unsigned int ejectionIndex = auxNodes[rand() % 6];
	//walk the plank ye lousy land lubber,
	char * temp = remove(H[ejectionIndex]);
	m_size++;
	H[ejectionIndex] = strdup(str);
	//recursively call insert to try again
	insert(temp);
	//free the temp var mem
	//feed temp to the sharks
	free(temp);
      } else {
	m_didntMakeIt++;
	//ahoy, we've reached our limit!
	throw PinballHashFull("Ejection Limit Reached");
      }
      
    }
  } //end else
}

//make haste to the crow's nest and see if there be land ahead
int Pinball::find(const char * str) {

  //locate primary slot
  unsigned int primarySlotIndex = hashCode(str) % m_capacity;
  //if something is in primary slot, and that somthing is our lovely
  //lass, so return her!
  if (at(primarySlotIndex) != NULL && strcmp(at(primarySlotIndex), str) == 0) {
    return primarySlotIndex;
  } else {
    //set up for fishing boys!
    //set the random generator to acquire auxiliary nodes
    srand(m_seeds[primarySlotIndex]);

    //create array of aux nodes
    int auxNodes[6];
    for (int i = 0; i < 6; i++) {
      auxNodes[i] = rand() % m_capacity;
    }
    for (int i = 0; i < 6; i++ ){
      //
      if (strcmp(H[auxNodes[i]],str) == 0) {
	//drink up lads, we've found our string at last
	return auxNodes[i];
      }
    }
  }
  //Nothing found, abandon shiiiiip
  return -1; 
}

//Arrrrg, here be the remove function, made 'specially for cstrings and 
// stowaways, but mostly the first thing.
char * Pinball::remove(const char * str) {
  
  if (find(str) >= 0) {//if str is in the table
    unsigned int index = find(str);//get it's index
    char * tempRemoveChar = H[index];//make a pointer to take in cstring
    H[index] = (char*)"___";//rest the index value to default
    m_size--;//decrement size
    return tempRemoveChar;//return the pointer
  } else {
    return NULL;//return null if the thing isn't in the hash
  }
}

//check at a location for an initialized pointer, or buried treasure, but
// mostly the first thing
const char * Pinball::at(int index) {

  if (index > m_capacity || index < 0) {
    throw out_of_range("I say good fellow, you've gone out of range!");
  }
  //reset to default
  if (H[index] != (char*)"___")
    return H[index];
  else//wasn't an initilized char there
    return NULL;
}

//We've made it to the end captain!
//Time to print out the data!
void Pinball::printStats() {
  //calculate average hits
  m_avgHitsToPrimarySlots = (double)m_size/(double)m_primarySlots;
  cout << "Hash statistics report!" << endl;
  cout << "   randomness level                      = pseudo-random" << endl;
  cout << "   capacity                              = " << m_capacity << endl;
  cout << "   size                                  = " << m_size << endl;
  cout << "   degree                                = 7"<< endl;
  cout << "   ejection limit                        = 20" << endl;
  cout << "   number of primary slots               = " << m_primarySlots << endl;
  cout << "   average hits to primary slots         = " << m_avgHitsToPrimarySlots  << endl;
  cout << "   maximum hits to primary slots         = " << calculateMaxHitsToPrimarySlot()  << endl;
  cout << "   total number of ejections             = " << m_totalEjections << endl;
  cout << "   Maximum ejections in single insertion = " << m_maxEjectionsInSingleInsert  << endl;
}

//used as the name says vvvvvvvvvvvvvvvvvv
int Pinball::calculateMaxHitsToPrimarySlot() {
  int max = 0;
  for (int i = 0; i < m_capacity; i++) {
    if (m_primarySlotsArray[i] > max)
      max = m_primarySlotsArray[i];
  }
  return max;
}
