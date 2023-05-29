#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct _s_stack {
  struct _s_stack *next;
  stack_elem elem;
};

stack stack_empty() {
  stack s = NULL;
  return s;
}

stack stack_push(stack s, stack_elem e) {
  stack p;
  p = malloc(sizeof(stack));
  p->elem = e;
  p->next = s;
  return p;
}

stack stack_pop(stack s) {
  assert(s!=NULL);
  stack p;
  p = s;
  s = s->next;
  free(p);
  p = NULL;
  return s;
}

unsigned int stack_size(stack s) {
  unsigned int i = 0;
    while (s != NULL) {
      i += 1;
      s = s->next;
    }
    return i;
}

stack_elem stack_top(stack s) {
  assert(s != NULL);
  return s->elem;
}

bool stack_is_empty(stack s) { return s == NULL; }

stack_elem *stack_to_array(stack s) {
  if (s == NULL) {
    return NULL;
  }
  stack_elem *a = calloc(stack_size(s), sizeof(stack_elem));
  stack p = s;
  unsigned int i = stack_size(s) - 1;
  while (p != NULL) {
    a[i] = p->elem;
    p = p->next;
    i--;
  }
  return a;
}

/**
 * @brief Destroys the stack
 * @param s A stack
 * @note All memory resources are freed
 */
stack stack_destroy(stack s) {
  stack p = s;
  while (s != NULL) {
    if (s->next != NULL) {
      s = s->next;
    }
    free(p);
    p = s;
  }
  s = NULL;
  return s;
}
