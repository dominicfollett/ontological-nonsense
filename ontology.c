#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ontology.h"
#include "hash.h"
#include <ctype.h>

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
  hash_map ontology_map;
};

struct ontology_node
{
  char * topic;
  struct ontology_node * child; /* A linked list of child nodes */
  struct ontology_node * sibling;
  void * data; /* Data that someone wants to store in refence to this topic */
};

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

struct ontology_node * node_init(char * topic) {
  struct ontology_node * new_node;
  new_node = malloc(sizeof(struct ontology_node));
  memset(new_node, 0, sizeof(struct ontology_node));
  copy_string(&(new_node->topic), topic);
  return new_node;
}

/*
 * strtok_r is reentrant so I can use it accross recursive calls
 */

static void parse_flat_tree(struct ontology_node ** on, char * flat_ontology,
           char **save_ptr, int * p_to_close, hash_map map)
{
  char *token;
  struct ontology_node *last_created;

  if(!*on)
    {
    if ((token = strtok_r(flat_ontology, " ", save_ptr)) != NULL)
      {
        *on = node_init(token);
      }
    }

  last_created = *on;

  while ((token = strtok_r(NULL, " ", save_ptr)) != NULL)
  {
    switch (*token)
    {
    case '(':
      *p_to_close += 1;
      parse_flat_tree(&last_created, NULL, save_ptr, p_to_close, map);
      break;
    case ')':
      *p_to_close -= 1;
      return;
      break;
    default:
      if (*p_to_close > 0)
      {
        /* Create a new node */
        last_created = node_init(token);
        hash_insert(map, (void *) last_created, token);
        /* Add it onto on's children */
        if((*on)->child)
        {
          last_created->sibling = (*on)->child;
        }/* else last created sibling is null */
        (*on)->child = last_created;
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
  char * save_ptr;
  char * save_place;
  int p_to_close;
  struct ontology_node *on;
  struct ontology_s *ontology_tree;

  save_ptr = NULL;
  p_to_close = 0;
  on = NULL;
  save_place = flat_ontology;

  /* Malloc the ontology_s struct */
  ontology_tree = malloc(sizeof(struct ontology_s));
  memset(ontology_tree, 0, sizeof(struct ontology_s));
  ontology_tree->ontology_map = hash_init(N);
  /* Initialize the Root and Current nodes and the Hash Map */

  for ( ; *flat_ontology; ++flat_ontology) *flat_ontology = tolower(*flat_ontology);
  flat_ontology = save_place;

  parse_flat_tree(&on, flat_ontology, &save_ptr, &p_to_close, ontology_tree->ontology_map);
  ontology_tree->root = on; /* Never changes */
  ontology_tree->current = on;

  return ontology_tree;
}

void ontology_cleanup(ontology_t opaque_pointer) {
  /* recursively free the tree */
}

struct ontology_node * ontology_find(ontology_t opaque_pointer, char * topic)
{
  /* Use the hashmap to find the correct node and set it as the current node */
  return NULL;
}
