#include <assert.h>
#include <stdbool.h>

#include "fixstring.h"

unsigned int fstring_length(fixstring s) {
  int i = 0;
  while (s[i] != '\0') {
    i++;
  }
  return i;
}

bool fstring_eq(fixstring s1, fixstring s2) {
  if (fstring_length(s1) != fstring_length(s2)) {
    return false;
  }
  unsigned int i = 0;
  while (i < fstring_length(s1)) {
    if (s1[i] != s2[i]) {
      return false;
    }
    i++;
  }
  return true;
}

bool fstring_less_eq(fixstring s1, fixstring s2) {
  unsigned int i = 0;
  while (i < fstring_length(s1)) {
    if (s1[i] < s2[i]) {
      return true;
    } else if (s1[i] > s2[i]) {
      return false;
    }
    i++;
  }
  return true;
}
