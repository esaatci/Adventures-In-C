#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "my_dirent.h"

void my_fsize(char *name);
void dirwalk(char *dir, void (*fcn)(char *));

/* print filename */
int main(int argc, char **argv) {
  if (argc == 1) { /* default: current directory */
    my_fsize(".");
  } else {
    while (--argc > 0) {
      my_fsize(*++argv);
    }
  }

  return 0;
}

void my_fsize(char *name) {
  struct stat stbuf;

  if (stat(name, &stbuf) == -1) {
    fprintf(stderr, "fsize? cant access %s\n", name);
    return;
  }

  if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
    dirwalk(name, my_fsize);
    return;
  }

  printf("%8hu %8lld %s\n", stbuf.st_mode, stbuf.st_size, name);
}

#define MAX_PATH 1024

void dirwalk(char *dir, void (*fcn)(char *)) {
  char name[MAX_PATH];
  Dirent *dp;
  DIR *dfd;

  if ((dfd = opendir(dir)) == NULL) {
    fprintf(stderr, "dirwalk: can’t open %s\n", dir);
    return;
  }

  while ((dp = readdir(dfd)) != NULL) {
    /* will cause an infine loop if not skipped */
    if (strcmp(dp->name, ".") == 0 ||
        strcmp(dp->name, "..") == 0) {
      continue;
    }

    if (strlen(dir) + strlen(dp->name) + 2 > sizeof(name)) {
      fprintf(stderr, "dirwalk: name %s %s too long\n", dir, dp->name);
    } else {
      sprintf(name, "%s/%s", dir, dp->name);
      (*fcn) (name);
    }
  }

  closedir(dfd);
}
