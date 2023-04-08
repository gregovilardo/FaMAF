#include <math.h>
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
      print_array(a, 0, tam_org - 1);

    } else {
      a[i - 1] = a[k - 1];
      k++;
      printf("esto es el array a despues de el if FALSE con i = %d: \n", i);
      print_array(a, 0, tam_org - 1);
    }
  }
}

void merge_sort(int a[], int n, int tam_org) {
  int m = 1;
    merge(a, 1, pow(2, n), pow(2, (n + 1)), tam_org);
  for (int i = n + 1; i < sqrt(tam_org); i++) {
    merge(a, pow(2, i) + 1, (1 + pow(2, m)) * pow(2, n),
          pow(2, (i + 1)), tam_org);
    m++;
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
  int arr_len = sizeof(a) / sizeof(a[0]);

  print_array(a, 0, arr_len - 1);
  for (int i =0; i < arr_len; i++) {
    merge_sort(a, i, arr_len);  
  }
  print_array(a, 0, arr_len - 1);
  return 0;
}
