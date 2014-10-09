#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <time.h>
using namespace std;

class Verylong
{
	private:

		Verylong multdigit(int) const;
		Verylong mult10(int) const;
		bool SetZero();
		char *vlstr;
		int  vlen;
		int  vlsign;

	public:

		Verylong(const char* = NULL);
		Verylong(int);
		Verylong(const Verylong &);
		~Verylong();

		operator int() const;
		operator long() const;
		operator double() const;
		operator char * () const;
		operator bool () const;        

		const Verylong& operator=(const Verylong&);

		Verylong operator- () const;
		Verylong operator++ ();
		Verylong operator++ (int);
		Verylong operator-- ();
		Verylong operator-- (int);

		Verylong operator+= (const Verylong &);
		Verylong operator-= (const Verylong &);
		Verylong operator*= (const Verylong &);
		Verylong operator/= (const Verylong &);
		Verylong operator%= (const Verylong &);

		friend Verylong operator+ (const Verylong &, const Verylong &);
		friend Verylong operator- (const Verylong &, const Verylong &);
		friend Verylong operator* (const Verylong &, const Verylong &);
		friend Verylong operator/ (const Verylong &, const Verylong &);
		friend Verylong operator% (const Verylong &, const Verylong &);
		
		friend Verylong operator+ (const Verylong &, const int&);
		friend Verylong operator- (const Verylong &, const int&);
		friend Verylong operator* (const Verylong &, const int&);
		friend Verylong operator/ (const Verylong &, const int&);
		friend Verylong operator% (const Verylong &, const int&);

		friend int operator== (const Verylong &, const Verylong &);
		friend int operator!= (const Verylong &, const Verylong &);
		friend int operator< (const Verylong &, const Verylong &);
		friend int operator<= (const Verylong &, const Verylong &);
		friend int operator> (const Verylong &, const Verylong &);
		friend int operator>= (const Verylong &, const Verylong &);

		char *strrev(char *s) const;
		friend Verylong abs(const Verylong &);
		friend Verylong sqrt(const Verylong &);
		friend Verylong pow(const Verylong &, const Verylong &);
		friend double div(const Verylong &, const Verylong &);

		friend ostream & operator<< (ostream &, const Verylong &);
		friend istream & operator>> (istream &, Verylong &);
		
		int GetLength();

};

Verylong zero = Verylong("0");
Verylong one = Verylong("1");
Verylong two = Verylong("2");