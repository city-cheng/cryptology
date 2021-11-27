#include "Matrix.h"

static const string ALPHA ="abcdefghijklmnopqrstuvwxyz";

#include <string>

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


//矩阵逆元
Matrix AVerse(Matrix A){
    Matrix A_verse = Matrix(3,3);
    int det_A = ((A.data[0][0] * A.data[1][1] * A.data[2][2] + A.data[0][1] * A.data[1][2]*A.data[2][0] +A.data[1][0]*A.data[2][1]*A.data[0][2]-A.data[1][1]*A.data[2][0]*A.data[0][2]-A.data[0][1]*A.data[1][0]*A.data[2][2]-A.data[0][0]*A.data[1][2]*A.data[2][1]
    			+ 26 * 1024)%26); //行列式的值 

    int det_A_verse = aVerse(det_A);

    //代数余子式
    A_verse.data[0][0] = det_A_verse * (A.data[1][1] * A.data[2][2] - A.data[1][2] * A.data[2][1]) % 26;
    A_verse.data[0][1] = det_A_verse * (A.data[0][1] * A.data[2][2] - A.data[0][2] * A.data[2][1]) * (- 1) % 26;
    A_verse.data[0][2] = det_A_verse * (A.data[0][1] * A.data[1][2] - A.data[0][2] * A.data[1][1]) % 26;
    A_verse.data[1][0] = det_A_verse * (A.data[1][0] * A.data[2][2] - A.data[1][2] * A.data[2][0]) * (- 1) % 26;
    A_verse.data[1][1] = det_A_verse * (A.data[0][0] * A.data[2][2] - A.data[0][2] * A.data[2][0]) % 26;
    A_verse.data[1][2] = det_A_verse * (A.data[0][0] * A.data[1][2] - A.data[0][2] * A.data[1][0]) * (- 1) % 26;
    A_verse.data[2][0] = det_A_verse * (A.data[1][0] * A.data[2][1] - A.data[1][1] * A.data[2][0]) % 26;
    A_verse.data[2][1] = det_A_verse * (A.data[0][0] * A.data[2][1] - A.data[0][1] * A.data[2][0]) * (- 1) % 26;
    A_verse.data[2][2] = det_A_verse * (A.data[0][0] * A.data[1][1] - A.data[0][1] * A.data[1][0]) % 26;

    //防止出现负数
    for(int i = 0; i < 3; i ++){
        for(int j = 0; j < 3; j ++){
            A_verse.data[i][j] = (A_verse.data[i][j] + 26) % 26;
        }
    }
    for(int i = 0; i < 3; i ++){
        for(int j = 0; j < 3; j ++){
            cout << A_verse.data[i][j] << " ";
        }
        cout << endl;
    }
    return A_verse;
}


//加密
string duoBiaoEncrypt(string d,Matrix A,Matrix B){
    Matrix C = Matrix(4,1);
    Matrix M = Matrix(4,1);
    string cipherText;
    for(int i = 0;i < d.size() - 3;i+=4){
        //分组
        for(int j = 0;j < 4;j++){
            M.data[j][0] = d[i + j] - 'a';
        }
        C = A.multiply(M).plus(B).mod(26);
        for(int i = 0;i < 4;i++){
            // cout << C.data[i][0];
            cipherText += ALPHA[C.data[i][0]];
        }
    }
    return cipherText;
}

string duoBiaoDecrypt(string d,Matrix A_,Matrix B){
    Matrix C = Matrix(4,1);
    Matrix M = Matrix(4,1);
    string cipherText;
    for(int i = 0;i < d.size() - 3;i+=4){
        //分组
        for(int j = 0;j < 4;j++){
            C.data[j][0] = d[i + j] - 'a';
        }
        C = A_.multiply(C.minus(B)).mod(26);
        for(int i = 0;i < 4;i++){
            if(C.data[i][0] < 0){
                C.data[i][0] += 26;
            }
            cipherText += ALPHA[C.data[i][0]];
        }
    }
    return cipherText;
}





int main(){
    string str = "pleasesendmethebookmycreditcardnoissixonetwoonethreeeightsixzeroonesixeightfourninesevenzerotwo";
    Matrix A = Matrix(4,4);
    Matrix B = Matrix(4,1);
    Matrix A_ = Matrix(4,4);


    int a[4][4] = {{3,13,21,9},{15,10,6,25},{10,17,4,8},{1,23,7,2}};
    int b[4] = {1,21,8,17};
    for(int i = 0;i < 4;i++){
        for(int j = 0;j < 4;j++){
            A.data[i][j] = a[i][j];
        }
    }
    for(int i = 0;i < 4;i++){
        B.data[i][0] = b[i];
    }

    int a_[4][4] = {{26,13,20,5},{0,10,11,0},{9,11,15,22},{9,22,6,25}};
    for(int i = 0;i < 4;i++){
        for(int j = 0;j < 4;j++){
            A_.data[i][j] = a_[i][j];
        }
    }
    string str1 = duoBiaoEncrypt(str,A,B);
    string str2 = duoBiaoDecrypt(str1,A_,B);
    cout << str1;
    cout << endl;
    cout << str2;
    return 0;
}