#include "abb.h"

int main(){
  abb tree = abb_empty();
  tree = abb_add(tree, 7);
  tree = abb_add(tree, 4);
  tree = abb_add(tree, 15);
  tree = abb_add(tree, 2);
  tree = abb_add(tree, 5);
  tree = abb_add(tree, 10);
  tree = abb_add(tree, 18);
  tree =abb_remove(tree,15);
  abb_dump(tree);

  return 0;
}
