#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "get_word.h"
/*

steps
delete \ \n
split program in tokens by whitespace
  comments are replaced by single space
  macros are expanded
espace sequences in character constants and string literals are replaced by taking adjacent strings are concat

*/
#define PROGRAMSIZE 8192
#define WORD_LIMIT 150

char *needle = "\\\n";

static char program_buf[PROGRAMSIZE];
static int c, buf_p;

static char *line_ptr;
size_t line_size = 32;
size_t char_count;

enum token_type {
  DEFINE,
  COMMENT_START,
  COMMENT_END,
  EXPANSION,
  DONT_CARE,
};
typedef enum token_type token_type_t;

enum main_states {
  START,
  COMMENT,
  EXPAND,
  STORE
};

typedef enum main_states main_states;

enum store_states {
  DECIDE_FORM,
  FORM1,
  FORM2,
  TOKEN
};
typedef enum store_states store_states;

/* individiual state machine handlers */
void handle_start(void);
void handle_store(void);
void handle_expand(void);
void handle_comment(void);

/* main state machine states */
main_states cur_state = START;
main_states next_state;

/* parses the token and returns the type */
token_type_t parse_token(char * token);
void remove_backslash_newline(void);
void copy_line(void);

char word[WORD_LIMIT] = {0};

int main() {
  char *token;
  memset(program_buf, 0, PROGRAMSIZE);
  /* read the program line by line */
  while ((char_count = getline(&line_ptr, &line_size, stdin)) != EOF) {
    /* remove the \\n sequences */
    remove_backslash_newline();
    copy_line();
  }
  program_buf[buf_p] = '\0';
  /* start tokenizing the file */
  token = strtok(program_buf, " ");
  while (token) {
    printf("token is %s\n", token);
    token_type_t type = parse_token(token);
    switch (cur_state) {

      case START: {
        if (type == DEFINE) {
          next_state = STORE;
        } else if (type == COMMENT_START) {
          next_state = COMMENT;
        } else if (type == EXPANSION) {
          next_state = EXPAND;
        } else {
          next_state = START;
        }
        cur_state = next_state;
        break;
      }
      case STORE: {
        printf("we are here\n");
        /* check define form */
        /* form the name */
        /* form the definition */
        /* add it to the hash_table */
        break;
      }
      default: {
        break;
      }
    }
    break;
    // token = strtok(NULL, " ");
  }
  return 0;
}

void remove_backslash_newline(void) {
  char *p;
  while ((p = strstr(line_ptr, needle)) != NULL) {
    *p++ = 0;
    *p = 0;
  }
}
void copy_line(void) {
  int i;

  for (i = 0; i < char_count; i++) {
    if (line_ptr[i] != 0) {
      program_buf[buf_p++] = line_ptr[i];
    }
  }
}

token_type_t parse_token(char *token) {
  int token_len = strlen(token);
  int c, sp;
  sp = 0;

  if (strcmp(token, "#define") == 0) {
    return DEFINE;
  } else if (token_len == 2 && token[0] == '/' && token[1] == '*') {
    return COMMENT_START;
  } else if (token_len == 2 && token[0] == '*' && token[1] == '/') {
    return COMMENT_END;
  } else {

    while ((c = getword(word, token, WORD_LIMIT, token_len, sp) != ']')) {
      if (lookup(word)) {
        return EXPANSION;
      }
    }
  }

  return DONT_CARE;
}