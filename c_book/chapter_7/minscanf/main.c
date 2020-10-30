#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>
/*

Exercise 7-4. Write a private version of scanf analogous to minprintf from the previous section.

*/


#define BUFSIZE 100

static int getch(void);
static int ungetch(int c);

void minscanf(char *fmt, ...) {
  int c, bp, *ip;
  char io_buf[BUFSIZE];
  va_list ap; /* points to each unnamed arg in turn */

  va_start(ap, fmt); /* make ap point to 1st unnamed arg */
  for (; fmt && *fmt != '\0'; fmt++) {
    if (*fmt != '%') {
      c = getch();
      if (*fmt != c) {
        return;
      }
    }
    else {
      switch(*++fmt) {
        case 'd': {
          bp = 0;
          for (c = getch(); isdigit(c); c = getch()) {
            io_buf[bp++] = c;
          }
          io_buf[bp] = '\0';
          ip = va_arg(ap, int *);
          *ip = atoi(io_buf);
          ungetch(c);
          break;
        }
        default: {
          return;
        }
      }
    }
  }
  va_end(ap); /* clean up when done */
}



int main(void) {

  int digit = 0;
  int d2 = 0;

  minscanf("H%dH%d", &digit, &d2);
  printf("the res is %d\n", digit);
  printf("the res2 is %d\n", d2);
  return 0;
}



/* buffer for ungetch */
static char buf[BUFSIZE];
/* next free position in buf */
static int bufp = 0;

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

