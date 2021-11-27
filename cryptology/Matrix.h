#pragma once

#include <iostream>
using namespace std;

class Matrix
{
public:
    int **data;
    int line;
    int col;

    Matrix(int m,int n);

    Matrix multiply(Matrix A);
    Matrix minus(Matrix A);
    Matrix plus(Matrix A);
    Matrix mod(int n);
};

Matrix::Matrix(int m,int n){
    this->data = (int **)malloc(sizeof(int *) * m);
    //“10”为数组大小
	if(this->data){
		for(int i = 0;i < m;i++){
			this->data[i] = (int *)malloc(sizeof(int)*n);
		}
	}
    this->line = m;
    this->col = n;
}

Matrix Matrix::multiply(Matrix A){
    if(this->col != A.line){
        return *this;
    }
    Matrix B = Matrix(this->line,A.col);
    for(int i = 0;i < this->line;i++){
        for(int j = 0;j < A.col;j++){
                B.data[i][j] = 0;
            for(int k = 0;k < this->col;k++){
                B.data[i][j] += this->data[i][k] * A.data[k][j];
            }
        }
    }
    return B;
}

Matrix Matrix::minus(Matrix A){
    if((this->line != A.line) || (this->col != A.col)){
        return *this;
    }
    Matrix B = Matrix(A.line,A.col);
    for(int i = 0;i < A.line;i++){
        for(int j = 0;j < A.col;j++){
            B.data[i][j] = this->data[i][j] - A.data[i][j];
        }
    }
    return B;
}


Matrix Matrix::plus(Matrix A){
    if((this->line != A.line) || (this->col != A.col)){
        return *this;
    }
    Matrix B = Matrix(A.line,A.col);
    for(int i = 0;i < A.line;i++){
        for(int j = 0;j < A.col;j++){
            B.data[i][j] = this->data[i][j] + A.data[i][j];
        }
    }
    return B;
}

Matrix Matrix::mod(int n){
    Matrix B = Matrix(this->line,this->col);
    for(int i = 0;i < this->line;i++){
        for(int j = 0;j < this->col;j++){
            B.data[i][j] = this->data[i][j] % n;
        }
    }
    return B;
}

