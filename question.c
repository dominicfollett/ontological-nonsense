#include "question.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct question ** question_init(int n_topics) {
  struct question ** questions_hash =  malloc(n_topics * sizeof(struct question *));

  n_topics--;
  while (n_topics >= 0) {
    questions_hash[n_topics] = (struct question *) malloc(sizeof(struct question));
    questions_hash[n_topics]->topic = "";
    n_topics--;
  }

  return questions_hash;
}
