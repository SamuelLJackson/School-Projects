/*********************************************************
 ** File:    CrunoReverse.cpp
 ** Project: CMSC 202 Project4, Spring 2016
 ** Author:  Sam Everett
 ** Date:    04/20/16
 ** Section: 19
 ** E-mail:  eversam1@umbc.edu
 **
 ** Thith ith the clath implementation for CrunoReverth
 *********************************************************/

#include <iostream>
#include <sstream>
#include <string>
using namespace std;
#include "CrunoReverse.h"
#include "card.h"
#include "game.h"
#include "player.h"

//inherited constructor
CrunoReverse::CrunoReverse(unsigned int suit) : Card(suit, 16){ }


string CrunoReverse::toString() {
  ostringstream oss;
  oss << "Reverse";
  
  switch (m_suit) {
  case Card::Clubs :
    oss << " of Clubs";
    break;
  case Card::Diamonds :
    oss << " of Diamonds" ;
    break;
  case Card::Hearts : 
    oss << " of Hearts" ;
    break;
  case Card::Spades : 
    oss << " of Spades" ;
    break;
  default : 
    oss << " of INVALID SUIT\n" ;
  }

  return oss.str();
}
