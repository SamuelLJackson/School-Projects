//File: testing2.cpp

#include <iostream>
#include "card.h"
#include "pokerhand.h"

using namespace std;

int main() {
  Card card1(Card::Spades,   2);
  Card card2(Card::Hearts,   2);
  Card card3(Card::Diamonds, 2);
  Card card4(Card::Spades,   3);
  Card card5(Card::Hearts,   3);

  //hand1 is a full house
  PokerHand hand1(card1, card2, card3, card4, card5);

  Card card6(Card::Hearts,   4);
  
  //hand2 is a three of a kind
  PokerHand hand2(card1, card4, card6, card2, card3);

  Card card7(Card::Clubs,    2);
  
  //hand3 is a four of a kind
  PokerHand hand3(card1, card2, card3, card7, card6);

  //hand4 is a two pair
  PokerHand hand4(card1, card2, card4, card5, card6);

  Card card8(Card::Clubs,    6);
  Card card9(Card::Hearts,  11);

  //hand5 is a high card
  PokerHand hand5(card1, card4, card6, card8, card9);

  Card a;

  PokerHand hand6(a, a, a, a, a);


  Card caard1(Card::Spades,     2);
  Card caard2(Card::Spades,     3);
  Card caard3(Card::Spades,     6);
  Card caard4(Card::Spades,    10);
  Card caard5(Card::Spades,    14);

  //hand7 is a flush
  PokerHand hand7(caard1, caard2, caard3, caard4, caard5);

  cout << "hand 1 and hand2: " << hand1.cmp(hand2) << endl;




  return 0;
}
