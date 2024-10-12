#include "Fraction.h"
#include <stdexcept>

Fraction::Fraction() : up(0), down(1) {}

Fraction::Fraction(int u, int d) : up(u), down(d) {
    reduce();
}

const Fraction One(1, 1);
const Fraction Zero(0, 1);

void Fraction::reduce() {
    if (down < 0) {
        up = -up;
        down = -down;
    }
    if (up == 0) down = 1;
    else {
        int g = gcd(abs(up), abs(down));
        up /= g;
        down /= g;
    }
}

int Fraction::gcd(int a, int b) {
    return !b ? a : gcd(b, a % b);
}

Fraction Fraction::operator+(const Fraction& a) const {
    return Fraction(up * a.down + a.up * down, down * a.down);
}

Fraction Fraction::operator-(const Fraction& a) const {
    return Fraction(up * a.down - a.up * down, down * a.down);
}

Fraction Fraction::operator*(const Fraction& a) const {
    return Fraction(up * a.up, down * a.down);
}

Fraction Fraction::operator/(const Fraction& a) const {
    if (a.up == 0) throw std::runtime_error("Division by zero");
    return Fraction(up * a.down, down * a.up);
}

Fraction& Fraction::operator+=(const Fraction& a) {
    *this = *this + a;
    return *this;
}

Fraction& Fraction::operator-=(const Fraction& a) {
    *this = *this - a;
    return *this;
}

Fraction& Fraction::operator*=(const Fraction& a) {
    *this = *this * a;
    return *this;
}

Fraction& Fraction::operator/=(const Fraction& a) {
    if (a.up == 0) throw std::runtime_error("Division by zero");
    *this = *this / a;
    return *this;
}

Fraction& Fraction::operator=(int a) {
    up = a;
    down = 1;
    reduce();
    return *this;
}

bool Fraction::operator==(const Fraction& a) const {
    Fraction temp(*this);
    Fraction aTemp(a);
    temp.reduce();
    aTemp.reduce();
    return temp.up == aTemp.up && temp.down == aTemp.down;
}

std::istream& operator>>(std::istream& input, Fraction& a) {
    input >> a.up >> a.down;
    a.reduce();
    return input;
}

std::ostream& operator<<(std::ostream& output, const Fraction& a) {
    if (a.down == 0) return output << "INF";
    if (a.down == 1) return output << a.up;
    return output << a.up << "/" << a.down;
}