#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define min(i, j) (((i) < (j)) ? (i) : (j))
#define max(i, j) (((i) > (j)) ? (i) : (j))

enum Direction {Left, Right};
typedef enum Direction Direction;

typedef struct Node2 {
  Direction elem;
  struct Node2 *next;
} Node2;

typedef Node2 *List;

List empty() {
//  Node *l;
  List l;
  l = NULL;
  return l;
}

void addl(Direction e, List *l) {
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












typedef struct Node {
  int elem;
  struct Node *left;
  struct Node *right;
} Node;

typedef Node *Tree;


typedef List Path;

Tree empty_tree() {
  Node *l;
  l = NULL;
  return l;
}

Tree node(Tree tl, int e, Tree tr) {
  Tree t;
  t = (Tree)malloc(sizeof(Tree));
  t->elem = e;
  t->right = tr;
  t->left = tl;
  return t;
}

bool is_empty_tree(Tree t) {
  return t == NULL;
}

int root(Tree t) {
  return t->elem;
}

Tree left(Tree t) {
  return t->left;
}

Tree right(Tree t) {
  return t->right;
}

// void height_rec(Tree t, int *m){
//   if (t != NULL) {
//     printf("elem: %d, m: %d\n", t->elem, *m);
//     int mr, ml;
//     *m = *m+1;
//     mr = *m;
//     ml = *m;
//     height_rec(right(t), &mr);
//     height_rec(left(t), &ml);
//     if (mr > ml) {
//       *m = mr;
//     } else {
//       *m = ml;
//     }
//   }
//   printf("%d\n", *m);
// }
//
// int height(Tree t) {
//   int n = 0;
//   height_rec(t, &n);
//   return n; 
// }

int height(Tree t) {
  if (t == NULL) {
    return 0;
  } else {
    return  1+max(height(right(t)), height(left(t)));
  }
}

Tree direction(Tree t, Direction d) {
  Tree t0;
  if (d==Left) t0 = left(t);
  if (d==Right) t0 = right(t);
  return t0;

}

bool is_path(Tree t, Path p){
  Tree q = t;
  while (p != NULL && !is_empty_tree(q)) {
    q = direction(q, head(p));
    tail(&p);
  }
  return q != NULL;
}

Tree subtree_at(Tree t, Path p) {
  Tree t0 = t;
  while (p!=NULL && !is_empty_tree(t0)) {
    t0 = direction(t0, head(p));
    tail(&p);
  }
  return t0;
}

int elem_at(Tree t, Path p) {
  return subtree_at(t, p)->elem;
}

int main() {
  Path p = empty();
  addr(&p, Right);
  
  Tree t1 = node(NULL, 5, node(NULL, 2, NULL));
  Tree t2 = node(node(NULL, 4, NULL), 6, node(NULL, 1, node(NULL, 0, NULL)));
  Tree t3 = node(t1, 10, t2);
  
  printf("%d\n",is_path(t1, p));
  return 0;
}



