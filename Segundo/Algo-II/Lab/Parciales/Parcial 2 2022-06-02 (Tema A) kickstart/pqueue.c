#include "pqueue.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

struct s_pqueue {
  struct s_node *front;
  unsigned int size;
  unsigned int min_priority;
};

struct s_node {
  struct s_node *next;
  pqueue_elem elem;
  unsigned int priority;
};

static struct s_node *create_node(pqueue_elem e, unsigned int priority) {
  struct s_node *new_node = NULL;
  new_node = malloc(sizeof(struct s_node));
  assert(new_node != NULL);
  new_node->elem = e;
  new_node->priority = priority;
  new_node->next = NULL;
  /* assert(e == e && priority == priority); // BORRAR ESTE ASSERT */
  return new_node;
}

static struct s_node *destroy_node(struct s_node *node) {
  assert(node != NULL);
  free(node);
  node = NULL;
  assert(node == NULL);
  return node;
}

static bool invrep(pqueue q) {
  bool b = true;
  if (q != NULL && q->size != 0) {
    struct s_node *tmp = q->front;
    while (tmp->next != NULL) {
      if (tmp->priority > tmp->next->priority) {
        b = false;
      }
      tmp = tmp->next;
    }
  }
  return b;
}

pqueue pqueue_empty(void) {
  pqueue q = NULL;
  q = malloc(sizeof(struct s_pqueue));
  q->size = 0;
  q->front = NULL;
  return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority) {
  assert(invrep(q));
  struct s_node *new_node = create_node(e, priority);
  if (q->size == 0) {
    q->front = new_node;
    (q->size)++;
  } else {
    struct s_node *tmp = q->front;
    if (tmp->priority > priority) {
      new_node->next = tmp;
      q->front = new_node;
    } else {
      while (tmp->next != NULL && tmp->next->priority <= priority) {
        tmp = tmp->next;
      }
      new_node->next = tmp->next;
      tmp->next = new_node;
    }
    (q->size)++;
  }
  assert(invrep(q) && !pqueue_is_empty(q)); // ?
  return q;
}

bool pqueue_is_empty(pqueue q) { return q->size == 0; }

pqueue_elem pqueue_peek(pqueue q) {
  assert(invrep(q) && !pqueue_is_empty(q));
  pqueue_elem p = q->front->elem;
  assert(invrep(q));
  return p;
}

unsigned int pqueue_peek_priority(pqueue q) {
  assert(invrep(q) && !pqueue_is_empty(q));
  pqueue_elem p = q->front->priority;
  assert(invrep(q));
  return p;
}

unsigned int pqueue_size(pqueue q) {
  assert(invrep(q));
  unsigned int size = q->size;
  return size;
}

pqueue pqueue_dequeue(pqueue q) {
  assert(invrep(q) && !pqueue_is_empty(q));
  struct s_node *p = q->front;
  q->front = q->front->next;
  (q->size)--;
  destroy_node(p);
  p = NULL;
  assert(invrep(q));
  return q;
}

pqueue pqueue_destroy(pqueue q) {
  assert(invrep(q));
  if (pqueue_is_empty(q)) {
    free(q);
    q = NULL;
  } else {
    struct s_node *p = q->front;
    struct s_node *aux;
    while (p->next != NULL) {
      aux = p;
      p = p->next;
      destroy_node(aux);
    }
    destroy_node(p);
    p = NULL;
    free(q);
    q = NULL;
  }
  assert(q == NULL);
  return q;
}
