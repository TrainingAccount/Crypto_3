#pragma once 

const char* filename[16] = { "p.txt", "g.txt", "q.txt", "y.txt", "x.txt", "r.txt", "w.txt", "e.txt", "q.txt", "s.txt", "x.txt", "g.txt", "s.txt", "y.txt", "e.txt", "p.txt" };

#include <iostream>

using namespace std;

void ShowInfo(bool);
bool ShnorrStage1();
bool ShnorrStage2();
bool ShnorrStage3();
bool ShnorrStage4();
Verylong binpow(Verylong, Verylong, Verylong);
Verylong inverse(Verylong, Verylong);
Verylong gcdex(Verylong, Verylong, Verylong&, Verylong&);