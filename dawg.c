#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dawg.h"

static char * alphabet[26];

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

void dawg_bury(struct dawg *** good_dawg, char * question) {
  struct dawg ** dawg_array = *good_dawg;
  int i = -1;
  char c[] = "\0";
  chop_letter(&question, c);
  printf("%s\n", c);
  while(i++){
    return;
    if((dawg_array[i]) && (strcmp(dawg_array[i]->letter,c) == 0) ){
        // fine, get child dawg array
      dawg_bury(&(dawg_array[i]->pups), question);
      return;
    }else{
      if (!dawg_array[i]) {
        dawg_array[i] = dawg_init();
        dawg_array[i]->letter = dawg_index(c);
        dawg_array[i]->pups = dawg_init_array();
        dawg_array[i]->both_cases;
        // resize
        dawg_array = (struct dawg **) realloc((void *) dawg_array, (i+2) * sizeof(struct dawg *));
        //printf("%s\n", dawg_array[i]->letter);
        dawg_bury(&(dawg_array[i]->pups), question);
        return;
      }
      return;
    }
  }
}

void alpha_check(int i, const char * c) {
  if (!alphabet[i]){
    alphabet[i] = malloc(sizeof(char));
    memset(alphabet[i], 0, sizeof(char));
    memcpy(alphabet[i], c, sizeof(char));
  }
}

char * dawg_index(char * letter) {
  switch (*letter) {
    case 'A' :
      alpha_check(0,"A");
      return alphabet[0];
    case 'a' :
      alpha_check(0,"a");
      return alphabet[0];
    case 'B' :
      alpha_check(1,"B");
      return alphabet[1];
    case 'b' :
      alpha_check(1,"b");
      return alphabet[1];
    case 'C' :
      alpha_check(2,"C");
      return alphabet[2];
    case 'c' :
      alpha_check(2,"c");
      return alphabet[2];
    case 'D' :
      alpha_check(3,"D");
      return alphabet[3];
    case 'd' :
      alpha_check(3,"d");
      return alphabet[3];
    case 'E' :
      alpha_check(4,"E");
      return alphabet[4];
    case 'e' :
      alpha_check(4,"e");
      return alphabet[4];
    case 'F' :
      alpha_check(5,"F");
      return alphabet[5];
    case 'f' :
      alpha_check(5,"f");
      return alphabet[5];
    case 'G' :
      alpha_check(6,"G");
      return alphabet[6];
    case 'g' :
      alpha_check(6,"g");
      return alphabet[6];
    case 'H' :
      alpha_check(7,"H");
      return alphabet[7];
    case 'h' :
      alpha_check(7,"h");
      return alphabet[7];
    case 'I' :
      alpha_check(8,"I");
      return alphabet[8];
    case 'i' :
      alpha_check(8,"i");
      return alphabet[8];
    case 'J' :
      alpha_check(9,"J");
      return alphabet[9];
    case 'j' :
      alpha_check(9,"j");
      return alphabet[9];
    case 'K' :
      alpha_check(10,"K");
      return alphabet[10];
    case 'k' :
      alpha_check(10,"k");
      return alphabet[10];
    case 'L' :
      alpha_check(11,"L");
      return alphabet[11];
    case 'l' :
      alpha_check(11,"l");
      return alphabet[11];
    case 'M' :
      alpha_check(12,"M");
      return alphabet[12];
    case 'm' :
      alpha_check(12,"m");
      return alphabet[12];
    case 'N' :
      alpha_check(13,"N");
      return alphabet[13];
    case 'n' :
      alpha_check(13,"n");
      return alphabet[13];
    case 'O' :
      alpha_check(14,"O");
      return alphabet[14];
    case 'o' :
      alpha_check(14,"o");
      return alphabet[14];
    case 'P' :
      alpha_check(15,"P");
      return alphabet[15];
    case 'p' :
      alpha_check(15,"p");
      return alphabet[15];
    case 'Q' :
      alpha_check(16,"Q");
      return alphabet[16];
    case 'q' :
      alpha_check(16,"q");
      return alphabet[16];
    case 'R' :
      alpha_check(17,"R");
      return alphabet[17];
    case 'r' :
      alpha_check(17,"r");
      return alphabet[17];
    case 'S' :
      alpha_check(18,"S");
      return alphabet[18];
    case 's' :
      alpha_check(18,"s");
      return alphabet[18];
    case 'T' :
      alpha_check(19,"T");
      return alphabet[19];
    case 't' :
      alpha_check(19,"t");
      return alphabet[19];
    case 'U' :
      alpha_check(20,"U");
      return alphabet[20];
    case 'u' :
      alpha_check(20,"u");
      return alphabet[20];
    case 'V' :
      alpha_check(21,"V");
      return alphabet[21];
    case 'v' :
      alpha_check(21,"v");
      return alphabet[21];
    case 'W' :
      alpha_check(22,"W");
      return alphabet[22];
    case 'w' :
      alpha_check(22,"w");
      return alphabet[22];
    case 'X' :
      alpha_check(23,"X");
      return alphabet[23];
    case 'x' :
      alpha_check(23,"x");
      return alphabet[23];
    case 'Y' :
      alpha_check(24,"Y");
      return alphabet[24];
    case 'y' :
      alpha_check(24,"y");
      return alphabet[24];
    case 'Z' :
      alpha_check(25,"Z");
      return alphabet[25];
    case 'z' :
      alpha_check(25,"z");
      return alphabet[25];
    default :
      return NULL;
  }
}
