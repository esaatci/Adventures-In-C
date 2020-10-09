#ifndef __BINTREE__
#define __BINTREE__



struct bin_tree {
  /* linked list that holds our words */
  struct word_list *list;
  /* the children of the node */
  struct bin_tree *right;
  struct bin_tree *left;
};

struct bin_tree *create_empty_tree(void);
struct bin_tree *create_node(char *w);
void insert_word(struct bin_tree **r, char *w, int n);
void print_tree(struct bin_tree *r);
void delete_tree(struct bin_tree *r);


#endif /* __BINTREE__ */
