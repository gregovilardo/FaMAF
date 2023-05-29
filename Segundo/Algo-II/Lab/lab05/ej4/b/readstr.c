#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 20

int main(void) {
  char user_input[MAX_LENGTH];
  /* char *user_input; */

  printf("Ingrese su nombre y apellido: ");
  //The problem is that after space scanf stop reading
/*   scanf("%s", user_input); */
  fgets(user_input, MAX_LENGTH, stdin);
  user_input[strlen(user_input)-1] = '\0';
  printf("Te damos la bienvenida %s a este maravilloso programa!\n",
         user_input);

  return EXIT_SUCCESS;
}
