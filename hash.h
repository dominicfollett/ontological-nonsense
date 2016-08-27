/*
 * Hash implementation for reuse accross the project.
 */


typedef struct hash_s ** _hash_map;
typedef _hash_map hash_map;

/*
 * Initialize the hashmap
 * Int is acceptible since the ontology size is small << 2^20
 */
hash_map hash_init(int number_of_elements);

/*
 * Insert into the hash_map, with separate chaining for minimize collisions.
 */
void hash_insert(hash_map map, void * pointer, char * key);

/*
 * A cleanup method, we don't cleanup whatever is being pointed to.
 */

void * hash_find(hash_map map, char * key);
