#ifndef _LIST_H
#define _LIST_H
#include <stdbool.h>

// our list elements
typedef int list_elem;

typedef struct _list * list;

// Constructors
// returns an empty list
list empty(void); 

// add an element on the left
list addl(list_elem e, list l);

// returns true if the list is empty
bool is_empty(list l);

// returns the first elemnt of the list
// PRE: !is_empty(l)
list_elem head(list l);

// delete the first element
// PRE: !is_empty(l)
list tail(list l);

// add an elemnt on the right
list addr(list l, list_elem e);

// return the length of the list
unsigned int length(list l);

// cancatenate two list
list concat(list l1, list l2);

// returns the element of an index
// PRE: length(l) > n
list_elem index(list l, unsigned int n);

// leaves only the first n elemnts
list take(list l, unsigned int n);

// drop the first n elemnts
list drop(list l, unsigned int n);

// copy the list to another list
list copy_list(list l);

// Destroy
list destroy(list l);


#endif
