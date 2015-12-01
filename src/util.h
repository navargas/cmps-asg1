#ifndef __util_h__
#define __util_h__

#define ASCII_MAP_LEN 75

typedef enum { false = 0, true = !false } bool;

extern char asciimap[ASCII_MAP_LEN];

char* allocBitseqStr(const char* digits);
void digitToBinaryString(char* opstr, char value);
int stringToBitseq(char* opstr, const char* s);
int bitseqToDigitseq(int* intarray, char* bs, int k);

#endif
