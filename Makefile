CC     = gcc
CFLAGS = -Wall -g

LIBS = -lpthread


#### RPC Client Part ####
dawg.o: dawg.c
	$(CC) -c $^ $(CFLAGS)

parser.o: parser.c
	$(CC) -c $^ $(CFLAGS)

ontology.o: ontology.c
	$(CC) -c $^ $(CFLAGS)

ontology_main: parser.o ontology.o dawg.o
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

#### Cleanup ####
clean:
	rm -f *.o
