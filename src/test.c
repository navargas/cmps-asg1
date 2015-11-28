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
#include "minunit.h"
#include "uims.h"
#include "util.h"

int tests_run = 0;

static char* test_bool() {
  bool testBool_f = false;
  bool testBool_t = true;
  mu_assert("False does not equal 0", testBool_f == 0);
  mu_assert("True equals false", testBool_f != testBool_t);
  return 0;
}

static char* uims_initial_state() {
  mu_assert("Uims customerId does start at 0", UIMS.customerId == 0);
  return 0;
}

static char* all_tests() {
  mu_run_test(uims_initial_state);
  mu_run_test(test_bool);
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
