CPPFLAGS = -ansi -Wall

main:
	g++ card.cpp -c 
	g++ pokerhand.cpp -c
	g++ mytest.cpp pokerhand.o card.o -o mytest
	g++ play5.cpp pokerhand.o card.o -o play5
	g++ play7.cpp pokerhand.o card.o -o play7


testing2: testing2.o 

play5:
	./play5

play7:
	./play7

run:
	./mytest