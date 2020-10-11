#ifndef __REFERENCER__
#define __REFERENCER__
#include <stdlib.h>
#include <string.h>

struct referencer;


void insert_word(struct referencer *ref, char *word, int line_num);
struct referencer *init_referencer(void);
void print_referencer(struct referencer *ref);

#endif /* __REFERENCER__*/
