/**************************************************************
 ** File:        CrunoGame.cpp
 ** Project:     CMSC 202 Project 4, Spring 2016
 ** Author:      Sam Everett
 ** Date:        04/20/16
 ** Section:     19
 ** E-mail:      eversam1@umbc.edu
 **
 ** This is the implementation of the CrunoGame class
 **
 ***************************************************************/


#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;
#include "game.h"
#include "player.h"
#include "card.h"
#include "CrunoReverse.h"
#include "CrunoSkip.h"
#include "CrunoDraw2.h"
#include "CrunoGame.h"
#include "CrunoPlayer.h"

static void ifNullCrash(void *ptr) {
  if (ptr == NULL){
    cerr << "Could not allocate memor\n";
    exit(1) ;
  }
  return ;
}


void CrunoGame::initialize(int numPlayers) {
  m_reverseMode = false;
  m_suit = 0;
  m_points = 0;
  m_currentPlayer = 0;
  cout << "hey you guyyyyyys" << endl;
  // can't play by yourself
  //
  if (numPlayers < 2) {
    cerr << "Insufficient players\n" ;
    exit(1) ;
  }

  if (numPlayers > 10) {
    cerr << "too many players\n" ;
    exit(1);
  }

  m_numPlayers = 0;

  m_maxPlayers = numPlayers;
  m_players = new Player*[numPlayers];
  ifNullCrash(m_players) ;
  m_winner = m_maxPlayers + 1;  // not a real player

  // usually use just one deck
  int decks = 1;
  m_maxCards = 76;

  if (numPlayers > 5) {
    // use two decks
    decks = 2;
    m_maxCards = 152;
  }

  m_discard = new Card*[m_maxCards];
  ifNullCrash(m_discard) ;


  m_stock = new Card*[m_maxCards];
  ifNullCrash(m_stock) ;

  int i = 0;

  for (int d = 0; d < decks ; d++) {

    for (unsigned int s = Card::Clubs ; s <= Card::Spades ; s++) {
      for (unsigned int p = 2; p <= 7; p++) {
	m_stock[i] = new Card(s,p);
	i++;
      }
      //add in a Cruno8 card for each suit
      m_stock[i] = new Cruno8(s);
      cout << m_stock[i]->toString() << endl;
      i++;
      for (unsigned int p = 9; p <= Card::Ace; p++) {
	m_stock[i] = new Card(s,p);
	i++;
      }
      // add in two of each action card per suit
      m_stock[i] = new CrunoSkip(s);
      cout << m_stock[i]->toString() << endl;
      i++;
      m_stock[i] = new CrunoSkip(s);
      i++;
      m_stock[i] = new CrunoReverse(s);
      i++;
      m_stock[i] = new CrunoReverse(s);
      i++;
      m_stock[i] = new CrunoDraw2(s);
      i++;
      m_stock[i] = new CrunoDraw2(s);
      i++;
    }
  }

  m_numStock = m_maxCards;

  m_started = false;
}
 

unsigned int CrunoGame::nextPlayer() {          

  // check if game is in reverseMode, i.e. play
  // goes from player 1 to player 0
  if (m_reverseMode) {



    switch (m_points) {
      // if card is skip, travel backwards 2
    case CrunoSkip::Skip:
      // if player is zero, set next player to penultimate spot
      if (m_currentPlayer == 0) {
	m_currentPlayer = numPlayers() - 2;
	// if current player is 1, set next player to ultimate spot
      } else if (m_currentPlayer == 1) {
	m_currentPlayer = numPlayers() - 1;
      } else {
	m_currentPlayer = m_currentPlayer - 2;
      }
      break;

    case CrunoReverse::Reverse : 
      //if card is reverse, change back to normal mode, with
      // game play flowing from player 0 to player 1
      m_reverseMode = false;
      m_currentPlayer = (m_currentPlayer + 1) % numPlayers();
      break;
    case CrunoDraw2::Draw2 :
      //if card is draw2 set current player back one
      if (m_currentPlayer == 0) {
	m_currentPlayer = numPlayers() - 1;
      } else {
	m_currentPlayer = (m_currentPlayer - 1);
      }      
      cout << "Player " << m_currentPlayer << " is drawing two cards" << endl;
      //make the new current player draw 2 cards
      m_players[m_currentPlayer]->takeCard(dealOneCard());
      m_players[m_currentPlayer]->takeCard(dealOneCard());

    default:
      // if card is non-action card
      if (m_currentPlayer == 0) {
	m_currentPlayer = numPlayers() - 1;
      } else {
	m_currentPlayer = (m_currentPlayer - 1);
      }
    }

  } else {
    // if in regular mode, i.e. gameplay flows from player 0
    // to player 1

    switch (m_points) {
    case CrunoSkip::Skip:
      m_currentPlayer = (m_currentPlayer + 2) % numPlayers();
      break;

    case CrunoReverse::Reverse : 
      // if card is reverse, set gameplay to reverseMode
      m_reverseMode = true;
      if (m_currentPlayer == 0) {
	//if currentPlayer is 0, set currentPlayer to 
	// penultimate spot
	m_currentPlayer = numPlayers() - 1;
      } else {
	// if current Player is not zero, set currentPlayer
	// back one
	m_currentPlayer = (m_currentPlayer - 1);
      }
      break;
    case CrunoDraw2::Draw2 :
      // if draw 2 card, set current player ahead one
      m_currentPlayer = (m_currentPlayer + 1) % numPlayers();      

      cout << "Player " << m_currentPlayer << " is drawing two cards" << endl;
      // make new current Player draw two cards
      m_players[m_currentPlayer]->takeCard(dealOneCard());
      m_players[m_currentPlayer]->takeCard(dealOneCard());
      break;
    default:
      m_currentPlayer = (m_currentPlayer + 1) % numPlayers();
    }
  }

  return m_currentPlayer;

}



Card * CrunoGame::dealOneCard() {
  //card pointer that will ultimately return from stock
  Card *cptr ;

  if (m_numStock < 1) {
    // initialize card that will be the only one in the discard
    Card * faceUp;
    //pop off the top card of the discard pile
    m_numDiscard--;
    faceUp = m_discard[m_numDiscard];
    m_discard[m_numDiscard] = NULL;
    // add each card from discard pile into stock
    for (int i = 1; i <= m_numDiscard; i++) {
      m_stock[m_numDiscard - i] = m_discard[m_numDiscard - i];
      m_numStock++;
      m_discard[m_numDiscard-1] = NULL;
    }
    //set only card in discard equal to the card currently in play
    m_numDiscard = 1;
    m_discard[0] = faceUp;


    //initialize random variable
    int j;
    srand(333);
    //shuffle deck
    for (unsigned int i = 0; i < m_numStock; i++) {
      Card * temp;
      j = rand() % m_numStock;
      temp = m_stock[i];
      m_stock[i] = m_stock[j];
      m_stock[j] = temp;
    }

  }

  // pop top card off of stock, then set cptr equal to it
  m_numStock--;
  cptr = m_stock[m_numStock];
  // set last m_stock pointer equal to NULL
  m_stock[m_numStock] = NULL;

  return cptr;
}




