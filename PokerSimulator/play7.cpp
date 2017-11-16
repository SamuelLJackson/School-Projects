/* File: play7.cpp

   CMSC 202 Computer Science II
   Spring 2016 Project 2

   The main() function in this program uses
   the Card and PokerHand classes to pick 
   the best five cards to keep at the end 
   of game of Seven Card Stud.

*/

#include <iostream>
using namespace std ;

#include "pokerhand.h"

int main() {

  const int SEVEN = 7 ;

  Card h7[SEVEN] ;   // holds the seven cards dealt
  PokerHand maxH ;   // the best five card hand so far
  PokerHand thisH ;  // current five card hand being considered

  // the seven cards we have been dealt 
  //
  h7[0] = Card(Card::Spades,   12) ;
  h7[1] = Card(Card::Clubs,    11) ;
  h7[2] = Card(Card::Clubs,    12) ;
  h7[3] = Card(Card::Diamonds,  8) ;
  h7[4] = Card(Card::Diamonds, 12) ;
  h7[5] = Card(Card::Clubs,     2) ;
  h7[6] = Card(Card::Hearts,   12) ;


  // print out the origingal seven card hand
  //
  cout << "Original cards:\n" ;
  for (int k=0 ; k < SEVEN ; k++) {
    h7[k].print() ;
  }
  cout << "\n\n" ;


  // Consider all possible ways of dropping two cards
  // from the seven card hand. The variable i is the
  // first card dropped and j is the second card dropped.
  //
  for (int i=0 ; i < SEVEN ; i++) {
    for (int j=i+1 ; j < SEVEN ; j++) {

      // cout << "Dropping i=" << i << ", j=" << j << endl ;

      Card pick[PokerHand::FIVE] ;
      int t = 0 ;

      // Iterate over all seven cards and assign them
      // to the pick[] array, but not cards #i and #j.
      // 
      for (int k=0 ; k < SEVEN ; k++) {
	if (k == i || k == j) continue ;
	pick[t] = h7[k] ;
	t++ ;
      }

      /* 
         // Some debugging code to see pick[] array
         //
         cout << "t = " << t << " (should be 5)\n" ;
         for (int k=0 ; k < PokerHand::FIVE ; k++) {
            pick[k].print() ;
         }
      */
         

      // Make a PokerHand with pick[]
      //
      thisH = PokerHand(pick[0], pick[1], pick[2], pick[3], pick[4]) ;
      cout << "Current pick: " ;
      thisH.printRank() ;
      cout << endl ;
      thisH.printCards() ;
      cout << endl ;


      // Check to see if this hand is better than
      // the best we've seen so far
      //
      if (maxH.cmp(thisH) < 0) {

	maxH = thisH ;

	cout << "*** Better hand found!\n" ;
	cout << "New best hand: " ;
	thisH.printRank() ;
	cout << endl ;
	thisH.printCards() ;
	cout << endl ;
      }
    }
  }


  // What's the best hand??
  //
  cout << "*** Best five-card hand ***\n" ;
  maxH.printRank() ;
  cout << endl ;
  maxH.printCards() ;

}
