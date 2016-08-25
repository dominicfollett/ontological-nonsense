/*
 * Ontology stucture
 */

typedef struct ontology_s * ontology_t;
typedef struct ontology_node * ontology_n;
/*
 * Set up entire DS, return opaque point for further calls.
 */
struct ontology_s *  ontology_init(char * flat_ontology, int N);

/*
 * Find cycle through a topic subtree.
 * If topic is NULL. then cycle through children.
 * If this function returns NULL, then there are no more children.
 * Do not pass NULL on 1st iteration.
 */
struct ontology_node * ontology_find(ontology_t opaque_pointer, char * topic);

/*
 * Set related data on the current node this can be anything, int, struct ...
 */
void ontology_save_data(ontology_t opaque_pointer, void * data);

/*
 * Get related data on the current node
 */
void * ontology_get_data(ontology_t opaque_pointer);

/*
 * A cleanup method
 */
