#include <cstdlib>
#include <iostream>
using namespace std;
typedef unsigned int uint;
unsigned int rotateLeft(unsigned int value, unsigned int shift) {
         return (value << shift) | ((value) >> (32-shift));
}

uint F0(uint m, uint l, uint k) {
     return (k ^ (m & (l ^ k)));
}

uint F20(uint m, uint l, uint k) {
     return (m ^ l ^ k);
}

uint F40(uint m, uint l, uint k) {
     return ((m & l) | (k & (m | l)));
}

string ToHex(uint num) {
       char* buffer = new char[20];
       itoa(num,buffer,16);
       string out(buffer);
       return out;
}