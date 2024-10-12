#ifndef MATRIX_H
#define MATRIX_H

#include "Fraction.h"

class Matrix {
public:
    int m, n;
    Fraction num[100][100];

    Matrix();
    Matrix(int _m, int _n, Fraction _num[100][100]);

    void set(int _m, int _n, Fraction _num[100][100]);
    void set(int _m, int _n, int _num[100][100]);
    void set(int _m, int _n);
    void set(Matrix in);

    void display();

    void simplify();

    void swapRow(int a, int b);
    void swapColumn(int a, int b);

    Matrix inverse();

    Matrix transform();

    static Matrix multiply(Matrix lm, Matrix rm);
};

#endif // MATRIX_H