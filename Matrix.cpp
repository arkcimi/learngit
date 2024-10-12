#include "Matrix.h"
#include <iostream>
#include <cmath>

// Global constant definitions
const Fraction One(1, 1);
const Fraction Zero(0, 1);
Fraction wrong[100][100] = {{Zero}};
const Matrix wrongMatrix(0, 0, wrong);

Matrix::Matrix(){
    m = 0;
    n = 0;
}

Matrix::Matrix(int _m, int _n, Fraction _num[100][100]) {
    m = _m;
    n = _n;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            num[i][j] = _num[i][j];
        }
    }
}

void Matrix::set(int _m, int _n, Fraction _num[100][100]) {
    m = _m;
    n = _n;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            num[i][j] = _num[i][j];
        }
    }
}

void Matrix::set(int _m, int _n, int _num[100][100]) {
    m = _m;
    n = _n;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            num[i][j] = _num[i][j];
        }
    }
}

void Matrix::set(int _m, int _n) {
    m = _m;
    n = _n;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            std::cin >> num[i][j];
        }
    }
}

void Matrix::display() {
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            std::cout << num[i][j] << '\t';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void Matrix::simplify() {
    int stt = 1;         //stop
    Fraction mult;
    for(int i = 0; i < m; i++)
    {
        if(num[i][i] == Zero)
        {
            stt = 1;
            for(int j = i; j < m; j++)
            {
                if(!(num[j][i] == Zero))
                {
                    swapRow(i, j);
                    stt = 0;
                    break;
                }
            }
            if(stt)
            {
                break;
            }
        }
        mult = One / num[i][i];
        for(int k = i; k < n; k++)
        {
            num[i][k] *= mult;
        }
        for(int j = i+1; j < m; j++)
        {
            mult = num[j][i];
            for(int k = i; k < n; k++)
            {
                num[j][k] -= num[i][k]*mult;
            }
        }
    }
    for(int i = 0; i < m; i++)
    {
        for(int j = i+1; j < m; j++)
        {
            if(!(num[m-1-j][m-1-i] == Zero))
            {
                mult = num[m-1-j][m-1-i];
                for(int k = 0; k < n; k++)
                {
                    num[m-1-j][k] -= num[m-1-i][k]*mult;
                }
            }
        }
    }
}

void Matrix::swapRow(int a, int b) {
    Fraction temp;
    for(int j = 0; j < n; j++) {
        temp = num[a][j];
        num[a][j] = num[b][j];
        num[b][j] = temp;
    }
}

void Matrix::swapColumn(int a, int b) {
    Fraction temp;
    for(int j = 0; j < m; j++) {
        temp = num[j][a];
        num[j][a] = num[j][b];
        num[j][b] = temp;
    }
}

Matrix Matrix::inverse() {
    int stt = 1;         //stop
    Fraction mult;
    Matrix out, origin;
    out.m = m;
    out.n = n;
    origin.m = m;
    origin.n = n;
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            origin.num[i][j] = num[i][j];
        }
    }
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i != j)
            {
                out.num[i][j] = 0;
            }
            else
            {
                out.num[i][j] = 1;
            }
        }
    }


    for(int i = 0; i < m; i++)
    {
        if(origin.num[i][i] == Zero)
        {
            stt = 1;
            for(int j = i; j < m; j++)
            {
                if(!(origin.num[j][i] == Zero))
                {
                    swapRow(i, j);
                    stt = 0;
                    break;
                }
            }
            if(stt)
            {
                break;
            }
        }
        mult = One / origin.num[i][i];
        for(int k = 0; k < n; k++)
        {
            origin.num[i][k] *= mult;
            out.num[i][k] *= mult;
        }
        for(int j = i+1; j < m; j++)
        {
            mult = origin.num[j][i];
            for(int k = 0; k < n; k++)
            {
                origin.num[j][k] -= origin.num[i][k]*mult;
                out.num[j][k] -= out.num[i][k]*mult;
            }
        }
    }
    for(int i = 0; i < m; i++)
    {
        for(int j = i+1; j < m; j++)
        {
            if(!(origin.num[m-1-j][m-1-i] == Zero))
            {
                mult = origin.num[m-1-j][m-1-i];
                for(int k = 0; k < n; k++)
                {
                    origin.num[m-1-j][k] -= origin.num[m-1-i][k]*mult;
                    out.num[m-1-j][k] -= out.num[m-1-i][k]*mult;
                }
            }
        }
    }
    return out;
}

Matrix Matrix::transform() {
    Matrix out;
    out.m = this->n;
    out.n = this->m;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            out.num[i][j] = this->num[j][i];
        }
    }
    return out;
}

Matrix Matrix::multiply(Matrix lm, Matrix rm) {
    if(lm.n != rm.m) return wrongMatrix;
    Matrix out;
    out.m = lm.m;
    out.n = rm.n;
    for(int i = 0; i < out.m; i++) {
        for(int j = 0; j < out.n; j++) {
            out.num[i][j] = Zero;
            for(int k = 0; k < lm.n; k++) {
                out.num[i][j] += lm.num[i][k] * rm.num[k][j];
            }
        }
    }
    return out;
}