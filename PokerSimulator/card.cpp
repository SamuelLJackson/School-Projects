/*******************************************
File:    card.cpp
Project: CMSC 202 Project 2, Spring 2016
Author:  Sam Everett
Date:    03/10/16
Section: 22
E-mail:  eversam1@umbc.edu

this file contains all methods for card class

********************************************/


#include <iostream>
#include <string>
#include "card.h"

using namespace std;

Card::Card() {

  m_suit = Invalid;
  m_points = 0;

}

Card::Card(cSuit s, cPoints p) {
  if (p > 14 || p < 2) {
    m_suit = Invalid;
    m_points = 0;
  } else {
    
    m_suit = s;
    m_points = p;
  }
  
}

Card::cPoints Card::points() {

  return m_points;

}

Card::cSuit Card::suit() {

  return m_suit;

}

void Card::print() {
  //name and suit of card to print
  string cardName;
  string suitName;
  switch(m_points) {
  case 11: cardName = "Jack ";
    break;
  case 12: cardName = "Queen";
    break;
  case 13: cardName = "King ";
    break;
  case 14: cardName = "Ace  ";
    break;
  } 

  switch (m_suit) {
  case 0: suitName = "Invalid";
    break;
  case 1: suitName = "Clubs";
    break;
  case 2: suitName = "Diamonds";
    break;
  case 3: suitName = "Hearts";
    break;
  case 4: suitName = "Spades";
    break;
  }
  if (cardName == "") {
    cout << m_points << "     of " << suitName << endl;
  } else {
    cout << cardName << " of " << suitName << endl;
  }
      


}

