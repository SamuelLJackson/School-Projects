/***********************************************************************
 ** file:    Cruno8.cpp
 ** Project: CMSC 202 Project 4, Spring 2016
 ** Author:  Sam Everett
 ** Date:    04/20/16
 ** Section: 19
 ** E-mail:  eversam1@umbc.edu
 **
 ** This is the implementation of the Cruno8 class
 **
 *****************************************************************/

#include <string>
#include <iostream>
using namespace std;
#include "card.h"
#include "Cruno8.h"
#include "player.h"
#include "game.h"

Cruno8::Cruno8() {
  m_points = 8;
}

//inherited constructor
Cruno8::Cruno8(unsigned int s) : Card(s, 8){ }

bool Cruno8::playable(Game *gptr) {
  //wild cards are always playable
  return true;
}

//Even though this card has a suit value, it is irrelevent
// information, therefore it will not be printed
string Cruno8::toString() {
  return "Crazy Eight";
}

void Cruno8::playCard(Game *gptr, Player *pptr) {
  //set suit using the pickSuit function
  gptr->setSuit(pptr->pickSuit());
  gptr->setPoints(m_points);

}
