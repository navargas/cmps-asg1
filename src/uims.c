/******************************************************************************/
/**
@file		  uims.c
@author		Nicholas Vargas
@brief		User ID Management System
@details
    Contains functions associated with the storage and verification of
    user IDs
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
#include <stdio.h>
#include "uims.h"
#include "linked_list.h"

void print_uims(Uims* item) {
  int c;
  for (c = 0; c < item->table_size; c++) {
    SLItemList* on = item->userT[c];
    if (on) {
      printf("%d - ", c);
      SLItem* onItem = on->header;
      while (onItem != NULL) {
        printf(onItem->userId, "");
        if (onItem->next != NULL) printf(", ");
        onItem = onItem->next;
      }
      printf("\n");
    } else {
      //printf("%d - ", c);
    }
  }
}

Uims* uimsinit(void) {
  Uims* item = malloc(sizeof(Uims));
  item->customerId = 0;
  item->table_size = 131; // a prime number
  item->userT = calloc(sizeof(hashItem*), item->table_size);
  return item;
}

void add(Uims* this, char* uid) {
  int target_hash = uims.hash(this, uid);
  SLItemList* target = this->userT[target_hash];
  if (target  == 0) {
    SLItemList* list = sLItemList.init();
    sLItemList.pushFront(list, uid, this->customerId);
    this->userT[target_hash] = list;
  } else {
    sLItemList.pushFront(target, uid, this->customerId);
  }
}

void reallocate(Uims* this) {
}

bool isAvailable(Uims* this, char* uid) {
  return true;
}

int hash(Uims* this, char* str) {
  // 5381 magic number from http://www.cse.yorku.ca/~oz/hash.html
  // * 33 ( << 5 + 1 ) also from this algorithm
  unsigned long hash = 5381;
  int on_char = *str++;
  while (on_char) {
    hash = ((hash << 5) + hash) + on_char;
    on_char = *str++;
  }
  return hash % this->table_size;
}

void uimsfree(Uims* this) {
  int c;
  for (c = 0; c < this->table_size; c++) {
    SLItemList* item = this->userT[c];
    if (item) {
      sLItemList.free(item);
    }
  }
  free(this->userT);
  free(this);
}

const Uims uims = {
  .isAvailable = isAvailable,
  .hash = hash,
  .add = add,
  .init = uimsinit,
  .free = uimsfree,
  .customerId = 0
};
