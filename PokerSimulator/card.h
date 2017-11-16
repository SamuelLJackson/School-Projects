#ifndef _CARD_H_
#define _CARD_H_

class Card {

 public:
  typedef enum { Invalid, Clubs, Diamonds, Hearts, Spades} cSuit;

  typedef unsigned int cPoints ;

  Card() ;

  Card(cSuit s, cPoints p) ;

  cSuit suit();

  cPoints points();

  void print();

 private:
  
  cSuit m_suit ;
  cPoints m_points;

};

#endif
