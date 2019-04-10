OBJS = scanner.o prim.o queue.o node.o binheap.o CDLL.o value.o vertex.o graph.o
OPTS = -Wall -g -std=c99

prim : $(OBJS)
		gcc $(OPTS) $(OBJS) -o prim -lm

prim.o : prim.c scanner.h 
		gcc $(OPTS) -c prim.c

scanner.o : scanner.c scanner.h
		gcc $(OPTS) -c scanner.c

queue.o : queue.c queue.h
		gcc $(OPTS) -c queue.c

node.o : node.c node.h
		gcc $(OPTS) -c node.c

graph.o : graph.c graph.h
		gcc $(OPTS) -c graph.c

vertex.o : vertex.c vertex.h
		gcc $(OPTS) -c vertex.c

CDLL.o : CDLL.c CDLL.h
		gcc $(OPTS) -c CDLL.c

binheap.o : binheap.c binheap.h
		gcc $(OPTS) -c binheap.c
		
clean :
		rm -f $(OBJS) prim

test : ./prim
		$(testing simple Prim)
		./prim test.txt proof
		
		

