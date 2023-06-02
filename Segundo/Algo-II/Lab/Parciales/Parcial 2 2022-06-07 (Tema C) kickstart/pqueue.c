#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "pqueue.h"

struct s_pqueue {
  unsigned int size;
  priority_t min_priority;
  struct s_node *(*priority_array);
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
  q->priority_array = calloc(min_priority + 1, sizeof(struct s_node *));
  assert(invrep(q) && pqueue_is_empty(q));
  return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, priority_t priority) {
  assert(invrep(q));
  assert(priority <= q->min_priority);
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
  priority_t i = 0;
  struct s_node *node = q->priority_array[i];
  while (node == NULL) {
    i++;
    node = q->priority_array[i];
  }
  return node->elem;
}

priority_t pqueue_peek_priority(pqueue q) {
  assert(invrep(q) && !pqueue_is_empty(q));
  priority_t i = 0;
  struct s_node *node = q->priority_array[i];
  while (node == NULL) {
    i++;
    node = q->priority_array[i];
  }
  return i;
}

size_t pqueue_size(pqueue q) {
  assert(invrep(q));
  return q->size;
}

pqueue pqueue_dequeue(pqueue q) {
  assert(invrep(q) && !pqueue_is_empty(q));
  priority_t i = 0;
  struct s_node *node = q->priority_array[i];
  while (node == NULL) {
    i++;
    node = q->priority_array[i];
  }
  q->priority_array[i] = node->next;
  q->size--;
  destroy_node(node);
  assert(invrep(q));
  return q;
}

pqueue pqueue_destroy(pqueue q) {
  assert(invrep(q));
  if (q != NULL) {
    for (priority_t i = 0; i <= q->min_priority; i++) {
      struct s_node *node = q->priority_array[i];
      if (node != NULL) {
        struct s_node *nodenext = node->next;
        destroy_node(node);
        node = nodenext;
      }
    }
      free(q->priority_array);
      free(q);
      q = NULL;
  }
  return q;
}
