#include "ripemd-160.h"
/*
 * 32-bit integer manipulation macros (little endian)
 */
 
#ifndef GET_UINT32_LE
#define GET_UINT32_LE(n,b,i)                 \
{                                            \
   ( n ) = ( ( uint ) b[ i     ]        )    \
         | ( ( uint ) b[ i + 1 ] << 8   )    \
         | ( ( uint ) b[ i + 2 ] << 16  )    \
         | ( ( uint ) b[ i + 3 ] << 24  );   \
}
#endif

#ifndef GET_UINT32_BE
#define GET_UINT32_BE(n,b,i)                 \
{                                            \
   ( n ) = ( ( uint ) b[ i     ] << 24  )    \
         | ( ( uint ) b[ i + 1 ] << 16  )    \
         | ( ( uint ) b[ i + 2 ] << 8   )    \
         | ( ( uint ) b[ i + 3 ]        );   \
}
#endif

#ifndef PUT_UINT32_LE
#define PUT_UINT32_LE(n,b,i)                                \
{                                                           \
   ( b[ i     ] = ( unsigned char ) ( ( n )       );        \
   ( b[ i + 1 ] = ( unsigned char ) ( ( n ) >> 8  );        \
   ( b[ i + 2 ] = ( unsigned char ) ( ( n ) >> 16 );        \
   ( b[ i + 3 ] = ( unsigned char ) ( ( n ) >> 24 );        \
}
#endif

/*
 * RIPEMD160 context setup
 */

void RIPEMD160_starts( RIPEMD160_context* ctx )
{
     ctx->state[0] = 0x67452301;
     ctx->state[1] = 0xEFCDAB89;
     ctx->state[2] = 0x98BADCFE;
     ctx->state[3] = 0x10325476;
     ctx->state[4] = 0xC3D2E1F0;
}

void RIPEMD160_process( RIPEMD160_context* ctx, const unsigned char data[64] )
{
     uint temp, W[16], A, B, C, D, E,
          a, b, c, d, e;
     
     GET_UINT32_LE(W[0 ], data, 0 );
     GET_UINT32_LE(W[1 ], data, 4 );
     GET_UINT32_LE(W[2 ], data, 8 );
     GET_UINT32_LE(W[3 ], data, 12);
     GET_UINT32_LE(W[4 ], data, 16);
     GET_UINT32_LE(W[5 ], data, 20);
     GET_UINT32_LE(W[6 ], data, 24);
     GET_UINT32_LE(W[7 ], data, 28);
     GET_UINT32_LE(W[8 ], data, 32);
     GET_UINT32_LE(W[9 ], data, 36);
     GET_UINT32_LE(W[10], data, 40);
     GET_UINT32_LE(W[11], data, 44);
     GET_UINT32_LE(W[12], data, 48);
     GET_UINT32_LE(W[13], data, 52);
     GET_UINT32_LE(W[14], data, 56);
     GET_UINT32_LE(W[15], data, 60);
     
#define rol(n,s) (( n << s ) | ( ( n & 0xFFFFFFFF ) >> ( 32 - s ) ) )

#define P(a,b,c,d,e,x,s)                                                     \
{                                                                            \
        a = rol((a + f(b,c,d) + x + k ),s) + e; c = rol( c , 10 );               \
}

     A = ctx->state[0]; 
     B = ctx->state[1];
     C = ctx->state[2];
     D = ctx->state[3];
     E = ctx->state[4];
     a = ctx->state[0]; 
     b = ctx->state[1];
     c = ctx->state[2];
     d = ctx->state[3];
     e = ctx->state[4];
     
#define f(x,y,z) (x ^ y ^ z)
#define k 0x00000000

     P(A,B,C,D,E,W[0 ],11);
     P(E,A,B,C,D,W[1 ],14);
     P(D,E,A,B,C,W[2 ],15);
     P(C,D,E,A,B,W[3 ],12);
     P(B,C,D,E,A,W[4 ],5 );
     P(A,B,C,D,E,W[5 ],8 );
     P(E,A,B,C,D,W[6 ],7 );
     P(D,E,A,B,C,W[7 ],9 );
     P(C,D,E,A,B,W[8 ],11);
     P(B,C,D,E,A,W[9 ],13);
     P(A,B,C,D,E,W[10],14);
     P(E,A,B,C,D,W[11],15);
     P(D,E,A,B,C,W[12],6 );
     P(C,D,E,A,B,W[13],7 );
     P(B,C,D,E,A,W[14],9 );
     P(A,B,C,D,E,W[15],8 );
     
#undef f
#undef k

#define f(x,y,z) ((x & y) | ((~x) & z))
#define k 0x5A827999

     P(E,A,B,C,D,W[7 ],7 );
     P(D,E,A,B,C,W[4 ],6 );
     P(C,D,E,A,B,W[13],8 );
     P(B,C,D,E,A,W[1 ],13);
     P(A,B,C,D,E,W[10],11);
     P(E,A,B,C,D,W[6 ],9 );
     P(D,E,A,B,C,W[15],7 );
     P(C,D,E,A,B,W[3 ],15);
     P(B,C,D,E,A,W[12],7 );
     P(A,B,C,D,E,W[0 ],12);
     P(E,A,B,C,D,W[9 ],15);
     P(D,E,A,B,C,W[5 ],9 );
     P(C,D,E,A,B,W[2 ],11);
     P(B,C,D,E,A,W[14],7 );
     P(A,B,C,D,E,W[11],13); 
     P(E,A,B,C,D,W[8 ],12);   
     
#undef f
#undef k

#define f(x,y,z) ((x | (~y)) ^ z)
#define k 0x6ED9EBA1

     P(D,E,A,B,C,W[3 ],11);
     P(C,D,E,A,B,W[10],13);
     P(B,C,D,E,A,W[14],6 );
     P(A,B,C,D,E,W[4 ],7 );
     P(E,A,B,C,D,W[9 ],14);
     P(D,E,A,B,C,W[15],9 );
     P(C,D,E,A,B,W[8 ],13);
     P(B,C,D,E,A,W[1 ],15);
     P(A,B,C,D,E,W[2 ],14);
     P(E,A,B,C,D,W[7 ],8 );
     P(D,E,A,B,C,W[0 ],13);
     P(C,D,E,A,B,W[6 ],6 );
     P(B,C,D,E,A,W[13],5 );
     P(A,B,C,D,E,W[11],12); 
     P(E,A,B,C,D,W[5 ],7 );
     P(D,E,A,B,C,W[12],5 );

#undef f
#undef k

#define f(x,y,z) ((x & z) | (y & (~z)))
#define k 0x8F1BBCDC

     P(C,D,E,A,B,W[1 ],11);
     P(B,C,D,E,A,W[9 ],12);
     P(A,B,C,D,E,W[11],14);
     P(E,A,B,C,D,W[10],15);
     P(D,E,A,B,C,W[0 ],14);
     P(C,D,E,A,B,W[8 ],15);
     P(B,C,D,E,A,W[12],9 );
     P(A,B,C,D,E,W[4 ],8 );
     P(E,A,B,C,D,W[13],9 );
     P(D,E,A,B,C,W[3 ],14);
     P(C,D,E,A,B,W[7 ],5 );
     P(B,C,D,E,A,W[15],6 );
     P(A,B,C,D,E,W[14],8 ); 
     P(E,A,B,C,D,W[5 ],6 );
     P(D,E,A,B,C,W[6 ],5 );
     P(C,D,E,A,B,W[2 ],12);

#undef f
#undef k

#define f(x,y,z) (x ^ (y | (~z)))
#define k 0xA953FD4E

     P(B,C,D,E,A,W[4 ],9 );
     P(A,B,C,D,E,W[0 ],15);
     P(E,A,B,C,D,W[5 ],5 );
     P(D,E,A,B,C,W[9 ],11);
     P(C,D,E,A,B,W[7 ],6 );
     P(B,C,D,E,A,W[12],8 );
     P(A,B,C,D,E,W[2 ],13);
     P(E,A,B,C,D,W[10],12);
     P(D,E,A,B,C,W[14],5 );
     P(C,D,E,A,B,W[1 ],12);
     P(B,C,D,E,A,W[3 ],13);
     P(A,B,C,D,E,W[8 ],14); 
     P(E,A,B,C,D,W[11],11);
     P(D,E,A,B,C,W[6 ],8 );
     P(C,D,E,A,B,W[15],5 );
     P(B,C,D,E,A,W[13],6 );
     
#undef f
#undef k
     
     temp = ctx->state[1] + C;
     ctx->state[1] = ctx->state[2] + D;
     ctx->state[2] = ctx->state[3] + E;
     ctx->state[3] = ctx->state[4] + A;
     ctx->state[4] = ctx->state[0] + B;
     ctx->state[0] = temp;
     
#define f(x,y,z) (x ^ (y | (~z)))
#define k 0x50A28BE6
     
     P(a,b,c,d,e,W[5 ],8 );
     P(e,a,b,c,d,W[14],9 );
     P(d,e,a,b,c,W[7 ],9 );
     P(c,d,e,a,b,W[0 ],11);
     P(b,c,d,e,a,W[9 ],13);
     P(a,b,c,d,e,W[2 ],15);
     P(e,a,b,c,d,W[11],15);
     P(d,e,a,b,c,W[4 ],5 );
     P(c,d,e,a,b,W[13],7 );
     P(b,c,d,e,a,W[6 ],7 );
     P(a,b,c,d,e,W[15],8 );
     P(e,a,b,c,d,W[8 ],11);
     P(d,e,a,b,c,W[1 ],14);
     P(c,d,e,a,b,W[10],14);
     P(b,c,d,e,a,W[3 ],12);
     P(a,b,c,d,e,W[12],6 );
     
#undef f
#undef k

#define f(x,y,z) ((x & z) | (y & (~z)))
#define k 0x5C4DD124

     P(e,a,b,c,d,W[6 ],9 );
     P(d,e,a,b,c,W[11],13);
     P(c,d,e,a,b,W[3 ],15);
     P(b,c,d,e,a,W[7 ],7 );
     P(a,b,c,d,e,W[0 ],12);
     P(e,a,b,c,d,W[13],8 );
     P(d,e,a,b,c,W[5 ],9 );
     P(c,d,e,a,b,W[10],11);
     P(b,c,d,e,a,W[14],7 );
     P(a,b,c,d,e,W[15],7 );
     P(e,a,b,c,d,W[8 ],12);
     P(d,e,a,b,c,W[12],7 );
     P(c,d,e,a,b,W[4 ],6 );
     P(b,c,d,e,a,W[9 ],15);
     P(a,b,c,d,e,W[1 ],13);
     P(e,a,b,c,d,W[2 ],11);
     
#undef f
#undef k

#define f(x,y,z) ((x | (~y)) ^ z)
#define k 0x6D703EF3

     P(d,e,a,b,c,W[15],9 );
     P(c,d,e,a,b,W[5 ],7 );
     P(b,c,d,e,a,W[1 ],15);
     P(a,b,c,d,e,W[3 ],11);
     P(e,a,b,c,d,W[7 ],8 );
     P(d,e,a,b,c,W[14],6 );
     P(c,d,e,a,b,W[6 ],6 );
     P(b,c,d,e,a,W[9 ],14);
     P(a,b,c,d,e,W[11],12);
     P(e,a,b,c,d,W[8 ],13);
     P(d,e,a,b,c,W[12],5 );
     P(c,d,e,a,b,W[2 ],14);
     P(b,c,d,e,a,W[10],13);
     P(a,b,c,d,e,W[0 ],13);
     P(e,a,b,c,d,W[4 ],7 );
     P(d,e,a,b,c,W[13],5 );

#undef f
#undef k

#define f(x,y,z) ((x & y) | ((~x) & z))
#define k 0x7A6D76E9

     P(c,d,e,a,b,W[8 ],15);
     P(b,c,d,e,a,W[6 ],5 );
     P(a,b,c,d,e,W[4 ],8 );
     P(e,a,b,c,d,W[1 ],11);
     P(d,e,a,b,c,W[3 ],14);
     P(c,d,e,a,b,W[11],14);
     P(b,c,d,e,a,W[15],6 );
     P(a,b,c,d,e,W[0 ],14);
     P(e,a,b,c,d,W[5 ],6 );
     P(d,e,a,b,c,W[12],9 );
     P(c,d,e,a,b,W[2 ],12);
     P(b,c,d,e,a,W[13],9 );
     P(a,b,c,d,e,W[9 ],12);
     P(e,a,b,c,d,W[7 ],5 );
     P(d,e,a,b,c,W[10],15);
     P(c,d,e,a,b,W[14],8 );

#undef f
#undef k

#define f(x,y,z) (x ^ y ^ z)
#define k 0x00000000

     P(b,c,d,e,a,W[12],8 );
     P(a,b,c,d,e,W[15],5 );
     P(e,a,b,c,d,W[10],12);
     P(d,e,a,b,c,W[4 ],9 );
     P(c,d,e,a,b,W[1 ],12);
     P(b,c,d,e,a,W[5 ],5 );
     P(a,b,c,d,e,W[8 ],14);
     P(e,a,b,c,d,W[7 ],6 );
     P(d,e,a,b,c,W[6 ],8 );
     P(c,d,e,a,b,W[2 ],13);
     P(b,c,d,e,a,W[13],6 );
     P(a,b,c,d,e,W[14],5 );
     P(e,a,b,c,d,W[0 ],15);
     P(d,e,a,b,c,W[3 ],13);
     P(c,d,e,a,b,W[9 ],11);
     P(b,c,d,e,a,W[11],11);

#undef f
#undef k

     ctx->state[1] += e;
     ctx->state[2] += a;
     ctx->state[3] += b;
     ctx->state[4] += c;
     ctx->state[0] += d;
     
}

/*
 * RIPEMD-160 process buffer
 */
 
void RIPEMD160_update( RIPEMD160_context *ctx, unsigned char *input, uint ilen )
{
}

void RIPEMD160( const unsigned char *input, size_t ilen, unsigned char output[20] )
{
     uint numOfWords = ((uint)ilen)/64;
     uint maxLength = (((uint)ilen)%64 > 55) ? (numOfWords+2)*64 : (numOfWords+1)*64;
     
     unsigned char flow[maxLength];

     memcpy(&flow, input, ilen);
     flow[ilen] = 0x80;
     int i = 0;
     for ( i = (uint)ilen+1 ; i < maxLength - 8 ; i++)
         flow[i] = 0;
     
     long long bitLength = ilen*8;
     for ( i = 0 ; i < 4 ; i++)
     {
         flow[maxLength - 8 + i] = (bitLength & 0xFFFFFFFF) >> i*8;
         flow[maxLength - 4 + i] = bitLength >> (32 + i*8);
     }
     
     RIPEMD160_context ctx;
     RIPEMD160_starts(&ctx);
     
     while (maxLength > 63)
     {
           RIPEMD160_process(&ctx, flow);
           input+=64;
           maxLength-=64;
     }
     
     unsigned char buffer[20];
     for (i = 0 ; i < 5 ; i++)
     {
         while (ctx.state[i])
         {
              itoa(ctx.state[i]%256, (char*)&buffer, 16);
              printf("%s", buffer);
              ctx.state[i] = ctx.state[i] >> 8;
         }
         printf(" ");
     }         
     printf("\n");
     
}