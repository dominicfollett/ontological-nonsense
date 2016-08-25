#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

struct ontology_s
{
  struct ontology_node * root;
  struct ontology_node * current;
  hash_map ontology_m;
};

struct ontology_node
{
  char * topic;
  struct ontology_node ** children;
  void * data; /* Data that someone wants to store in refence to this topic */
};

/*
 * strtok_r is no reentrant so I can use it accross recursive calls
 */

static void parse_flat_tree(struct ontology_node * on, char * flat_ontology, char * save_ptr, int * p_to_close)
{
  char *token;

  if(flat_ontology)
  {
    if ((token = strtok_r(flat_ontology, " ", &save_ptr)) != NULL)
    {
      strcpy(on->topic, token);
    }
  }

  while ((token = strtok_r(NULL, " ", &save_ptr)) != NULL)
  {
    switch (*token)
    {
    case '(':
      *p_to_close += 1;
      /* Get the most recently created child */
      /* parse_flat_tree(child_node, NULL, save_ptr, &p_to_close) */
      break;
    case ')':
      *p_to_close -= 1;
      return;
      break;
    default:
      if (*p_to_close > 0)
      {
        /* Create a new node */
        /* Set the topic */
        /* Add it on's children */
      }
    }
    if (*p_to_close == 0)
    {
      break;
    }
  }
  return;
}

struct ontology_s *  ontology_init(char * flat_ontology, int N)
{
  /* Malloc the ontology_s struct */
    /* Initialize the Root and Current nodes and the Hash Map */
    /* While */
      /* Parse the flat tree */
      /* Create a node */
      /* recursively create children */
      /* resize children array based OR get the size as part of the recursive process */
    char * save_ptr = NULL;
    int p_to_close = 0;
    struct ontology_node * on = malloc(sizeof(struct ontology_node));
    parse_flat_tree(on, flat_ontology, save_ptr, &p_to_close);
    return NULL;
}

struct ontology_node * ontology_find(ontology_t opaque_pointer, char * topic)
{
  /* Use the hashmap to find the correct node and set it as the current node */
  return NULL;
}
