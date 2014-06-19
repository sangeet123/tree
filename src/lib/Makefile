CC = gcc
LIBCFLAG = -Wall -g -c
data_structures.o: list.o rbtree.o
	${CC} ${LIBCFLAG} list.o rbtree.o -o data_structures.o

list.o: list.c
	${CC} ${LIBCFLAG}  list.c -o list.o

rbtree.o: rbtree.c
	${CC} ${LIBCFLAG} rbtree.c -o rbtree.o

clean:
	rm *.o