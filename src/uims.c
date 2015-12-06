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
#include "primes.h"
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
  item->table_size = primes[4]; // a prime number
  item->userT = calloc(sizeof(hashItem*), item->table_size);
  return item;
}

int hashc(char* str, int table_size) {
  // 5381 magic number from http://www.cse.yorku.ca/~oz/hash.html
  // * 33 ( << 5 + 1 ) also from this algorithm
  unsigned long hash = 5381;
  int on_char = *str++;
  while (on_char) {
    hash = ((hash << 5) + hash) + on_char;
    on_char = *str++;
  }
  return hash % table_size;
}

void addc(hashItem* hashT, char* uid, int cid, int table_size) {
  int target_hash = hashc(uid, table_size);
  SLItemList* target = hashT[target_hash];
  if (target  == 0) {
    SLItemList* list = sLItemList.init();
    sLItemList.pushFront(list, uid, cid);
    hashT[target_hash] = list;
  } else {
    sLItemList.pushFront(target, uid, cid);
  }
}

void add(Uims* this, char* uid) {
  if (uims.load(this) > .75) {
    uims.reallocate(this);
  }
  addc(this->userT, uid, this->customerId++, this->table_size);
}

void reallocate(Uims* this) {
  int current_size = this->table_size;
  int new_size = current_size * 2;
  int i;
  for (i = 0; i < NUMBER_OF_PRIMES; i++) {
    if (primes[i] > new_size) {
      new_size = primes[i];
      break;
    }
  }
  hashItem* new_userT = calloc(sizeof(hashItem*), new_size);
  /* move old entries to new table */
  int c;
  /* for every item in hashTable */
  for (c = 0; c < this->table_size; c++) {
    SLItemList* item = this->userT[c];
    if (item) {
      SLItem* onItem = item->header;
      /* for each item in linked list */
      while (onItem != NULL) {
        addc(new_userT, onItem->userId, onItem->customerId, new_size);
        onItem = onItem->next;
      }
    }
  }
  int old_size = this->table_size;
  hashItem* old_userT = this->userT;
  this->table_size = new_size;
  this->userT = new_userT;
  for (c = 0; c < old_size; c++) {
    SLItemList* item = old_userT[c];
    if (item) {
      /* "false" will preserve the userId arrays */
      freeSLItemList(item, true);
    }
  }
  free(old_userT);
}

bool isAvailable(Uims* this, char* uid) {
  int target_hash = uims.hash(this, uid);
  if (this->userT[target_hash] == 0) {
    return true;
  } else if (sLItemList.find(this->userT[target_hash], uid) == NULL) {
    return true;
  }
  return false;
}

int hash(Uims* this, char* str) {
  return hashc(str, this->table_size);
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

float uimsload(Uims* this) {
  return  (float)this->customerId / (float)this->table_size;
}

const Uims uims = {
  .isAvailable = isAvailable,
  .hash = hash,
  .add = add,
  .reallocate = reallocate,
  .load = uimsload,
  .init = uimsinit,
  .free = uimsfree,
  .customerId = 0
};
