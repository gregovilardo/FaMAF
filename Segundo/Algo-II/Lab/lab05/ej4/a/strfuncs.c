#include "strfuncs.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

size_t string_length(const char *str) {
  size_t size = 0;
  while(str[size] != '\0') {
    size++;
  }
  return size;
}

char *string_filter(const char *str, char c) {
  char *new_str = calloc(string_length(str),sizeof(char));
  unsigned int j=0;
  for (unsigned int i = 0; i < string_length(str); i++) {
    //funciona pero tira warnings
/*     new_str[i] = str[i] == c ?: str[i];  */

    if (str[i] != c) { 
      new_str[j] = str[i];
      j++;
    }
  }
  return new_str;
}
