/*******************************************************
 ** File:      CrunoSkip.cpp
 ** Project:   CMSC 202 Project 4, Spring 2016
 ** Author:    Sam Everett
 ** Date:      04/20/16
 ** Section:   19
 ** E-mail:    eversam1@umbc.edu
 **
 ** This is the implementation of the CrunoSkip class
 *******************************************************/

#include <iostream>
#include <sstream>
#include <string>
using namespace std;
#include "card.h"
#include "CrunoSkip.h"
#include "game.h"
#include "player.h"

CrunoSkip::CrunoSkip(unsigned int suit) : Card(suit, 15){ }


string CrunoSkip::toString() {
  ostringstream oss;
  oss << "Skip";
  switch (m_suit) {
  case Clubs :
    oss << " of Clubs";
    break;
  case Diamonds :
    oss << " of Diamonds" ;
    break;
  case Hearts : 
    oss << " of Hearts" ;
    break;
  case Spades : 
    oss << " of Spades" ;
    break;
  default : 
    oss << " of INVALID SUIT\n" ;
  }

  return oss.str();
}
