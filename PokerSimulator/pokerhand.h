//did not alter this file, tho you'll notice comments are gone


#ifndef _POKERHAND_H_
#define _POKERHAND_H_

#include "card.h"

class PokerHand {

 public:
  
  static const int FIVE = 5;

  typedef enum { NoRank, HighCard, OnePair, TwoPair, ThreeOfAKind,
		 Straight, Flush, FullHouse, FourOfAKind, StraightFlush,
		 RoyalFlush } pRank;

  PokerHand();

  PokerHand(Card c0, Card c1, Card c2, Card c3, Card c4);

  int cmp(PokerHand &otherHand);

  void printRank();

  void printCards();

  pRank getRank();

  bool isRoyalFlush();

  bool isStraightFlush();

  bool isFourOfAKind();

  bool isFullHouse();

  bool isFlush();

  bool isStraight();
  
  bool isThreeOfAKind();
  
  bool isTwoPair();

  bool isOnePair();

  bool isHighCard();

 private:
  
  Card m_cards[FIVE];
  bool m_valid;
  pRank m_rank;

  Card::cPoints m_lastCardPoints;

  Card::cPoints m_firstPairPoints;

  Card::cPoints m_secondPairPoints;

  Card::cPoints m_tripletPoints;

  Card::cPoints m_quadrupletPoints;

  void sort();

  bool isAllOneSuit() ;

  bool isSequence() ;


};

#endif
