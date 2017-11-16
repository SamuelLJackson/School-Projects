/* File: card.h

   CMSC 202 Computer Science II
   Spring 2016 Project 4

   This file has the class declarations for the Card class.

*/


#ifndef _CARD_H_
#define _CARD_H_

#include <string>
using namespace std ;


// Forward class declarations
//
class Game ;
class Player ;


class Card {

public:
   // public constants for convenience
   //
   static const unsigned int Invalid = 0 ; 
   static const unsigned int Clubs = 1 ; 
   static const unsigned int Diamonds = 2 ; 
   static const unsigned int Hearts = 3 ; 
   static const unsigned int Spades = 4 ; 

   static const unsigned int Jack = 11 ; 
   static const unsigned int Queen = 12 ; 
   static const unsigned int King = 13 ; 
   static const unsigned int Ace = 14 ; 


   // Default constructor.
   //
   // We allow uninitialized Cards to be created.
   // 
   Card() ; 


   // Alternate constructor, with suit and points.
   //
   Card(unsigned int suit, unsigned int points) ;


   // Virtual destructor, just in case.
   //
   virtual ~Card() ;


   // Returns suit of the host Card.
   //
   virtual unsigned int getSuit() ;


   // Returns point value of the host Card.
   //
   virtual unsigned int getPoints() ; 


   // Returns a string description of the card, e.g.,
   //   8 of Diamonds
   //   Queen of Hearts
   //   ...
   //
   virtual string toString() ;


   // Says whether the host Card can be played
   // played in the game right now.
   // 
   virtual bool playable(Game *gptr) ;
   

   // Each player is shown to the card.
   // (After the Game class shows the card
   // to each player.)
   // 
   virtual void showPlayerToCard(Player *pptr) ;


   // Actually play this card
   // 
   virtual void playCard(Game *gptr, Player *pptr) ;


protected:

   unsigned int  m_suit ;      // suit of host Card
   unsigned int  m_points ;    // point value of host Card

} ;

#endif
