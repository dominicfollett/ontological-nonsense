#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>
#include <string.h>

FILE * file_handle = NULL;
char * line = NULL;
size_t len  = 0;

struct sub_topics_list * list_index;

struct sub_topics_list {
  char * topic;
  struct sub_topics_list * topic_parent;
  struct sub_topics_list * topic_child;
};

static void clean_list() {
  while(list_index->topic_parent) {
    if (list_index->topic) {
      free(list_index->topic);
    }
    list_index = list_index->topic_parent;
    if (list_index->topic_child) {
      free(list_index->topic_child);
    }
  }
}

static void free_list() {
  clean_list(list_index);
  free(list_index);
}

static void add_to_list(char * token) {
  struct sub_topics_list * item = (struct sub_topics_list *) malloc(sizeof(struct sub_topics_list));
  item->topic = (char *) malloc(strlen(token) + 1);
  strcpy(item->topic, token);
  item->topic_parent = list_index;
  list_index->topic_child = item;
  list_index = item;
}

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

static void copy_string(char * src, char ** dest){
  size_t length = strlen(src);
  *dest = (char *) malloc(length + 1);
  if (!*dest) {
    perror("During malloc:");
  }
  memcpy(*dest, src, length + 1);
}

static void get_sub_topics_list(char *topics, char * topic){
  char *subtree;
  if((subtree = strstr(topics, topic)) != NULL) {
    char * token;
    char * buffer = NULL;
    int p_to_close = 0;

    clean_list();

    copy_string(subtree, &buffer);
    if((token = strtok(buffer, " ")) != NULL) {
      add_to_list(token);
    }

    while ((token = strtok(NULL, " ")) != NULL) {
      // Exit if p_to_close == 0
      switch(*token) {
        case '(' :
          p_to_close+=1;
          break;
        case ')' :
          p_to_close-=1;
          break;
        default:
          if (p_to_close > 0) {
            add_to_list(token);
          }
      }
      if (p_to_close == 0) {
        break;
      }
    }
    free(buffer);
  }
}

int main(int argc, char* argv[]){
  char * ontology;
  int m_questions, k_queries;

  if (argv[1] == NULL){
    fprintf(stderr,"No work load file specified\n");
    exit(EXIT_FAILURE);
  }

  get_line(argv[1]);
  list_index = (struct sub_topics_list *) malloc(sizeof(struct sub_topics_list));
  memset((void *) list_index, 0, sizeof(struct sub_topics_list));

  get_line(NULL);
  copy_string(line, &ontology);

  get_line(NULL);
  m_questions = atoi(line);

  //struct timespec tstart={0,0}, tend={0,0};
  //clock_gettime(CLOCK_MONOTONIC, &tstart);

  get_sub_topics_list(ontology, "Birds");

  get_sub_topics_list(ontology, "Dogs");


  //clock_gettime(CLOCK_MONOTONIC, &tend);
  //printf("some_long_computation took about %.5f seconds\n",
  //       ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) -
  //       ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));

  free(line);
  free_list();
  free(ontology);
  fclose(file_handle);
  return 0;
}
