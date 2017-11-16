/* File: player.cpp

   CMSC 202 Computer Science II
   Spring 2016 Project 4

   This file has the implementation of the Player class.

*/

#include <stdlib.h>
#include <iostream>

using namespace std ;

#include "card.h"
#include "player.h"
#include "game.h"


// Create Player and allocate array to store Card pointers.
//
Player::Player(Game *gptr, unsigned int numCards) {
   m_numCards = 0 ;
   m_maxCards = numCards ;
   m_game = gptr ;

   m_cards = new Card * [m_maxCards] ;
   if (m_cards == NULL) {
      cerr << "Cannot allocate memory in Player class constructor\n" ;
      exit(1) ;
   }
}


// Free up allocated space.
//
Player::~Player() {
   for (unsigned int i=0 ; i < m_numCards ; i++) {
      delete m_cards[i] ;
   }
   delete [] m_cards ;
} 


// Add given card to our hand
//
void Player::takeCard(Card *cptr) {
   m_cards[m_numCards] = cptr ;
   m_numCards++ ;

   // sanity check
   //
   if (m_numCards == m_maxCards) {
      cerr << "Something is wrong in Player::takeCard !!!\n" ;
      exit(1) ;
   }
}


// Main game playing strategy goes here. However, this implementation
// just plays the first playable card.
//
Card *Player::playOneCard(bool &lastCard, bool &oneCardLeft) {

   unsigned int c ;
   Card *cptr, *temp ;

   // find first card that is playable
   
   c = 0 ;        // index into array of Card pointers
   cptr = NULL ;  // haven't found a playable card yet

   while( 1 ) {
      if (c >= m_numCards) break ;   // hit end of array
      
      if (m_cards[c]->playable(m_game)) { // found playable card

         cptr = m_cards[c] ;  // remember the card

         // To remove the card we will play from the hand,
         // we replace it with the last card in the array.
         // This changes the order of the cards, but 
         // order doesn't matter here.

         m_numCards-- ;                       // one less card
         m_cards[c] = m_cards[m_numCards] ;   // replace with last card
         m_cards[m_numCards] = NULL ;         // just to be safe

         if (m_numCards == 1) oneCardLeft = true ;  // say "Uno"?
         if (m_numCards == 0) lastCard = true ;     // did we win?
         break ;
      }

      c++ ;    // no pun intended
   }

   return cptr ; 
   
}


// We are told what other players played.
// This implementation ignores the information.
// 
void Player::showCardToPlayer(const Card *cptr, unsigned int player, bool oneCardLeft ) {

   // "dumb" player ignores this info

   return ;
}


// This is really dumb behavior. A smarter player will pick a suit 
// based on his/her hand (e.g., pick the most common suit).
// Override to implement different behavior.
//
unsigned int Player::pickSuit() {
   return Card::Clubs ;
}


// Compute penalty for having cards in hand when the game ends.
// In this implementation, 10 J Q K A cost 10 points.
// Other cards are penalized at their regular values.
// Override to implement different behavior.
//
int Player::gameOverPenalty() {
   int sum = 0 ;

   for (unsigned int c=0 ; c < m_numCards ; c++) {
      if (m_cards[c]->getPoints() < 10) {
         sum += m_cards[c]->getPoints() ;
      } else {
         sum += 10 ;
      }
   }

   return sum ;
}


// Print out the cards in hand for debugging & tracing.
//
void Player::dump() {
   for (unsigned int c=0 ; c < m_numCards ; c++) {
      cout << "   " << m_cards[c]->toString() << endl ;
   }
}


