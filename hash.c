#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"


void ** hash_init(int struct_pointer_size, int number_of_elements) {
  return (void **) malloc(struct_pointer_size*number_of_elements);
}

static unsigned long hash(char *str, unsigned long modulo)
{
	unsigned long hash = 5381;
	int c;

	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;	/* hash * 33 + c */

	return hash % modulo;
}
