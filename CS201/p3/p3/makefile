OBJS = dijkstra.o vertex.o queue.o sll.o darray.o integer.o scanner.o binomial.o
OPTS = -Wall -g -std=c99

dijkstra : $(OBJS)
		gcc $(OPTS) $(OBJS) -o dijkstra -lm

dijkstra.o : dijkstra.c
		gcc $(OPTS) -c dijkstra.c

darray.o : darray.c darray.h
		gcc $(OPTS) -c darray.c

scanner.o : scanner.c scanner.h
		gcc $(OPTS) -c scanner.c

binomial.o : binomial.c binomial.h
		gcc $(OPTS) -c binomial.c
		
vertex.o : vertex.c vertex.h
		gcc $(OPTS) -c vertex.c
 
queue.o : queue.c queue.h
		gcc $(OPTS) -c queue.c

integer.o : integer.c integer.h
		gcc $(OPTS) -c integer.c

sll.o : sll.c sll.h
		gcc $(OPTS) -c sll.c

clean :
		rm -f $(OBJS) 

test :
	./dijkstra assign3testing/graph_assign3example_1.txt > assign3testing/myoutput/graph_assign3example_1.txt
	./dijkstra assign3testing/graph_assign3example_2.txt > assign3testing/myoutput/graph_assign3example_2.txt
	./dijkstra assign3testing/graph_whitespace.txt > assign3testing/myoutput/graph_whitespace.txt
	./dijkstra assign3testing/graph_empty.txt > assign3testing/myoutput/graph_empty.txt
	./dijkstra assign3testing/graph_single.txt > assign3testing/myoutput/graph_single.txt
	./dijkstra assign3testing/graph_multiplepaths_1.txt > assign3testing/myoutput/graph_multiplepaths_1.txt
	./dijkstra assign3testing/graph_multiplepaths_2.txt > assign3testing/myoutput/graph_multiplepaths_2.txt
	./dijkstra assign3testing/graph_multiplevertexdefs.txt > assign3testing/myoutput/graph_multiplevertexdefs.txt
	./dijkstra assign3testing/graph_sparce_1.txt > assign3testing/myoutput/graph_sparce_1.txt
	./dijkstra assign3testing/graph_sparce_2.txt > assign3testing/myoutput/graph_sparce_2.txt
	./dijkstra assign3testing/graph_random_10.txt > assign3testing/myoutput/graph_random_10.txt
	./dijkstra assign3testing/graph_random_50.txt > assign3testing/myoutput/graph_random_50.txt
	./dijkstra assign3testing/graph_random_200.txt > assign3testing/myoutput/graph_random_200.txt
	diff assign3testing/myoutput/graph_assign3example_1.txt assign3testing/output/graph_assign3example_1.txt
	diff assign3testing/myoutput/graph_assign3example_2.txt assign3testing/output/graph_assign3example_2.txt
	diff assign3testing/myoutput/graph_whitespace.txt assign3testing/output/graph_whitespace.txt
	diff assign3testing/myoutput/graph_empty.txt assign3testing/output/graph_empty.txt
	diff assign3testing/myoutput/graph_single.txt assign3testing/output/graph_single.txt
	diff assign3testing/myoutput/graph_multiplepaths_1.txt assign3testing/output/graph_multiplepaths_1.txt
	diff assign3testing/myoutput/graph_multiplepaths_2.txt assign3testing/output/graph_multiplepaths_2.txt
	diff assign3testing/myoutput/graph_multiplevertexdefs.txt assign3testing/output/graph_multiplevertexdefs.txt
	diff assign3testing/myoutput/graph_sparce_1.txt assign3testing/output/graph_sparce_1.txt
	diff assign3testing/myoutput/graph_sparce_2.txt assign3testing/output/graph_sparce_2.txt
	diff assign3testing/myoutput/graph_random_10.txt assign3testing/output/graph_random_10.txt
	diff assign3testing/myoutput/graph_random_50.txt assign3testing/output/graph_random_50.txt
	diff assign3testing/myoutput/graph_random_200.txt assign3testing/output/graph_random_200.txt

	./dijkstra large1.txt > myOut1.txt
	./dijkstra large2.txt > myOut2.txt
	./dijkstra large3.txt > myOut3.txt
	./dijkstra large4.txt > myOut4.txt
	diff testOut1.txt myOut1.txt
	diff testOut2.txt myOut2.txt
	diff testOut3.txt myOut3.txt
	diff testOut4.txt myOut4.txt

	# p3Testing

	./dijkstra single.0 > myOutSingle.txt
	./dijkstra two.0 > myOutTwo.txt
	./dijkstra unweighted.0 > myOutUnweighted.txt
	./dijkstra g6.0 > myOutG6.txt
	./dijkstra g7.0 > myOutG7.txt
	./dijkstra g8.0 > myOutG8.txt
	./dijkstra g9.0 > myOutG9.txt
	./dijkstra g10.0 > myOutG10.txt
	./dijkstra g11.0 > myOutG11.txt
	./dijkstra g12.0 > myOutG12.txt
	./dijkstra g13.0 > myOutG13.txt
	./dijkstra g14.0 > myOutG14.txt
	./dijkstra g15.0 > myOutG15.txt
	diff outSingle.txt myOutSingle.txt
	diff outTwo.txt myOutTwo.txt
	diff outUnweighted.txt myOutUnweighted.txt
	diff outG6.txt myOutG6.txt
	diff outG7.txt myOutG7.txt
	diff outG8.txt myOutG8.txt
	diff outG9.txt myOutG9.txt
	diff outG10.txt myOutG10.txt
	diff outG11.txt myOutG11.txt
	diff outG12.txt myOutG12.txt
	diff outG13.txt myOutG13.txt
	diff outG14.txt myOutG14.txt
	diff outG15.txt myOutG15.txt
