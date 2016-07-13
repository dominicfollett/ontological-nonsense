#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>
#include <string.h>
#include "parser.h"

FILE * file_handle = NULL;
char * line = NULL;
size_t len  = 0;

struct question {
  struct question * child;
  char * topic;
  // This needs to be the dawg
};

int get_line(char *workload_path){
  if (!file_handle) {
    file_handle = fopen(workload_path, "r");
    if (!file_handle) {
      fprintf(stderr,"cannot open workload file %s\n", workload_path);
      exit(EXIT_FAILURE);
    }
  }
  if(getline(&line, &len, file_handle) != -1){
    return 0;
  }else{
    free(line);
    fclose(file_handle);
    return -1;
  }
}

unsigned long hash(unsigned char *str, unsigned long modulo)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % modulo;
}

int main(int argc, char* argv[]){
  char * ontology;
  int n_topics, m_questions, k_queries, index;
  struct sub_topics_list * list;
  struct question ** questions_hash;

  if (argv[1] == NULL){
    fprintf(stderr,"No work load file specified\n");
    exit(EXIT_FAILURE);
  }

  list = parser_init();

  get_line(argv[1]);
  n_topics = atoi(line);

  questions_hash = malloc(n_topics * sizeof(struct question *));

  for(index=0; index < n_topics; index++) {
    questions_hash[index] = (struct question *) malloc(sizeof(struct question));
  }

  get_line(NULL);
  copy_string(line, &ontology);

  get_line(NULL);
  m_questions = atoi(line);

  while(m_questions > 0) {
    get_line(NULL);
    char * token = strtok(line, " ");
    line = NULL;
    token[strlen(token)-1] = 0;
    //printf("%s\n", token);
    int i = (int) hash(token, n_topics);
    printf("%i\n", i);
    struct question * q_tmp = questions_hash[i];

    while(1) {
      if (strcmp(q_tmp->topic, token) == 0) {
        // do nothing for now
      }else{
        if(!q_tmp->child){
          q_tmp = (struct question *) malloc(sizeof(struct question));
          copy_string(token, &(q_tmp->topic));
          printf("%s\n", q_tmp->topic);
          // Insert dawg
          break;
        }else{
          q_tmp = q_tmp->child;
        }

      }

    }

    m_questions--;
  }

  get_line(NULL);
  k_queries = atoi(line);

  while(k_queries > 0 ) {
    get_line(NULL);
    printf("%s\n", line);
    k_queries--;
  }

  //struct timespec tstart={0,0}, tend={0,0};
  //clock_gettime(CLOCK_MONOTONIC, &tstart);

  get_sub_topics_list(&list, ontology, "Birds");

  get_sub_topics_list(&list, ontology, "Dogs");

  //clock_gettime(CLOCK_MONOTONIC, &tend);
  //printf("some_long_computation took about %.5f seconds\n",
  //       ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) -
  //       ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));

  free(line);
  parser_destroy(&list);

  free(ontology);
  fclose(file_handle);
  return 0;
}
