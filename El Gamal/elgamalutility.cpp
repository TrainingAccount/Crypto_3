#include "VeryLong.cpp"
#include "main.hpp"

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
       bool isKey = !strcmp(argc[1], "key");
       bool isEnc = !strcmp(argc[1], "enc");
       bool isDec = !strcmp(argc[1], "dec");
       bool isHlp = !strcmp(argc[1], "info");
       bool result;
       
       int switcher = isKey + isEnc*2 + isDec*3 + isHlp*4;
       
       switch ( switcher ) 
       {
              case 1:
                   result = ElgamalKey();
                   break;
              case 2:
                   result = ElgamalEnc();
                   break;
              case 3:
                   result = ElgamalDec();
                   break;
              case 4:
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
        cout << "This is the Elgamal encryprion\\decription utility." << endl
             << "Use following keys to process ur info:" << endl
             << "key - creates new key" << endl
             << "enc - encrypts the file" << endl
             << "dec - decrypts the file" << endl;         
     }
     else
        cout << "Please, use the 'info' key to see how to work with this utility" << endl;
}

//==============================================================================
// ???? ???????? ???????
//==============================================================================
// ?????????? ????????? ?????
//------------------------------------------------------------------------------

#define p numbers[0]
#define g numbers[1]
#define x numbers[2]

bool ElgamalKey()
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
     
     Verylong y = binpow(g, x, p);
     cout << "Your y-number generated and saved in " << filename[3] << endl;
     freopen(filename[3], "w", stdout);
     cout << y.GetLength() << " " << y;
    // freopen("CONOUT$","w",stdout);
     return true;
}

//------------------------------------------------------------------------------
// ??????? ????????? ???????????
//------------------------------------------------------------------------------

#undef x

#define y numbers[2]
#define m numbers[3]

bool ElgamalEnc()
{
     FILE* f;
     char* tempNumber;
     int length;
     Verylong numbers[4];
     
     for (int i = 0 ; i < 4 ; i++)
     {
         f = fopen(filename[4+i], "r");
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
             if (i == 2)
             {
                   cout << "Please use this utility with 'key' param to generate y.txt" << endl;
             }
             else
             {
                   cout << "Please create '" << filename[4+i] << "' file with initiate number" << endl;
             }
             return false;
         }
     }
     srand(time(NULL));
     Verylong k(rand());
     k %= p - 2;
     k += 1;
     
     
     Verylong a = binpow(g,k,p);
     Verylong b = binpow(y,k,p);
     b = (b * m) % p;
     
     cout << "Your cipher-text was generated and saved in " << filename[8] << " and " << filename[9] << endl;
     freopen(filename[8], "w", stdout);
     cout << a.GetLength() << " " << a;
     freopen(filename[9], "w", stdout);
     cout << b.GetLength() << " " << b;
     
    // freopen("CONOUT$", "w", stdout);
     
     return true;
}

//------------------------------------------------------------------------------
// ??????? ?????????? ????????? ????????? (???? ??? ????????)
//------------------------------------------------------------------------------

#undef p
#undef g
#undef y
#undef m

#define a numbers[0]
#define b numbers[1]
#define x numbers[2]
#define p numbers[3]

bool ElgamalDec()
{
     FILE* f;
     char* tempNumber;
     int length;
     Verylong numbers[4];
     
     for (int i = 0 ; i < 4 ; i++)
     {
         f = fopen(filename[8+i], "r");
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
             if (i < 2)
             {
                   cout << "Please use this utility with 'enc' param to encrypt your message" << endl
                        << "It would be saved in files a.txt and b.txt" << endl;
             }
             else
             {
                   cout << "Please create '" << filename[8+i] << "' file with initiate number" << endl;
             }
             return false;
         }
     }
     
     Verylong axmodp = binpow(a,x,p);
     Verylong t = inverse(axmodp, p);
     
     //p isnt a prime so i cant decrypt message
     if ( t == zero )
        return false;
        
     t = ( t * b ) % p;
     
     cout << "Your decrypted message saved in decryptedmessage.txt" << endl;
     freopen("decryptedmessage.txt", "w", stdout);
     cout << t;
    // freopen("CONOUT$", "w", stdout);
     
     return true;
}

#undef a
#undef b
#undef x
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