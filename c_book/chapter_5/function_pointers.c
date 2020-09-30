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
int foldcomp(char *s1, char *s2);
/* sort input lines */
int nlines = 0;    /* number of input lines read */
int numeric = 0;   /* 1 if numeric sort */
int reverse = 0;   /* -1 if -r flag */
int fold = 0;      /* 1 if fold cases together */
int directory = 0; /* 1 if directory */

int main(int argc, char *argv[]) {
  int i;
  void *fun;

  if (argc > 1 && strcmp(argv[1], "-n") == 0)
    numeric = 1;

  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-n") == 0) {
      numeric = 1;
    } else if (strcmp(argv[i], "-r") == 0) {
      reverse = -1;
    } else if (strcmp(argv[i], "-f")) {
      fold = 1;
    } else if (strcmp(argv[i], "-d")) {
      directory = 1;
    }
  }

  if (numeric) {
    fun = numcmp;
  } else if (fold || directory) {
    fun = foldcomp;
  } else {
    fun = strcmp;
  }
  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    my_qsort((void **)lineptr, 0, nlines - 1, reverse, (int (*)(void *, void *))fun);
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
    my_qsort(v, left, last - 1, reverse, comp);
    my_qsort(v, left + 1, right, reverse, comp);
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

/*
  No error checking
  works with both fold and comp
*/
int foldcomp(char *s1, char *s2) {
  /* write recursive function */
  char temp1, temp2;
  if (*s1 == '\0' && *s2 == '\0') {
    return 0;
  }
  if (*s1 == '\0' && *s2 != '\0') {
    return -1;
  }
  if (*s1 != '\0' && *s2 == '\0') {
    return 1;
  }
  if (directory) {
    temp1 = (isalnum(*s1) || isblank(*s1)) ? *s1 : 0;
    temp2 = (isalnum(*s2) || isblank(*s2)) ? *s2 : 0;
  }
  if (fold) {
    temp1 = isalpha(*s1) ? tolower(*s1) : *s1;
    temp2 = isalpha(*s2) ? tolower(*s2) : *s2;
  }
  if (temp1 > temp2) {
    return 1;
  } else if (temp1 < temp2) {
    return -1;
  } else {
    return foldcomp(s1 + 1, s2 + 1);
  }
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
