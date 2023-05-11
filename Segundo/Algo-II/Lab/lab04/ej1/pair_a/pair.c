#include "pair.h"
#include <assert.h>

pair_t pair_new(int x, int y) {
  pair_t p = {
    p.fst = x,
    p.snd = y,
  };
/*   assert(p == pair_new(x, y));  */
  return p;
}

int pair_first(pair_t p){
 /*  assert(typeof(p) == pair_t) */
  return p.fst;

}

int pair_second(pair_t p){
  return p.snd;
}

pair_t pair_swapped(pair_t p){
  int aux = p.fst;
  p.fst = p.snd;
  p.snd = aux;
  return p;
}

pair_t pair_destroy(pair_t p){
  return p; 
}

