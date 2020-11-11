#include <stdio.h>
#include <unistd.h>

#define NALLOC  1024   /* minimum #units to request */


typedef long Align;     /* for alignment to long boundary */

union header {          /* block header */
  struct {
    union header *ptr;  /* next block on the the free list */
    unsigned size;      /* size of this block */
  } s;
  Align x;              /* force alignment of blocks */
};

typedef union header Header;

static Header base;     /* empty list */
static Header *freep = NULL; /* start of free list */


static Header *morecore(unsigned nu);
void *my_malloc(unsigned nbytes);
void my_free(void *ap);
void *my_calloc(int n, unsigned size);
void bfree(void *p, unsigned n);

int main(void) {
  char *my_ptr = (char *) my_malloc(10);
  char *test_ptr = (char *) my_calloc(10, 10);
  // for (int i = 0; i < 100; i++) {
  //   printf("%d\n", test_ptr[i]);
  // }
  char arr[100];
  bfree((void *)arr, 100);
  return 0;
}

void *my_malloc(unsigned nbytes) {
  Header *p, *prevp;
  unsigned nunits;

  nunits = (nbytes + sizeof(Header) -1) / sizeof(Header) + 1;

  if ((prevp = freep) == NULL) {
    base.s.ptr = freep = prevp = &base;
    base.s.size = 0;
  }

  for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
    if (p->s.size >= nunits) { /* big enough */
      if (p->s.size == nunits) { /* exactly */
        prevp->s.ptr = p->s.ptr;
      } else { /* allocate tail end */
        p->s.size -= nunits;
        p += p->s.size;
        p->s.size = nunits;
      }
      freep = prevp;
      return (void *) (p + 1);
    }
    if (p == freep) { /* wrapped around free list */
      if ((p = morecore(nunits)) == NULL) {
        return NULL;
      }
    }
  }
}

/* morecore:  ask system for more memory */
static Header *morecore(unsigned nu) {
  char *cp;
  Header *up;

  if (nu < NALLOC) {
    nu = NALLOC;
  }

  cp = sbrk(nu * sizeof(Header));
  if (cp == (char *) -1) { /* no space left */
    return NULL;
  }
  up = (Header *) cp;
  up->s.size = nu;
  my_free((void *)(up + 1));

  return freep;
}

/* free:  put block ap in free list */
void my_free(void *ap) {
  Header *bp, *p;
  bp = (Header *) ap - 1;    /* point to block header */

  for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
    if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) {
      break;  /* freed block at start or end of arena */
    }
  }

  if (bp + bp->s.size == p->s.ptr) {    /* join to upper nbr */
    bp->s.size += p->s.ptr->s.size;
    bp->s.ptr = p->s.ptr->s.ptr;
  } else {
    bp->s.ptr = p->s.ptr;
  }

  if (p + p->s.size == bp) {          /* join to lower nbr */
    p->s.size += bp->s.size;
    p->s.ptr = bp->s.ptr;
  } else {
    p->s.ptr = bp;
  }

  freep = p;
}

/*
  my_calloc: pointer to n objects of size
  size with the storarage initialized to 0
*/
void *my_calloc(int n, unsigned size) {
  unsigned total;
  void *ptr, *p;
  char *cast;

  total = (n * size);
  if ((ptr = my_malloc(total)) == NULL) {
    return NULL;
  }

  for (p = ptr; p != ptr + total; p++) {
    cast = (char *) p;
    *cast = 0;
  }

  return ptr;
}

/*
Write a routine bfree(p,n) that will free any arbitrary block p of n characters
into the free list maintained by malloc and free.
By using bfree, a user can add a static or external array to the free list at any time.
*/

void bfree(void *p, unsigned n) {
  Header *up;

  up = (Header *) p;
  up->s.size = n;
  my_free((void *)(up + 1));
}