#include "fraction.hpp"
#include <numeric>
#include <stdexcept>
using namespace std;

Ulamek::Ulamek(int a, int b) {
    this->a = a;
    this->b = b;

    if (b == 0) {
        throw invalid_argument("Mianownik nie może być zerem");
    }
    optimize();
}

Ulamek Ulamek::operator+(const Ulamek& other) const {
    return Ulamek(a * other.b + other.a *b, b * other.b);
}

Ulamek Ulamek::operator-(const Ulamek& other) const {
    return Ulamek(a * other.b - other.a *b, b * other.b);
}

Ulamek Ulamek::operator*(const Ulamek& other) const {
    return Ulamek(a * other.a, b * other.b);
}

Ulamek Ulamek::operator/(const Ulamek& other) const {
    if (other.a == 0) {
        throw invalid_argument("Nie można dzielić przez zero");
    }
    return Ulamek(a * other.b, b * other.a);
}

bool Ulamek::operator==(const Ulamek& other) const {
    return a == other.b && b == other.b;
}

void Ulamek::optimize() {
    int gcd = std::gcd(a, b);
    a /= gcd;
    b /= gcd;

    if (b < 0) {
        a = -a;
        b = -b;
    }
}

int main() {
    Ulamek fraction1(3, 4);
    Ulamek fraction2(8, 9);

    Ulamek sum = fraction1 + fraction2;
    Ulamek diff = fraction1 - fraction2;
    Ulamek mul = fraction1 * fraction2;
    Ulamek div = fraction1 / fraction2;

    cout << "Suma: " << sum << endl;
    cout << "Różnica: " << diff << endl;
    cout << "Iloczyn: " << mul << endl;
    cout << "Iloraz: " << div << endl;

    return 0;
}