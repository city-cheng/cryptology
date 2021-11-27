#include <iostream>
// #include <stdio.h>
// #include <stdlib.h>
using namespace std;

#include <string>

static const string ALPHA ="abcdefghijklmnopqrstuvwxyz";


//仿射变换加密
string FSEncrypt(string e,int a,int b){
    string cipherText;
    for(int i = 0;i < e.size();i++){
        cipherText += ALPHA[(a * (e[i] - 97) + b) % 26];
    }
    return cipherText;
}


//拓展欧几里得求逆元
void Exgcd(int a, int b, int &x, int &y) {
    if (!b) x = 1, y = 0;
    else Exgcd(b, a % b, y, x), y -= a / b * x;
}

int aVerse(int a){
    int n = 26;
    int x, y;
    Exgcd (a, n, x, y);
    x = (x % n + n) % n;
    return x;
}



//仿射变换解密
string FSDecrypt(string d,int a,int b){
    int a_ = aVerse(a);
    int num;
    string plainText;
    for(int i = 0;i < d.size();i++){
        num = (a_ * ((d[i] - 97) - b)) % 26;
        num = (num + 26) % 26;
        plainText += ALPHA[num];
    }
    return plainText;
}   


int main(){
    string str1 = "thenationalsecurityagency";
    string str2 = FSEncrypt(str1,11,23);
    cout << str2 << endl;

    string str3 = FSDecrypt(str2,11,23);
    cout << str3 << endl;

    string str4 = "edsgickxhuklzveqzvkxwkzukvcuh";
    string str5 = FSDecrypt(str4,9,10);
    cout << str5;
    return 0;

}

