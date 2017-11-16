/********************************************

File:     pokerhand.cpp
Project:  CMSC 202 Project 2, Spring 2016
Author:   Sam Everett
Date:     03/10/16
Section:  22
E-mail:   eversam1@umbc.edu

this file contains the driver of the program for project 2
defines all useful functions in "playing" poker game

*********************************************/


#include <iostream>
#include "pokerhand.h"
#include <string>
using namespace std;

PokerHand::PokerHand () {
  m_valid = false;
  m_rank = NoRank;

  m_lastCardPoints = 0;
  m_firstPairPoints = 0;
  m_secondPairPoints = 0;
  m_tripletPoints = 0;
  m_quadrupletPoints =0;
}

void PokerHand::sort() {

  // bubble sort
  for (int i = 0; i < FIVE; i++) {
    for (int j = 0; j < FIVE - 1; j++) {
      Card tempMin;
      if (m_cards[j+1].points() < m_cards[j].points()) {
	tempMin = m_cards[j+1];
	m_cards[j+1] = m_cards[j];
	m_cards[j] = tempMin;
      }
    }
  }
}

PokerHand::pRank PokerHand::getRank() {
  return m_rank;
}

// check what rank the hand is and return it
void PokerHand::printRank() {
  string rankName;
  switch(m_rank) {
  case 0: rankName = "NoRank";
    break;
  case 1: rankName = "HighCard";
    break;
  case 2: rankName = "OnePair";
    break;
  case 3: rankName = "TwoPair";
    break;
  case 4: rankName = "ThreeOfAKind";
    break;
  case 5: rankName = "Straight";
    break;
  case 6: rankName = "Flush";
    break;
  case 7: rankName = "FullHouse";
    break;
  case 8: rankName = "FourOfAKind";
    break;
  case 9: rankName = "StraightFlush";
    break;
  case 10: rankName = "RoyalFlush";
    break;
  }
    cout << rankName << endl;
}

void PokerHand::printCards() {
  // for loop to print cardz
  for (int i = 0; i < FIVE; i++) {
    m_cards[i].print();
  }
}


bool PokerHand::isOnePair() {
  //eliminate overlapping possibilities
  if (isTwoPair() || isFullHouse() || isFourOfAKind()) {
    return false;
  }

  // if there are any two cards with same point value, return true and
  // update firstPairPoints value
  for (int i = 0; i < FIVE -1; i++ ) {
    if (m_cards[i].points() == m_cards[i+1].points()) {
   
      m_firstPairPoints = m_cards[i].points();
      m_rank = PokerHand::OnePair;
      return true;
    }
  }
  return false;
}

bool PokerHand::isHighCard() {
  // if this hand is nothing else, it is high card
  if (isTwoPair() || isFullHouse() || isFourOfAKind() || isFlush() || isRoyalFlush() || isThreeOfAKind() || isStraight() || isStraightFlush() || isRoyalFlush() || isOnePair()) {
    return false;
  }
  for (int i = 0; i < FIVE; i++) {
    if (m_cards[i].points() == 0) {
      m_rank = PokerHand::NoRank;
      return false;
    }
  }
  m_rank = PokerHand::HighCard;
  return true;

}

bool PokerHand::isFourOfAKind() {

  //if the first and fourth cards are the same, or the second and fifth
  //cards are the same, then this is a four of a kind
  
  if ( m_cards[0].points() == m_cards[3].points() || m_cards[1].points() == m_cards[4].points() ) {
    m_rank = PokerHand::FourOfAKind;
    return true;
  } else {
    return false;
  }
}

bool PokerHand::isThreeOfAKind() {
  // in case it's a full house, just return false

  if (isFullHouse() || isFourOfAKind()) {
    return false;
  } else if (m_cards[0].points() == m_cards[2].points() || m_cards[1].points() == m_cards[3].points() || m_cards[2].points() == m_cards[4].points()) {
    m_rank = PokerHand::ThreeOfAKind;
    return true;
  }
  return false;

}


bool PokerHand::isTwoPair() {
  if ( isFullHouse() || isFourOfAKind() || isThreeOfAKind()) {
    return false;
  }
  // if there is a pair found, keep going
  int numPairs = 0;
  int tempFirstPairPoints = 0;
  for (int i = 0; i < FIVE - 1; i++) {
    if (m_cards[i].points() == m_cards[i+1].points()) {
      if (numPairs == 0) {
	tempFirstPairPoints = m_cards[i].points();
	numPairs++;
      } else {
	// if second pair is found, update rank & pertinent point values
	m_rank = TwoPair;
	m_secondPairPoints = m_cards[i].points();
	m_firstPairPoints = tempFirstPairPoints;
	return true;
      }
    }
  }


  return false;
}

bool PokerHand::isFullHouse() {

  // look for full house
  if(m_cards[0].points() != m_cards[1].points() || m_cards[3].points() != m_cards[4].points() || isFourOfAKind()) {
    return false;
  } else if (m_cards[1].points() != m_cards[2].points() && m_cards[2].points() != m_cards[3].points()) {
    return false;
  } else {
    m_tripletPoints = m_cards[2].points();
    if (m_cards[0].points() == m_cards[2].points()) {
      m_firstPairPoints = m_cards[4].points();
    } else {
      m_firstPairPoints = m_cards[0].points();
    }
    m_rank = PokerHand::FullHouse;
    return true;
  }

}

//check if each card has same suit as the first
bool PokerHand::isFlush() {
  
  if (!isStraightFlush() && !isRoyalFlush() && isAllOneSuit()) {
    m_rank = PokerHand::Flush;
    return true;
  }

  return false;
}


bool PokerHand::isAllOneSuit() {
  // simple for loop
  for (int i = 1; i < FIVE; i++) {
    if (m_cards[i].suit() != m_cards[0].suit()) {
      return false;
    }
  }
  return true;
}


//check if is flush and royal
bool PokerHand::isRoyalFlush() { 
    

  if (m_cards[0].points() > 9 && isAllOneSuit()) {
    m_rank = PokerHand::RoyalFlush;
    return true;
  } 
  return false;

}

//helper method for straight
bool PokerHand::isSequence() {
  for (int i = 0; i < FIVE - 1; i++) {
    if (m_cards[i+1].points() != m_cards[i].points() + 1) {
      return false;
    }
  }
  return true;
}

bool PokerHand::isStraight() {
  //use isSequence 
  if (!isStraightFlush() && !isFlush() && isSequence()) {
    m_rank = PokerHand::Straight;
    return true;
  }
  return false;


}




bool PokerHand::isStraightFlush() {
  //use previous functions to determine.
  if (isAllOneSuit() && isSequence()) {
    m_rank = PokerHand::StraightFlush;
    return true;
  } else {
    return false;
  }
}


int PokerHand::cmp(PokerHand &otherHand) {
  // if my rank is greater, outcome will be positive and vice versa
  int outcome = m_rank - otherHand.getRank();
  if (outcome == 0) {
    int yourPointTotal = m_lastCardPoints + m_firstPairPoints + m_secondPairPoints + m_tripletPoints + m_quadrupletPoints;
    int theirPointTotal = otherHand.m_lastCardPoints + otherHand.m_firstPairPoints + otherHand.m_secondPairPoints + otherHand.m_tripletPoints + otherHand.m_quadrupletPoints;

    outcome = yourPointTotal - theirPointTotal;

  }
  return outcome;
}

PokerHand::PokerHand (Card c0, Card c1, Card c2, Card c3, Card c4) {

  m_cards[0] = c0;
  m_cards[1] = c1;
  m_cards[2] = c2;
  m_cards[3] = c3;
  m_cards[4] = c4;

  m_valid = true;
  m_rank = NoRank;

  m_lastCardPoints = 0;
  m_firstPairPoints = 0;
  m_secondPairPoints = 0;
  m_tripletPoints = 0;
  m_quadrupletPoints = 0;
  
  sort();

  // assign last card value to every hand
  m_lastCardPoints = m_cards[4].points();

  // this will assign the rank of the card

  isRoyalFlush();
  isStraightFlush();
  isFourOfAKind();
  isFullHouse();
  isFlush();
  isStraight();
  isThreeOfAKind();
  isTwoPair();
  isOnePair();
  isHighCard();
}
