#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

/* buffer for ungetch */
static char buf[BUFSIZE];
/* next free position in buf */
static int bufp = 0;

/* helper functions for get_word */
static int getch(char *stream, int stream_size, int *sp);
static int ungetch(int c);


int getword(char *word, char *stream, int lim, int stream_size, int *sp) {
  int c;
  char *w = word;
  while (isspace(c = getch(stream, stream_size, sp))) {}

  if (c != EOF) {
    *w++ = c;
  }

  if (!isalpha(c)) {
    *w = '\0';
    return c;
  }

  for ( ; --lim > 0; w++) {
    if (!isalnum(*w = getch(stream, stream_size, sp))) {
      if (*w == '_') {
        continue;
      }
      ungetch(*w);
      break;
    }
  }

  *w = '\0';
  return word[0];
}

/* get a (possibly pushed-back) character */
static int getch(char *stream, int stream_size, int *sp) {
  int c = (bufp > 0) ? buf[--bufp] : stream[(*sp)++];
  printf("c is %c\n", c);
  return c;
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
