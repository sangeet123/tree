CC = gcc
CFLAG = -Wall -g
LIBCFLAG = -Wall -g -c

splaytree_test: splaytree_test.c list.o splaytree.o
	${CC} ${CFLAG} splaytree_test.c list.o splaytree.o -o splaytree_test -O2

list.o: lib/list.c
	${CC} ${LIBCFLAG}  lib/list.c -o list.o -O2

splaytree.o: lib/splaytree.c
	${CC} ${LIBCFLAG} lib/splaytree.c -o splaytree.o -O2

clean:
	rm splaytree_test
	rm *.o
clean-all:
	rm splaytree_test
	rm *.o
	rm a.out
	rm *.o~
