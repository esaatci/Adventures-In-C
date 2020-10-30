#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Exercise 7-6. Write a program to compare two files, printing the first line where they differ. */

int main(int argc, char **argv) {
  char *prog = *argv;

  if (argc < 3) {
    fprintf(stderr, "%s not enough args\n" ,prog);
    exit(1);
  } else if (argc > 3) {
    fprintf(stderr, "%s alot of args\n", prog);
  }
  exit(0);
}