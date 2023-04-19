#include <stdio.h>
#include <stdbool.h>

bool lex_less(int a[], int b[], int n) {
  bool res;
  int i = 0;
  while (i < n && a[i] == b[i]) {
    i++;
  }
  if (a[i] < b[i]) {
    res = true;
  } else {
    res = false;
  }


  return res;
}

int main() {

  return 0;
}
