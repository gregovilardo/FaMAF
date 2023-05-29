#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct _s_stack {
  struct _s_stack *next;
  stack_elem elem;
  unsigned int size;
};

stack stack_empty() {
  stack s = malloc(sizeof(struct _s_stack));
  s->size = 0;
  return s;
}

stack stack_push(stack s, stack_elem e) {
  assert(s != NULL);
  stack p;
  p = malloc(sizeof(stack));
  p->elem = e;
  p->next = s;
  p->size= s->size+1;
  return p;
}

stack stack_pop(stack s) {
  assert(s != NULL);
  assert(s->size != 0);
  stack p;
  p = s;
  s = s->next;
  (s->size)--;
  free(p);
  p = NULL;
  return s;
}

unsigned int stack_size(stack s) { return s->size; }

stack_elem stack_top(stack s) {
  assert(s != NULL);
  assert(s->size != 0);
  return s->elem;
}

bool stack_is_empty(stack s) {
  assert(s != NULL);
  return s->size == 0;
}

stack_elem *stack_to_array(stack s) {
  assert(s != NULL);
  stack_elem *a = calloc(stack_size(s), sizeof(stack_elem));
  for (int i = stack_size(s); i >= 0; i--) {
    a[i] = s->elem;
    s = s->next;
  }
  return a;
}

/**
 * @brief Destroys the stack
 * @param s A stack
 * @note All memory resources are freed
 */
stack stack_destroy(stack s) {
  if (s->size == 0) {
    free(s);
  } else {
    stack p = s;
    while (s != NULL) {
      if (s->next != NULL) {
        s = s->next;
      }
      free(p);
      p = s;
    }
  }
  s = NULL;
  return s;
}
