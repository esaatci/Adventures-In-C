#include <stdlib.h>
#include <stdio.h>


#define IS_UPPER_MACRO(c) (((c) >= 'A') && ((c) <= 'Z'))

/*
Exercise 7-9. Functions like isupper can be
implemented to save space or to save time.
Explore both possibilities.
*/

int my_isupper(int c) {
  return (c >= 'A' && c <= 'Z');
}

int main(void) {
  return 0;
}