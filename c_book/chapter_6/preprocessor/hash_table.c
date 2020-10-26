#include "hash_table.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE];
static int table_init = 0;
static unsigned int hash(char *s);

static unsigned int hash(char *s) {
  unsigned int hash_val;
  for (hash_val = 0; *s != '\0'; s++) {
    hash_val = *s + 31 * hash_val;
  }
  return hash_val % HASHSIZE;
}

struct nlist *lookup(char *s) {
  struct nlist *h;
  for (h = hashtab[hash(s)]; h != NULL; h = h->next) {
    if (strcmp(h->name, s) == 0) {
      return h;
    }
  }
  return NULL;
}

struct nlist *install(char *name, char *defn) {
  struct nlist *np;
  unsigned int hash_val;

  if ((np = lookup(name)) == NULL) {
    np = (struct nlist *) malloc(sizeof(struct nlist));
    if (np == NULL || (np->name = strdup(name)) == NULL) {
      return NULL;
    }
    hash_val = hash(name);
    np->next = hashtab[hash_val];
    hashtab[hash_val] = np;
  } else {
    free((void *) np->defn);
  }
  if ((np->defn = strdup(defn)) == NULL) {
      return NULL;
  }
  return np;
}

struct nlist *undef(char *s) {
  struct nlist *res, *h;
  unsigned int hash_val;

  if ((res = lookup(s)) == NULL) {
    return NULL;
  }

  hash_val = hash(s);
  for (h = hashtab[hash_val]; h != NULL & h->next != res; res = res->next) {}
  if (!h->next) {
    free(h->name);
    free(h->defn);
    free(h);
  } else {
    h->next = h->next->next;
  }
  return res;
}
