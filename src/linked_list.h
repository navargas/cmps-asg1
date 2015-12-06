#ifndef __linked_list_h__
#define __linked_list_h__

typedef struct SLItem SLItem;
struct SLItem {
  char* userId;
  int customerId;
  SLItem* next;
};

/* Names from assignment pdf*/
typedef struct SLItemList SLItemList;
struct SLItemList {
  SLItem* header;
  SLItemList* (*init)(void);
  void (*pushFront)(SLItemList* this, char* uid, int cid);
  SLItem* (*find)(SLItemList* this, char* uid);
  void (*free)(SLItemList* this);
};
extern const SLItemList sLItemList;

void freeSLItemList(SLItemList* this, bool free_userId);

#endif
