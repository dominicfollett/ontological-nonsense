#include "dawg.h"

struct dawg * dawg_init() {
  struct dawg * dg = (struct dawg *) malloc(sizeof(struct dawg));
  memset(dg, 0, sizeof(struct dawg));
  return dg
}
