#include "ontology.h"

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
  /* struct hashmap * map; */
};

struct ontology_node {
  char * topic;
  struct ontology ** children;
};
