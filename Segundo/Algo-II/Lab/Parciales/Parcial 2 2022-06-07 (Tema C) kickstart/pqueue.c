#include "pqueue.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

struct s_pqueue {
  unsigned int size;
  unsigned int min_priority;
  struct s_node **priority_array;
};

struct s_node {
  pqueue_elem elem;
  struct s_node *next;
};

static struct s_node *create_node(pqueue_elem e) {
  struct s_node *new_node = NULL;
  new_node = malloc(sizeof(struct s_node));
  new_node->elem = e;
  new_node->next = NULL;
  assert(new_node != NULL);
  return new_node;
}

static struct s_node *destroy_node(struct s_node *node) {
  free(node);
  node = NULL;
  return node;
}

static bool invrep(pqueue q) { return true; }

pqueue pqueue_empty(priority_t min_priority) {
  pqueue q = NULL;
  q = malloc(sizeof(struct s_pqueue));
  q->min_priority = min_priority;
  q->size = 0;
  q->priority_array = calloc(sizeof(struct s_node *), min_priority);
  assert(invrep(q) && pqueue_is_empty(q));
  return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, priority_t priority) {
  assert(invrep(q));
  assert(priority < q->min_priority);
  struct s_node *node = create_node(e);
  if (q->priority_array[priority] == NULL) {
    q->priority_array[priority] = node;
  } else {
    struct s_node *tmp = q->priority_array[priority];
    while (tmp->next != NULL) {
      tmp = tmp->next;
    }
    tmp->next = node;
  }
  q->size++;

  assert(invrep(q) && !pqueue_is_empty(q));
  return q;
}

bool pqueue_is_empty(pqueue q) {
  assert(invrep(q));
  return q->size == 0; 
}

pqueue_elem pqueue_peek(pqueue q) {
  assert(invrep(q) && !pqueue_is_empty(q));
  return true; // BORRAR ESTA LINEA
}

priority_t pqueue_peek_priority(pqueue q) {
  assert(invrep(q) && !pqueue_is_empty(q));
  return true; // BORRAR ESTA LINEA
}

size_t pqueue_size(pqueue q) {
  assert(invrep(q));
  return 0u; // BORRAR ESTA LINEA
}

pqueue pqueue_dequeue(pqueue q) {
  assert(invrep(q) && !pqueue_is_empty(q));
  /* COMPLETAR */
  assert(invrep(q));
  return q;
}

pqueue pqueue_destroy(pqueue q) {
  assert(invrep(q));
  /* COMPLETAR*/
  return q;
}
