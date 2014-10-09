#include "main.h"
#include <cmath>

int main(int argc, char *argv[])
{
    unsigned int A = 0x67452301, a = A,
                 B = 0xEFCDAB89, b = B,
                 C = 0x98BADCFE, c = C,
                 D = 0x10325476, d = D,
                 E = 0xC3D2E1F0, e = E;
    uint* K = new uint[4];    
    K[0] = 0x5A827999;
    K[1] = 0x6ED9EBA1;	
    K[2] = 0x8F1BBCDC;
    K[3] = 0xCA62C1D6;
    
    string input;
    
    freopen("output.txt", "w" , stdout);
    freopen("input.txt", "r", stdin);
    string temp;
    cin >> input;
    while (!feof(stdin)) {
          cin >> temp;
          input+= " " + temp;
    }
          

    //Выравнивание
    uint L = input.length();
    input += 0x80;
    
    int numOfWords = L/64;
    if (L%64 > 56) numOfWords++;
    int maxLength = (numOfWords+1) * 64;
    
    unsigned char* flow = new unsigned char[maxLength];
    for (int i = 0 ; i <= L ; i++)
        flow[i] = input[i];
        
    for (int i = L+1 ; i < maxLength-8 ; i++)
        flow[i] = 0;
    //ЗаписьДлины
    long long bitLength = L*8;
    for (int i = 0 ; i < 8 ; i++) {
        flow[maxLength - 8 + i] = bitLength >> (7-i)*8;   
        }
    
    uint* M = new uint[maxLength/4];
    for (int i = 0 ; i < maxLength ; i+=4)
        M[i/4] = flow[i] * pow(256.0,3.0) + flow[i+1] * pow(256.0,2.0) + flow[i+2]*256 + flow[i+3];
    
    uint* W = new uint[80];
    
    for (int i = 0 ; i < maxLength/4 ; i+=16) {
        for (int j = 0 ; j < 80 ; j++) {
            if (j < 16) 
               W[j] = M[i+j];
            else
                W[j] = rotateLeft(W[j-3] ^ W[j-8] ^ W[j-14] ^ W[j-16],1); 
                
            uint temp = 0;
            uint (*F)(uint,uint,uint);
            if (j < 20) 
               F = &F0;
            else
                if (j > 39 && j < 60)
                   F = &F40;
                else
                    F = &F20;
             
             
             temp = rotateLeft(a,5) + F(b,c,d) + e + W[j] + K[j/20];
            e = d;
            d = c;
            c = rotateLeft(b,30);
            b = a;
            a = temp;
            
        }    
        A+=a;
        B+=b;
        C+=c;
        D+=d;
        E+=e;
    }
    
    string out = ToHex(A) + " " + ToHex(B) + " " + ToHex(C) + " " + ToHex(D) + " " + ToHex(E);
        
    cout << out << endl;
    
    return EXIT_SUCCESS;
}