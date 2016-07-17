/*
 * Directed Acyclic Word Graph
 */

struct dawg {
  char * letter;
  struct dawg * children[26];
  unsigned int both_cases:1;
};

char * alphabet[26];

/*
 * Creates and initialises a dawg element.
 */
struct dawg * dawg_init();

/*
 * Insert string elements into dawg.
 */
void dawg_bury(struct dawg ** good_dawg, char * question);

/*
 * Check if the given string exists.
 */
void dawg_fetch(struct dawg ** good_dawg);

/*
 * Free all memory associated with this dawg.
 */
void dawg_demolish(struct dawg ** good_dawg);

/*
 * Returns a pointer to the memory allocated letter
 */
char * dawg_index(char * letter);
