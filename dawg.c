#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dawg.h"

struct dawg * dawg_init() {
  // create 26 separate entry points
  struct dawg * dg = (struct dawg *) malloc(sizeof(struct dawg));
  memset(dg, 0, sizeof(struct dawg));
  return dg;
}

void dawg_bury(struct dawg ** good_dawg, char * question) {
  // Traverse the dawg
}

char * dawg_index(char * letter) {
  switch (*letter) {
    case 'a' :
      return alphabet[0];
    case 'b' :
      return alphabet[1];
    case 'c' :
      return alphabet[2];
    case 'd' :
      return alphabet[3];
    case 'e' :
      return alphabet[4];
    case 'f' :
      return alphabet[5];
    case 'g' :
      return alphabet[6];
    case 'h' :
      return alphabet[7];
    case 'i' :
      return alphabet[8];
    case 'j' :
      return alphabet[9];
    case 'k' :
      return alphabet[10];
    case 'l' :
      return alphabet[11];
    case 'm' :
      return alphabet[12];
    case 'n' :
      return alphabet[13];
    case 'o' :
      return alphabet[14];
    case 'p' :
      return alphabet[15];
    case 'q' :
      return alphabet[16];
    case 'r' :
      return alphabet[17];
    case 's' :
      return alphabet[18];
    case 't' :
      return alphabet[19];
    case 'u' :
      return alphabet[20];
    case 'v' :
      return alphabet[21];
    case 'w' :
      return alphabet[22];
    case 'x' :
      return alphabet[23];
    case 'y' :
      return alphabet[24];
    case 'z' :
      return alphabet[25];
    default :
      return NULL;
  }
}
