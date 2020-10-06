#include <stdio.h>


#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

struct point {
  int x;
  int y;
};


struct rect {
  struct point pt1;
  struct point pt2;
};


/* makepoint: make a point from x and y component */
struct point makepoint(int x, int y) {
  struct point temp;
  temp.x = x;
  temp.y = y;
  return temp;
}

/* addpoint: add two points */
struct addpoint(struct point p1, struct point p2) {
  p1.x += p2.x;
  p1.y += p2.y;
  return p1;
}


/* ptinrect:  return 1 if p in r, 0 if not */
int ptinrect(struct point p, struct rect r) {
  return p.x >= r.pt1.x && p.x < r.pt2.x && p.y >= r.pt1.y && p.y < r.pt2.y;
}


/* canonrect: canonicalize coordinates of rectangle */
struct rect canonrect(struct rect r) {
  struct rect temp;
  temp.pt1.x = min(r.pt1.x, r.pt2.x);
  temp.pt1.y = min(r.pt1.y, r.pt2.y);
  temp.pt2.x = max(r.pt1.x, r.pt2.x);
  temp.pt2.y = max(r.pt1.y, r.pt2.y);
  return temp;
}



struct key {
  char *word;
  int count;
} keytab[NKEYS];


int main() {
  struct point maxpt = { 320, 200 };
  printf("%p %p %p\n",&maxpt, &maxpt.x, &maxpt.y);

  return 0;
}