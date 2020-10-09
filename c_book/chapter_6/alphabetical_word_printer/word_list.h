#ifndef __WORDLIST__
#define __WORDLIST__

struct word_list {
  char *word;
  struct word_list *next;
};

struct word_list *create_list(char *word);
void append(struct word_list *head, char *word);
void print_list(struct word_list *list);


#endif /* __WORDLIST__ */
