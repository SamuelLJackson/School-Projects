/******************************************
 ** File:     CrunoSkip.h
 ** Project:  CMSC 202 Project 4, Spring 2016
 ** Author:   Sam Everett
 ** Date:     04/20/16
 ** Section:  19
 ** E-mail:   eversam1@umbc.edu
 **
 ** This is the definition of the CrunoSkip class
 **
 *************************************************/

#ifndef CRUNOSKIP_H_
#define CRUNOSKIP_H_

#include <string>
using namespace std;
#include "card.h"
#include "game.h"
#include "player.h"
class CrunoSkip : public Card { 

 public:
  CrunoSkip(unsigned int suit);
  string toString();
  static const unsigned int Skip = 15;

};  

#endif
