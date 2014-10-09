#include "VeryLong.cpp"
#include "shnorr.hpp"

int main(int argv, char** argc)
{
    if (argv == 1 )
    {
       ShowInfo(false);
      // system("pause");
       return -1;
    }
    else
    {
       bool isStage1 = !strcmp(argc[1], "peggy1");
       bool isStage2 = !strcmp(argc[1], "victor2");
       bool isStage3 = !strcmp(argc[1], "peggy3");
       bool isStage4 = !strcmp(argc[1], "victor4");
       bool isHlp = !strcmp(argc[1], "info");
       bool result;
       
       int switcher = isStage1 + isStage2*2 + isStage3*3 + isStage4*4 + isHlp*5;
       
       switch ( switcher ) 
       {
              case 1:
                   result = ShnorrStage1();
                   break;
              case 2:
                   result = ShnorrStage2();
                   break;
              case 3:
                   result = ShnorrStage3();
                   break;
              case 4:
                   result = ShnorrStage4();
                   break;
              case 5:
                   ShowInfo(true);
                   break;
              default:
                   ShowInfo(false);
                   return -1;
       } 
    }      
    //system("pause");
    return 0;
}

void ShowInfo(bool Type)
{
     if ( Type )
     {
        cout << "This is the Shnorr authentication utility." << endl
             << "Use following keys to process ur info:" << endl
             << "peggy1 - creates new key and x,r numbers" << endl
             << "victor2 - generates e number" << endl
             << "peggy3 - generates s number" << endl
             << "victor4 - final check" << endl;         
     }
     else
        cout << "Please, use the 'info' key to see how to work with this utility" << endl;
}

//==============================================================================
// ???? ???????? ???????
//==============================================================================

#define p numbers[0]
#define g numbers[1]
#define q numbers[2]

bool ShnorrStage1()
{
     FILE* f;
     char* tempNumber;
     int length;
     Verylong numbers[3];
     
     for (int i = 0 ; i < 3 ; i++)
     {
         f = fopen(filename[i], "r");
         if ( f )
         {
              fscanf(f, "%d", &length);
              tempNumber = new char[length];
              fscanf(f, "%s", tempNumber);
              fclose(f);

              numbers[i] = Verylong(tempNumber);
              
              delete [] tempNumber;
         }
         else
         {
             cout << "Please create '" << filename[i] << "' file with initiate number" << endl;
             return false;
         }
     }
     
     srand(time(NULL));
     
     Verylong w(rand());
     w = w % ( q - 2 ) + 1;
     
     Verylong r(rand());
     r = r % ( q - 2 ) + 1;
     
     Verylong some = inverse(g, p);
     Verylong y = binpow(some, w, p);     
     Verylong x = binpow(g, r, p);
     
     cout << "Your y number generated and saved in " << filename[3] << endl
          << "Your private key generated and saved in " << filename[6] << endl
          << "Your r number generated and saved in " << filename[5] << endl
          << "Your x number generated and saved in " << filename[4] << endl;
          
     freopen(filename[3], "w", stdout);
     cout << y.GetLength() << " " << y;
     
     freopen(filename[6], "w", stdout);
     cout << w.GetLength() << " " << w;
     
     freopen(filename[5], "w", stdout);
     cout << r.GetLength() << " " << r;
     
     freopen(filename[4], "w", stdout);
     cout << x.GetLength() << " " << x;
     
     //freopen("CONOUT$","w",stdout);
     return true;
}

#undef p
#undef g
#undef q

bool ShnorrStage2()
{
     FILE* f;
     char* tempNumber;
     int length;
     Verylong p,e;
     
     f = fopen(filename[0], "r");
     if ( f )
     {
         fscanf(f, "%d", &length);
         tempNumber = new char[length];
         fscanf(f, "%s", tempNumber);
         fclose(f);
         
         p = Verylong(tempNumber);
         
         delete [] tempNumber;
     }
     else
     {
         cout << "Please create " << filename[0] << " file, which contain p number from public key" << endl;
         return false;
     }
     
     srand(time(NULL));
     e = Verylong(rand());
     e = e % ( p - 2 ) + 1;
     
     cout << "Your random e number was generated and saved in " << filename[7] << endl;
     freopen(filename[7], "w", stdout);
     cout << e.GetLength() << " " << e;
     
    //freopen("CONOUT$", "w", stdout);
     
     return true;
}

#define r numbers[0]
#define w numbers[1]
#define e numbers[2]
#define q numbers[3]

bool ShnorrStage3()
{
     FILE* f;
     char* tempNumber;
     int length;
     Verylong numbers[4];
     
     for (int i = 0 ; i < 4 ; i++)
     {
         f = fopen(filename[5+i], "r");
         if ( f )
         {
              fscanf(f, "%d", &length);
              tempNumber = new char[length];
              fscanf(f, "%s", tempNumber);
              fclose(f);

              numbers[i] = Verylong(tempNumber);
              
              delete [] tempNumber;
         }
         else
         {
             cout << "Please create '" << filename[5+i] << "' file with your number" << endl;
             return false;
         }
     }

     Verylong s;
     s = (r + w * e) % q;

     cout << "Your s number was generated and saved in " << filename[9] << endl;
     freopen(filename[9], "w", stdout);
     cout << s.GetLength() << " " << s;
     
     //freopen("CONOUT$", "w", stdout);
     
     return true;
}

#undef r
#undef w
#undef e
#undef q

#define x numbers[0]
#define g numbers[1]
#define s numbers[2] 
#define y numbers[3]
#define e numbers[4]
#define p numbers[5]

bool ShnorrStage4()
{
     FILE* f;
     char* tempNumber;
     int length;
     Verylong numbers[6];
     
     for (int i = 0 ; i < 6 ; i++)
     {
         f = fopen(filename[10+i], "r");
         if ( f )
         {
              fscanf(f, "%d", &length);
              tempNumber = new char[length];
              fscanf(f, "%s", tempNumber);
              fclose(f);

              numbers[i] = Verylong(tempNumber);
              
              delete [] tempNumber;
         }
         else
         {
             cout << "Please create '" << filename[10+i] << "' file with your number" << endl;
             return false;
         }
     }
     
     Verylong temp1 = binpow(g,s,p);
     Verylong temp2 = binpow(y,e,p);
     temp1 = (temp1 * temp2) % p;
     
     if (x == temp1)
     { 
         cout << "Checked!" << endl;
         return true;
     }
     else
     {
         cout << "Message is wrong!" << endl;
         return false;
     }
}

#undef x
#undef g
#undef s
#undef y
#undef e
#undef p

//==============================================================================
// ?????????????? ?????????????? ???????
//==============================================================================
// ?????????? ? ??????? ??? ???????? ????? (a^n) mod m
//------------------------------------------------------------------------------
Verylong binpow(Verylong a, Verylong n, Verylong m)
{
    if (n == zero)
		return one;

	if (n % two == one)
		return ( binpow(a, n-1, m) * a) % m;
	else 
    {
		Verylong b = binpow(a, n/2, m);
		return (b * b) % m;
	}
}

//------------------------------------------------------------------------------
// ?????? ????????? ???????? ??? ???????? ????? (a * a^(-1) == 1 mod p)
//------------------------------------------------------------------------------
Verylong inverse(Verylong a, Verylong p)
{
    Verylong x,y;
    Verylong CommonDivisor = gcdex(a, p, x, y);

    if ( CommonDivisor == one )
       return (x % p + p) % p;
    else
    {
        cout << "the number in " << filename[11] << " isn't a prime number, " << endl
             << "so utility can't decrypt the message." << endl;
        return zero;
    }
}

//==============================================================================
// ??????????? ???????? ???????
//------------------------------------------------------------------------------
Verylong gcdex(Verylong a, Verylong b, Verylong& x, Verylong& y)
{
     if ( a == zero )
     {
          y = one;
          x = zero;
          return b;
     }
     
     Verylong x1, y1;
     Verylong d = gcdex(b%a, a, x1, y1);
     
     Verylong x2;
	 if (b / a == (Verylong)0)
		x2 = (Verylong)10;
	 else
		x2 = (b / a) * x1;
	 Verylong ten = (Verylong)10;
	 for (int i = 0; i < x2.GetLength(); i++)
		 ten = ten * (Verylong)10;
	 x = y1 + ten;
	 x2 = x2 + ten;
	 x = x - x2;
	 y = x1;
	 return d;         
}