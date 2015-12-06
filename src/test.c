/******************************************************************************/
/**
@file		  test.c
@author		Nicholas Vargas
@brief		Test component of the Best Stuff Ever CS101 asg
@details
    Test code for project
    November 2015
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
#include <string.h>
#include <stdlib.h>
#include "minunit.h"
#include "uims.h"
#include "util.h"
#include "linked_list.h"
#include "primes.h"

int tests_run = 0;

static char* test_bool() {
  bool testBool_f = false;
  bool testBool_t = true;
  mu_assert("False does not equal 0", testBool_f == 0);
  mu_assert("False is true", !testBool_f);
  mu_assert("True is false", testBool_t);
  mu_assert("True equals false", testBool_f != testBool_t);
  return 0;
}

static char* uims_initial_state() {
  Uims* new_uims = uims.init();
  mu_assert("Uims customerId does start at 0", new_uims->customerId == 0);
  print_uims(new_uims);
  uims.free(new_uims);
  return 0;
}

static char* test_sLItemList() {
  SLItemList* list = sLItemList.init();
  char* uid = "thisistheuid";
  char* uid2 = "thisistheuid2";
  sLItemList.pushFront(list, uid, 1);
  sLItemList.pushFront(list, uid2, 2);
  sLItemList.pushFront(list, "another item", 3);
  SLItem* firstSLItem = sLItemList.find(list, uid);
  SLItem* secondSLItem = sLItemList.find(list, uid2);
  SLItem* doesNotExist = sLItemList.find(list, "thisdoesnotexist");
  mu_assert("first item customer id does not equal 1", firstSLItem->customerId == 1);
  mu_assert("second item customer id does not equal 2", secondSLItem->customerId == 2);
  mu_assert("a match was found for a nonexistant uid", doesNotExist == NULL);
  sLItemList.free(list);
  return 0;
}

static char* test_binseq() {
  char binstr[6+1];
  digitToBinaryString(binstr, 4);
  mu_assert("binary sequence for 4 does not equal 4",
            strcmp(binstr, "000100") == 0);
  digitToBinaryString(binstr, 0xF);
  mu_assert("binary sequence for 15 does not equal 1111",
            strcmp(binstr, "001111") == 0);
  digitToBinaryString(binstr, 0b111111);
  mu_assert("binary sequence for 0b111111 does not equal 111111",
            strcmp(binstr, "111111") == 0);
  const char s1[32] = "moLLY1";
  const char expected[42] = "010110011000101111101111111100000001";
  char* seqstr = allocBitseqStr(s1);
  int res = stringToBitseq(seqstr, s1);
  mu_assert("stringToBitseq did not return status 0",
            res == 0);
  mu_assert("Sample string moLLY1 does not equal expected output",
            strcmp(expected, seqstr) == 0);
  res = stringToBitseq(seqstr, "0");
  mu_assert("stringToBitseq did not return status 0",
            res == 0);
  mu_assert("The zero character does not map to 62",
            strcmp("111110", seqstr) == 0);
  free(seqstr);
  return 0;
}

static char* test_bitseqToDigitseq() {
  char tstring[30] = "0000111100001111"; // k=4 should be 0,15,0,15
  int* tarray = calloc(40,sizeof(int));
  int expected4[4] = {0,15,0,15};
  int expected8[2] = {15,15};
//int bitseqToDigitseq(int* intarray, char* bs, int k) {
  bitseqToDigitseq(tarray, tstring, 4);
  mu_assert("Bit sequence does not equal digit sequence when k=4",
            memcmp(tarray, expected4, sizeof(expected4)) == 0);
  bitseqToDigitseq(tarray, tstring, 8);
  mu_assert("Bit sequence does not equal digit sequence when k=8",
            memcmp(tarray, expected8, sizeof(expected8)) == 0);
  free(tarray);
  return 0;
}

static char* test_primes() {
  mu_assert("The 1000th prime is not 7919", primes[999] == 7919);
  return 0;
}

static char* all_tests() {
  mu_run_test(uims_initial_state);
  mu_run_test(test_bool);
  mu_run_test(test_sLItemList);
  mu_run_test(test_binseq);
  mu_run_test(test_bitseqToDigitseq);
  mu_run_test(test_primes);
  return 0;
}

int main(int argc, char* argv[]) {
  (void) argc; (void) argv;
  printf("Testing ===================================================\n");
  char *result = all_tests();
  if (result != 0) {
   printf("%s\n", result);
  }
  else {
   printf("ALL TESTS PASSED\n");
  }
  printf("Tests run: %d\n", tests_run);
  printf("===========================================================\n");
  return result != 0;
}
