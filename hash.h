/*
 * Hash implementation for reuse accross the project.
 */

typedef void ** hash_map;

/*
 * Initialize the hashmap
 * Int is acceptible since the ontology size is small << 2^20
 */
void ** hash_init(int struct_size, int number_of_elements);

/*
 * Compute a hash from a given string and modulo (hash array size)
 */
static unsigned long hash(char *str, unsigned long modulo);


/*
 * A cleanup method, we don't cleanup whatever is being pointed to.
 */
