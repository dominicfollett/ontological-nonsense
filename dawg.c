#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dawg.h"

static char *alphabet[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
	"K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
	"U", "V", "W", "X", "Y", "Z", "a", "b", "c", "d",
	"e", "f", "g", "h", "i", "j", "k", "l", "m", "n",
	"o", "p", "q", "r", "s", "t", "u", "v", "w", "x",
	"y", "z"
};

struct dawg *dawg_init(void)
{
	struct dawg *dg = malloc(sizeof(struct dawg));
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
