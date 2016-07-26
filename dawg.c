#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dawg.h"

static char * alphabet[51];

struct dawg * dawg_init() {
  struct dawg * dg = (struct dawg *) malloc(sizeof(struct dawg));
  memset(dg, 0, sizeof(struct dawg));
  return dg;
}

struct dawg ** dawg_init_array() {
  struct dawg ** da = malloc(sizeof(struct dawg *));
  memset(da, 0, sizeof(struct dawg *));
  return da;
}

void chop_letter(char ** word, char * c){
  *c = ' ';
  while(*c == ' ') {
    *c = *word[0];
    (*word)++;
  }
}

int dawg_fetch(struct dawg ** good_dawg, char * query) {
  int i = 0;
  char c[] = "\0";

  chop_letter(&query, c);

  if (strcmp(query, "\n") == 0) {
    return 1;
  }

  while(good_dawg[i]) {
      if (strcmp(query, "\n") == 0) {
        return 1; // return the value stored at the node.
      }
      if ((strcmp(good_dawg[i]->letter,c) == 0)) {
        if (good_dawg[i]->pups) {
          return dawg_fetch(good_dawg[i]->pups, query);
        }
    }
    i++;
  }
  return 0;
}

struct dawg ** dawg_bury(struct dawg ** dawg_array, char * question) {
  //struct dawg ** dawg_array = *good_dawg;
  int i = 0;
  char c[] = "\0";

  if (strcmp(question, "\n") == 0) {
    return dawg_array;
  }

  chop_letter(&question, c);

  while(1){
    if((dawg_array[i]) && (strcmp(dawg_array[i]->letter,c) == 0) ){
      dawg_bury(dawg_array[i]->pups, question);
      return dawg_array;
    }else{

      if (!dawg_array[i]) { // TODO need to check if the char exists as well

        dawg_array[i] = dawg_init();
        dawg_array[i]->letter = dawg_index(c);
        dawg_array[i]->pups = dawg_init_array();
        // resize

        if(!(dawg_array = (struct dawg **) realloc((void *) dawg_array, (2+i) * sizeof(struct dawg *)))) {
          perror("Error: ");
        }
        memset(&dawg_array[i + 1], 0, sizeof(struct dawg *));

        dawg_array[i]->pups = dawg_bury(dawg_array[i]->pups, question);
        // perhaps return the pointer of the newly allocated dawg_array
        return dawg_array;
      }
      i++;
    }
  }
  return dawg_array;
}

void dawg_demolish(struct dawg ** good_dawg) {
  int i = 0;
  while(1) {
    if(good_dawg[i]) {
      dawg_demolish(good_dawg[i]->pups);
      free(good_dawg[i]->pups);
      free(good_dawg[i]);
    }else{
      return;
    }
    i++;
  }
}

void dawg_cleanup() {
  int i = 50;
  while(i >=0 ) {
    if(alphabet[i]) {
      free(alphabet[i]);
    }
    i--;
  }
}

void alpha_check(int i, const char * c) {
  if (!alphabet[i]){
    alphabet[i] = malloc(2*sizeof(char));
    memset(alphabet[i], 0, sizeof(char));
    strcpy(alphabet[i], c);
  }
}

char * dawg_index(char * letter) {
  switch (*letter) {
    case 'A' :
      alpha_check(0,"A");
      return alphabet[0];
    case 'B' :
      alpha_check(1,"B");
      return alphabet[1];
    case 'C' :
      alpha_check(2,"C");
      return alphabet[2];
    case 'D' :
      alpha_check(3,"D");
      return alphabet[3];
    case 'E' :
      alpha_check(4,"E");
      return alphabet[4];
    case 'F' :
      alpha_check(5,"F");
      return alphabet[5];
    case 'G' :
      alpha_check(6,"G");
      return alphabet[6];
    case 'H' :
      alpha_check(7,"H");
      return alphabet[7];
    case 'I' :
      alpha_check(8,"I");
      return alphabet[8];
    case 'J' :
      alpha_check(9,"J");
      return alphabet[9];
    case 'K' :
      alpha_check(10,"K");
      return alphabet[10];
    case 'L' :
      alpha_check(11,"L");
      return alphabet[11];
    case 'M' :
      alpha_check(12,"M");
      return alphabet[12];
    case 'N' :
      alpha_check(13,"N");
      return alphabet[13];
    case 'O' :
      alpha_check(14,"O");
      return alphabet[14];
    case 'P' :
      alpha_check(15,"P");
      return alphabet[15];
    case 'Q' :
      alpha_check(16,"Q");
      return alphabet[16];
    case 'R' :
      alpha_check(17,"R");
      return alphabet[17];
    case 'S' :
      alpha_check(18,"S");
      return alphabet[18];
    case 'T' :
      alpha_check(19,"T");
      return alphabet[19];
    case 'U' :
      alpha_check(20,"U");
      return alphabet[20];
    case 'V' :
      alpha_check(21,"V");
      return alphabet[21];
    case 'W' :
      alpha_check(22,"W");
      return alphabet[22];
    case 'X' :
      alpha_check(23,"X");
      return alphabet[23];
    case 'Y' :
      alpha_check(24,"Y");
      return alphabet[24];
    case 'Z' :
      alpha_check(25,"Z");
      return alphabet[25];
    case 'a' :
      alpha_check(26,"a");
      return alphabet[26];
    case 'b' :
      alpha_check(27,"b");
      return alphabet[27];
    case 'c' :
      alpha_check(28,"c");
      return alphabet[28];
    case 'd' :
      alpha_check(29,"d");
      return alphabet[29];
    case 'e' :
      alpha_check(30,"e");
      return alphabet[30];
    case 'f' :
      alpha_check(31,"f");
      return alphabet[31];
    case 'g' :
      alpha_check(32,"g");
      return alphabet[32];
    case 'h' :
      alpha_check(33,"h");
      return alphabet[33];
    case 'i' :
      alpha_check(34,"i");
      return alphabet[34];
    case 'j' :
      alpha_check(35,"j");
      return alphabet[35];
    case 'k' :
      alpha_check(36,"k");
      return alphabet[36];
    case 'l' :
      alpha_check(37,"l");
      return alphabet[37];
    case 'm' :
      alpha_check(38,"m");
      return alphabet[38];
    case 'n' :
      alpha_check(39,"n");
      return alphabet[39];
    case 'o' :
      alpha_check(40,"o");
      return alphabet[40];
    case 'p' :
      alpha_check(41,"p");
      return alphabet[41];
    case 'q' :
      alpha_check(42,"q");
      return alphabet[42];
    case 'r' :
      alpha_check(43,"r");
      return alphabet[43];
    case 's' :
      alpha_check(44,"s");
      return alphabet[44];
    case 't' :
      alpha_check(45,"t");
      return alphabet[45];
    case 'u' :
      alpha_check(46,"u");
      return alphabet[46];
    case 'v' :
      alpha_check(47,"v");
      return alphabet[47];
    case 'w' :
      alpha_check(48,"w");
      return alphabet[48];
    case 'x' :
      alpha_check(49,"x");
      return alphabet[49];
    case 'y' :
      alpha_check(50,"y");
      return alphabet[50];
    case 'z' :
      alpha_check(51,"z");
      return alphabet[51];
    default :
      return NULL;
  }
}
