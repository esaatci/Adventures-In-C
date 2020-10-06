#include <stdio.h>
#include <ctype.h>
#include <string.h>


#define MAXWORD 100
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define NKEYS (sizeof keytab / sizeof(struct key))

#define BUFSIZE 100
/* buffer for ungetch */
char buf[BUFSIZE];
/* next free position in buf */
int bufp = 0;

struct key {
  char *word;
  int count;
} keytab[] = {
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    "default", 0,
    "unsigned", 0,
    "void", 0,
    "volatile", 0,
    "while", 0,
};



int getword(char *, int);
int binsearch(char *word, struct key *tab, int n);
int getch(void);
int ungetch(int c);




int main() {

  int n;
  char word[MAXWORD];

  while (getword(word, MAXWORD) != EOF) {
    printf("word is %s\n", word);
    if (isalpha(word[0])) {
      if ((n = binsearch(word, keytab, NKEYS)) >= 0) {
          keytab[n].count++;
      }
    }
  }
  for (n = 0; n < NKEYS; n++) {
    if (keytab[n].count > 0) {
      printf("%4d %s\n",
        keytab[n].count, keytab[n].word);
    }
  }

  return 0;
}

int binsearch(char *word, struct key *tab, int n) {
  int cond;
  int low, high, mid;

  low = 0;
  high = n - 1;

  while (low <= high) {
    mid = (low+high) / 2;
    if ((cond = strcmp(word, tab[mid].word)) < 0) {
        high = mid - 1;
    } else if (cond > 0) {
        low = mid + 1;
    } else {
        return mid;
    }
  }

  return -1;
}


/* getword:  get next word or character from input */



int getword(char *word, int lim) {
  int c;
  char *w = word;

  while (isspace(c = getch()))
  ;

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
int getch(void) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
int ungetch(int c) {
  if (bufp >= BUFSIZE) {
    printf("ungetch: too many characters\n");
    return 1;
  }

  buf[bufp++] = c;
  return 0;
}

/*
Exercise 6-1. Our version of getword does not properly handle underscores, string constants, comments, or preprocessor control lines.
Write a better version. */