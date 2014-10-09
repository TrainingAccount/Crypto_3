#pragma once

#include "VeryLong.cpp"

const char* filename[8] = {"p.txt", "q.txt", "e.txt", "publickey.txt", "privatekey.txt" , "m.txt", "c.txt", "decryptedmessage.txt"};

void ShowInfo(bool);
bool RSAKeys();
bool RSAEnc();
bool RSADec();
Verylong binpow(Verylong, Verylong, Verylong);
Verylong inverse(Verylong, Verylong);
Verylong gcdex(Verylong, Verylong, Verylong&, Verylong&);