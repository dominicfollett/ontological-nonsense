/*
 * Hash map holding question topics
 */

 #include "dawg.h"

 struct question {
   struct question * child;
   char * topic;
   // This needs to be the dawg -- dynamically sized array
   struct dawg ** parent_dawg;
 };

/*
 * Initilize question hash
 */
struct question ** question_init(int n_topics);

void recursive_free(struct question * q_tmp);

/*
 * Insert a question to the hash
 */
void question_insert(struct question ** questions_hash, char * token, int n_topics, char * line);

/*
 * Clean up all allocated memory
 */
void question_destroy(struct question ** questions_hash, int n_topics);
