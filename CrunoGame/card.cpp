/* File: card.cpp

   CMSC 202 Computer Science II
   Spring 2016 Project 4

   This file has the implemenation of the Card class.

*/

#include <iostream>
#include <sstream>
#include <string>

using namespace std ;

#include "card.h"
#include "player.h"
#include "game.h"


// default constructor
//
Card::Card() {
   m_suit = Invalid ;
   m_points = 0 ;
}


Card::Card(unsigned int s, unsigned int p) {

   if (s > Spades) {   // sanity check
      s = Invalid ;
   }
   m_suit = s ;

   if (p > Ace || p == 1) {   // sanity check
      p = 0 ;
   }
   m_points = p ;
}


Card::~Card() {
   // no dynamically allocated parts
}


unsigned int Card::getPoints() {
   return m_points ;
}


unsigned int Card::getSuit() {
   return m_suit ;
}


string Card::toString() {

   ostringstream oss ;

   switch ( m_points ) {
      case 2 : case 3 : case 4 : 
      case 5 : case 6 : case 7 : 
      case 8 : case 9 : case 10 : 
         oss << m_points ;
         break ;
      case Jack:
         oss << "Jack" ;
         break ; 
      case Queen:
         oss << "Queen" ;
         break ;
      case King:
         oss << "King" ;
         break ;
      case Ace:
         oss << "Ace" ;
         break ;
      default :
         oss << "INVALID" ;
   }

   switch ( m_suit ) {
      case Clubs :
         oss << " of Clubs" ;
         break ;
      case Diamonds :
         oss << " of Diamonds" ;
         break ;
      case Hearts :
         oss << " of Hearts" ;
         break ;
      case Spades :
         oss << " of Spades" ;
         break ;
      default :
         oss << "of INVALID SUIT\n" ;
   }

   return oss.str() ;
}


// Can we play this card right now?
// Override for action cards!
//
bool Card::playable(Game *gptr) {

   if ( m_suit == gptr->currentSuit() )  // matches suit?
      return true ;

   if ( m_points == gptr->currentPoints() )  // matches point value?
      return true ;

   return false ;
}


// Normal cards don't do anything to the players.
// Action cards can make the player do something
// (e.g., draw cards).
//
void Card::showPlayerToCard(Player *pptr) {
   return ;
}


// Not much to do for normal cards. Just set the
// suit and point values.
// Action cards can override to do more.
// Note: pptr points to the player who played this card.
//
void Card::playCard(Game *gptr, Player *pptr) {
   gptr->setSuit(m_suit) ;
   gptr->setPoints(m_points) ;
   return ;
}
