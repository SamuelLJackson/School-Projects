/********************************************************
 ** File:     CrunoReverse.h
 ** Project:  CMSC 202 Project 4, Spring 2016
 ** Author:   Sam Everett
 ** Date:     04/20/16
 ** Section:  19
 ** E-mail:   eversam1@umbc.edu
 **
 ** this ith the clath definition for cruno reverth
 **********************************************************/

#ifndef CRUNOREVERSE_H_
#define CRUNOREVERSE_H_

using namespace std;
#include "card.h"
#include "game.h"
#include "player.h"
class CrunoReverse : public Card { 

 public:
  CrunoReverse(unsigned int suit);
  string toString();
  static const unsigned int Reverse = 16;
  
};

#endif
