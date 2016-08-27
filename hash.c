#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

struct hash_s { /* Just always use this as our type */
  char * key;
  void * data;
};
unsigned long modulo;

static void copy_string(char **dest, char *src)
{
	size_t length = strlen(src);
	*dest = malloc(length + 1);
	if (!*dest)
	{
		perror("During malloc:");
	}
	memcpy(*dest, src, length + 1);
}

hash_map hash_init(int number_of_elements) {
  /* Assume worst case scenario where the matrix is number of elements^2 */
  /* Don't really have to resize the hash_map/matix ... */
  int size;
  struct hash_s ** hash_map;
  modulo = number_of_elements;

  size = (sizeof(struct hash_s *))*modulo;
  hash_map = malloc(size);

  while(number_of_elements--)
  {
    hash_map[number_of_elements] = malloc(size);
  }
  return hash_map;
}

static unsigned long hash(char *str)
{
	unsigned long hash = 5381;
	int c;

	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;	/* hash * 33 + c */

	return hash % modulo;
}

void * hash_find(hash_map map, char * key) {
  unsigned long index;
  struct hash_s * iterator;

  index = hash(key);
  iterator = map[index];
  while(strcmp(iterator->key, key) != 0)
    {
      iterator++;
    }
  return iterator->data;
}

void hash_insert(hash_map map, void * pointer, char * key)
{

  unsigned long index;
  struct hash_s * iterator;

  index = hash(key);
  iterator = map[index];
  while(iterator->data)
    {
      iterator++;
    }
  copy_string(&(iterator->key), key);
  iterator->data = pointer;
}
