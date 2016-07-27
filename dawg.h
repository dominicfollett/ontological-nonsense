/*
 * Directed Acyclic Word Graph
 */

struct dawg {
  char * letter;
  struct dawg ** pups;
};

/*
 * Creates and initialises a dawg element.
 */
struct dawg * dawg_init(void);

void init_alphabet(void);

struct dawg ** dawg_init_array(void);

void chop_letter(char ** word, char * c);

void alpha_check(int i, const char * c);

/*
 * Insert string elements into dawg.
 */
struct dawg ** dawg_bury(struct dawg ** good_dawg, char * question);

/*
 * Check if the given string exists.
 */
int dawg_fetch(struct dawg ** good_dawg, char * query);

/*
 * Free all memory associated with this dawg.
 */
void dawg_demolish(struct dawg ** good_dawg);

void dawg_cleanup(void);

/*
 * Returns a pointer to the memory allocated letter
 */
char * dawg_index(char * letter);
