CC     = gcc
CFLAGS = -Wall -g -Wextra -std=c89 -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition

LIBS = -lpthread

question.o: question.c
	$(CC) -c $^ $(CFLAGS)

dawg.o: dawg.c
	$(CC) -c $^ $(CFLAGS)

parser.o: parser.c
	$(CC) -c $^ $(CFLAGS)

ontology.o: ontology.c
	$(CC) -c $^ $(CFLAGS)

main.o: main.c
	$(CC) -c $^ $(CFLAGS)

main: main.o parser.o ontology.o dawg.o question.o
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

#### Cleanup ####
clean:
	rm -f *.o
