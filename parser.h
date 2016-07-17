/*
 * Simple Flat Tree parser
 */

struct sub_topics_list {
  char * topic;
  struct sub_topics_list * topic_parent;
  struct sub_topics_list * topic_child;
};

/*
 * Initialises and returns the topic ontology linked list
 */
struct sub_topics_list * parser_init();

/*
 * Simple helper for copying strings.
 */
void copy_string(char * src, char ** dest);

/*
 * Populates linked list with the subtree of the ontology, including parent.
 * Takes the entire topic flat tree, and the parent key.
 */
void parser_get_sub_topics_list(struct sub_topics_list ** list_index, char *topics, char * topic);

/*
 * Clean up all allocated memory.
 */
void parser_destroy(struct sub_topics_list ** list_index);
