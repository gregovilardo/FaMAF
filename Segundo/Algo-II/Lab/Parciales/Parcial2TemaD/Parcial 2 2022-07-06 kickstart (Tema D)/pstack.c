#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "pstack.h"

struct s_pstack {
  struct s_node *(*priority_array);
  priority_t max_priority;
  unsigned int size;
};

struct s_node {
  struct s_node *next;
  pstack_elem elem;
  priority_t priority;
};

static struct s_node *create_node(pstack_elem e) {
  struct s_node *new_node = NULL;
  new_node = malloc(sizeof(struct s_node));
  assert(new_node != NULL);
  new_node->elem = e;
  new_node->next = NULL;
  return new_node;
}

static struct s_node *destroy_node(struct s_node *node) {
  node->next = NULL;
  free(node);
  node = NULL;
  return node;
}

static bool invrep(pstack s) {
  unsigned int issize = 0u;
  bool b = true;
  for (priority_t i = 0u; i <= s->max_priority; i++) {
    struct s_node *node = s->priority_array[i];
    if (node != NULL) {
      issize++;
      if (node->priority != i) b = false;
      while (node->next != NULL) {
        node = node->next;
        if (node->priority != i) b = false;
        issize++;
      }
    }
  }
  b = b && s->size == issize;
  return true; }

pstack pstack_empty(priority_t max_priority) {
  pstack s = NULL;
  s = malloc(sizeof(struct s_pstack));
  s->priority_array =
      calloc(max_priority + 1, sizeof(struct s_node)); // or *s_node?
  s->max_priority = max_priority;
  s->size = 0;
  assert(invrep(s) && pstack_is_empty(s));
  return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
  assert(invrep(s));
  struct s_node *new_node = create_node(e);
  new_node->priority = priority;
  struct s_node *top_node = s->priority_array[priority];
  new_node->next = top_node;
  s->priority_array[priority] = new_node;
  s->size++;
  assert(invrep(s) && !pstack_is_empty(s));
  return s;
}

bool pstack_is_empty(pstack s) {
  assert(invrep(s));
  return s->size == 0;
}

pstack_elem pstack_top(pstack s) {
  assert(invrep(s) && !pstack_is_empty(s));
  priority_t i = 0;
  struct s_node *node = s->priority_array[s->max_priority - i];
  while (node == NULL &&
         i <= s->max_priority) { // does i have to initialize all in null?
    i++;
    node = s->priority_array[s->max_priority - i];
  }
  return node->elem;
}

priority_t pstack_top_priority(pstack s) {
  assert(invrep(s) && !pstack_is_empty(s));
  priority_t i = 0;
  struct s_node *node = s->priority_array[s->max_priority - i];
  while (node == NULL &&
         i <= s->max_priority) { // does i have to initialize all in null?
    i++;
    node = s->priority_array[s->max_priority - i];
  }
  return s->max_priority - i;
}

size_t pstack_size(pstack s) {
  assert(invrep(s));
  return s->size;
}

pstack pstack_pop(pstack s) {
  assert(invrep(s) && !pstack_is_empty(s));
  priority_t i = 0;
  struct s_node *node = s->priority_array[s->max_priority - i];
  while (node == NULL &&
         i <= s->max_priority) { // does i have to initialize all in null?
    i++;
    node = s->priority_array[s->max_priority - i];
  }
  s->priority_array[s->max_priority-i] = node->next;
  destroy_node(node);
  s->size--;

  assert(invrep(s));
  return s;
}

pstack pstack_destroy(pstack s) {
  assert(invrep(s));
  for (priority_t i = 0u; i <= s->max_priority; i++) {
    struct s_node *node = s->priority_array[i];
    if (node != NULL) {
      while (node->next != NULL) {
        struct s_node *node2 = node->next;
        destroy_node(node);
        node = node2;
        node2 = NULL;
      }
      destroy_node(node);
    }
  }
  free(s->priority_array);
  free(s);
  s = NULL;
  return s;
}
