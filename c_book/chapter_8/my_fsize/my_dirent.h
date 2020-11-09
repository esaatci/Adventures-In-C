#define NAME_MAX 14 /* longest filename component */

typedef struct {              /* Portable directory entry */
  long ino;                   /* inode number */
  char name[NAME_MAX + 1];    /* name + terminator */
} Dirent;

typedef struct {            /* minimal DIR: no bufferig etc */
  int fd;                   /* file descriptor for the directory */
  Dirent d;
} DIR;

DIR *opendir(char *dirname);
Dirent *readdir(DIR *dfd);
void closedir(DIR *dfd);
