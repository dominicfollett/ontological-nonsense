CC     = gcc
CFLAGS = -Wall -g

LIBS = -lpthread


#### RPC Client Part ####
parser.o: parser.c
	$(CC) -c $^ $(CFLAGS)

ontology.o: ontology.c
	$(CC) -c $^ $(CFLAGS)

ontology_main: parser.o ontology.o
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

#### Cleanup ####
clean:
	rm -f *.o
