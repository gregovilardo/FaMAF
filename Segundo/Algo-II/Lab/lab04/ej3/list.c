#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct _list {
  list next;
  list_elem elem;
};

list empty() {
  list l = NULL;
  return l;
}

list addl(list_elem e, list l) {
  list q;
  q = malloc(sizeof(list));
  q->elem = e;
  q->next = l;
  l = q;
  return l;
}

list destroy(list l) {
  while (l != NULL) {
    list p = l;
    l = l->next;
    free(p);
  }
  return l;
}

bool is_empty(list l) { return l == NULL; }

list_elem head(list l) {
  assert(!is_empty(l));
  list_elem e = l->elem;
  return e;
}

list tail(list l) {
  assert(!is_empty(l));
  list p = l;
  l = l->next;
  free(p);
  return l;
}

list addr(list l, list_elem e) {
  list p, q;
  p = l;
  q = malloc(sizeof(list));
  q->elem = e;
  q->next = NULL;
  if (is_empty(l)) {
    l = q;
  } else {
    while (p->next != NULL) {
      p = p->next;
    }
    p->next = q;
  }
  return l;
}

unsigned int length(list l) {
  unsigned int i = 0;
  list p = l;
  while (p != NULL) {
    p = p->next;
    i++;
  }
  return i;
}

list concat(list l1, list l2) {
  if (is_empty(l1)) {
    return l2;
  } else {
    list p = l1;
    while (p->next != NULL) {
      p = p->next;
    }
    p->next = l2;
    return l1;
  }
}

list_elem index(list l, unsigned int n) {
  assert(length(l) > n);
  list p = l;
  while (n != 0) {
    p = p->next;
    n--;
  }
  return p->elem;
}

list take(list l, unsigned int n) {
  if (n == 0)
    return NULL;
  else {
    list p = l;
    while (n != 1 && p->next != NULL) {
      p = p->next;
      n--;
    }
    destroy(p->next);
    p->next = NULL;
    return l;
  }
}

list drop(list l, unsigned int n) {
  while (n != 0 && l->next != NULL) {
    list p = l;
    l = l->next;
    free(p);
    n--;
  }
  return l;
}

list copy_list(list l) {
  list lc, p;
  lc = empty();
  if (!is_empty(l)) {
    p = l;
    lc = addr(lc, p->elem);
    while (p->next != NULL) {
      p = p->next;
      lc = addr(lc, p->elem);
    }
  }
  return lc;
}
