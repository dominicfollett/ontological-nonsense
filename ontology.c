#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "question.h"

/* Prototype declaration */
int get_line(char *workload_path);

FILE *file_handle = NULL;
char *line = NULL;
size_t len = 0;

int get_line(char *workload_path)
{
	if (!file_handle)
	{
		file_handle = fopen(workload_path, "r");
		if (!file_handle)
		{
			fprintf(stderr, "cannot open workload file %s\n", workload_path);
			exit(EXIT_FAILURE);
		}
	}
	if (getline(&line, &len, file_handle) != -1)
	{
		return 0;
	}
	else
	{
		free(line);
		fclose(file_handle);
		return -1;
	}
}

int main(int argc, char *argv[])
{
	char *ontology;
	int m_questions, k_queries, i, score;
	struct sub_topics_list *list;
	struct question **questions_hash;
	struct sub_topics_list *tmp_list;
	char *token;
	char *tmp_str;

	if (argv[argc - 1] == NULL)
	{
		fprintf(stderr, "No work load file specified\n");
		exit(EXIT_FAILURE);
	}

	list = parser_init();
	get_line(argv[1]);

	get_line(NULL);
	copy_string(line, &ontology);

	get_line(NULL);
	m_questions = atoi(line);

	questions_hash = question_init(m_questions);
	i = m_questions;

	/* Insert questions */
	while (i > 0)
	{
		get_line(NULL);
		token = strtok(line, ":");
		question_insert(&questions_hash, token, m_questions,
						strtok(NULL, ":"));
		i--;
	}

	get_line(NULL);
	k_queries = atoi(line);

	while (k_queries > 0)
	{
		get_line(NULL);
		tmp_str = (char *)malloc(strlen(line) + 1);
		strcpy(tmp_str, line);
		token = strtok(tmp_str, " ");

		parser_get_sub_topics_list(&list, ontology, token);
		line += strlen(token) + 1;

		tmp_list = list;

		score = 0;
		while (tmp_list->topic_parent)
		{
			score +=
				question_count(&questions_hash, m_questions, line,
							   tmp_list->topic);
			tmp_list = tmp_list->topic_parent;
		}

		printf("%i\n", score);
		line -= strlen(token) + 1;
		free(tmp_str);
		k_queries--;
	}

	free(line);
	parser_destroy(&list);
	question_destroy(&questions_hash, m_questions);
	free(ontology);
	fclose(file_handle);
	return 0;
}
