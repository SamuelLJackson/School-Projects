#include <iostream>
#include "card.h"
#include "pokerhand.h"
using namespace std;

int main() {

  Card spades10(Card::Spades, 10);
  Card spades11(Card::Spades, 11);
  Card spades12(Card::Spades, 12);
  Card spades13(Card::Spades, 13);
  Card spades14(Card::Spades, 14);

  // this is a royal flush
  PokerHand royalFlush(spades10, spades11, spades12, spades13, spades14);

  cout << "this should print out RoyalFlush: " << endl;
  royalFlush.printRank();
  
  Card spades09(Card::Spades, 9);

  PokerHand straightFlush(spades10, spades11, spades12, spades13, spades09);

  cout << "this should print StraightFlush: " << endl;

  straightFlush.printRank();

  Card hearts10(Card::Hearts, 10);
  Card clubs10(Card::Clubs, 10);
  Card diamonds10(Card::Diamonds, 10);
  
  PokerHand fourOfAKind(spades10, hearts10, clubs10, diamonds10, spades11);
  
  cout << "this should print fourOfAKind: " << endl;
  fourOfAKind.printRank();

  Card hearts09(Card::Hearts, 9);

  PokerHand fullHouse(spades10, hearts10, clubs10, spades09, hearts09);

  cout << "this shoudl print FullHouse: " << endl;

  fullHouse.printRank();

  Card spades04(Card::Spades, 4);
  
  PokerHand flush(spades11, spades10, spades04, spades09, spades12);

  cout << "this shold print Flush" << endl;

  flush.printRank();

  PokerHand straight(spades10, spades11, spades12, spades13, hearts09);

  cout << "this should print Straight: " << endl;

  straight.printRank();

  PokerHand threeOfAKind(spades10, hearts10, clubs10, hearts09, spades14);

  cout << "this shoudl print ThreeOfAKind : " << endl;

  threeOfAKind.printRank();
  
  PokerHand twoPair(spades10, hearts10, spades09, hearts09, spades11);

  cout << "this should print TwoPair: " << endl;
  
  twoPair.printRank();

  PokerHand onePair(spades10, hearts10, spades09, spades13, spades14);

  cout << "this should print onePair: " << endl;
 

  onePair.printRank();
  Card clubs02(Card::Clubs, 2);

  PokerHand highCard(clubs02, spades09, spades10, spades14, spades13);
  cout << "this should print highCard" << endl;


  highCard.printRank();

  Card clubs99(Card::Clubs, 99);
  PokerHand noRank(clubs99, clubs02, spades09, spades10, spades14);

  cout << "this shoudl print NoRank: " << endl;
  noRank.printRank();

  cout << "this should be negative" << endl;

  cout << onePair.cmp(twoPair) << endl;

  PokerHand onePair2(spades09, hearts09, clubs02, spades13, spades12);

  cout << "this value should be positive: " << endl;
  cout << onePair.cmp(onePair2) << endl;
  return 0;

}
