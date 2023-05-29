#include "abb.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct _s_abb {
  abb_elem elem;
  struct _s_abb *left;
  struct _s_abb *right;
};

static bool elem_eq(abb_elem a, abb_elem b) { return a == b; }

static bool elem_less(abb_elem a, abb_elem b) { return a < b; }

static bool invrep(abb tree) {
  if (tree == NULL)
    return true;
  bool b = true;
  if (!abb_is_empty(tree->left)) {
    b = elem_less(tree->left->elem, tree->elem);
  }
  if (!abb_is_empty(tree->right)) {
    b = elem_less(tree->elem, tree->right->elem);
  }
  b = b && invrep(tree->left) && invrep(tree->right);

  return b;
}

abb abb_empty(void) {
  abb tree = NULL;
  assert(invrep(tree) && abb_is_empty(tree));
  return tree;
}

abb abb_add(abb tree, abb_elem e) {
  assert(invrep(tree));
  if (abb_is_empty(tree)) {
    tree = malloc(sizeof(struct _s_abb));
    tree->elem = e;
    tree->right = abb_empty();
    tree->left = abb_empty();
  } else {
    if (elem_less(tree->elem, e))
      tree->right = abb_add(tree->right, e);
    if (elem_less(e, tree->elem))
      tree->left = abb_add(tree->left, e);
  }
  assert(invrep(tree) && abb_exists(tree, e));
  return tree;
}

bool abb_is_empty(abb tree) {
  bool is_empty = false;
  assert(invrep(tree));
  is_empty = tree == NULL;
  return is_empty;
}

bool abb_exists(abb tree, abb_elem e) {
  bool exists = false;
  assert(invrep(tree));
  if (abb_is_empty(tree))
    return false;
  if (elem_eq(tree->elem, e))
    return true;
  if (elem_less(e, tree->elem))
    exists = exists || abb_exists(tree->left, e);
  if (elem_less(tree->elem, e))
    exists = exists || abb_exists(tree->right, e);
  return exists;
}

unsigned int abb_length(abb tree) {
  unsigned int length = 0;
  assert(invrep(tree));
  length += abb_is_empty(tree)
                ? 0
                : 1 + abb_length(tree->right) + abb_length(tree->left);

  assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
  return length;
}

abb change_tree(abb tree) {
  abb tree_aux, new_tree;
  assert(invrep(tree));
  if (abb_is_empty(tree))
    return tree;
  if (abb_is_empty(tree->left) && abb_is_empty(tree->right)) {
    tree = abb_destroy(tree);
  } else if (!abb_is_empty(tree->left) && abb_is_empty(tree->right)) {
    new_tree = tree->left;
    free(tree);
    tree = new_tree;
  } else if (abb_is_empty(tree->left) && !abb_is_empty(tree->right)) {
    new_tree = tree->right;
    free(tree);
    tree = new_tree;
  } else if (!abb_is_empty(tree->left) && !abb_is_empty(tree->right)) {
    new_tree = tree->right;
    tree_aux = tree->right;
    while (!abb_is_empty(tree_aux->left)) {
      tree_aux = tree_aux->left;
    }
    tree_aux->left = tree->left;
    free(tree);
    tree = new_tree;
  }
  assert(invrep(tree));
  return tree;
}

abb abb_remove(abb tree, abb_elem e) {
  assert(invrep(tree));
  if (!abb_exists(tree, e))  {
    printf("El elemento no existe en el arbol\n");
    return tree;
  }
  if (elem_eq(abb_root(tree), e)) {
    tree = change_tree(tree);
    return tree;
  }
   if (elem_eq(abb_root(tree->left), e)) {
     tree->left = change_tree(tree->left);
     return tree;
   }
   if (elem_eq(abb_root(tree->right), e)) {
     tree->right = change_tree(tree->right);
     return tree;
   }
  if (elem_less(abb_root(tree), e))
    abb_remove(tree->right, e);
  if (elem_less(e, abb_root(tree)))
    abb_remove(tree->left, e);

  assert(invrep(tree) && !abb_exists(tree, e));
  return tree;
}

abb_elem abb_root(abb tree) {
  abb_elem root;
  assert(invrep(tree) && !abb_is_empty(tree));
  root = tree->elem;
  assert(abb_exists(tree, root));
  return root;
}

abb_elem abb_max(abb tree) {
  abb_elem max_e;
  assert(invrep(tree) && !abb_is_empty(tree));
  max_e = abb_root(tree);

  if (!abb_is_empty(tree->right))
    max_e = max_e > abb_max(tree->right) ? max_e : abb_max(tree->right);
  if (!abb_is_empty(tree->left))
    max_e = max_e > abb_max(tree->left) ? max_e : abb_max(tree->left);
  assert(invrep(tree) && abb_exists(tree, max_e));
  return max_e;
}

abb_elem abb_min(abb tree) {
  abb_elem min_e;
  min_e = abb_root(tree);
  assert(invrep(tree) && !abb_is_empty(tree));
  if (!abb_is_empty(tree->right))
    min_e = min_e < abb_min(tree->right) ? min_e : abb_min(tree->right);
  if (!abb_is_empty(tree->left))
    min_e = min_e < abb_min(tree->left) ? min_e : abb_min(tree->left);
  assert(invrep(tree) && abb_exists(tree, min_e));
  return min_e;
}

void abb_dump(abb tree) {
  assert(invrep(tree));
  // De esta manera no va a mostrar 'exactamente' como fueron agregados los elementos
  // pero si seguimos el orden que nos da vamos a terminar con el mismo arbol
  if (tree != NULL) {
    printf("%d ", tree->elem);
    abb_dump(tree->left);
    abb_dump(tree->right);
  }
}

abb abb_destroy(abb tree) {
  assert(invrep(tree));
  if (abb_is_empty(tree))
    return tree;
  if (!abb_is_empty(tree->left))
    abb_destroy(tree->left);
  if (!abb_is_empty(tree->right))
    abb_destroy(tree->right);
  free(tree);
  tree = NULL;
  assert(tree == NULL);
  return tree;
}
