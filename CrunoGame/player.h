/* File: player.h

   CMSC 202 Computer Science II
   Spring 2016 Project 4

   This file has the class declarations for the Player class.

*/


#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "card.h"
#include "game.h"

class Player {

public:

   // Make a player. Worst case scenario, the player has all
   // of the cards. So, need to know numCards to allocate 
   // enough space.
   //
   Player(Game *gptr, unsigned int numCards) ;
   

   // deallocate memory!
   //
   virtual ~Player() ;


   // add card to our hand. Use this when dealing
   // cards to players or when players have to draw
   // cards.
   //
   virtual void takeCard(Card *cptr) ;


   // main game playing strategy goes here.
   // Which card should we play? return NULL if we want to draw a card.
   // Basic implementation just plays the first playable card and uses
   // no strategy beyond that.  Override to implement different behavior.
   //
   virtual Card *playOneCard(bool &lastCard, bool &oneCardLeft) ;


   // Each time a card is played, the Game::playGame() shows the card to
   // each player. It also says which player played the card and whether
   // it is the penultimate card (Uno!) or the last card.
   // Basic implementation ignores this information, but potentially a
   // player could record this information and use it in game playing
   // strategy. Override to implement different behavior.
   //
   virtual void showCardToPlayer(const Card *cptr, unsigned int player, bool oneCardLeft ) ;


   // Player may be asked to pick a suit (e.g., after playing an 8 in Crazy Eights).
   //
   virtual unsigned int pickSuit() ;


   // Tally up the cards in hand after someone wins.
   // Different games have different rules for how to compute
   // the penalty. Override to implement different behavior
   //
   virtual int gameOverPenalty() ;


   // Print out current hand
   //
   virtual void dump() ;

protected:
   Card **m_cards ;       // dynamically allocated array of pointers to Card
   int m_numCards ;       // number of cards left
   int m_maxCards ;       // total # of cards in the game
   Game *m_game ;         // link into the game

} ;

#endif
