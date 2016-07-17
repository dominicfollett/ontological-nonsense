/*
 * Hash map holding question topics
 */

 struct question {
   struct question * child;
   char * topic;
   // This needs to be the dawg
 };

/*
 * Initilize question hash
 */
struct question ** question_init(int n_topics);
