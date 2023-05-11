#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int elem;
  struct Node *next;
} Node;

typedef Node *List;

List empty() {
//  Node *l;
  List l;
  l = NULL;
  return l;
}

void addl(int e, List *l) {
  List p;
  // List p = &node;
  p = (List)malloc(sizeof(List));
  // p = (struct Node*)malloc(p) ;
  p->elem = e;
  p->next = *l;
  *l = p;
}

void concat(List *l, List l0) {
  List p;
  p = *l;
  while (p->next != NULL) {
    p = p->next;
  }
  p->next = l0;
}

void tail(List *l) {
  List p;
  p = *l;
  *l = (*l)->next;
  free(p);
}


int head(List l) {
  return l->elem;
}

bool is_empty(List l) {
  return l == NULL;
}

void concat_r(List *l, List l0){
  if (is_empty(*l)) {
    *l = l0;
  } else {
    int tmp;
    tmp = head(*l);
    tail(&(*l));
    concat(&(*l), l0);
    addl(tmp, &(*l));
  }
}

void take(List *l, int n) {
  List p;
  p = *l;
  if (n == 0) {
    //destroy(l);
    *l = NULL;
  } else {
    for (int i = 1; i <= n - 1; i++) {
      *l = (*l)->next;
    }
    // destroy(*l->next);
    (*l)->next = NULL;
    *l = p;
  }
}

void drop(List *l, int n) {
  List p;
  for (int i = 1; i <= n; i++) {
    p = *l;
    *l = (*l)->next;
    free(p);
  }
}

void pop(List *l) {
  List p;
  p = *l;
  while (p->next != NULL) {
    p = p->next;
  }
  free(p);
  p = NULL;
}

/*List copy_list(List l1) {
  List p, q, l2;
  p = (List)malloc(sizeof(List));
  p->elem = l1->elem;
  p->next = l1->next;
  l2 = p;
  while (p->next != NULL) {
    q = (List)malloc(sizeof(List));
    p = p->next;
    q->elem = p->elem;
    q->next = p->next;
  }
  return l2;
}*/

void addr(List *l, int e) {
  List q;
  q = (List)malloc(sizeof(List));
  q->elem = e;
  q->next = NULL;
  if (is_empty(*l)) {
      *l = q;
    } else {
      List p = *l;
      while(p->next != NULL) {
        p = p->next;
      }
      p->next = q;
  }
}

List copy_list(List l1) {
  List p, l2;
  l2 = empty();
  if (is_empty(l1)) {
    l2 = empty();
  } else {
    p = l1;
    addr(&l2, p->elem);
    while(p->next != NULL) {
      p = p->next;
      addr(&l2, p->elem);
    }
  }
  return l2;
}

List copy_list_r(List l1) {
  List l2;
  if (is_empty(l1)) {
    l2 = empty();
  } else {
    l2 = (List)malloc(sizeof(List));
    l2->elem = l1->elem;
    l2->next = copy_list_r(l1);
  }
  return l2;
}

void p(List *l) {
  List a, b;
  a = *l;
  while(a != NULL){
    b = a->next;
    if(b!=NULL){
      a->next = b->next;
      free(b);
    }
    a = a->next;
  }
}

int main() {
  List l1 = empty();
//  List l2 = empty();
//  addl(10, &l2);
  addr(&l1, 2);
  addr(&l1, 3);
  addr(&l1, 4);
  addr(&l1, 5);
  addr(&l1, 6);
  addl(10, &l1);
  addl(10, &l1);
  List l2 = copy_list(l1);
  addr(&l2, 1);
//  concat(&l2, l1);
//  p(&l1);
//  pop(&l1);  
  printf("%d", l1->elem);
  while(l2 != NULL) {
    printf("%d\n", l2->elem);
    l2 = l2->next;
  }
  return 0;
}
