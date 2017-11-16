/**************************************
 ** File:     Cruno8.h
 ** Project:  CMSC 202 Project 4, Spring 2016
 ** Author:   Sam Everett
 ** Date:     04/20/16
 ** Section:  19
 ** E-mail:   eversam1@umbc.edu
 **
 ** This is the definition of the Cruno8 class
 **
 *************************************/

#ifndef CRUNO8_H_
#define CRUNO8_H_

#include <string>
using namespace std;
#include "card.h"
#include "game.h"
#include "player.h"
class Cruno8 : public Card {

 public:
  Cruno8();
  Cruno8(unsigned int s);
  bool playable(Game *gptr);
  void playCard(Game *gptr, Player *pptr);  
  string toString(); 
  
};
  
#endif
