#ifndef __BINTREE__
#define __BINTREE__
#include "word_list.h"


struct bin_tree {
  /* linked list that holds our words */
  struct word_list *list;
  /* the children of the node */
  struct bin_tree *right;
  struct bin_tree *left;
};


struct bin_tree *create_node(void);
void set_list(struct word_list *l);
char *get_word(struct bin_tree *r);
void insert_word(struct bin_tree *r);
void print_tree(struct bin_tree *r);

#endif /* __BINTREE__ */
