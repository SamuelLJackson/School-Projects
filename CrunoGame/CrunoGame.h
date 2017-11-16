/*********************************************************************
 ** File:     CrunoGame.h
 ** Project:  CMSC 202 Project 4, Spring 2016
 ** Author:   Sam Everett
 ** Date:     04/20/16
 ** Section:  19
 ** E-mail:   eversam1@umbc.edu
 **
 ** This is the definition of the CrunoPlayer class
 **
 *********************************************************************/


#ifndef CRUNOGAME_H_
#define CRUNOGAME_H_

#include <string>
using namespace std;

#include "card.h"
#include "game.h"
#include "player.h"
#include "Cruno8.h"
#include "CrunoReverse.h"
#include "CrunoSkip.h"
#include "CrunoDraw2.h"
#include "CrunoPlayer.h"

class CrunoGame : public Game {

 public: 
  void initialize(int numPlayers);
  unsigned int nextPlayer();
  Card * dealOneCard();
  //  void drawTwoCards();
 private:
  bool m_reverseMode;
};

#endif
