#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

struct hash_s { /* Just always use this as our type */
  void * data;
};

hash_map hash_init(int struct_pointer_size, int number_of_elements) {
  /* Assume worst case scenario where the matrix is number of elements^2 */
  /* Don't really have to resize the hash_map/matix ... */
  int size;
  struct hash_s ** hash_map;

  size = (sizeof(struct hash_s *))*number_of_elements;
  hash_map = malloc(size);

  while(number_of_elements--)
  {
    hash_map[number_of_elements] = malloc(size);
  }
  return hash_map;
}

static unsigned long hash(char *str, unsigned long modulo)
{
	unsigned long hash = 5381;
	int c;

	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;	/* hash * 33 + c */

	return hash % modulo;
}

void hash_insert(hash_map map, void * pointer, char * key, int size)
{
  unsigned long index;
  struct hash_s * iterator;

  index = hash(key, size);
  iterator = map[index];

  while(iterator) iterator++;
  iterator->data = pointer;
}
