/**********************************************************
 ** File:      CrunoPlayer.cpp
 ** Project:   CMSC 202 Project 4, Spring 2016
 ** Author:    Sam Everett
 ** Date:      04/20/16
 ** Section:   19
 ** E-mail:    eversam1@umbc.edu
 **
 ** This is the implementation of the CrunoPlayer class
 **
 **********************************************************/


#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;
#include "card.h"
#include "game.h"
#include "player.h"
#include "CrunoGame.h"
#include "CrunoPlayer.h"

CrunoPlayer::CrunoPlayer(Game *gptr, unsigned int numCards) 
  : Player(gptr, numCards) {}

// pick suit based on most numerous suit
unsigned int CrunoPlayer::pickSuit() {

  //initialize counters for number of each suit in hand
  vector <unsigned int> suitCounters(4);


  //loop through hand to update counters
  for (int i = 0; i < m_numCards; i++) {
    switch (m_cards[i]->getSuit()) {
    case Card::Clubs:
      suitCounters.at(0)++;
      break;
    case Card::Diamonds:
      suitCounters.at(1)++;
      break;
    case Card::Hearts:
      suitCounters.at(2)++;
      break;
    case Card::Spades:
      suitCounters.at(3)++;
      break;
    default:
      break;
    }
  }
  
  //find most numerous suit
  int maxSuit = 0;
  for (unsigned int i = 1; i < 4; i++) {
    if (suitCounters.at(i) > suitCounters.at(maxSuit)) {
      maxSuit = i;
    }
  }

  return maxSuit;

}


// strategy for playing card
Card *CrunoPlayer::playOneCard(bool &lastCard, bool &oneCardLeft) {
  
  srand(33);
  unsigned int randomNum;
  
  //initialize
  unsigned int c;
  Card *cptr;

  c = 0;
  cptr = NULL;
  //This loop preferentially plays the suit present in the 
  //highest quantity
  while( 1 ) { 
    if (c >= m_numCards) break;

    if (m_cards[c]->playable(m_game) && m_cards[c]->getSuit() == pickSuit()) {
      cptr = m_cards[c];
      m_numCards--;
      m_cards[c] = m_cards[m_numCards];
      m_cards[m_numCards] = NULL;
      if (m_numCards == 1) oneCardLeft = true;
      if (m_numCards == 0) lastCard = true;
      break; 
    } 
    c++;
  }

  //this loop is the default loop
  c = 0;
  while(1) {
    if (c >= m_numCards) break;
    if (m_cards[c]->playable(m_game)) {
      cptr = m_cards[c];
      m_numCards--;
      m_cards[c] = m_cards[m_numCards];
      m_cards[m_numCards] = NULL;
      if (m_numCards == 1) oneCardLeft = true;
      if (m_numCards == 0) lastCard = true;
      break;
    }
    c++;
  }

  return cptr;
}

