#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
/*
Exercise 6-4. Write a program that prints the distinct words in its input sorted into decreasing order of frequency of occurrence.
Precede each word by its count.
*/

#define TABLESIZE (5096 * 2)

/* assume int won't overflow */
struct pair {
  char *word;
  int count;
};

struct pair table[TABLESIZE];
int top = 0;


void insert_word(char *w);
void print_words();
void init_table(void);
void selection_sort(void);
void swap(int i, int j);
/* removes the newline and points and commas */
void trim_and_lower(char *w);
char *token, *line;
unsigned long char_count;



int main() {
  init_table();
  /* Read input */
  while (getline(&line, &char_count, stdin) != EOF) {
    /* parse the words */
    token = strtok(line, " ");
    while (token) {
      /* insert the words to our structure */
      trim_and_lower(token);
      insert_word(token);
      token = strtok(NULL, " ");
    }
  }
  /* sort the words */
  selection_sort();
  /* print the words in sorted order */
  print_words();
  return 0;
}



/* Planning

  Distinct words
  sort by frequency

  simple approach
    Insert words to an array insertion O(n)
    sort the array based on freq O(nlgn)

  slightly complicated
    Hash Table insertion O(1)
    sort it O(nlgn)

  Another Approach
    Hash Table insertion O(1)
    Heap

*/
void init_table(void) {
  int i;
  for (i = 0; i < TABLESIZE; i++) {
    table[i].word = NULL;
    table->count = 0;
  }
}

void insert_word(char *w) {
  int i;
  char *cur;
  if (w[0] == '\0') {
    return;
  }
  for (i = 0; i < top; i++) {
    cur = table[i].word;
    if (strcmp(cur, w) == 0) {
      table[i].count++;
      return;
    }
  }
  table[top].word = strdup(w);
  table[top].count++;
  top++;
}

void print_words(struct pair *t) {
  int i;
  for (i = 0; table[i].word != NULL; i++) {
    printf("%s %d\n", table[i].word, table[i].count);
  }
}

void trim_and_lower(char *w) {
  for (; *w != '\0'; w++) {
    if (isalpha(*w)) {
      *w = tolower(*w);
    } else if (*w == '.' || *w == ',') {
      *w = '\0';
    } else if (*w == '\n') {
      *w = '\0';
      return;
    }
  }
}

void selection_sort(void) {
  int i, j;
  int max, idx;

  for (i = 0; table[i].word != NULL; i++) {
    max = -1;
    for (j = i; table[j].word != NULL; j++) {
      if (table[j].count > max) {
        max = table[j].count;
        idx = j;
      }
    }
    swap(i, idx);
  }
}


void swap(int i, int j) {

  struct pair temp;
  int s_len;

  temp.word = strdup(table[i].word);
  temp.count = table[i].count;

  table[i].word = strdup(table[j].word);
  table[i].count = table[j].count;

  table[j].word = strdup(temp.word);
  table[j].count = temp.count;
}