#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>
#include <string.h>
#include "parser.h"
#include "question.h"

FILE * file_handle = NULL;
char * line = NULL;
size_t len  = 0;


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

int main(int argc, char* argv[]){
  char * ontology;
  int m_questions, k_queries;
  struct sub_topics_list * list;
  struct question ** questions_hash;

  if (argv[1] == NULL){
    fprintf(stderr,"No work load file specified\n");
    exit(EXIT_FAILURE);
  }

  list = parser_init();
  get_line(argv[1]);

  get_line(NULL);
  copy_string(line, &ontology);

  get_line(NULL);
  m_questions = atoi(line);

  questions_hash = question_init(m_questions);
  int i = m_questions;

  /* Insert questions */
  while(i > 0) {
    get_line(NULL);
    char * token = strtok(line, ":");
    question_insert(&questions_hash, token, m_questions, strtok(NULL, ":"));
    i--;
  }

  get_line(NULL);
  k_queries = atoi(line);

  while(k_queries > 0 ) {
    get_line(NULL);
    char * tmp_str = malloc(strlen(line) +1);
    strcpy(tmp_str, line);
    char * token = strtok(tmp_str, " ");

    //line += strlen(tmp_str) +1;
    parser_get_sub_topics_list(&list, ontology, token);
    line+=strlen(token) +1;

    struct sub_topics_list * tmp_list;
    tmp_list = list;
    int score = 0;

    while (tmp_list->topic_parent) {
      // search for provided string accross multiple topics.
      score += question_count(&questions_hash, m_questions, line, tmp_list->topic);
      tmp_list = tmp_list->topic_parent;
    }

    printf("%s %i\n", token, score);
    line -= strlen(token) +1;
    free(tmp_str);
    k_queries--;
  }

  struct timespec tstart={0,0}, tend={0,0};
  clock_gettime(CLOCK_MONOTONIC, &tstart);

  clock_gettime(CLOCK_MONOTONIC, &tend);
  printf("some_long_computation took about %.5f seconds\n",
         ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) -
         ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));

  free(line);
  parser_destroy(&list);
  question_destroy(&questions_hash, m_questions);
  free(ontology);
  fclose(file_handle);
  return 0;
}
