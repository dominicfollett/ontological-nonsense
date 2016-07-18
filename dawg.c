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

struct dawg * dawg_index(char * letter, struct dawg ** litter) {
  switch (*letter) {
    case 'a' :
      return litter[0];
    case 'b' :
      return litter[1];
    case 'c' :
      return litter[2];
    case 'd' :
      return litter[3];
    case 'e' :
      return litter[4];
    case 'f' :
      return litter[5];
    case 'g' :
      return litter[6];
    case 'h' :
      return litter[7];
    case 'i' :
      return litter[8];
    case 'j' :
      return litter[9];
    case 'k' :
      return litter[10];
    case 'l' :
      return litter[11];
    case 'm' :
      return litter[12];
    case 'n' :
      return litter[13];
    case 'o' :
      return litter[14];
    case 'p' :
      return litter[15];
    case 'q' :
      return litter[16];
    case 'r' :
      return litter[17];
    case 's' :
      return litter[18];
    case 't' :
      return litter[19];
    case 'u' :
      return litter[20];
    case 'v' :
      return litter[21];
    case 'w' :
      return litter[22];
    case 'x' :
      return litter[23];
    case 'y' :
      return litter[24];
    case 'z' :
      return litter[25];
    default :
      return NULL;
  }
}
