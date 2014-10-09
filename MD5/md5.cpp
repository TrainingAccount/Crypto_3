#include <iostream>
#include <cmath>
#include <stdlib.h>

#define suff1 256*256*256
#define suff2 256*256

using namespace std;

string ToHex(unsigned int value) {
       unsigned int inHex;
       
       char *buffer = new char[2];
	   string result = "";
	   while (value)
	   {
		   itoa(value%256, buffer, 16);
		   string out(buffer);
		   if (value%256 < 16)
		      result+="0";
		   result+=out;
		   value/=256;
       }
	   return result;
}
  
unsigned int FunF(unsigned int x,unsigned int y,unsigned int z) { 
         return (x & y)|((~x) & z);
}
unsigned int FunG(unsigned int x,unsigned int y,unsigned int z) {
         return (x & z)|((~z) & y);
}
unsigned int FunH(unsigned int x,unsigned int y,unsigned int z) {
         return (x ^ y ^ z);
}
unsigned int FunI(unsigned int x, unsigned int y, unsigned int z) {
         return (y ^ ((~z) | x));
}

unsigned int rotateLeft(unsigned int value, unsigned int shift) {
         return value << shift | value >> (32-shift);
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    string h;
    cin >> h;
    string temp;
    while (!feof(stdin)) {
          cin >> temp;
          h+= " " + temp;
    }
    int L = h.length();
    h+=0x80;
    //????????????
    int numOfWords = L/64;
    int maxLength = (numOfWords+1) * 64;
    char* flow = new char[maxLength];
    for (int i = 0 ; i <= L ; i++)
        flow[i] = h[i];
        
    for (int i = L+1 ; i < maxLength-8 ; i++)
        flow[i] = 0;
    //???????????
    long long bitLength = L*8;
    for (int i = 0 ; i < 8 ; i++) 
        flow[maxLength - 8 + i] = bitLength >> i*8;

        
    // ????????????? ????????
    unsigned int A = 0x67452301, 
        B = 0xefcdab89,
        C = 0x98badcfe,
        D = 0x10325476,
        AA, BB, CC, DD;
        
    unsigned int* T = new unsigned int[65];
    for (int i = 1 ; i < 65 ; i++) {
        T[i] = (unsigned int)(pow(2.0,32.0)* abs(sin(i)));
    }
        
    //??????? ????
    unsigned int* X = new unsigned int[maxLength/4];
    X = (unsigned int*)flow;
    
    
    
    for (int i = 0 ; i < maxLength/4 ; i+=16)
    {
        AA = A; BB = B; CC = C; DD = D;
        //????? 1
        /*[abcd k s i] a = b + ((a + F(b,c,d) + X[k] + T[i]) <<< s). 
        [ABCD  0 7  1][DABC  1 12  2][CDAB  2 17  3][BCDA  3 22  4]
        [ABCD  4 7  5][DABC  5 12  6][CDAB  6 17  7][BCDA  7 22  8]
        [ABCD  8 7  9][DABC  9 12 10][CDAB 10 17 11][BCDA 11 22 12]
        [ABCD 12 7 13][DABC 13 12 14][CDAB 14 17 15][BCDA 15 22 16] */
        
        A = B + rotateLeft(A + FunF(B,C,D) + X[i + 0] + T[1], 7);
        D = A + rotateLeft(D + FunF(A,B,C) + X[i + 1] + T[2], 12);
        C = D + rotateLeft(C + FunF(D,A,B) + X[i + 2] + T[3], 17);
        B = C + rotateLeft(B + FunF(C,D,A) + X[i + 3] + T[4], 22);
           
        A = B + rotateLeft(A + FunF(B,C,D) + X[i + 4] + T[5], 7);
        D = A + rotateLeft(D + FunF(A,B,C) + X[i + 5] + T[6], 12);
        C = D + rotateLeft(C + FunF(D,A,B) + X[i + 6] + T[7], 17);
        B = C + rotateLeft(B + FunF(C,D,A) + X[i + 7] + T[8], 22);
        
        A = B + rotateLeft(A + FunF(B,C,D) + X[i + 8] + T[9], 7);
        D = A + rotateLeft(D + FunF(A,B,C) + X[i + 9] + T[10], 12);
        C = D + rotateLeft(C + FunF(D,A,B) + X[i + 10] + T[11], 17);
        B = C + rotateLeft(B + FunF(C,D,A) + X[i + 11] + T[12], 22);
        
        A = B + rotateLeft(A + FunF(B,C,D) + X[i + 12] + T[13], 7);
        D = A + rotateLeft(D + FunF(A,B,C) + X[i + 13] + T[14], 12);
        C = D + rotateLeft(C + FunF(D,A,B) + X[i + 14] + T[15], 17);
        B = C + rotateLeft(B + FunF(C,D,A) + X[i + 15] + T[16], 22);
        
        /*[abcd k s i] a = b + ((a + G(b,c,d) + X[k] + T[i]) <<< s). 
        [ABCD  1 5 17][DABC  6 9 18][CDAB 11 14 19][BCDA  0 20 20]
        [ABCD  5 5 21][DABC 10 9 22][CDAB 15 14 23][BCDA  4 20 24]
        [ABCD  9 5 25][DABC 14 9 26][CDAB  3 14 27][BCDA  8 20 28]
        [ABCD 13 5 29][DABC  2 9 30][CDAB  7 14 31][BCDA 12 20 32]*/
        
        A = B + rotateLeft(A + FunG(B,C,D) + X[i + 1] + T[17], 5);
        D = A + rotateLeft(D + FunG(A,B,C) + X[i + 6] + T[18], 9);
        C = D + rotateLeft(C + FunG(D,A,B) + X[i + 11] + T[19], 14);
        B = C + rotateLeft(B + FunG(C,D,A) + X[i + 0] + T[20], 20);
        
        
        A = B + rotateLeft(A + FunG(B,C,D) + X[i + 5] + T[21], 5);
        D = A + rotateLeft(D + FunG(A,B,C) + X[i + 10] + T[22], 9);
        C = D + rotateLeft(C + FunG(D,A,B) + X[i + 15] + T[23], 14);
        B = C + rotateLeft(B + FunG(C,D,A) + X[i + 4] + T[24], 20);
        
        
        
        A = B + rotateLeft(A + FunG(B,C,D) + X[i + 9] + T[25], 5);
        D = A + rotateLeft(D + FunG(A,B,C) + X[i + 14] + T[26], 9);
        C = D + rotateLeft(C + FunG(D,A,B) + X[i + 3] + T[27], 14);
        B = C + rotateLeft(B + FunG(C,D,A) + X[i + 8] + T[28], 20);
        
        
        
        A = B + rotateLeft(A + FunG(B,C,D) + X[i + 13] + T[29], 5);
        D = A + rotateLeft(D + FunG(A,B,C) + X[i + 2] + T[30], 9);
        C = D + rotateLeft(C + FunG(D,A,B) + X[i + 7] + T[31], 14);
        B = C + rotateLeft(B + FunG(C,D,A) + X[i + 12] + T[32], 20);
        
        
        
        /*[abcd k s i] a = b + ((a + H(b,c,d) + X[k] + T[i]) <<< s). 
        [ABCD  5 4 33][DABC  8 11 34][CDAB 11 16 35][BCDA 14 23 36]
        [ABCD  1 4 37][DABC  4 11 38][CDAB  7 16 39][BCDA 10 23 40]
        [ABCD 13 4 41][DABC  0 11 42][CDAB  3 16 43][BCDA  6 23 44]
        [ABCD  9 4 45][DABC 12 11 46][CDAB 15 16 47][BCDA  2 23 48]*/
        
        A = B + rotateLeft(A + FunH(B,C,D) + X[i + 5] + T[33], 4);
        D = A + rotateLeft(D + FunH(A,B,C) + X[i + 8] + T[34], 11);
        C = D + rotateLeft(C + FunH(D,A,B) + X[i + 11] + T[35], 16);
        B = C + rotateLeft(B + FunH(C,D,A) + X[i + 14] + T[36], 23);
        
        
        
        A = B + rotateLeft(A + FunH(B,C,D) + X[i + 1] + T[37], 4);
        D = A + rotateLeft(D + FunH(A,B,C) + X[i + 4] + T[38], 11);
        C = D + rotateLeft(C + FunH(D,A,B) + X[i + 7] + T[39], 16);
        B = C + rotateLeft(B + FunH(C,D,A) + X[i + 10] + T[40], 23);
        
        
        
        A = B + rotateLeft(A + FunH(B,C,D) + X[i + 13] + T[41], 4);
        D = A + rotateLeft(D + FunH(A,B,C) + X[i + 0] + T[42], 11);
        C = D + rotateLeft(C + FunH(D,A,B) + X[i + 3] + T[43], 16);
        B = C + rotateLeft(B + FunH(C,D,A) + X[i + 6] + T[44], 23);
        
        
        
        A = B + rotateLeft(A + FunH(B,C,D) + X[i + 9] + T[45], 4);
        D = A + rotateLeft(D + FunH(A,B,C) + X[i + 12] + T[46], 11);
        C = D + rotateLeft(C + FunH(D,A,B) + X[i + 15] + T[47], 16);
        B = C + rotateLeft(B + FunH(C,D,A) + X[i + 2] + T[48], 23);
        
        
        
        /*[abcd k s i] a = b + ((a + I(b,c,d) + X[k] + T[i]) <<< s).
        [ABCD  0 6 49][DABC  7 10 50][CDAB 14 15 51][BCDA  5 21 52]
        [ABCD 12 6 53][DABC  3 10 54][CDAB 10 15 55][BCDA  1 21 56]
        [ABCD  8 6 57][DABC 15 10 58][CDAB  6 15 59][BCDA 13 21 60]
        [ABCD  4 6 61][DABC 11 10 62][CDAB  2 15 63][BCDA  9 21 64] */
        
        A = B + rotateLeft(A + FunI(B,C,D) + X[i + 0] + T[49], 6);
        D = A + rotateLeft(D + FunI(A,B,C) + X[i + 7] + T[50], 10);
        C = D + rotateLeft(C + FunI(D,A,B) + X[i + 14] + T[51], 15);
        B = C + rotateLeft(B + FunI(C,D,A) + X[i + 5] + T[52], 21);
        
        
        
        A = B + rotateLeft(A + FunI(B,C,D) + X[i + 12] + T[53], 6);
        D = A + rotateLeft(D + FunI(A,B,C) + X[i + 3] + T[54], 10);
        C = D + rotateLeft(C + FunI(D,A,B) + X[i + 10] + T[55], 15);
        B = C + rotateLeft(B + FunI(C,D,A) + X[i + 1] + T[56], 21);
        
        
        
        A = B + rotateLeft(A + FunI(B,C,D) + X[i + 8] + T[57], 6);
        D = A + rotateLeft(D + FunI(A,B,C) + X[i + 15] + T[58], 10);
        C = D + rotateLeft(C + FunI(D,A,B) + X[i + 6] + T[59], 15);
        B = C + rotateLeft(B + FunI(C,D,A) + X[i + 13] + T[60], 21);
        
        
        
        A = B + rotateLeft(A + FunI(B,C,D) + X[i + 4] + T[61], 6);
        D = A + rotateLeft(D + FunI(A,B,C) + X[i + 11] + T[62], 10);
        C = D + rotateLeft(C + FunI(D,A,B) + X[i + 2] + T[63], 15);
        B = C + rotateLeft(B + FunI(C,D,A) + X[i + 9] + T[64], 21);
        
        
        
        A = AA + A;
        B = BB + B;
        C = CC + C;
        D = DD + D;
    }
    
    string out = ToHex(A) + " " + ToHex(B) + " " + ToHex(C) + " " + ToHex(D);
    cout << out << endl;  
    
    return 1;
}