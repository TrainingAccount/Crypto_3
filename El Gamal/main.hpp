//#pragma once 

const char* filename[12] = { "p.txt", "g.txt", "x.txt", "y.txt", "p.txt", "g.txt", "y.txt", "m.txt", "a.txt", "b.txt", "x.txt", "p.txt" };

#include <iostream>

using namespace std;

void ShowInfo(bool);
bool ElgamalKey();
bool ElgamalEnc();
bool ElgamalDec();
Verylong binpow(Verylong, Verylong, Verylong);
Verylong inverse(Verylong, Verylong);
Verylong gcdex(Verylong, Verylong, Verylong&, Verylong&);