#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/*

Exercise 6-6. Implement a simple version of the #define processor
(i.e., no arguments) suitable for use with C programs, based on the routines of this section.
You may also find getch and ungetch helpful.



# define identifier token-sequence
# define identifier(identifier, ... , identifier) token-sequence


*/
char my_buf[1000000];
int bufp = 0;
char *line;
unsigned long size;


int main() {
  int c;
  while ((c = getchar()) != EOF && bufp < 1000000) {
    my_buf[bufp++] = c;
  }
  printf("%s", my_buf);
  return 0;
}

void random_code(void) {
  char test[] = "Hello World";
  char *copy;
  char *needle = "World";
  char *rep = "wooooooooop";

  int hay_len = strlen(test);
  int need_len = strlen(needle);
  int rep_len = strlen(rep);
  int delta = hay_len - need_len;

  if (rep_len > delta) {
    copy = (char *) malloc(sizeof(char) * delta + rep_len);
    strcpy(copy, test);
    char *res = strstr(copy, needle);
    strcpy(res, rep);
    char *test = copy;
  }
}