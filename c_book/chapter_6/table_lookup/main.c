#include <stdio.h>
#include "hash_table.h"


int main() {
  struct nlist *res;
  char *key, *value;
  key = "Hello";
  value = "World";
  /* undef test cases
  returns NULL for unknown symbol
  returns the deleted struct
  */
  install(key, value);
  undef(key);
  res = lookup(key);
  printf("res should be NULL %p\n", res);
  return 0;
}
