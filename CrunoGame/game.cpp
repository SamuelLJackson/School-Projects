
/* File: game.h

   CMSC 202 Computer Science II
   Spring 2016 Project 4

   This file has the implemenation of the Game class.

*/


#include <stdlib.h>
#include <iostream>
using namespace std ;

#include "card.h"
#include "player.h"
#include "game.h"


// A little helper function to quit the program if
// memory is not allocated. Here "static" means only
// code in this file can see this function.
//
static void ifNullCrash(void *ptr) {
   if (ptr == NULL) {
      cerr << "Could not allocate memory\n" ;
      exit(1) ;
   }
   return ;
}


// The default constructor doesn't do very much.
//
Game::Game() {
   m_suit = 0 ;
   m_points = 0 ;
   m_currentPlayer = 0 ;
   m_players = NULL ;
   m_numPlayers = 0 ;
   m_maxPlayers = 0 ;
   m_winner = 0 ;
   m_maxCards = 0 ;
   m_stock = NULL ;
   m_numStock = 0 ;
   m_discard = NULL ;
   m_numDiscard = 0 ;
   m_started = false ;
   m_over = false ;
}


// Deallocate all the space.
//
Game::~Game() {

   // de-allocate array of players
   //
   for (int i=0 ; i < m_numPlayers ; i++) {
      delete m_players[i] ;
   }
   delete [] m_players ;


   // de-allocate array of stock cards
   //
   for (int i=0 ; i < m_numStock ; i++) {
      delete m_stock[i] ;
   }
   delete [] m_stock ;


   // de-allocate array of discards
   //
   for (int i=0 ; i < m_numDiscard ; i++) {
      delete m_discard[i] ;
   }
   delete [] m_discard ;
}



// Initialize the game based on the number of players.
//
void Game::initialize(int numPlayers) {
   m_suit = 0 ;
   m_points = 0 ;
   m_currentPlayer = 0 ;

   // can't play by yourself
   //
   if (numPlayers < 2) {
      cerr << "Insufficient players\n" ;
      exit(1) ;
   }

   // not enough cards to make it fun for >10.
   //
   if (numPlayers > 10) {
      cerr << "Too many players\n" ;
      exit(1) ;
   }

   m_numPlayers = 0 ;  // no players added yet.

   // allocate space for max requested
   //
   m_maxPlayers = numPlayers ;
   m_players = new Player*[numPlayers] ;
   ifNullCrash(m_players) ;

   m_winner = m_maxPlayers + 1 ;  // not a real player

   // usually use just one deck
   int decks = 1 ;
   m_maxCards = 52 ;   // 52 cards in one deck

   if (numPlayers > 5) {
      // use two decks
      decks = 2 ;
      m_maxCards = 104 ;   // 104 cards in two decks
   }


   // allocate space for the discard pile
   m_discard = new Card*[m_maxCards] ;
   ifNullCrash(m_discard) ;
   m_numDiscard = 0 ;  // nothing discarded yet

   // allocate space for the stock pile
   m_stock = new Card*[m_maxCards] ;
   ifNullCrash(m_stock) ;


   int i = 0 ;  // next available slot in m_stock[]

   for (int d = 0 ; d < decks ; d++) {  // # of decks
      
      // iterate over suits
      for (unsigned int s = Card::Clubs ; s <= Card::Spades ; s++) {

         // iterate over point values 
         for (unsigned int p = 2 ; p <= Card::Ace ; p++) {

            m_stock[i] = new Card(s,p) ;  // insert new card
            ifNullCrash(m_stock[i]) ;
            i++ ;

         }
      }
   }

   // remember how many cards we added
   m_numStock = m_maxCards ;

   // Still haven't started (need to have players added)
   m_started = false ;
   m_over = false ;
}


// simple accessor function
//
unsigned int Game::getNumCards() {
   return m_maxCards ;
}


// Add player. Note that Player can be polymorphic 
// (has virtual functions). So, players in the
// m_players[] array may behave differently.
//
void Game::addPlayer(Player *pptr) {

   // sanity check
   //
   if (m_numPlayers == m_maxPlayers) {
      cerr << "Too many players added!\n" ;
      return ;
   }

   m_players[m_numPlayers] = pptr ;
   m_numPlayers++ ;
   return ;
}


// startGame() should be called after players have
// been added to the game.
//
void Game::startGame(unsigned int seed) {

   int j ;

   // shuffle cards
   //
   cout << "Random seed = " << seed << endl ;
   srand(seed) ;
   for(unsigned int i = 0 ; i < m_numStock ; i++) {
      Card *temp ;

      j = rand() % m_numStock ;
      temp = m_stock[i] ;
      m_stock[i] = m_stock[j] ;
      m_stock[j] = temp ;
   }
   
   // give players cards
   //
   dealCards() ;


   // Sanity check. Did we run out?
   //
   if (m_numStock < 1) {
      cerr << "Missing cards!\n" ;
      exit(1) ;
   }


   // turn over one card in the stock pile
   // and make it the top of the discard pile
   //
   m_numStock-- ;
   m_discard[0] = m_stock[m_numStock] ;
   m_stock[m_numStock] = NULL ;
   m_numDiscard = 1 ;
   setSuit( m_discard[0]->getSuit() ) ;
   setPoints( m_discard[0]->getPoints() ) ;

   cout << "First card: " << m_discard[0]->toString() << endl ;

   m_started = true ;
   playGame() ;  // main game loop

   gameOver() ;  // who won?

}


// Give players 5 cards each. 
// Override for different behavior.
//
void Game::dealCards() {
   
   for(int i=0 ; i < 5 ; i++) {
      for (int p=0 ; p < m_numPlayers ; p++) {

         if (m_numStock < 1) {
            cerr << "Ran out of cards while dealing!\n" ;
            exit(1) ;
         }

         m_numStock-- ;
         m_players[p]->takeCard(m_stock[m_numStock]) ;
         m_stock[m_numStock] = NULL ;
      }
   }
}


// Main game loop
//
void Game::playGame() {

   bool lastCard, oneCardLeft ;
   unsigned int p, q ;
   Card *cptr ;


   // Each iteration of this while loop is 
   // a player taking a turn
   //
   while (not m_over) {

      lastCard = false ;
      oneCardLeft = false ;

      // debugging output so we can see
      //
      cout << endl ;
      for (unsigned int i=0 ; i < m_numPlayers ; i++) {
         cout << "----------------------------\n" ;
         cout << "Player " << i << " has:\n" ;
         m_players[i]->dump() ;
      }
      cout << "----------------------------\n\n" ;


      p = currentPlayer() ;  // virtual

      cptr = m_players[p]->playOneCard(lastCard, oneCardLeft) ;

      // keep drawing cards until a card is played.
      // Note: a player can choose not to play a card that is playable.
      // After drawing a card, the player can play any card in his/her
      // hand. This is not necessarily the card that was just drawn.
      //
      while (cptr == NULL) {
         cptr = dealOneCard() ;
         if (cptr == NULL) break ;
         cout << "Player " << p << " draws a card: " << cptr->toString() << endl ;
         m_players[p]->takeCard(cptr) ;
         cptr = m_players[p]->playOneCard(lastCard, oneCardLeft) ;
      }


      // if a card was actually played...
      //
      if (cptr != NULL) {

         cout << "Player " << p << " plays " << cptr->toString() << endl ;

         // Show each player what was played. (They can ignore the info.)
         // Also allow the card to interact with each player
         //
         q = playerAfter(p) ;  // virtual
         while (q != p) {
            m_players[q]->showCardToPlayer(cptr, p, oneCardLeft) ;
            cptr->showPlayerToCard(m_players[q]) ;
            q = playerAfter(q) ;  // virtual
         }


         // Now let the card do what it needs to do with the game.
         // (E.g. set the suit and points for others to follow.)
         //
         cptr->playCard(this, m_players[p]) ;


         // Card played goes into the discard pile.
         //
         m_discard[m_numDiscard] = cptr ;
         m_numDiscard++ ;
      } 


      // Say "Uno!"
      //
      if (oneCardLeft) {
         cout << "Player " << p << " has one card left!\n" ;
      }

      // Player went out?
      //
      if (lastCard) {
         cout << "Player " << p << " wins!\n" ;
         m_winner = p ;
         m_over = true ;
      } else {
         nextPlayer() ;  // virtual
      }   
   }

   return ;
}


// Handles the end of the game
//
void Game::gameOver() {
   int lowestPenalty, penalty ;

   // If no one went out with an empty hand, winner is one with
   // the least penalty.
   //
   if (m_winner >= m_numPlayers) {
      cout << "\n\n========== GAME OVER =================\n" ;
      cout << "Nobody has an empty hand\n\n" ;

      // Figure out the value of the lowest penalty
      // Note: gameOverPenalty() is virtual
      //
      lowestPenalty = m_players[0]->gameOverPenalty() ;
      cout << "Player 0 penalty = " << lowestPenalty << endl ;

      for (unsigned int p=1 ; p < m_numPlayers ; p++) {
         penalty = m_players[p]->gameOverPenalty() ;
         cout << "Player " << p << " penalty = " << penalty << endl ;
         if (penalty < lowestPenalty) {
            lowestPenalty = penalty ;
         }
      }

      cout << "\nLowest penalty = " << lowestPenalty << endl ;

      // List all players that have the lowest penalty.
      //
      for (unsigned int p=0 ; p < m_numPlayers ; p++) {
         penalty = m_players[p]->gameOverPenalty() ;
         if (penalty == lowestPenalty) {
            cout << "Player " << p << " is a winner.\n" ;
         }
      }
   }
}


Card *Game::dealOneCard() {
   Card *cptr ;

   // Sanity check
   //
   if (m_numStock < 1) {
      m_over = true ;
      return NULL ;
   }

   // Gimme!
   //
   m_numStock-- ;
   cptr = m_stock[m_numStock] ;
   m_stock[m_numStock] = NULL ;

   return cptr ;
}


unsigned int Game::currentSuit() {
   return m_suit ;
}


unsigned int Game::currentPoints() {
   return m_points ;
}


void Game::setSuit(unsigned int suit) {
   m_suit = suit ;
   return ;
}


void Game::setPoints(unsigned int points) {
   m_points = points ;
   return ;
}


unsigned int Game::numPlayers() {
   return m_numPlayers ;
}


unsigned int Game::currentPlayer() {
   return m_currentPlayer ;
}


// use % m_numPlayers to wrap around.
//
unsigned int Game::nextPlayer() {
   m_currentPlayer = (m_currentPlayer + 1) % m_numPlayers ;
   return m_currentPlayer ;
}


// use % m_numPlayers to wrap around.
//
unsigned int Game::playerAfter(unsigned int thisPlayer) {
   return (thisPlayer + 1) % m_numPlayers ;
}


