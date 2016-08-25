#include "ontology.h"
#include "hash.h"
/*
 * Searches are expensive. Store a pointer to the node, in a hash map wrt.
 * topic name. Separate out the hashing mechanism in question.c so that it
 * will be reuseable.
 */

/*
 * A single struct is returned to the user: it contains, a pointer to the
 * root node, and a pointer to the hashmap. This struct is returned as an
 * opaque pointer
 */

/*
 * All topic names must be converted to lower case.
 */

struct ontology_s {
  struct ontology_node * root;
  struct ontology_node * current;
  hash_map ontology_m;
};

struct ontology_node {
  char * topic;
  struct ontology ** children;
  void * data; /* Data that someone wants to store in refence to this topic */
};

struct ontology_s *  ontology_init(char * flat_ontology, int N) {
  /* Parse the flat tree and create */
}

struct ontology_node * ontology_find(ontology_t opaque_pointer, char * topic) {
  /* Use the hashmap to find the correct node and set it as the current node */
}
