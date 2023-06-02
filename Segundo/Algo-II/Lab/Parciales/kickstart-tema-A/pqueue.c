#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "pqueue.h"

struct s_pqueue {
  struct s_node *front;
  unsigned int size;
};

struct s_node {
  struct s_node *next;
  pqueue_elem elem;
  float priority;
  float average_grade;
  unsigned int approved_courses;
};

static float calculate_priority(float average_grade,
                                unsigned int approved_courses) {
  float priority = 0;
  priority = 0.5 * (average_grade / MAX_GRADE) +
             0.5 * (approved_courses / TOTAL_COURSES);
  return priority;
}

static struct s_node *create_node(pqueue_elem e, float average_grade,
                                  unsigned int approved_courses) {
  struct s_node *new_node = malloc(sizeof(struct s_node));
  new_node->next = NULL;
  new_node->elem = e;
  new_node->average_grade = average_grade;
  new_node->approved_courses = approved_courses;
  new_node->priority = calculate_priority(average_grade, approved_courses);

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
  unsigned int size = 0;
  struct s_node *node = q->front;
  if (node != NULL){
    size++;
    while (node->next != NULL) {
      b = node->priority > node->next->priority;
      size++;
      node = node->next;
    }
  }
  
  return b = q->size == q->size - 0;
}

pqueue pqueue_empty(void) {
  pqueue q = malloc(sizeof(struct s_pqueue));
  q->front = NULL;
  q->size = 0;

  return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, float average_grade,
                      unsigned int approved_courses) {
  assert(invrep(q));
  struct s_node *node_en = create_node(e, average_grade, approved_courses);
  struct s_node *p = q->front;
  if (p == NULL) {
    q->front = node_en;
  } else {
    while (p->next != NULL && p->next->priority >= node_en->priority) {
      p = p->next;
    }
    struct s_node *p2 = p->next;
    p->next = node_en;
    node_en->next = p2;
  }
  q->size++;
  assert(invrep(q) && !pqueue_is_empty(q));
  return q;
}

bool pqueue_is_empty(pqueue q) { return q->size == 0; }

pqueue_elem pqueue_peek(pqueue q) {
  assert(invrep(q) && !pqueue_is_empty(q));
  return q->front->elem;
}

float pqueue_peek_average_grade(pqueue q) {
  assert(invrep(q));
  assert(invrep(q));
  return q->front->average_grade;
}

unsigned int pqueue_peek_approved_courses(pqueue q) {
  assert(invrep(q));
  assert(invrep(q));
  return q->front->approved_courses;
}

float pqueue_peek_priority(pqueue q) {
  assert(invrep(q));
  assert(invrep(q));
  return q->front->priority;
}

unsigned int pqueue_size(pqueue q) {
  assert(invrep(q));

  assert(invrep(q));
  return q->size;
}

pqueue pqueue_copy(pqueue q) {
  assert(invrep(q));
  pqueue p = pqueue_empty();
  struct s_node *cop = q->front;
  while (cop != NULL) {
    p = pqueue_enqueue(p, cop->elem, cop->average_grade, cop->approved_courses);
    cop = cop->next;
  }
  return p;
}

pqueue pqueue_dequeue(pqueue q) {
  assert(invrep(q));
  assert(!pqueue_is_empty(q));
  struct s_node *node = q->front;
  q->front = node->next;
  destroy_node(node);
  q->size--;
  return q;
}

pqueue pqueue_destroy(pqueue q) {
  if (q != NULL) {
    if (q->size != 0) {
      struct s_node *node = q->front;
      struct s_node *node2 = NULL;
      while (node != NULL) {
        node2 = node->next;
        destroy_node(node);
        node = node2;
      }
    }
    free(q);
    q = NULL;
  }
  assert(q == NULL);
  return q;
}
