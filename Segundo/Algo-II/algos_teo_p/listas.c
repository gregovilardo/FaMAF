#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct Node {
  int elem;
  struct Node *next;
} Node;

typedef Node *List;

List empty() {
  Node *l;
  l = NULL;
  return l;
}

void addl(int e, List *l){
  List p;
  //List p = &node;
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

int main() {
  List lista = empty();
  List lista_c = empty();
  addl(1, &lista_c);
  addl(2, &lista_c);
  addl(3, &lista);
  concat(&lista, lista_c);
  for (int i = 0; i < 3; i++) {
    printf("%d\n", lista->elem);
    lista = lista->next;
    
  }
  return 0;
}


