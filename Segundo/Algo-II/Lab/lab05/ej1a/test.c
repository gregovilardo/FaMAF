#include "stack.h"
#include <stdbool.h>
#include <stdio.h>

int main(){
  stack s = stack_empty();
  s = stack_push(s, 1);
  s = stack_pop(s);
  s = stack_push(s, 2);
  s = stack_pop(s);
  stack_elem *a = stack_to_array(s);
  printf("Is array a from empty stack NULL?: %d\n", a == NULL);
  s = stack_push(s, 5);
  s = stack_push(s, 4);
  s = stack_push(s, 3);
  s = stack_push(s, 2);
  a = stack_to_array(s);
  unsigned int size = stack_size(s);
  bool b = true;
  for (unsigned int i = 0; i < size; i++) {
    b = b && a[i] == stack_top(s);
    s = stack_pop(s);
  }
  printf("Does stack_to_array return the values in right order?: %d", b);
  return 0;
}
