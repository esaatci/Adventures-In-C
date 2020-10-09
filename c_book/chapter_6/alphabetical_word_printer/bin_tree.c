#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bin_tree.h"
#include "word_list.h"

struct bin_tree *create_empty_tree(void) {
  return NULL;
}

struct bin_tree *create_node(char *w) {
  struct bin_tree *n;
  struct word_list *l;

  n = (struct bin_tree *) malloc(sizeof(struct bin_tree));
  l = create_list(w);
  n->left = n->right = NULL;
  n->list = l;

  return n;
}

static char *get_word(struct bin_tree *r) {
  return (r && r->list) ? r->list->word : NULL;
}

void insert_word(struct bin_tree **r, char *w, int n) {
  struct bin_tree *fast, *slow, *ins;
  char *temp;
  int cmp;

  if (*r == NULL) {
    *r = create_node(w);
    return;
  }

  fast = *r;
  while (fast) {
    slow = fast;
    temp = get_word(fast);
    if ((cmp = strncmp(temp, w, n)) == 0) {
      break;
    } else if (cmp < 1) {
      fast = fast->right;
    } else {
      fast = fast->left;
    }
  }
  if (cmp == 0) {
    append(&slow->list, w);
  } else if (cmp < 0) {
    ins = create_node(w);
    slow->right = ins;
  } else {
    ins = create_node(w);
    slow->left = ins;
  }
}

void print_tree(struct bin_tree *r) {
  if (!r) {
    return;
  }
  print_tree(r->left);
  print_list(r->list);
  print_tree(r->right);
}
