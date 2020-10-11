#include <stdio.h>
#include <string.h>
#include "referencer.h"

#define LIM 1000

char *line;
unsigned long char_count;
char *word;


char *noise_words[] = {"the", "and", "to",
                        "must", "a", "and",
                        "off", "on", NULL};

int main() {
  int i, j, is_noise;
  struct referencer *refs = init_referencer();

  is_noise = 0;
  /* read a line */
  for (i = 1; getline(&line, &char_count, stdin) != EOF; i++) {
    /* parse each line to word */
    char *token = strtok(line, " ");
    while (token != NULL) {
      /* check if the word is a noise word */
      for (j = 0; noise_words[j] != NULL; j++) {
        if (strcmp(noise_words[j], token) == 0) {
          is_noise = 1;
          break;
        }
        is_noise = 0;
      }
      if (!is_noise && strcmp(token, "/n")) {
        insert_word(refs, token, i);
      }
      token = strtok(NULL, " ");
    }
  }
  /* print the structure */
  print_referencer(refs);
  return 0;
}
