#ifndef __uims_h__

#define __uims_h__

#include "util.h"

typedef int hashItem; // placeholder

/* wonky namespace style from
 * http://stackoverflow.com/a/28535585/3875024
 * Names from assignment pdf*/
typedef const struct uims {
  bool (*isAvailable)(char* uid);
  int (*lookupCustomerId)(char* uid);
  int (*hash)(char* uid);
  void (*generateSalt)(void);
  int (*load)(void);
  void (*reallocate)(void);
  hashItem* userT; // hash table data
  size_t m; // hash table load
  int salt;
  int customerId;
} uims;

extern const uims UIMS;
#endif
