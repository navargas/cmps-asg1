/******************************************************************************/
/**
@file		  main.c
@author		Nicholas Vargas
@brief		Main component of the Best Stuff Ever CS101 asg
@details
    This program was written with C style syntax with permission
    from the instructor.
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
#include <stdlib.h>
#include <string.h>
#include "uims.h"

void command_line_eval(FILE* input) {
  char    *buffer = NULL;
  size_t  n = 0;
  int chars;
  Uims* UIMS = uims.init();
  while (1) {
    // this must be freed
    chars = getline(&buffer, &n, input);
    if (chars < 0) {
      free(buffer);
      break;
    }
    // strip trailing newline
    buffer[chars-1] = 0;
    uims.add(UIMS, buffer);
    free(buffer);
    buffer = NULL;
    n = 0;
  }
  print_uims(UIMS);
  uims.free(UIMS);
}

int main(int argc, char* argv[]) {
  (void) argv; (void) argc;
  FILE* input = stdin;
  if (argc > 1) {
    input = fopen(argv[1], "r");
  }
  command_line_eval(input);
  fclose(input);
  return 0;
}
