/*
 * Hash map holding question topics
 */

#include "dawg.h"

struct question
{
	struct question *child;
	char *topic;
	struct dawg **dawg_array;
};

/*
 * Initilize question hash
 */
struct question **question_init(int n_topics);

/*
 * Clean up the memory for each question
 */
void recursive_free(struct question **q_tmp);

/*
 * Insert a question to the hash
 */
void question_insert(struct question ***questions_hash, char *token,
					 int n_topics, char *line);

/*
 * Return the number of questions which match
 */
int question_count(struct question ***questions_hash, int m_questions,
				   char *query, char *topic);
/*
 * Clean up all allocated memory
 */
void question_destroy(struct question ***questions_hash, int n_topics);
