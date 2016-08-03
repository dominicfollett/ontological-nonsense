#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>
#include <string.h>
#include "parser.h"

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
