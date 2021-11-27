#include <iostream>
using namespace std;

#include <string>


//��λ�任����
string YiWeiEncrypt(string e,int k){
    string cipherText;
    for(int i = 0; i < e.size();i++){
        cipherText += (char)(e[i] + (k % 26));
    }
    return cipherText;
}


//��λ�任����
string YiWeiDecrypt(string d,int k){
    string plainText;
    for(int i = 0;i < d.size();i++){
        plainText += (char)(d[i] - (k % 26));
    }
    return plainText;
}

int main(){
    int key = 3;
    string a = "cheng";
    cout << a <<endl;
    string b = YiWeiEncrypt(a,key);
    cout << b << endl;
    string c = YiWeiDecrypt(b,key);
    cout << c << endl;
    return 0;
}