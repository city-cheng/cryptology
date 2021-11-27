#include <iostream>
using namespace std;
#include <random>
#include <math.h>

static const string ALPHA = " abcdefghijklmnopqrstuvwxyz";

long int  gcd(long int a,long int b)
{
	if(a%b==0) 
		return b;
	else 
		return (gcd(b,a%b));
}

void Exgcd(long int a, long int b, long int &x, long int &y) {
    if (!b) x = 1, y = 0;
    else Exgcd(b, a % b, y, x), y -= a / b * x;
}

void generateKey(long int p,long int q,long int pk[2],long int sk[2]){
    long int n = p * q;
    long int phi_n = (p - 1) * (q - 1);
    uniform_int_distribution<unsigned long int> u(1,phi_n);
    default_random_engine engine;
    long int e;
    
    do{
        long int e = u(engine);
    } while(gcd(e,phi_n) != 1);

    long int d,y;
    Exgcd(e,phi_n,d,y);
    
    pk[0] = e;
    pk[1] = n;
    cout << "¹«Ô¿Îª£º{" << pk[0] << "," << pk[1] << "}" << endl;
    sk[0] = d;
    sk[1] = n;
    cout << "Ë½Ô¿Îª£º{" << sk[0] << "," << sk[1] << "}" << endl;
}

long int RSAEncrypt(long int plain,long int pk[]){
    long int cipher = (long int)powl(plain,pk[0]) % pk[1];
    return cipher;
}

long int RSADecrypt(long int cipher,long int sk[]){
    long int plain = (long int)powl(cipher,sk[0]) % sk[1];
    return plain;
}

int main(){
    long int p = 7;
    long int q = 17;
    long int sk[2],pk[2];
    generateKey(p,q,pk,sk);
    return 0;

}