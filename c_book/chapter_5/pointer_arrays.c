#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 /* max #lines to be sorted */
#define MAXLEN 1000   /* max length of any input line */

char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines, char p[]);
void writelines(char *lineptr[], int nlines);

int my_getline(char *buf, int len);

void swap(char *v[], int i, int j) {
  char *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

/* qsort:  sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right) {
  int i, last;

  if (left >= right) {
    /* do nothing if array contains */
    /* fewer than two elements */
    return;
  }
  swap(v, left, (left + right) / 2);
  last = left;

  for (i = left + 1; i <= right; i++) {
    if (strcmp(v[i], v[left]) < 0) {
      swap(v, ++last, i);
    }
  }

  swap(v, left, last);
  qsort(v, left, last - 1);
  qsort(v, last + 1, right);
}

int main() {
  int nlines;
  /* kludge method: use an array that can hold all the characters and use offset
   * as a way to copy stuff over */
  char p[MAXLEN * MAXLINES];

  if ((nlines = readlines(lineptr, MAXLINES, p)) >= 0) {
    qsort(lineptr, 0, nlines - 1);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("error: input too big to sort\n");
    return 1;
  }
  return 0;
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

char *alloc(int x) { return 0; }

/* Exercise 5-7. Rewrite readlines to store lines in an array supplied by main,
rather than calling alloc to maintain storage. How much faster is the program?
*/

/* readlines:  read input lines */
int readlines(char *lineptr[], int maxlines, char *p) {
  int len, nlines, offset;
  char line[MAXLEN];

  nlines = offset = 0;
  while ((len = my_getline(line, MAXLEN)) > 0) {
    if (nlines >= maxlines) {
      return -1;
    } else {
      if (line[len - 1] == '\n') {
        line[len - 1] = '\0'; /* delete newline */
      }
      strcpy(p + offset, line);
      lineptr[nlines] = p + offset;
      nlines++;
      offset += len;
    }
  }
  return nlines;
}
/* writelines:  write output lines */
void writelines(char *lineptr[], int nlines) {
  int i;

  for (i = 0; i < nlines; i++) {
    printf("%s\n", lineptr[i]);
  }
}
