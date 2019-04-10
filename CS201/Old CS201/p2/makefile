OBJS = scanner.o trees.o queue.o node.o binarysearchtree.o 
OPTS = -Wall -g -std=c99

trees : $(OBJS)
		gcc $(OPTS) $(OBJS) -o trees -lm

trees.o : trees.c scanner.h 
		gcc $(OPTS) -c trees.c

scanner.o : scanner.c scanner.h
		gcc $(OPTS) -c scanner.c

queue.o : queue.c queue.h
		gcc $(OPTS) -c queue.c

node.o : node.c node.h
		gcc $(OPTS) -c node.c

binarysearchtree.o : binarysearchtree.c binarysearchtree.h
		gcc $(OPTS) -c binarysearchtree.c
		
clean :
		rm -f $(OBJS) trees

test : ./trees
		$(testing simple BST)
		./trees -b test2.txt data.txt
		$(testing AVL tree)
		./trees -a test2.txt data.txt

