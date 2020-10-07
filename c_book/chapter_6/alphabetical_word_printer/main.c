#include <stdio.h>
#include "word_list.h"
/*

input:  a C program
output: alpahbetical order printed variable names that are equal within n chars

n chars is a command line feature
do not count words within comments or strings

*/

int main(int argc, char**argv) {
  /* read the words in file */
  /* insert them into our tree */
  /* print tree */
  char *word = "efe";
  struct word_list *list = create_list(word);
  append(list, "charizard");
  print_list(list);
  return 0;
}