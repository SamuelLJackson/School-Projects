/**********************************************************
 ** File:      CrunoPlayer.h
 ** Project:   CMSC 202 Project 4, Spring 2016
 ** Author:    Sam Everett
 ** Date:      04/20/16
 ** Section:   19
 ** E-mail:    eversam1@umbc.edu
 **
 ** This is the definition of the CrunoPlayer class
 **
 **********************************************************/

#ifndef CRUNOPLAYER_H_
#define CRUNOPLAYER_H_

#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;
#include "card.h"
#include "game.h"
#include "player.h"

class CrunoPlayer : public Player {

public:
  CrunoPlayer(Game  *gptr, unsigned int numCards);
  unsigned int pickSuit();
  Card *playOneCard(bool &lastCard, bool &oneCardLeft);
  int maxSuit();
  void actuallyPlaysCard(unsigned int c, Card * cptr);
};

#endif
