#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define LINE 256
/*
Exercise 7-6. Write a program to compare
two files, printing the first line where they differ.
*/

int main(int argc, char **argv) {
  char *file1, *file2, *prog;
  char *c1, *c2;
  char l1[LINE], l2[LINE];
  int cmp_res;

  prog = *argv;
  if (argc < 3) {
    fprintf(stderr, "%s not enough args\n", prog);
    exit(1);
  } else if (argc > 3) {
    fprintf(stderr, "%s alot of args\n", prog);
    exit(1);
  }

  file1 = argv[1];
  file2 = argv[2];

  /* open the files */
  FILE *f1 = fopen(file1, "r");
  FILE *f2 = fopen(file2, "r");
  if (!f1 || !f2) {
    fprintf(stderr, "can't open files\n");
    exit(1);
  }
  /* start comparing them */
  while ((c1 = fgets(l1, LINE, f1)) != NULL &&
          (c2 = fgets(l2, LINE, f2)) != NULL) {
    cmp_res = strcmp(l1, l2);
    if (cmp_res < 0) {
      printf("%s", l2);
      exit(0);
    } else if (cmp_res > 0) {
      printf("%s", l1);
      exit(0);
    }
  }
  /* if file 2 is shorter print the last line in file 1 */
  if ((c1 = fgets(l1, LINE, f1)) != NULL) {
      printf("%s", l1);
      exit(0);
  }
  /* if file 1 is shorter print the last line in file 2 */
  if ((c2 = fgets(l2, LINE, f2)) != NULL) {
      printf("%s", l2);
      exit(0);
  }
  /* close the files */
  fclose(f1);
  fclose(f2);

  printf("the files are identical\n");
  exit(0);
}
