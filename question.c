#include "question.h"
#include "parser.h"				/* copy string */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void question_destroy(struct question ***questions_hash, int m_questions)
{
	struct question **qh = *questions_hash;
	m_questions--;
	while (m_questions >= 0)
	{
		struct question *q_tmp = qh[m_questions];
		if (q_tmp)
		{
			recursive_free(&q_tmp);
		}						/* If not NULL */
		m_questions--;
	}
	free(qh);
}

void recursive_free(struct question **q_tmp)
{
	if ((*q_tmp)->child)
	{
		recursive_free(&((*q_tmp)->child));
	}
	free((*q_tmp)->topic);
	dawg_demolish((*q_tmp)->dawg_array);
	free((*q_tmp)->dawg_array);
	free(*q_tmp);
}

static unsigned long hash(char *str, unsigned long modulo)
{
	unsigned long hash = 5381;
	int c;

	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;	/* hash * 33 + c */

	return hash % modulo;
}

struct question **question_init(int m_questions)
{
	struct question **questions_hash;
	questions_hash = malloc(m_questions * sizeof(struct question *));
	memset((void *)questions_hash, 0, m_questions * sizeof(struct question *));
	return questions_hash;
}

int question_count(struct question ***questions_hash, int m_questions,
				   char *query, char *topic)
{
	struct question **q_tmp;
	int i;

	i = (int)hash(topic, m_questions--);
	q_tmp = &(*questions_hash)[i];

	while (1)
	{
		if (*q_tmp)
		{
			if (0 == strcmp((*q_tmp)->topic, topic))
			{
				return dawg_fetch((*q_tmp)->dawg_array, query);
			}
			else
			{
				q_tmp = &((*q_tmp)->child);
			}
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

void question_insert(struct question ***questions_hash, char *token,
					 int m_questions, char *line)
{
	struct question **q_tmp;
	int i;

	i = (int)hash(token, m_questions--);
	q_tmp = &(*questions_hash)[i];

	while (1)
	{
		if (*q_tmp)
		{
			if (0 == strcmp((*q_tmp)->topic, token))
			{
				(*q_tmp)->dawg_array = dawg_bury((*q_tmp)->dawg_array, line);
				break;
			}
			else
			{
				q_tmp = &((*q_tmp)->child);
			}
		}
		else
		{
			*q_tmp = malloc(sizeof(struct question));
			memset((void *)*q_tmp, 0, sizeof(struct question));
			copy_string(token, &((*q_tmp)->topic));
			(*q_tmp)->dawg_array = dawg_init_array();
			(*q_tmp)->dawg_array = dawg_bury((*q_tmp)->dawg_array, line);
			break;
		}
	}
}
