#ifndef __linked_list_h__
#define __linked_list_h__

typedef struct SLItem SLItem;
struct SLItem {
  char* userId;
  int customerId;
  SLItem* next;
};

/* Names from assignment pdf*/
typedef const struct sLItemList {
  SLItem* header;
  void (*pushFront)(char* uid, int cid);
  SLItem* (*find)(char* uid);
} sLItemList;
#endif
