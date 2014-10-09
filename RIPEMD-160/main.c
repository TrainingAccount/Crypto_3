#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ripemd-160.h"

int main(int argc, char *argv[])
{
  FILE* f1 = fopen("input.txt", "r");
  unsigned char input[64];
  unsigned char output[20];
  memset(output, 0, sizeof(unsigned char) * 20);
  memset(input, 0 , sizeof(unsigned char) * 64);
  size_t ilen = 0;
  int i = 0;
    while (!feof(f1)) {
          fscanf(f1 , "%c", &input[i]);
          ilen = ilen + 1;
          i = i+1;
    }
    ilen = i-1;
  RIPEMD160(input, ilen, output);
  system("PAUSE");	
  return 0;
}