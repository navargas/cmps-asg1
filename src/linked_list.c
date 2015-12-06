/******************************************************************************/
/**
@file		  linked_list.c
@author		Nicholas Vargas
@brief		Singlely linked list implementation
@details
    This file also contains the definition for the linked list item type
@license
    Licensed under the Apache License, Version 2.0 (the "License");
		you may not use this file except in compliance with the License.
		You may obtain a copy of the License at
			http://www.apache.org/licenses/LICENSE-2.0
@par
		Unless required by applicable law or agreed to in writing,
		software distributed under the License is distributed on an
		"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
		either express or implied. See the License for the specific
		language governing permissions and limitations under the
		License.
*/
/******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include "linked_list.h"


SLItemList* init(void) {
  SLItemList* item = malloc(sizeof(SLItemList));
  item->header = NULL;
  return item;
}

void pushFront(SLItemList* this, char* uid, int cid) {
  SLItem* newItem = malloc(sizeof(SLItem));
  SLItem* oldHead = this->header;
  // 17 = 16 chars + null terminator
  char* uidstr = malloc(sizeof(char) * 17);
  strcpy(uidstr, uid);
  newItem->userId = uidstr;
  newItem->customerId = cid;
  newItem->next = oldHead;
  this->header = newItem;
}

void freeSLItemList(SLItemList* this) {
  SLItem* onItem = this->header;
  while (onItem != NULL) {
    SLItem* lastItem = onItem;
    onItem = lastItem->next;
    free(lastItem->userId);
    free(lastItem);
  }
  free(this);
}

SLItem* find(SLItemList* this, char* uid) {
  SLItem* onItem = this->header;
  while (onItem != NULL) {
    if (strcmp(onItem->userId, uid) == 0) {
      return onItem;
    }
    onItem = onItem->next;
  }
  return NULL;
}

const SLItemList sLItemList = {
  .init = init,
  .pushFront = pushFront,
  .find = find,
  .free = freeSLItemList
};
