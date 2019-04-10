OBJS = scanner.o value.o calculon.o queue.o node.o stack.o binarysearchtree.o
OPTS = -Wall -g -std=c99

calculon : $(OBJS)
		gcc $(OPTS) $(OBJS) -o calculon -lm

calculon.o : calculon.c scanner.h value.h
		gcc $(OPTS) -c calculon.c

scanner.o : scanner.c scanner.h
		gcc $(OPTS) -c scanner.c

value.o : value.c value.h
		gcc $(OPTS) -c value.c

queue.o : queue.c queue.h
		gcc $(OPTS) -c queue.c

node.o : node.c node.h
		gcc $(OPTS) -c node.c

stack.o : stack.c stack.h
		gcc $(OPTS) -c stack.c

binarysearchtree.o : binarysearchtree.c binarysearchtree.h
		gcc $(OPTS) -c binarysearchtree.c
clean :
		rm -f $(OBJS) calculon
test : ./calculon 
	./calculon test.txt
	
