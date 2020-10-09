#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

/* buffer for ungetch */
static char buf[BUFSIZE];
/* next free position in buf */
static int bufp = 0;

/* helper functions for get_word */
static int getch(void);
static int ungetch(int c);


int getword(char *word, int lim) {
  int c;
  char *w = word;

  while (isspace(c = getch())) {}

  if (c != EOF) {
    *w++ = c;
  }

  if (!isalpha(c)) {
    *w = '\0';
    return c;
  }

  for ( ; --lim > 0; w++) {
    if (!isalnum(*w = getch())) {
      ungetch(*w);
      break;
    }
  }

  *w = '\0';
  return word[0];
}

/* get a (possibly pushed-back) character */
static int getch(void) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
static int ungetch(int c) {
  if (bufp >= BUFSIZE) {
    printf("ungetch: too many characters\n");
    return 1;
  }

  buf[bufp++] = c;
  return 0;
}
