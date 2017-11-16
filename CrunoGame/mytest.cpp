/********************************************************
 ** File:       mytest.cpp
 ** Project:    CMSC 202 Project4, Spring 2016
 ** Author:     Sam Everett
 ** Date:       04/20/16
 ** Section:    19
 ** E-mail:     eversam1@umbc.edu
 **
 **  This is my test file
 **
 *******************************************************/
#include <string>
#include <stdlib.h>
#include <iostream>
using namespace std;

#include "card.h"
#include "CrunoGame.h"
#include "CrunoReverse.h"
#include "CrunoSkip.h"
#include "Cruno8.h"
#include "CrunoPlayer.h"
#include "player.h"
#include "game.h"
#include "player.h"

int main() {
  Cruno8 thing(1);
  
  cout << thing.toString() << endl;
  CrunoReverse thing1(2);
   cout << thing1.toString() << endl;
   CrunoSkip thing2(2);
  cout << thing2.toString() << endl;
  CrunoDraw2 thing3(2);
  cout << thing3.toString() << endl;


  CrunoGame CG ;
  CG.initialize(4);

  int n = CG.getNumCards();
  cout << "Number of cards in this game is: " << n << endl;
  Player *cpptr1 = new CrunoPlayer(&CG,n);
  Player *cpptr2 = new CrunoPlayer(&CG,n);
  Player *cpptr3 = new CrunoPlayer(&CG,n);
  Player *cpptr4 = new CrunoPlayer(&CG,n);

  CG.addPlayer(cpptr1);
  CG.addPlayer(cpptr3);
  CG.addPlayer(cpptr2);
  CG.addPlayer(cpptr4);

  CG.startGame(344);

  CrunoGame CG2 ;
  CG2.initialize(4);

  int n2 = CG2.getNumCards();
  cout << "Number of cards in this game is: " << n << endl;
  Player *cpptr5 = new CrunoPlayer(&CG2,n2);
  Player *cpptr6 = new CrunoPlayer(&CG2,n2);
  Player *cpptr7 = new CrunoPlayer(&CG2,n2);
  Player *cpptr8 = new CrunoPlayer(&CG2,n2);
  Player *cpptr9 = new CrunoPlayer(&CG2,n2);

  CG2.addPlayer(cpptr5);
  CG2.addPlayer(cpptr6);
  CG2.addPlayer(cpptr7);
  CG2.addPlayer(cpptr8);
  CG2.addPlayer(cpptr9);

  CG2.startGame(3444);

  return 0;
}
