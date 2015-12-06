#ifndef __uims_h__
#define __uims_h__

#include "util.h"
#include "linked_list.h"


typedef SLItemList* hashItem; // placeholder

/* wonky namespace style from
 * http://stackoverflow.com/a/28535585/3875024
 * Names from assignment pdf*/
typedef struct Uims Uims;
struct Uims {
  int salt;
  size_t m; // hash table load
  int customerId;
  int table_size;
  hashItem* userT; // hash table data
  Uims* (*init)(void);
  bool (*isAvailable)(Uims* this, char* uid);
  void (*add)(Uims* this, char* uid);
  int (*lookupCustomerId)(Uims* this, char* uid);
  int (*hash)(Uims* this, char* uid);
  void (*generateSalt)(Uims* this);
  float (*load)(Uims* this);
  void (*reallocate)(Uims* this);
  void (*free)(Uims* this);
};

void print_uims(Uims* item);

extern const Uims uims;
#endif
