#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ARRAY_SIZE 4

typedef struct bound_data {
    bool is_upperbound;
    bool is_lowerbound;
    bool exists;
    unsigned int where;
}bound_data;

bound_data check_bound(int value, int arr[], unsigned int length) {
    bound_data res;
    //
    // TODO: COMPLETAR
    bool is_lower = true;
    bool is_upper = true;
    bool exist = false;
    unsigned int where;
    
    for (int i = 0, j = 3; i <= j && i < length; i++, j--) {
      printf("esto es i: %d\n", i);

      printf("esto es j: %d\n\n\n", j);
    }

    for (unsigned int i = 0; i < length; i++)
    {
      if (value > arr[i]) {
        is_lower = false;
      } 
      if (value < arr[i]) {
        is_upper = false;
      }
      if (value == arr[i]) {
        exist = true;
        where = i;
      }

    res.is_lowerbound = is_lower;
    res.is_upperbound = is_upper;
    res.exists = exist;
    res.where = where;
    }
    
    //
    return res;
}

int main(void) {
    int a[ARRAY_SIZE];
    int value;
    
    printf("Ingrese un valor:\n");
    scanf("%d", &value);
    // TODO: COMPLETAR - Pedir entrada al usuario
    for (int i = 0; i < ARRAY_SIZE; i++)
    
    {
      printf("Ingrese un valor para la posicion %d del arreglo:\n", i);
      scanf("%d", &a[i]);
    }
    
    //
    bound_data result = check_bound(value, a, ARRAY_SIZE);

    // TODO: REEMPLAZAR LO SIGUIENTE LUEGO POR LA SALIDA QUE PIDE EL ENUNCIADO
    
    if (result.exists) {
      if (result.is_lowerbound) {
        printf("El valor es un minimo y se encuentra en %d\n", result.where);
      }
      if (result.is_upperbound) {
        printf("El valor es un maximo y se encuentra en %d\n", result.where);
      }
    } else {
      if (result.is_lowerbound) {
        printf("El valor es una cota inferior\n");
      }
      if (result.is_upperbound) {
        printf("El valor es una cota superior\n");
      }
    } 

    return EXIT_SUCCESS;
}
