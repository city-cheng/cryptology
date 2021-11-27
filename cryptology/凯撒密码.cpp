#include <iostream>
using namespace std;

#include <string>


//¿­ÈöÃÜÂë¼ÓÃÜ
string CaesarEncrypt(string e){
    string cipherText;
    for(int i = 0;i < e.size();i++){
        cipherText += (char)((e[i] + (3 % 26)));
    }
    return cipherText;
}


//¿­ÈöÃÜÂë½âÃÜ
string CaesarDecrypt(string d){
    string plainText;
    for(int i = 0;i < d.size();i++){
        plainText += (char)((d[i] - (3 % 26)));
    }
    return plainText;
}

int main(){
    string a = "security";
    string b = CaesarEncrypt(a);
    cout << b << endl;

    string a_ = CaesarDecrypt(b);
    cout << a_ << endl;
    // cout << a.size();
    // cout << (char)('a' + 3 );
    return 0;
}
