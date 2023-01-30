test: test.o Queque.o
	cc test.o Queque.o -o test

test.o: test.c
	cc -c test.c

Queque.o: ../source/Queque.c ../include/Queque.h
	cc -c ../source/Queque.c

clear:
	rm *.o