/* * * * * * * * * ** * ** ** ** * * * * ** *** * * * * * *  * * * * *
 * File:     Pinball.h
 * Project:  Project 5
 * Author:   Sam Everett
 * Date:     12/06/16
 * Section:  03
 * E-mail:   eversam1@umbc.edu
 *
 * This is the header file for the Pinball hashtable object.  It includes 
 * declarations of many variables and functions.  funcions include insert, 
 * find, at, remove, printStats, size, and one to calculate the maximum number
 * of primary slots.  
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _PINBALL_H_
#define _PINBALL_H_

#include <string>
#include <stdexcept>
using namespace std;

class PinballHashFull : public std::out_of_range {
 public:
 PinballHashFull(const string& what) : std::out_of_range(what) {}
};

class Pinball {

 public:
  //////////////////////////////////////////////////////////////////////////
  //Name: Pinball
  //Input: an integer to set the capacity of the hash table
  //Output: a Pinball hashtable object
  //->Initializes the many and various member variables
  //  This implementation includes a value to initialize all indexes.
  //  The array of seed values is also set up in this constructr.
  ///////////////////////////////////////////////////////////////////////////
  Pinball(int n=1019); //default capacity is prime

  //////////////////////////////////////////////////////////////////////////
  //Name:~Pinball
  //Input: none
  //Ouput: destroys Pinball object
  //->In this destructor implementation, the program utilizes a for loop and
  //  the pinball class' remove function to free all of the character arrays
  //  withihn ght main data structure, representing the hash table, called H.
  //  apart from this, the destructor calls delete such other dynamically
  //  allocated member variables as needs be.
  /////////////////////////////////////////////////////////////////////////////
  ~Pinball();

  ////////////////////////////////////////////////////////////////////////////
  //Name: insert
  //Input: a consant character array
  //Ouptu: none, but the end result is (unless tha hash table is full) a new
  //       element in the has table
  //->This implementation ultimately seeks to place a given char* into the hash
  //  table.  There are three main cases accounted for: primary slot is empty,
  //  one of the auxiliary nodes is empty, or a previously inserted item needs
  //  to be ejected (cuckoo'd), so that the new one may find a home in the hash
  //  the process of ejecting and inserting stops when the number of ejections
  //  reaches a certain limit for a given insert, and the hash table is deemed
  //  full.  Memory is allocated when removing the char , and freed with a call
  //  to free.  This function also updates many useful member variables which
  //  are spit out in the printStats() function
  ///////////////////////////////////////////////////////////////////////////
  void insert(const char *str);

  ///////////////////////////////////////////////////////////////////////////
  //Name: find
  //Output: an integer, representing the index of the given char *, or a -1
  //        if the given char * is not found
  //Input: a constant character array
  //->This implementation is fairly short.  It employs the same logic as the
  //  insert did: if the given char's primary slot is full, then check the 
  //  successive auxiliary nodes.  This implementation makes use of the 
  //  member function at to assess the existence of the given char.
  ///////////////////////////////////////////////////////////////////////////
  int find (const char *str);

  //////////////////////////////////////////////////////////////////////////
  //Name: at(int index)
  //Input: an integer, representing an index in the hash table
  //Output: a pointer to a charavter array in the array, or NULL
  //->This implenentation is short.  It inculdes an exception throw iff the
  //  it is given a negative value, or an index beyond the capacity of the 
  //  hash table, it is thrown.  The raming too cases include the existence
  //  of the given char, in which case, the pointer is at that location is
  //  returned, and finally if there is no pointer at the given location,
  //  NULL is returned.
  //////////////////////////////////////////////////////////////////////////
  const char * at(int index);

  /////////////////////////////////////////////////////////////////////////
  //Name: remove(const char*str)
  //Input: a constant character array
  //Output: a pointer to the removed object
  //->This implementation is very similary to that of at.  There are two cases:
  //  if the given char* is found (using find function), then a pointer to it
  //  is returned, and the m_size member is decremented, otherwise NULL is
  //  returned.
  //  /////////////////////////////////////////////////////////////////////
  char * remove(const char *str);

  //////////////////////////////////////////////////////////////////////////
  //Name: printStats
  //Input: none
  //Ouptu: prints out several pieces of information pertaining to the Pinball
  //       object
  //->This implementation involves printing of member variables.  It also 
  //  includes the callling of a method to update the maximum hits to a 
  //  primary slot.
  //////////////////////////////////////////////////////////////////////////
  void printStats();

  //////////////////////////////////////////////////////////////////////////
  //Name: size
  //Input: none
  //Output: returns the m_size data member
  //////////////////////////////////////////////////////////////////////////
  int size() { return m_size;}


  //add public data members and public funcstion as needd
  //used to keep track of the total number of ejectiosn
  int m_totalEjections;
  //used to keep track of the number of slots that are primaries
  int m_primarySlots;
  //used to store the number of hits to each primary slot
  int * m_primarySlotsArray;
  //used to keep track of the number of ejections in single insert
  int m_maxEjectionsInSingleInsert;
  ///////////////////////////////////////////////////////////////////////////
  //Name: calculateMaxHitsToPrimarySlot
  //Input: noe
  //Ouput: an integer representing the highes value in the primarySlotsArray
  //->It simply iterates over the primarySlotsArray and finds the max value
  //////////////////////////////////////////////////////////////////////////
  int calculateMaxHitsToPrimarySlot();

  //used to choose the aux nodes to eject
  int m_savedSeed;
  //used to store the average hits to primary slots
  double m_avgHitsToPrimarySlots;
  //for debugging
  int m_didntMakeIt;


 private:
  
  char ** H;      // the actual hash table
  int m_size;     // number of items in stored H
  int m_capacity; // number of slots allocated in H

  int m_degree;   //use degree assigned
  int m_ejectLimit; //use ejection limit assigned
  int * m_seeds;
  int m_cuckooCount;

  //Made inline definition of hashCode() so everyone uses
  // the sam efunction

  unsigned int hashCode(const char * str) {
    unsigned int val = 0;
    const unsigned int thirtyThree = 33; // magick number from text book

    int i = 0;
    while (str[i] != '\0') {
      val = val * thirtyThree + str[i];
      i++;
    }
    return val;
  }

  //add private dat members and private functions here

};

#endif
