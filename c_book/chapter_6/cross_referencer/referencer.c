#include "referencer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAXLINE 10000
#define MAXWORDS 10000
#define MAXWORD 100

struct reference {
  char *word;
  int line_num[MAXLINE];
};

struct referencer {
  struct reference *refs[MAXWORDS];
  int cur_index;
};

struct reference *init_reference(char *word, int line_num) {
  struct reference *r;

  r = (struct reference *) malloc(sizeof(struct reference));
  r->word = strdup(word);
  r->line_num[line_num] = 1;

  return r;
}

void insert_word(struct referencer *ref, char *word, int line_num) {
  int i, cmp;
  struct reference *cur_ref;
  char *cur_word;

  for (i=0; i < ref->cur_index; i++) {
    cur_ref = ref->refs[i];
    cur_word = cur_ref->word;
    if (strcmp(cur_word, word) == 0) {
      cur_ref->line_num[line_num] = 1;
      return;
    }
  }

  ref->refs[ref->cur_index++] = init_reference(word, line_num);
}


struct referencer *init_referencer(void) {
  int i;
  struct referencer *ref;

  ref = (struct referencer *) malloc(sizeof(struct referencer));
  ref->cur_index = 0;

  for (i=0; i < MAXWORDS; i++) {
    ref->refs[i] = NULL;
  }

  return ref;
}

void print_referencer(struct referencer *ref) {
  int i, j, first;

  for (i = 0; ref->refs[i] != NULL; i++) {
    first = 1;
    printf("the word is \"%s\" ", ref->refs[i]->word);
    printf("the line numbers are: ");
    printf("[");
    for (j = 0; j < MAXLINE; j++) {
      if (ref->refs[i]->line_num[j]) {
        if (first) {
          printf("%d", j);
          first = 0;
        } else {
          printf(" ");
          printf("%d", j);
        }
      }
    }
    printf("]");
    printf("\n");
  }
}
