/*
 * Directed Acyclic Word Graph
 */

struct dawg
{
	char *letter;
	struct dawg **pups;
	int count;
};

/*
 * Creates and initialises a dawg element.
 */
struct dawg *dawg_init(void);

/*
 * Check if we're at the end of the string
 */
int peeks(char **word);

/*
 * Initialize an array of dawg with one item
 */
struct dawg **dawg_init_array(void);

/*
 * Remove a letter from the question or query
 */
void chop_letter(char **word, char *c);

/*
 * Insert string elements into dawg.
 */
struct dawg **dawg_bury(struct dawg **good_dawg, char *question);

/*
 * Check if the given string exists.
 */
int dawg_fetch(struct dawg **good_dawg, char *query);

/*
 * Free all memory associated with this dawg.
 */
void dawg_demolish(struct dawg **good_dawg);

/*
 * Returns a pointer to the memory allocated letter
 */
char *dawg_index(char *letter);
