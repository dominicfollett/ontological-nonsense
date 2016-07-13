/*
 * Directed Acyclic Word Graph
 */

struct dawg {
  char * letter;
  char * children[26];
  unsigned int both_cases:1;
};

/*
 * Creates and initialises root dawg.
 */
struct dawg * dawg_init();

/*
 * Insert string elements into dawg.
 */
void dawg_bury(struct dawg ** good_dawg);

/*
 * Check if the given string exists.
 */
void dawg_fetch(struct dawg ** good_dawg);

/*
 * Free all memory associated with this dawg.
 */
void dawg_demolish(struct dawg ** good_dawg);
