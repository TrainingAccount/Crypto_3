#include "rsa.hpp"

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
                   result = RSAKeys();
                   break;
              case 2:
                   result = RSAEnc();
                   break;
              case 3:
                   result = RSADec();
                   break;
              case 4:
                   ShowInfo(true);
                   break;
              default:
                   ShowInfo(false);
                   return -1;
       } 
    }      
   // system("pause");
    return 0;
}

void ShowInfo(bool Type)
{
     if ( Type )
     {
        cout << "This is the RSA encryprion\\decription utility." << endl
             << "Use following keys to process ur info:" << endl
             << "key - creates new keys" << endl
             << "enc - encrypts the file" << endl
             << "dec - decrypts the file" << endl;         
     }
     else
        cout << "Please, use the 'info' key to see how to work with this utility" << endl;
}

#define p numbers[0]
#define q numbers[1]
#define e numbers[2]

bool RSAKeys()
{
     FILE *f;
     Verylong numbers[3];
     int Length;
     char* tempNumber;
     
     for (int i = 0 ; i < 3 ; i++)
     {
         f = fopen(filename[i], "r");
         if (f)
         {
             fscanf(f, "%d", &Length);
             tempNumber = new char[Length];
             fscanf(f, "%s", tempNumber);
             numbers[i] = Verylong(tempNumber);
             
             delete [] tempNumber;
         }
         else
         {
             cout << "Please create " << filename[i] << " file with your prime number" << endl
                  << "Syntax is: Length_of_number Number EOF" << endl;
             return false;
         }
     }
     
     Verylong n = p * q;
     Verylong phin = ( p - 1 ) * ( q - 1 );
     
     Verylong d = inverse(e, phin);
     if (d == zero)
        return false;
     
     cout << "public and private keys are generated and saved in files:" << endl
          << filename[3] << " " << filename[4] << endl;
          
     freopen(filename[3], "w", stdout);
     cout << e.GetLength() << " " << e << endl
          << n.GetLength() << " " << n;
     
     freopen(filename[4], "w", stdout);
     cout << d.GetLength() << " " << d << endl
          << n.GetLength() << " " << n;
     
    // freopen("CONOUT$", "w", stdout);  
     return true;         
}

#undef p
#undef q
#undef e

bool RSAEnc()
{
     FILE *f;
     Verylong e, n, m;
     int Length;
     char* tempNumber;
     
     f = fopen(filename[3], "r");
     if (f)
     {
         fscanf(f, "%d", &Length);
         tempNumber = new char[Length];
         fscanf(f, "%s", tempNumber);
         e = Verylong(tempNumber);
         
         delete [] tempNumber;
         
         fscanf(f, "%d", &Length);
         tempNumber = new char[Length];
         fscanf(f, "%s", tempNumber);
         n = Verylong(tempNumber);
         
         delete [] tempNumber;        
     }
     else
     {
         cout << "Please generate your public key by using this utility with" << endl
              << "key param" << endl;
         return false;
     }
     
     f = fopen(filename[5], "r");
     if (f)
     {
         fscanf(f, "%d", &Length);
         tempNumber = new char[Length];
         fscanf(f, "%s", tempNumber);
         m = Verylong(tempNumber);

         delete [] tempNumber;
     }
     else
     {
         cout << "Please create " << filename[5] << " file with your message" << endl
              << "Syntax is: Length_of_message_in_bytes Message EOF" << endl;
         return false;
     }

     Verylong cipher = binpow(m, e, n);
     
     cout << "Message was encrypted and saved in " << filename[6] << endl;
     freopen(filename[6], "w", stdout);
     cout << cipher.GetLength() << " " << cipher;
     
    // freopen("CONOUT$", "w", stdout);
     return true;
}

bool RSADec()
{
     FILE *f;
     Verylong d, n, c;
     int Length;
     char* tempNumber;
     
     f = fopen(filename[4], "r");
     if (f)
     {
         fscanf(f, "%d", &Length);
         tempNumber = new char[Length];
         fscanf(f, "%s", tempNumber);
         d = Verylong(tempNumber);
         
         delete [] tempNumber;
         
         fscanf(f, "%d", &Length);
         tempNumber = new char[Length];
         fscanf(f, "%s", tempNumber);
         n = Verylong(tempNumber);
         
         delete [] tempNumber;        
     }
     else
     {
         cout << "Please generate your private key by using this utility with" << endl
              << "key param" << endl;
         return false;
     }
     
     f = fopen(filename[6], "r");
     if (f)
     {
         fscanf(f, "%d", &Length);
         tempNumber = new char[Length];
         fscanf(f, "%s", tempNumber);
         c = Verylong(tempNumber);

         delete [] tempNumber;
     }
     else
     {
         cout << "Please create " << filename[6] << " file with your encrypted message" << endl
              << "Syntax is: Length_of_encrypted_message_in_bytes Encrypted_Message EOF" << endl
              << "Also u can use this utility with 'enc' param to create it."<< endl;
         return false;
     }

     Verylong message = binpow(c, d, n);
     
     cout << "Message was decrypted and saved in " << filename[7] << endl;
     freopen(filename[7], "w", stdout);
     cout << message;
     
    // freopen("CONOUT$", "w", stdout);
     return true;
}

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
        cout << "the number in " << filename[2] << " isn't a prime number, " << endl
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