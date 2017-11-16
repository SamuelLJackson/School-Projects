/* File: game.h

   CMSC 202 Computer Science II
   Spring 2014 Project 4

   This file has the class declarations for the Game class.

*/


#ifndef _Game_H_
#define _Game_H_

class Card ;
class Player ;

class Game {

public:

   Game() ;
   virtual ~Game() ;


   // Check number of players & add cards to the game
   //
   virtual void initialize(int numPlayers) ;


   // Returns number of total cards used in the game.
   // Only makes sense after initialize() 
   //
   virtual unsigned int getNumCards() ;


   // Add another player to the game.
   // After adding player, Game class is responsible for 
   // deallocatiing memory used by the player.
   // If more players added than indicated in call to initiliaze(),
   // program will terminate
   //
   virtual void addPlayer(Player *pptr) ;


   // Shuffle cards, deal to players and call playGame()
   //
   virtual void startGame(unsigned int seed) ;


   // Removes next Card from the stock and returns a pointer
   // to that Card. If stock is empty, returns NULL.
   // Recipient of the pointer is responsible for deallocating
   // memory used by the Card.
   // 
   virtual Card * dealOneCard() ;


   // Returns the current suit in the game.
   // This is the suit that determines if a Card is playable.
   //
   virtual unsigned int currentSuit() ;


   // Returns the current points in the game.
   // This is the point value that determines if a Card is playable.
   //
   virtual unsigned int currentPoints() ;


   // Changes the current suit used for matching.
   // 
   virtual void setSuit(unsigned int suit) ;


   // Changes the current point value used for matching.
   //
   virtual void setPoints(unsigned int points) ;

   // Returns number of players in the game.
   //
   virtual unsigned int numPlayers() ;


   // Returns index of current player (not pointer).
   //
   virtual unsigned int currentPlayer() ;


   // Changes current player to be the next player to have 
   // a turn. Not trivial if Skip and Reverse action cards
   // are used in the game.
   //
   virtual unsigned int nextPlayer() ;


   // Given the current direction of play, the player that would
   // have the turn after thisPlayer's turn. The playGame() function
   // uses playerAfter() to step through the players.
   //
   virtual unsigned int playerAfter(unsigned int thisPlayer) ;


protected:

   // current suit & points, used to determine if cards playable
   //
   unsigned int m_suit ;       
   unsigned int m_points ;


   // index of current player
   //
   unsigned int m_currentPlayer ;


   // m_players is a dynamically allocated array of pointers to Players.
   // The number of slots allocated is m_maxPlayers.
   // The number of active players is m_numPlayers.
   // We need m_numPlayers <= m_maxPlayers, but they not have to be equal
   //
   Player **m_players ;
   unsigned int m_numPlayers ;
   unsigned int m_maxPlayers ;


   // Index of winner of the game.
   //
   unsigned int m_winner ;
   

   // maximum number of cards in the game.
   //
   unsigned int m_maxCards ;


   // m_stock is a dynamically allocated array of pointers to Cards.
   // The number of slots allocated is m_maxCards.
   // The number of cards currently in the stock pile is m_numStock
   //
   Card **m_stock ; 
   unsigned int m_numStock ;


   // Similar m_stock, m_discard is the dynamically allocated
   // array of pointers to cards for the discard pile.
   // The number of slots allocated is m_maxCards.
   // The number of cards currently in the stock pile is m_numDiscard
   //
   Card **m_discard ;
   unsigned int m_numDiscard ;


   // Booleans to record if the game has started and
   // if the game is over.
   //
   bool m_started ;
   bool m_over ;


   // dealCards() is the initial deal to players.
   //
   virtual void dealCards() ;


   // The main loop for playing the game.
   //
   virtual void playGame() ;


   // Determines the winner of the game after the game is over.
   //
   virtual void gameOver() ;

} ;

#endif
