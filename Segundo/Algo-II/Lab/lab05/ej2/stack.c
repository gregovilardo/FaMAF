#include "stack.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct _s_stack {
  stack_elem *elems;     // Arreglo de elementos
  unsigned int size;     // Cantidad de elementos en la pila
  unsigned int capacity; // Capacidad actual del arreglo elems
};

stack stack_empty() {
  stack s = malloc(sizeof(struct _s_stack));
  s->elems = NULL;
  s->size = 0;
  s->capacity = 0;
  return s;
}

stack stack_push(stack s, stack_elem e) {
  assert(s != NULL);
  assert(s->size <= s->capacity);
  if (s->size == s->capacity) {
    s->capacity = s->capacity == 0 ? 1 : s->capacity * 2;
    s->elems = realloc(s->elems, sizeof(stack_elem) * s->capacity);
  }
  (s->elems)[s->size] = e;
  s->size = s->size + 1;
  return s;
}

stack stack_pop(stack s) {
  s->size--;
  return s;
}

unsigned int stack_size(stack s) {
  unsigned int size = s->size;
  return size;
}

stack_elem stack_top(stack s) {
  stack_elem t = s->elems[s->size - 1];
  return t;
}

bool stack_is_empty(stack s) { return s->size == 0; }

stack_elem *stack_to_array(stack s) {
  assert(s!=NULL);
  stack_elem *a = NULL;
  if (s->size) {
    a = calloc(stack_size(s), sizeof(stack_elem));
    memcpy(a, s->elems, stack_size(s)*sizeof(stack_elem));
  }
  
  //WHY THIS DONT WORK??
  // stack_elem *a = calloc(stack_size(s), sizeof(stack_elem));
  // for (int i = s->size - 1; i >= 0; i--) {
  //   a[i] = s->elems[i];
  // }
  return a;
}


stack stack_destroy(stack s) {
  free(s->elems);
  free(s);
  s = NULL;
  return s;
}
