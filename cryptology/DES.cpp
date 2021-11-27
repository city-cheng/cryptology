#include <iostream>
using namespace std;

//使用byte数组来操作二进制数据
#include <bitset>

//初始变换 IP
const int IP[] = { 58, 50, 42, 34, 26, 18, 10, 2,
			       60, 52, 44, 36, 28, 20, 12, 4,
			       62, 54, 46, 38, 30, 22, 14, 6,
                   64, 56, 48, 40, 32, 24, 16, 8,
                   57, 49, 41, 33, 25, 17, 9,  1,
                   59, 51, 43, 35, 27, 19, 11, 3,
                   61, 53, 45, 37, 29, 21, 13, 5,
                   63, 55, 47, 39, 31, 23, 15, 7 };


// 密钥置换选择 1  将64位秘钥变成56位
const int PC_1[] = {57, 49, 41, 33, 25, 17, 9,
			   1, 58, 50, 42, 34, 26, 18,
			  10,  2, 59, 51, 43, 35, 27,
			  19, 11,  3, 60, 52, 44, 36,
			  63, 55, 47, 39, 31, 23, 15,
			   7, 62, 54, 46, 38, 30, 22,
			  14,  6, 61, 53, 45, 37, 29,
			  21, 13,  5, 28, 20, 12,  4}; 
 
// 密钥置换选择 2  将54位变成48位
const int PC_2[] = {14, 17, 11, 24,  1,  5,
			   3, 28, 15,  6, 21, 10,
			  23, 19, 12,  4, 26,  8,
			  16,  7, 27, 20, 13,  2,
			  41, 52, 31, 37, 47, 55,
			  30, 40, 51, 45, 33, 48,
			  44, 49, 39, 56, 34, 53,
			  46, 42, 50, 36, 29, 32};
 
// 密钥产生时，每轮左移的位数
const int shiftBits[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

// 选择扩展运算E，将 32位 扩展至 48位
const int E[] = {32,  1,  2,  3,  4,  5,
		    4,  5,  6,  7,  8,  9,
		    8,  9, 10, 11, 12, 13,
		   12, 13, 14, 15, 16, 17,
		   16, 17, 18, 19, 20, 21,
		   20, 21, 22, 23, 24, 25,
		   24, 25, 26, 27, 28, 29,
		   28, 29, 30, 31, 32,  1};
 
// S盒，每个S盒是4x16的置换表，6位 -> 4位
const int S_BOX[8][4][16] = {
	{  
		{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},  
		{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},  
		{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0}, 
		{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13} 
	},
	{  
		{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},  
		{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5}, 
		{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},  
		{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}  
	}, 
	{  
		{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},  
		{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},  
		{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},  
		{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}  
	}, 
	{  
		{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},  
		{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},  
		{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},  
		{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}  
	},
	{  
		{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},  
		{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},  
		{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},  
		{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}  
	},
	{  
		{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},  
		{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},  
		{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},  
		{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}  
	}, 
	{  
		{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},  
		{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},  
		{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},  
		{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}  
	}, 
	{  
		{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},  
		{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},  
		{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},  
		{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}  
	} 
};
 
// 置换运算P，32位 -> 32位
const int P[] = {16,  7, 20, 21,
		   29, 12, 28, 17,
		    1, 15, 23, 26,
		    5, 18, 31, 10,
		    2,  8, 24, 14,
		   32, 27,  3,  9,
		   19, 13, 30,  6,
		   22, 11,  4, 25 };

// 逆初始变换
int IP_1[] = {40, 8, 48, 16, 56, 24, 64, 32,
			  39, 7, 47, 15, 55, 23, 63, 31,
			  38, 6, 46, 14, 54, 22, 62, 30,
			  37, 5, 45, 13, 53, 21, 61, 29,
			  36, 4, 44, 12, 52, 20, 60, 28,
			  35, 3, 43, 11, 51, 19, 59, 27,
			  34, 2, 42, 10, 50, 18, 58, 26,
			  33, 1, 41,  9, 49, 17, 57, 25};

//密码函数F(R,K)  接受分组后的32位输入和生成的48位的密钥   输出32比特
bitset<32> F(bitset<32> R,bitset<48> K){
    //使用E表进行扩展置换
    bitset<48> expendR;
    for(int i = 0;i < 48;i++){
        expendR[47 - i] = R[32 - E[i]];
    }
    //与32位密钥K异或
    expendR = expendR ^ K;
    //使用S盒变换 得到32位输出
    bitset<32> output;
    int x = 0;  //第x组：用于选择分组对应的Si，x=1则对应S1
    for(int i = 0;i < 48;i+=6){
        //行：  第一位和第六位的十进制
        int row = expendR[47 - i] * 2 + expendR[47 - i - 5];
        //列：  中间四位的十进制
        int col = expendR[47 - i - 1] * 8 + expendR[47 - i - 2] * 4 + expendR[47 - i - 3] * 2 + expendR[47 - i - 4];
        //最后选择的数字
        int num = S_BOX[x][row][col];
        //化成4位二进制
        bitset<4> binary(num);
		//将每一组放入最后的输出数组
        for(int j = 0;j < 4;j++){
            output[31 - x * 4 - j] = binary[3 - j];
        }
        x++;
    }

    //置换运算P  32->32
    bitset<32> temp = output;
    for(int i = 0;i < 32;i++){
        output[31 - i] = temp[32 - P[i]];
    }

    return output;

}


//密钥的循环左移
bitset<28> leftShift(bitset<28> k, int shift)
{
	bitset<28> tmp = k;
	for(int i=27; i>=0; --i)
	{
		if(i-shift<0)
			k[i] = tmp[i-shift+28];
		else
			k[i] = tmp[i-shift];
	}
	return k;
}


//生成密钥
void generateKeys(bitset<48> subKeys[16],bitset<64> key){
	//一次性生成所有子密钥，存放在subKeys数组中

    bitset<56> tempKey;   //存放中间结果
    bitset<28> left,right;   //存放左右分组
    bitset<48> subKey;      //最后的子密钥
    //先经过置换选择 1 PC_1  64->56
    for(int i = 0;i < 56;i++){
        tempKey[55 - i] = key[64 - PC_1[i]];
    }
    //生成子密钥
    for(int round = 0; round < 16;round++){
        //分成前28位和后28位
        for(int i = 28;i < 56;i++){
            left[i - 28] = tempKey[i];
        }
        for(int i = 0;i < 28;i++){
            right[i] = tempKey[i];
        }
        //左移
        left = leftShift(left,shiftBits[round]);
        right = leftShift(right,shiftBits[round]);


        //首先将左移后的密钥拼起来
        for(int i = 28;i < 56;i++){
            tempKey[i] = left[i - 28];
        }
        for(int i = 0;i < 28;i++){
            tempKey[i] = right[i];
        }

        //置换选择 2 PC_2 56->48
        for(int i = 0;i < 48;i++){
            subKey[47 - i] = tempKey[56 - PC_2[i]];
        }

        //将生成的子密钥放入数组
        subKeys[round] = subKey;

    }

}

//DES加密
bitset<64> encrypt(bitset<64>& plain,bitset<64> key)
{
	bitset<64> cipher;
	bitset<64> temp;
	bitset<32> left;
	bitset<32> right;
	bitset<32> newLeft;
    bitset<48> subKeys[16];

    //先进行初始置换IP
	for(int i=0; i<64; ++i){
		temp[63-i] = plain[64-IP[i]];
    }

	//分成左右各32比特
	for(int i=32; i<64; ++i){
		left[i-32] = temp[i];
    }
	for(int i=0; i<32; ++i){
		right[i] = temp[i];
    }

    //生成子密钥
    generateKeys(subKeys,key);

	//进行16轮迭代
	for(int round=0; round<16; ++round)
	{
		newLeft = right;//存放原来的右边
		//右边先F再和左边异或
		right = left ^ F(right,subKeys[round]);  //此时密钥使用顺序为正序
		//左边变成原来的右边
		left = newLeft;
	}

	//左右交换并合并成64位密文
	for(int i=0; i<32; ++i){
		cipher[i] = left[i];
    }
	for(int i=32; i<64; ++i){
		cipher[i] = right[i-32];
    }

	//逆初始变换TP_1
	temp = cipher;
	for(int i=0; i<64; ++i){
		cipher[63-i] = temp[64-IP_1[i]];
    }
	// 返回密文
	return cipher;
}

//DES解密
bitset<64> decrypt(bitset<64>& cipher,bitset<64> key)
{
	bitset<64> plain;
	bitset<64> temp;
	bitset<32> left;
	bitset<32> right;
	bitset<32> newLeft;
    bitset<48> subKeys[16];

    //先进行初始置换IP
	for(int i=0; i<64; ++i){
		temp[63-i] = cipher[64-IP[i]];
    }

	//分成左右各32比特
	for(int i=32; i<64; ++i){
		left[i-32] = temp[i];
    }
	for(int i=0; i<32; ++i){
		right[i] = temp[i];
    }

    //生成子密钥
    generateKeys(subKeys,key);

	//进行16轮迭代  
	for(int round=0; round<16; ++round)
	{
		newLeft = right;
		right = left ^ F(right,subKeys[15 - round]);  //逆序使用子密钥
		left = newLeft;
	}

	//左右交换并合并成64位密文
	for(int i=0; i<32; ++i){
		plain[i] = left[i];
    }
	for(int i=32; i<64; ++i){
		plain[i] = right[i-32];
    }

	//逆初始变换TP_1
	temp = plain;
	for(int i=0; i<64; ++i){
		plain[63-i] = temp[64-IP_1[i]];
    }
	// 返回密文
	return plain;
}




int main(){
	long long m = 0x0123456789ABCDEF;
	bitset<64> M = m;
	cout << "十六进制(0123456789ABCDEF) = 二进制(" << M << ")" << endl;
	long long k = 0x133457799BBCDFF1;
	bitset<64> K = k;
	cout << "十六进制(133457799BBCDFF1) = 二进制(" << K << ")" << endl;


	bitset<64> C("1000010111101000000100110101010000001111000010101011010000000101");

	bitset<64> C_ = encrypt(M,K);
	// bitset<64> C_ = decrypt(E,K);
	cout << "加密后的密文是：" << C_ << endl;
    return 0;
}