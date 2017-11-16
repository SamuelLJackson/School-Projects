/**************************************************\
 ** File:     CrunoDraw2.cpp
 ** Project:  CMSC 202 Project 4, Spring 2016
 ** Author:   Sam Everett
 ** Date:     04/20/16
 ** Section:  19
 ** E-mail:   eversam1@umbc.edu
 **
 ** This is the implementation for the CrunoDraw2 class
 **
 ******************************************************/

#include <string>
#include <sstream>
using namespace std;
#include "game.h"
#include "card.h"
#include "player.h"
#include "CrunoDraw2.h"

CrunoDraw2::CrunoDraw2(unsigned int suit) : Card(suit, 17){}


//function to output a string version of the constructed card
string CrunoDraw2::toString() {
  ostringstream oss;
  oss << "Draw2";

  // set the suit that will print out
  switch (m_suit) {
  case Card::Clubs : 
    oss << " of Clubs";
    break;
  case Card::Diamonds :
    oss << " of Diamonds";
    break;
  case Card::Hearts :
    oss << " of Hearts";
    break;
  case Card::Spades :
    oss << " of Spades";
    break;
  default :
    oss << " of INVALID SUIT\n" ;
  }

  //set the string stream object to a string
  return oss.str();

}
