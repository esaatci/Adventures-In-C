#include "./word_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct word_list *create_list(char *word) {
  struct word_list *temp;

  temp = (struct word_list *) malloc(sizeof(struct word_list));
  if (!temp) {
    return NULL;
  }

  temp->next = NULL;
  temp->word = strdup(word);
  return temp;
}

void append(struct word_list *head, char *word) {
  struct word_list *temp = create_list(word);
  char *buf;

  temp->next = head->next;
  head->next = temp;
  buf = temp->word;
  temp->word = head->word;
  head->word = buf;
}

void print_list(struct word_list *list) {
  struct word_list *temp = list;

  while (temp) {
    printf("%s -> ", temp->word);
    temp = temp->next;
  }
  printf("NULL\n");
}
