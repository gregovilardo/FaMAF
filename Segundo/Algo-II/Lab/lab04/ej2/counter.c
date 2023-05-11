#include <stdbool.h>
#include <stdlib.h>

#include "counter.h"

struct _counter {
    unsigned int count;
};

counter counter_init(void) {
  counter c = NULL;
  c = malloc(sizeof(counter));
  c->count = 0;
  return c;
/*
    Needs implementation.
*/
}

void counter_inc(counter c) {
  c->count += 1;
/*
    Needs implementation.
*/
}

bool counter_is_init(counter c) {
  return c == 0;
/*
    Needs implementation.
*/
}

void counter_dec(counter c) {
  c->count -= 1;
/*
    Needs implementation.
*/
}

counter counter_copy(counter c) {
  counter cc = NULL;
  cc = malloc(sizeof(counter));
  cc->count = c->count;
  return cc;
/*
    Needs implementation.
*/
}

void counter_destroy(counter c) {
  free(c);
  c = NULL;
/*
   Needs implementation.
*/
}
