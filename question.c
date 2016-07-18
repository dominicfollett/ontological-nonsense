#include "question.h"
#include "parser.h"  /* copy string */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void question_destroy(struct question ** questions_hash, int n_topics) {
  n_topics--;
  while(n_topics >= 0 ){
    // free the dawg
    struct question * q_tmp = questions_hash[n_topics];
    recursive_free(q_tmp);
    n_topics--;
  }
}

void recursive_free(struct question * q_tmp) {
  if (q_tmp->child) {
    recursive_free(q_tmp->child);
  }else{
    free(q_tmp->topic);
    free(q_tmp);
  }
}

static unsigned long hash(char *str, unsigned long modulo)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % modulo;
}

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

void question_insert(struct question ** questions_hash, char * token, int n_topics, char * line) {
  int i = (int) hash(token, n_topics);
  struct question * q_tmp = questions_hash[i];
  while(1) {
      if (strcmp(q_tmp->topic, token) == 0) {
        // create and or insert to dawg

        break;
      }else{
        if(!q_tmp->child){
          q_tmp->child = (struct question *) malloc(sizeof(struct question));
          q_tmp = q_tmp->child;
          copy_string(token, &(q_tmp->topic));
          printf("%s\n", strtok(line, ":"));
          // create and or insert dawg
          break;
        }else{
          q_tmp = q_tmp->child;
        }
      }
  }
}
