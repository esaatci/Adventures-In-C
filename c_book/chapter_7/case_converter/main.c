#include <stdio.h>
#include <ctype.h>
#include <string.h>
/*

Exercise 7-1. Write a program that converts upper case to lower or lower case to upper,
depending on the name it is invoked with, as found in argv[0].

if no arg is presented the default is lower case

-u => upper case

*/


int main(int argc, char **argv) {
  int c;
  char *cmd_flag = NULL;

  /* read the command line */
  if (argc == 2) {
    cmd_flag = argv[1];
    printf("the cmd_flag is %s\n", cmd_flag);
  }

  /* determine the case function */
  int (*case_ptr) (int) = (cmd_flag && strcmp(cmd_flag, "-u") == 0) ? &toupper: &tolower;

  /* read the standard input */
  while ((c = getchar()) != EOF) {
    /* convert chars to the case */
    putchar((*case_ptr)(c));
  }

  return 0;
}