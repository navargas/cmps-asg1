/******************************************************************************/
/**
@file		  util.c
@author		Nicholas Vargas
@brief		Utils, etc
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

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

/* This data was generated from utils/gen_ascii_map.py
 * This allows for O(1) time lookup of characters in
 * the charmap provided by the assignment pdf.
 * Letters are looked up in the following way:
 *    asciimap[char - 48] = position in assignment character list*/
char asciimap[ASCII_MAP_LEN] =
    {0,1,2,3,4,5,6,7,8,9,255,255,255,255,255,255,255,36,37,38,39,
     40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,
     60,61,255,255,255,255,255,255,10,11,12,13,14,15,16,17,18,19,
     20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35};

/* There are 6 * sizeof(char) * len(digits) + 1 (nullplug) bytes in a Bitseq
 * This must be freed by the caller*/
char* allocBitseqStr(const char* digits) {
  size_t stingLength = strlen(digits);
  char* array = malloc(sizeof(char) * 6 * stingLength + 1);
  return array;
}

void digitToBinaryString(char* opstr, char value) {
  // opstr will always be 6 digits
  //char* opstr = calloc(sizeof(char) * 6 + 1);
  //memset(opstr, 0, 6+1);
  assert(value <= 0b111111);
  opstr[6] = '\0'; //null plug
  char mask = 0b100000 << 1;
  // itoa is not defined on my compiler
  while (mask >>= 1) {
    *opstr++ = !!(mask & value) + '0';
  }
}

int stringToBitseq(char* bitarray, const char* s) {
  char* on = (char *)s;
  int index = 0;
  char toBin[7];
  while (*on != '\0') {
    if (*on-48 >= ASCII_MAP_LEN || asciimap[*on-48] == 255) {
      fprintf(stderr, "Invalid character <%c> passed to stringToBitseq\n", *on);
      return 1;
    }
    char mapval = asciimap[*on-48];
    digitToBinaryString(toBin, mapval);
    strncpy(bitarray+(index*6), toBin, 6);
    ++index;
    ++on;
  }
  bitarray[(index*6)] = 0;
  return 0;
}

int bitseqToDigitseq(int* intarray, char* bs, int k) {
  int k_segment = 0;
  int c = 0;
  while (*bs != 0) {
    for (c = 0; c<k; c++) {
      assert(*bs == '0' || *bs == '1');
      k_segment <<= 1;
      k_segment = k_segment | (*bs - '0');
      ++bs;
    }
    *intarray = k_segment;
    ++intarray;
    k_segment = 0;
  }
  return 0;
}
