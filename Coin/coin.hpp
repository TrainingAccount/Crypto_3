#include <iostream>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

#include <cmath>
#define suff1 256*256*256
#define suff2 256*256

using namespace std;

string md5(string h);
string ToHex(unsigned int value);
unsigned int FunF(unsigned int x,unsigned int y,unsigned int z);
unsigned int FunG(unsigned int x,unsigned int y,unsigned int z);
unsigned int FunH(unsigned int x,unsigned int y,unsigned int z);
unsigned int FunI(unsigned int x,unsigned int y,unsigned int z);
unsigned int rotateLeft(unsigned int value, unsigned int shift);