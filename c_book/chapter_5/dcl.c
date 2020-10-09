#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN 100
enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN]; /* data type = char, int, etc. */
char out[1000];

void dcl(void) {
  int ns;

  for (ns = 0; gettoken() == '*';)
    ns++;
  dirdcl();
  while (ns-- > 0) {
    strcat(out, " pointer to");
  }
}

void dirdcl(void) {
  int type;
  if (tokentype == '(') {
    dcl();
    if (tokentype != ')') {
      printf("error: missing )\n");
    }
  } else if (tokentype == NAME) {
    strcpy(name, token);
  } else {
    printf("error: expected name or dcl (dcl)\n");
  }
  while ((type = gettoken()) == PARENS || type == BRACKETS)
    if (type == PARENS) {
      strcat(out, " function returning");
    } else {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }
}

int main() {
  while (gettoken() != EOF) { /* 1st token on line */
    strcpy(datatype, token);  /* is the datatype */
    out[0] = '\0';
    dcl(); /* parse rest of line */
    if (tokentype != '\n') {
      printf("syntax error\n");
    }
    printf("%s: %s %s\n", name, out, datatype);
  }

  return 0;
}


#define BUFSIZE 100
/* buffer for ungetch */
char buf[BUFSIZE];
/* next free position in buf */
int bufp = 0;

/* get a (possibly pushed-back) character */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
int ungetch(int c)
{
    if (bufp >= BUFSIZE)
    {
        printf("ungetch: too many characters\n");
        return 1;
    }
    buf[bufp++] = c;
    return 0;
}

int gettoken(void) {

  int c;
  char *p = token;

  while ((c = getch()) == ' ' || c == '\t')
  ;
  if (c == '(') {
    if ((c = getch()) == ')') {
      strcpy(token, "()");
      return tokentype = PARENS;
    } else {
      ungetch(c);
      return tokentype = '(';
    }
  } else if (c == '[') {
      for (*p++ = c; (*p++ = getch()) != ']';)
        ;
      *p = 0;
      return tokentype = BRACKETS;

  } else if (isalpha(c)) {
      for (*p++ = c; isalnum(c = getch()); ) {
        *p++ = c;
      }
      *p = '\0';
      ungetch(c);
      return tokentype = NAME;
  } else {
    return tokentype = c;
  }
}