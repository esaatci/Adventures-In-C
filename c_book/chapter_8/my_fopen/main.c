#include <fcntl.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <unistd.h>


#define EOF       (-1)
#define BUFSIZ    1024
#define OPEN_MAX  20    /* max #files open at once */

typedef struct _iobuf {
int  cnt;   /* characters left */
char *ptr;  /* next character position */
char *base; /* location of buffer */
int  flag;  /* mode of file access */
int  fd;    /* file descriptor */
} FILE;


#define stdin   (&_iob[0])
#define stdout  (&_iob[1])
#define stderr  (&_iob[2])


enum _flags {
  _READ  = 01,  /* file open for reading */
  _WRITE = 02,  /* file open for writing */
  _UNBUF = 04,  /* file is unbuffered */
  _EOF   = 010, /* EOF has occured in this file */
  _ERR   = 020  /* error occured on this file */
};

/* holds the files */
FILE _iob[OPEN_MAX] = {    /* stdin, stdout, stderr */
       { 0, (char *) 0, (char *) 0, _READ, 0 },
       { 0, (char *) 0, (char *) 0, _WRITE, 1 },
       { 0, (char *) 0, (char *) 0, (_WRITE | _UNBUF), 2 }
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p) ((p)->flag & _EOF) != 0)
#define ferror(p) ((p)->flag & _ERR) != 0)
#define funbuf(p) ((p)->flag & _UNBUF) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 \
                ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0 \
               ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar()   getc(stdin)
#define putcher(x)  putc((x), stdout)

#define PERMS 0666


FILE *fopen(char *name, char *mode) {
  int fd;
  FILE *fp;
  /* check for invalid mode */
  if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
    return NULL;
  }

  for (fp = _iob; fp < _iob + OPEN_MAX; fp++) {
    if ((fp->flag & (_READ | _WRITE)) == 0) { /* found free slot */
        break;
    }
  }

  if (fp >= _iob + OPEN_MAX) { /* no free slots */
      return NULL;
  }

  if (*mode == 'w') {
    fd = creat(name, PERMS);
  } else if (*mode == 'a') {
    if ((fd = open(name, O_WRONLY, 0)) == -1) {
        fd = creat(name, PERMS);
    }
    lseek(fd, 0L, 2);
  } else {
    fd = open(name, O_RDONLY, 0);
  }

  if (fd == -1) { /* couldn’t access name */
    return NULL;
  }

  fp->fd = fd;
  fp->cnt = 0;
  fp->base = NULL;
  fp->flag = (*mode == 'r') ? _READ : _WRITE;

  return fp;
}

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp) {
  int bufsize;

  if ((fp->flag & (_READ | _EOF | _ERR)) != _READ) {
    return EOF;
  }
  bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

  if (fp->base == NULL) {
    if ((fp->base = (char *) malloc(bufsize)) == NULL) {
      return EOF;
    }
  }

  fp->ptr = fp->base;
  fp->cnt = read(fp->fd, fp->ptr, bufsize);
  if (--fp->cnt < 0) {
    if (fp->cnt == -1) {
      fp->flag |= EOF;
    } else {
      fp->flag |= _ERR;
    }
    fp->cnt = 0;
    return EOF;
  }
  return (unsigned char) *fp->ptr++;
}

/* _flushbuf: clear the input buffer and set the first char with s*/
int _flushbuf(int s, FILE * fp) {
  char *pt;
  int i;

  if (fp->flag & _ERR) {
    return EOF;
  }

  if (fp->flag & _EOF) {
    fp->flag &= ~_EOF;
  }

  if (fp->flag & _UNBUF) {
    *fp->base = (unsigned char) s;
    return 0;
  }

  fp->cnt = 1;
  fp->ptr = fp->base;
  *fp->ptr++ = s;

  return 0;
}

/* fclose closes and deinit FILE */
int fclose(FILE *fp) {
  FILE *fptr;
  int found, flushed;

  found = 0;
  for (fptr = _iob; fptr < _iob + OPEN_MAX; fptr++) {
    if (fptr->fd == fp->fd) {
      found = 1;
      break;
    }
  }
  if (!found) {
    return 1;
  }

  fp->ptr = NULL;
  free(fp->base);

  fp->fd = -1;
  fp->cnt = 0;
  fp->flag = 0;

  return 0;
}

/*
is identical to lseek except that fp is a file pointer instead of a
file descriptor and return value is an int status, not a position.
*/

int fseek(FILE *fp, long offset, int origin) {
  int new_cnt;
  char *cur;
  enum position {
    START = 0,
    CURRENT = 1,
    END = 2
  };
  /* error checks */
  if (!fp) {
    return 1;
  }
  if (origin < 0 || origin > 2) {
    return 1;
  }
  if (fp->flag & _ERR) {
    return 1;
  }
  if (fp->flag & _UNBUF) {
    return 0;
  }

  switch (origin) {
    case START: {
      cur = fp->ptr;
      fp->ptr = fp->base;
      if (offset < 0 || offset >= BUFSIZ) {
        fp->ptr = cur;
        return 1;
      }
      fp->ptr += offset;
      if (cur > fp->ptr) {
        new_cnt = cur - fp->ptr;
        fp->cnt += new_cnt;
      } else {
        new_cnt = fp->ptr - cur;
        fp->cnt -= new_cnt;
      }
      break;
    }
    case CURRENT: {
      cur = fp->ptr;
      fp->ptr += offset;
      /* pointer exceeds the total size or smaller than base */
      if (fp->ptr > fp->base + BUFSIZ || fp->ptr < fp->base) {
        fp->ptr = cur;
        return 1;
      }
      if (cur > fp->ptr) {
        new_cnt = cur - fp->ptr;
        fp->cnt += new_cnt;
      } else {
        new_cnt = fp->ptr - cur;
        fp->cnt -= new_cnt;
      }
      break;
    }
    case END: {
      cur = fp->ptr;
      if (offset > 0) {
        return 1;
      }
      fp->ptr += offset;
      if (fp->ptr < fp->base) {
        fp->ptr = cur;
        return 1;
      }
      new_cnt = cur - fp->ptr;
      fp->cnt += new_cnt;
      break;
    }
  }
  return 0;
}



int main() {
  FILE *fp = fopen("Makefile", "r");
  return 0;
}
