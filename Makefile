CC     = gcc
CFLAGS = -Wall -g

LIBS = -lpthread


#### RPC Client Part ####
parser.o: parser.c
	$(CC) -c $^ $(CFLAGS)

ontology_main: parser.o
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

#### Cleanup ####
clean:
	rm -f *.o
