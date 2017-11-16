CC       = /usr/local/bin/g++
CFLAGS   = -g -ansi -Wall

PROJ         = a.out
CARDS        = card.h         card.cpp
GAMES        = game.h         game.cpp
PLAYERS      = player.h       player.cpp
CRUNO8       = Cruno8.h       Cruno8.cpp
CRUNOPLAYER  = CrunoPlayer.h  CrunoPlayer.cpp
CRUNOSKIP    = CrunoSkip.h    CrunoSkip.cpp
CRUNOREVERSE = CrunoReverse.h CrunoReverse.cpp
CRUNOGAME    = CrunoGame.h    CrunoGame.cpp
CRUNODRAW2   = CrunoDraw2.h   CrunoDraw2.cpp
DOTOS        = card.o game.o player.o Cruno8.o CrunoReverse.o CrunoSkip.o CrunoDraw2.o CrunoGame.o CrunoPlayer.o mytest.o

all: $(DOTOS)
	$(CC) $(CFLAGS) $(DOTOS)

run:       $(PROJ)
	./$(PROJ)

runV: $(PROJ)
	valgrind ./$(PROJ)

card.o:   $(CARDS) game.h player.h
	$(CC) $(CFLAGS) -c card.cpp

game.o: $(GAMES) card.h player.h
	$(CC) $(CFLAGS) -c game.cpp

player.o:  $(PLAYERS) game.h card.h
	$(CC) $(CFLAGS) -c player.cpp

Cruno8.o:  $(CRUNO8) card.h player.h game.h
	$(CC) $(CFLAGS) -c Cruno8.cpp

CrunoSkip.o: $(CRUNOSKIP) card.h player.h
	$(CC) $(CFLAGS) -c CrunoSkip.cpp

CrunoReverse.o: $(CRUNOREVERSE) card.h game.h player.h CrunoGame.h CrunoPlayer.h
	$(CC) $(CFLAGS) -c CrunoReverse.cpp

CrunoDraw2.o: $(CRUNODRAW2) card.h game.h player.h CrunoGame.h CrunoPlayer.h
	$(CC) $(CFLAGS) -c CrunoDraw2.cpp

CrunoPlayer.o: $(CRUNOPLAYER) player.h CrunoGame.h game.h Cruno8.h CrunoReverse.h CrunoSkip.h CrunoDraw2.h
	$(CC) $(CFLAGS) -c CrunoPlayer.cpp

CrunoGame.o: $(CRUNOGAME) card.h player.h game.h Cruno8.h CrunoReverse.h CrunoSkip.h CrunoDraw2.h CrunoPlayer.h
	$(CC) $(CFLAGS) -c CrunoGame.cpp

mytest.o: mytest.cpp card.h player.h game.h Cruno8.h CrunoReverse.h CrunoSkip.h CrunoGame.h CrunoPlayer.h CrunoDraw2.h
	$(CC) $(CFLAGS) -c mytest.cpp


.PHONY : clean cleaner

clean: 
	rm -f *~ *#
cleaner:
	rm -f *.o