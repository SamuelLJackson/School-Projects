/* File: play5.cpp

   CMSC 202 Computer Science II
   Spring 2016 Project 2

   The main() function in this program uses
   the Card and PokerHand classes to 
   to determine the rank of a poker hand.

*/

#include <iostream>
using namespace std ;

#include "pokerhand.h"

int main() {

  // Pick 5 cards
  //
  Card c0(Card::Spades,   12) ;
  Card c1(Card::Clubs,     4) ;
  Card c2(Card::Clubs,    12) ;
  Card c3(Card::Diamonds,  4) ;
  Card c4(Card::Hearts,   12) ;

  PokerHand myHand(c0, c1, c2, c3, c4) ;

  if ( myHand.isRoyalFlush() ) {
    cout << "Yes!! I have a Royal Flush\n" ;
  } else {
    cout << "My hand is a " ;
    myHand.printRank() ; 
    cout << endl ;
  }

  // Pick 5 more cards
  //
  Card d0(Card::Spades,    12) ;
  Card d1(Card::Spades,    14) ;
  Card d2(Card::Spades,     8) ;
  Card d3(Card::Spades,     4) ;
  Card d4(Card::Spades,     7) ;

  PokerHand yourHand(d0, d1, d2, d3, d4) ;

  cout << "Your hand is a " ;
  yourHand.printRank() ; 
  cout << endl ;

  if (myHand.cmp(yourHand) > 0) {
    cout << "My hand beats yours.\n" ;
  } else if (myHand.cmp(yourHand) < 0) {
    cout << "Your hand beats mine.\n" ;
  } else {
    cout << "Our hands are tied.\n" ;
  }

  cout << "\nMy hand is:\n" ;
  myHand.printCards() ;
  cout << "\nYour hand is:\n" ;
  yourHand.printCards() ;
}
