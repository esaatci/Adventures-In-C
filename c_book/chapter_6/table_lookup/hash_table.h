#ifndef __HASH_TABLE__
#define __HASH_TABLE__


/* Table entry */
struct nlist {
  char *name;
  char *defn;
  struct nlist *next;
};

struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);

/* Exercise 6-5. Write a function undef that will remove a
name and definition from the table maintained by lookup and install.
*/
struct nlist *undef(char *s);
#endif /* __HASH_TABLE__ */
