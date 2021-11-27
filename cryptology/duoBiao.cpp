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
    Matrix C = Matrix(3,1);
    Matrix M = Matrix(3,1);
    string cipherText;
    for(int i = 0;i < d.size() - 2;i+=3){
        //分组
        for(int j = 0;j < 3;j++){
            M.data[j][0] = d[i + j] - 'a';
        }
        C = A.multiply(M).plus(B).mod(26);
        for(int i = 0;i < 3;i++){
            // cout << C.data[i][0];
            cipherText += ALPHA[C.data[i][0]];
        }
    }
    return cipherText;
}

string duoBiaoDecrypt(string d,Matrix A_,Matrix B){
    Matrix C = Matrix(3,1);
    Matrix M = Matrix(3,1);
    string cipherText;
    for(int i = 0;i < d.size() - 2;i+=3){
        //分组
        for(int j = 0;j < 3;j++){
            C.data[j][0] = d[i + j] - 'a';
        }
        C = A_.multiply(C.minus(B)).mod(26);
        for(int i = 0;i < 3;i++){
            if(C.data[i][0] < 0){
                C.data[i][0] += 26;
            }
            cipherText += ALPHA[C.data[i][0]];
        }
    }
    return cipherText;
}





int main(){
    string str = "yourpinnoisfouronetwosix";
    Matrix A = Matrix(3,3);
    Matrix B = Matrix(3,1);
    Matrix A_ = Matrix(3,3);


    int a[3][3] = {{11,2,19},{5,23,25},{20,7,17}};
    int b[3] = {0,0,0};
    for(int i = 0;i < 3;i++){
        for(int j = 0;j < 3;j++){
            A.data[i][j] = a[i][j];
        }
    }
    for(int i = 0;i < 3;i++){
        B.data[i][0] = b[i];
    }


    string str1 = duoBiaoEncrypt(str,A,B);
    A_ = AVerse(A);
    string str2 = duoBiaoDecrypt(str1,A_,B);
    cout << str1;
    cout << endl;
    cout << str2;
    return 0;
}