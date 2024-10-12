#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

class Fraction {
private:
    static int gcd(int a, int b);
public:
    int up, down;

    void reduce();

    Fraction();

    Fraction(int u, int d);

    Fraction operator+(const Fraction& a) const;
    Fraction operator-(const Fraction& a) const;
    Fraction operator*(const Fraction& a) const;
    Fraction operator/(const Fraction& a) const;

    Fraction& operator+=(const Fraction& a);
    Fraction& operator-=(const Fraction& a);
    Fraction& operator*=(const Fraction& a);
    Fraction& operator/=(const Fraction& a);

    Fraction& operator=(int a);

    bool operator==(const Fraction& a) const;

    friend std::istream& operator>>(std::istream& input, Fraction& a);
    friend std::ostream& operator<<(std::ostream& output, const Fraction& a);
};

#endif // FRACTION_H