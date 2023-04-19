#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
  int aux = *a;
  *a = *b;
  *b = aux;
}

int partition(int a[], int lft, int rgt) {
  printf("Entrando a partition con lft: %d, y rgt %d\n", lft, rgt);
  int j = rgt;
  int i = lft + 1;
  int piv = lft;
  while (i <= j) {
    if (a[i] <= a[piv]) {
      i++;
    }
    if (a[j] >= a[piv]) {
      j--;
    }
    if (a[i] > a[piv] && a[j] < a[piv] && i <= j) {
      swap(&a[i], &a[j]);
      j--;
      i++;
    }
  }
  swap(&a[piv], &a[j]);
  piv = j;

  return piv;
}

int i_if_ord(int a[], int k) {
  int j = partition(a, 0, 7);
  while (j != k) {
    if (j > k) {
      j = partition(a, 0, j - 1);
    } else if (j < k) {
      j = partition(a, j + 1, 7);
    }
  }
  return a[k-1];
}

int main() {

  int n;
  printf("Ingrese tamaño del array\n");
  scanf("%d", &n);
  int a[n];
  for (int i = 0; i < n; i++) {
    printf("Valor: ");
    scanf("%d", &a[i]);
  }
  int a_len = sizeof(a) / sizeof(a[0]);
  printf("ESTE ES EL RESULTADO: %d\n", i_if_ord(a, 4));
  for (int i = 0; i < a_len; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");

  return 0;
}
