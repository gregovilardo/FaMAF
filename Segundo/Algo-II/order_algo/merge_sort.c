#include <stdio.h>
#include <stdlib.h>

void print_array(int array[], int lft, int rgt) {
  for (int i = lft; i <= rgt; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
}

void merge(int a[], int lft, int mid, int rgt, int tam_org) {
  printf("lft %d\nmid %d\nrgt %d\n", lft, mid, rgt);
  int tmp[mid];
  int j, k;
  for (int i = lft; i <= mid; i++) {
    tmp[i] = a[i - 1];
  }
  printf("esto es el array tmp: ");
  print_array(tmp, lft, mid);

  j = lft;
  k = mid + 1;
  for (int i = lft; i <= rgt; i++) {
    if (j <= mid && (k > rgt || tmp[j] <= a[k - 1])) {
      printf("i: %d\nj: %d\nk = %d\n", i, j, k);
      a[i - 1] = tmp[j];
      j++;

      printf("esto es el array a despues de el if TRUE con i = %d: \n", i);
      print_array(a, 0, tam_org-1);

    } else {
      a[i - 1] = a[k - 1];
      k++;
      printf("esto es el array a despues de el if FALSE con i = %d: \n", i);
      print_array(a, 0, tam_org-1);
    }
  }
}

void merge_sort_rec(int a[], int lft, int rgt, int tam_org) {
  int mid;
  if (rgt > lft) {
    mid = (rgt + lft) / 2;
    printf("esto es lft %d, esto es mid %d, y esto es rgt %d\n", lft, mid, rgt);
    merge_sort_rec(a, lft, mid, tam_org);
    merge_sort_rec(a, mid + 1, rgt, tam_org);
    printf("call to merge\n");
    merge(a, lft, mid, rgt, tam_org);
  }
}

int main() {
  int n;
  printf("ingrese el tamaño del array: \n");
  scanf("%d", &n);
  int a[n];
  printf("ingrese los elementos\n");
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  int arr_len = sizeof(a) / sizeof(a[1]);
  print_array(a, 0, arr_len - 1);
  merge_sort_rec(a, 1, arr_len, arr_len);
  print_array(a, 0, arr_len - 1);
}
