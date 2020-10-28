#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
/*
Exercise 7-3. Revise minprintf to handle more of the other facilities of printf.
*/

#define MAX_SIZE 100

enum states {
  PUT,
  FORMAT
};

typedef enum states states_t;

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...) {
  va_list ap; /* points to each unnamed arg in turn */
  char *p, *sval;
  int ival, cp;
  double dval;
  char conv_spec[100];

  states_t cur, next;

  va_start(ap, fmt); /* make ap point to 1st unnamed arg */
  cp = 0;
  cur = PUT;

  for (p = fmt; *p; p++) {
    if (cur == PUT && *p == '%') {
      cur = FORMAT;
      conv_spec[cp++] = '%';
    } else if (cur == PUT) {
      putchar(*p);
    } else if (cur == FORMAT) {
      if (isdigit(*p)) {
        conv_spec[cp++] = *p;
        continue;
      }

      switch (*p) {
      /* handle digit */
      case 'd':
        conv_spec[cp++] = 'd';
        conv_spec[cp] = '\0';
        ival = va_arg(ap, int);
        printf(conv_spec, ival);
        cur = PUT;
        break;

      /* handle floating point */
      case 'f':
        conv_spec[cp++] = 'f';
        conv_spec[cp] = '\0';
        dval = va_arg(ap, double);
        printf(conv_spec, dval);
        cur = PUT;
        break;

      /* handle string */
      case 's':
        conv_spec[cp++] = 's';
        conv_spec[cp] = '\0';
        sval = va_arg(ap, char *);
        printf(conv_spec, sval);
        cur = PUT;
        break;

      /* handle char */
      case 'c':
        conv_spec[cp++] = 'c';
        conv_spec[cp] = '\0';
        ival = va_arg(ap, int);
        printf(conv_spec, ival);
        cur = PUT;
        break;

      /* handle hex */
      case 'x':
        conv_spec[cp++] = 'x';
        conv_spec[cp] = '\0';
        ival = va_arg(ap, int);
        printf(conv_spec, ival);
        cur = PUT;
        break;

      case '-':
        conv_spec[cp++] = '-';
        break;

      case '.':
        conv_spec[cp++] = '.';
        break;

      case 'h':
      conv_spec[cp++] = 'h';
        break;

      case 'l':
      conv_spec[cp++] = 'l';
        break;

      default:
        putchar(*p);
        break;
      }
    }
  }
  va_end(ap); /* clean up when done */
}

int main() {
  char test[] = "Hello, world";
  double t_num = 4.1321431914134;
  /* String Tests */
  minprintf("%s\n", test);
  minprintf("%10s\n", test);
  minprintf("%.10s\n", test);
  minprintf("%-10s\n", test);
  minprintf("%.15s\n", test);
  minprintf("%-15s\n", test);
  /* floating point tests */
  minprintf("%f\n", t_num);
  minprintf("%.3f\n", t_num);

  return 0;
}
