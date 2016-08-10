#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
 * Simple Flat Tree parser
 */

struct sub_topics_list
{
	char *topic;
	struct sub_topics_list *topic_parent;
	struct sub_topics_list *topic_child;
};

/*
 * Initialises and returns the topic ontology linked list
 */
struct sub_topics_list *parser_init(void);

/*
 * Simple helper for copying strings.
 */
void copy_string(char *src, char **dest);

/*
 * Populates linked list with the subtree of the ontology, including parent.
 * Takes the entire topic flat tree, and the parent key.
 */
void parser_get_sub_topics_list(struct sub_topics_list **list_index,
								char *topics, char *topic);

/*
 * Clean up all allocated memory.
 */
void parser_destroy(struct sub_topics_list **list_index);

void copy_string(char *src, char **dest)
{
	size_t length = strlen(src);
	*dest = (char *)malloc(length + 1);
	if (!*dest)
	{
		perror("During malloc:");
	}
	memcpy(*dest, src, length + 1);
}

struct sub_topics_list *parser_init(void)
{
	struct sub_topics_list *list_index =
		(struct sub_topics_list *)malloc(sizeof(struct sub_topics_list));
	memset((void *)list_index, 0, sizeof(struct sub_topics_list));
	return list_index;
}

static void clean_list(struct sub_topics_list **list_index)
{
	while ((*list_index)->topic_parent)
	{
		if ((*list_index)->topic)
		{
			free((*list_index)->topic);
		}
		*list_index = (*list_index)->topic_parent;
		if ((*list_index)->topic_child)
		{
			free((*list_index)->topic_child);
		}
	}
}

void parser_destroy(struct sub_topics_list **list_index)
{
	clean_list(list_index);
	free(*list_index);
}

static void add_to_list(struct sub_topics_list **list_index, char *token)
{
	struct sub_topics_list *item =
		(struct sub_topics_list *)malloc(sizeof(struct sub_topics_list));
	item->topic = (char *)malloc(strlen(token) + 1);
	strcpy(item->topic, token);
	item->topic_child = NULL;
	item->topic_parent = *list_index;
	(*list_index)->topic_child = item;
	*list_index = item;
}

void parser_get_sub_topics_list(struct sub_topics_list **list_index,
								char *topics, char *topic)
{
	char *subtree;
	if ((subtree = strstr(topics, topic)) != NULL)
	{
		char *token;
		char *buffer = NULL;
		int p_to_close = 0;

		clean_list(list_index);

		copy_string(subtree, &buffer);
		if ((token = strtok(buffer, " ")) != NULL)
		{
			add_to_list(list_index, token);
		}

		while ((token = strtok(NULL, " ")) != NULL)
		{
			switch (*token)
			{
			case '(':
				p_to_close += 1;
				break;
			case ')':
				p_to_close -= 1;
				break;
			default:
				if (p_to_close > 0)
				{
					add_to_list(list_index, token);
				}
			}
			if (p_to_close == 0)
			{
				break;
			}
		}
		free(buffer);
	}
}

/*
 * Directed Acyclic Word Graph
 */

struct dawg
{
	char *letter;
	struct dawg **pups;
	int count;
};

/*
 * Creates and initialises a dawg element.
 */
struct dawg *dawg_init(void);

/*
 * Check if we're at the end of the string
 */
int peeks(char **word);

/*
 * Initialize an array of dawg with one item
 */
struct dawg **dawg_init_array(void);

/*
 * Remove a letter from the question or query
 */
void chop_letter(char **word, char *c);

/*
 * Insert string elements into dawg.
 */
struct dawg **dawg_bury(struct dawg **good_dawg, char *question);

/*
 * Check if the given string exists.
 */
int dawg_fetch(struct dawg **good_dawg, char *query);

/*
 * Free all memory associated with this dawg.
 */
void dawg_demolish(struct dawg **good_dawg);

/*
 * Returns a pointer to the memory allocated letter
 */
char *dawg_index(char *letter);


static char *alphabet[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
	"K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
	"U", "V", "W", "X", "Y", "Z", "a", "b", "c", "d",
	"e", "f", "g", "h", "i", "j", "k", "l", "m", "n",
	"o", "p", "q", "r", "s", "t", "u", "v", "w", "x",
	"y", "z"
};

struct dawg *dawg_init(void)
{
	struct dawg *dg = (struct dawg *)malloc(sizeof(struct dawg));
	memset(dg, 0, sizeof(struct dawg));
	dg->count = 1;
	return dg;
}

struct dawg **dawg_init_array(void)
{
	struct dawg **da = malloc(sizeof(struct dawg *));
	memset(da, 0, sizeof(struct dawg *));
	return da;
}

int peeks(char **word)
{
	char c[] = " \0";
	int delta;
	delta = 0;

	while ((' ' == *c) || ('\n' == *c) || ('?' == *c))
	{
		*c = *word[0];
		(*word)++;
		delta++;
	}
	if (*c == '\0')
	{
		return 1;
	}
	*word -= delta;
	return 0;
}

void chop_letter(char **word, char *c)
{
	*c = ' ';
	while ((' ' == *c) || ('\n' == *c) || ('?' == *c))
	{
		*c = *word[0];
		(*word)++;
	}
}

int dawg_fetch(struct dawg **good_dawg, char *query)
{
	int i, no_more_letters;
	char c[] = "\0";

	i = 0;
	chop_letter(&query, c);
	no_more_letters = peeks(&query);

	while (good_dawg[i] != NULL)
	{
		if (0 == (strcmp(good_dawg[i]->letter, c)) && !no_more_letters)
		{
			return dawg_fetch(good_dawg[i]->pups, query);
		}
		else if (0 == (strcmp(good_dawg[i]->letter, c)) && no_more_letters)
		{
			return good_dawg[i]->count;
		}
		i++;
	}
	return 0;
}

struct dawg **dawg_bury(struct dawg **dawg_array, char *question)
{
	int i;

	char c[] = "\0";

	i = 0;
	chop_letter(&question, c);

	if (0 == strcmp(c, "\0"))
	{
		return dawg_array;
	}

	while (1)
	{
		if ((dawg_array[i]) && (0 == strcmp(dawg_array[i]->letter, c)))
		{
			dawg_array[i]->count++;
			dawg_array[i]->pups = dawg_bury(dawg_array[i]->pups, question);
			return dawg_array;
		}
		else
		{
			if (!dawg_array[i])
			{

				dawg_array[i] = dawg_init();
				dawg_array[i]->letter = dawg_index(c);
				dawg_array[i]->pups = dawg_init_array();

				/* Resize the array */
				dawg_array =
					realloc(dawg_array, (i + 3) * sizeof(struct dawg *));

				if (!dawg_array)
				{
					perror("Error: ");
					exit(-1);
				}

				memset(dawg_array + i + 1, 0, sizeof(struct dawg *));
				dawg_array[i]->pups = dawg_bury(dawg_array[i]->pups, question);
				return dawg_array;
			}
			i++;
		}
	}
}

void dawg_demolish(struct dawg **good_dawg)
{
	int i = 0;
	while (good_dawg[i])
	{
		dawg_demolish(good_dawg[i]->pups);
		free(good_dawg[i]->pups);
		free(good_dawg[i]);
		i++;
	}
	return;
}

char *dawg_index(char *letter)
{
	switch (*letter)
	{
	case 'A':
		return alphabet[0];
	case 'B':
		return alphabet[1];
	case 'C':
		return alphabet[2];
	case 'D':
		return alphabet[3];
	case 'E':
		return alphabet[4];
	case 'F':
		return alphabet[5];
	case 'G':
		return alphabet[6];
	case 'H':
		return alphabet[7];
	case 'I':
		return alphabet[8];
	case 'J':
		return alphabet[9];
	case 'K':
		return alphabet[10];
	case 'L':
		return alphabet[11];
	case 'M':
		return alphabet[12];
	case 'N':
		return alphabet[13];
	case 'O':
		return alphabet[14];
	case 'P':
		return alphabet[15];
	case 'Q':
		return alphabet[16];
	case 'R':
		return alphabet[17];
	case 'S':
		return alphabet[18];
	case 'T':
		return alphabet[19];
	case 'U':
		return alphabet[20];
	case 'V':
		return alphabet[21];
	case 'W':
		return alphabet[22];
	case 'X':
		return alphabet[23];
	case 'Y':
		return alphabet[24];
	case 'Z':
		return alphabet[25];
	case 'a':
		return alphabet[26];
	case 'b':
		return alphabet[27];
	case 'c':
		return alphabet[28];
	case 'd':
		return alphabet[29];
	case 'e':
		return alphabet[30];
	case 'f':
		return alphabet[31];
	case 'g':
		return alphabet[32];
	case 'h':
		return alphabet[33];
	case 'i':
		return alphabet[34];
	case 'j':
		return alphabet[35];
	case 'k':
		return alphabet[36];
	case 'l':
		return alphabet[37];
	case 'm':
		return alphabet[38];
	case 'n':
		return alphabet[39];
	case 'o':
		return alphabet[40];
	case 'p':
		return alphabet[41];
	case 'q':
		return alphabet[42];
	case 'r':
		return alphabet[43];
	case 's':
		return alphabet[44];
	case 't':
		return alphabet[45];
	case 'u':
		return alphabet[46];
	case 'v':
		return alphabet[47];
	case 'w':
		return alphabet[48];
	case 'x':
		return alphabet[49];
	case 'y':
		return alphabet[50];
	case 'z':
		return alphabet[51];
	default:
		return NULL;
	}
}

/*
 * Hash map holding question topics
 */

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
			*q_tmp = (struct question *)malloc(sizeof(struct question));
			memset((void *)*q_tmp, 0, sizeof(struct question));
			copy_string(token, &((*q_tmp)->topic));
			(*q_tmp)->dawg_array = dawg_init_array();
			(*q_tmp)->dawg_array = dawg_bury((*q_tmp)->dawg_array, line);
			break;
		}
	}
}

/* Prototype declaration */
int get_line(char *workload_path);

FILE *file_handle = NULL;
char *line = NULL;
size_t len = 0;

int get_line(char *workload_path)
{

	if(!workload_path && !file_handle)
	{
		getdelim(&line, &len, '\n',stdin);
		return 0;
	}

	if (!file_handle && workload_path)
	{
		file_handle = fopen(workload_path, "r");
		if (!file_handle)
		{
			fprintf(stderr, "Cannot open workload file %s\n", workload_path);
			exit(EXIT_FAILURE);
		}
	}

	if (file_handle)
	{
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
	return -1;
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

	if (1 == argc)
	{

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
	if (file_handle)
	{
		fclose(file_handle);
	}

	return 0;
}
