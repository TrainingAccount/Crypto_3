#ifndef RIPEMD160_H
#define RIPEMD160_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;
typedef struct 
{
        uint state[5];              
        unsigned char buffer[64];   
} RIPEMD160_context;


void RIPEMD160_starts( RIPEMD160_context *ctx );

void RIPEMD160_update( RIPEMD160_context *ctx, unsigned char *input, uint ilen );
 
void RIPEMD160_finish( RIPEMD160_context *ctx, unsigned char output[20]); 

void RIPEMD160_process( RIPEMD160_context *ctx, const unsigned char data[64] );

void RIPEMD160( const unsigned char *input, size_t ilen, unsigned char output[20] );

#endif