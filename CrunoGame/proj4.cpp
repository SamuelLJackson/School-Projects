/* File: proj4.cpp

   CMSC 202 Computer Science II
   Spring 2016 Project 4

   Sample main program.

*/

#include <iostream>
using namespace std ;

#include "card.h"
#include "game.h"
#include "player.h"

int main() {

   Game G ;

   G.initialize(4) ;  // say we'll have four players

   // Make the 4 players and add them
   // We could add any object derived from Player.
   // So, we can have a mix of smart, dumb or cheating
   // players in the same game.
   //
   int n = G.getNumCards() ;
   Player *pptr1 = new Player(&G,n) ;
   Player *pptr2 = new Player(&G,n) ;
   Player *pptr3 = new Player(&G,n) ;
   Player *pptr4 = new Player(&G,n) ;

   G.addPlayer(pptr1) ;
   G.addPlayer(pptr2) ;
   G.addPlayer(pptr3) ;
   G.addPlayer(pptr4) ;

   // Play game with different random seeds.
   // The random seeds control the initial shuffle.

   G.startGame(3810743) ;
//   G.startGame(8132987) ;
//   G.startGame(7831035) ;
//   G.startGame(2310831) ;

   return 0 ;
}
