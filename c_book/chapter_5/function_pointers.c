#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000 /* max #lines to be sorted */
#define MAXLEN 1000   /* max length of any input line */

char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void my_qsort(void *lineptr[], int left, int right, int reverse,
              int (*comp)(void *, void *));
void swap(void *v[], int i, int j);
int numcmp(char *s1, char *s2);
int my_getline(char *buf, int len);

/* sort input lines */
int main(int argc, char *argv[]) {
  int nlines;        /* number of input lines read */
  int numeric = 0;   /* 1 if numeric sort */
  int reverse = 1;   /* -1 if -r flag */
  int fold = 0;      /* 1 if fold cases together */
  int directory = 0; /* 1 if directory */

  if (argc > 1 && strcmp(argv[1], "-n") == 0)
    numeric = 1;

  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    my_qsort((void **)lineptr, 0, nlines - 1, reverse,
             (int (*)(void *, void *))(numeric ? numcmp : strcmp));
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("input too big to sort\n");
    return 1;
  }
}

void my_qsort(void *v[], int left, int right, int reverse,
              int (*comp)(void *, void *)) {
  int i, last;

  if (left >= right) {
    return;
  }
  swap(v, left, (left + right) / 2);

  last = left;
  for (i = left + 1; i <= right; i++) {
    if ((((*comp)(v[i], v[left])) * reverse) < 0) {
      swap(v, ++last, i);
    }
    swap(v, left, last);
    qsort(v, left, last - 1, comp);
    qsort(v, left + 1, right, comp);
  }
}

int numcmp(char *s1, char *s2) {
  double v1, v2;

  v1 = atof(s1);
  v2 = atof(s2);

  if (v1 < v2)
    return -1;
  else if (v1 > v2)
    return 1;
  else
    return 0;
}

/* No error checking */
int foldcomp(char *s1, char *s2) {
  /* write recursive function */
  return 0;
}

void swap(void *v[], int i, int j) {
  void *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

/* readlines:  read input lines */
int readlines(char *lineptr[], int maxlines) {
  int len, nlines;
  char *p, line[MAXLEN];
  nlines = 0;
  while ((len = my_getline(line, MAXLEN)) > 0)
    if (nlines >= maxlines || (p = malloc(sizeof(char) * len)) == NULL) {
      return -1;
    } else {
      line[len - 1] = '\0'; /* delete newline */
      strcpy(p, line);
      lineptr[nlines++] = p;
    }
  return nlines;
}

/* writelines:  write output lines */
void writelines(char *lineptr[], int nlines) {
  int i;
  for (i = 0; i < nlines; i++)
    printf("%s\n", lineptr[i]);
}

int my_getline(char *buf, int len) {
  int c, i;

  for (i = 0; i < len - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
    buf[i] = c;
  }
  if (c == '\n') {
    buf[i] = c;
    i++;
  }
  buf[i] = '\0';
  return i;
}

/*
Exercise 5-14. Modify the sort program to handle a -r flag, which indicates
sorting in reverse (decreasing) order. Be sure that -r works with -n.
*/

/*
Exercise 5-15. Add the option -f to fold upper and lower case together, so that
case distinctions are not made during sorting; for example, a and A compare
equal.
*/
