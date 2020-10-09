#include <stdio.h>
#include "./bin_tree.h"
#include <string.h>
/*

input:  a C program
output: alpahbetical order printed variable names that are equal within n chars

n chars is a command line feature
do not count words within comments or strings

*/
#define NUMWORDS 5

int main(int argc, char **argv) {
  /* read the words in file */
  /* insert them into our tree */
  /* print tree */
  int i, n;
  n = 1;
  struct bin_tree *root = create_node();

  char *words[] = {"A" ,"B" ,"C", "D", "W"};
  for (i = 0; i < 4; i++) {
    insert_word(root, words[i], n);
  }
  print_tree(root);
  return 0;
}

// char *word = "efe";
// struct word_list *list = create_list(word);
// append(list, "charizard");
// print_list(list);