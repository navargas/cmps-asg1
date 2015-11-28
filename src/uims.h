#ifndef __uims_h__
#define __uims_h__

#include "util.h"

typedef int hashItem; // placeholder

/* wonky namespace style from
 * http://stackoverflow.com/a/28535585/3875024
 * Names from assignment pdf*/
typedef const struct uims {
  int salt;
  size_t m; // hash table load
  int customerId;
  hashItem* userT; // hash table data
  bool (*isAvailable)(char* uid);
  int (*lookupCustomerId)(char* uid);
  int (*hash)(char* uid);
  void (*generateSalt)(void);
  int (*load)(void);
  void (*reallocate)(void);
} uims;

extern const uims UIMS;
#endif
