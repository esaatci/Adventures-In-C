#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "bin_tree.h"
#include "get_word.h"
/*

input:  a C program
output: alpahbetical order printed variable names that are equal within n chars

n chars is a command line feature
do not count words within comments or strings TODO

has minimal error checking

*/
#define NUMWORDS 5
#define MAXWORD 100

int main(int argc, char **argv) {
  int i, n;
  n = 2;
  char word[MAXWORD];
  struct bin_tree *r = create_empty_tree();
  /* get command line arguments */
  if (argc == 1) {
    n = 1;
  } else {
    n = atoi(argv[1]);
  }
  /* read the words in file and insert them to tree */
  while (getword(word, MAXWORD) != EOF) {
    if (isalpha(word[0])) {
      insert_word(&r, word, n);
    }
  }
  /* output the tree to console */
  print_tree(r);
  return 0;
}
