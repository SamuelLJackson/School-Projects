driver.out: Pinball.o
	g++ -g -Wall -ansi Pinball.o myDriver.cpp -o driver.out

Pinball.o:
	g++ -g -c -Wall Pinball.cpp

clean:
	rm *.o
	rm *.out

cleaner: 
	rm *~

val:
	valgrind --leak-check=full ./driver.out

run:
	./driver.out 


