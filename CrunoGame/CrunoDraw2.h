/*****************************************************
 ** File:     CrunoDraw2.h
 ** Project:  CMSC 202 Project 4, Spring 2016
 ** Author:   Sam Everett
 ** Date:     04/20/16
 ** Section:  19
 ** E-mail:   eversam1@umbc.edu
 **
 ** This is the definition of the CrunoDraw2 class
 **
 *****************************************************/

#ifndef CRUNODRAW2_H_
#define CRUNODRAW2_H_

#include <string>
using namespace std;
#include "game.h"
#include "card.h"
#include "player.h"

class CrunoDraw2 : public Card {

 public:

  static const unsigned int Draw2 = 17;
  CrunoDraw2(unsigned int suit);
  string toString();

};



#endif
