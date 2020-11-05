#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <fcntl.h>
#include <stdlib.h>

/*
Exercise 8-1. Rewrite the program cat from Chapter 7
using read, write, open, and close instead of their standard library equivalents.

*/

void filecopy(int ifd);
void error(char *fmt, ...);

int main(int argc, char **argv) {
  int fd;

  if (argc == 1) { /* No args copy stdin */
    filecopy(0);
    exit(0);
  }
  while (--argc > 0) {
    if((fd = open(*++argv, O_WRONLY, 0)) == -1) {
      error("can't open the file %s", *argv);
    }
    filecopy(fd);
    close(fd);
  }

  exit(0);
}

void filecopy(int ifd) {
  char buf[BUFSIZ];
  int n;

  while ((n = read(ifd, buf, BUFSIZ)) > 0) {
    if (write(1, buf, n) != n) {
      error("can't write!!");
    }
  }
}

void error(char *fmt, ...) {
  va_list args;

  va_start(args, fmt);
  fprintf(stderr, "error: ");
  vprintf(fmt, args);
  fprintf(stderr, "\n");
  va_end(args);
  exit(1);
}