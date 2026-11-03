#include <iostream>
#include <stdexcept>
using namespace std;

class Vector {
    double* massivchik = nullptr;
    int razmerchik = 0;

public:
    Vector() = default;

    Vector(const double* chisla, int razmer) : razmerchik(razmer) {
        if (razmer < 0 || (razmer > 0 && chisla == nullptr)) throw invalid_argument("Invalid vector");
        massivchik = razmer ? new double[razmer] : nullptr;
        for (int shetchik = 0; shetchik < razmer; ++shetchik) massivchik[shetchik] = chisla[shetchik];
    }

    Vector(const Vector& drugoi) : Vector(drugoi.massivchik, drugoi.razmerchik) {}

    Vector(Vector&& drugoi) noexcept : massivchik(drugoi.massivchik),
                                       razmerchik(drugoi.razmerchik) {
        drugoi.massivchik = nullptr;
        drugoi.razmerchik = 0;
    }

    ~Vector() { delete[] massivchik; }

    Vector& operator=(const Vector& drugoi) {
        if (this != &drugoi) {
            Vector kopiyka(drugoi);
            double* staryiMassiv = massivchik;
            massivchik = kopiyka.massivchik;
            kopiyka.massivchik = staryiMassiv;
            int staryiRazmer = razmerchik;
            razmerchik = kopiyka.razmerchik;
            kopiyka.razmerchik = staryiRazmer;
        }
        return *this;
    }

    Vector& operator=(Vector&& drugoi) noexcept {
        if (this != &drugoi) {
            delete[] massivchik;
            massivchik = drugoi.massivchik;
            razmerchik = drugoi.razmerchik;
            drugoi.massivchik = nullptr;
            drugoi.razmerchik = 0;
        }
        return *this;
    }

    double& operator[](int nomer) {
        if (nomer < 0 || nomer >= razmerchik) throw out_of_range("Vector index");
        return massivchik[nomer];
    }

    const double& operator[](int nomer) const {
        if (nomer < 0 || nomer >= razmerchik) throw out_of_range("Vector index");
        return massivchik[nomer];
    }

    int size() const { return razmerchik; }

    friend Vector operator+(const Vector& pervyi, const Vector& vtoroi) {
        Vector itog;
        itog.razmerchik = pervyi.razmerchik + vtoroi.razmerchik;
        itog.massivchik = itog.razmerchik ? new double[itog.razmerchik] : nullptr;
        for (int shetchik = 0; shetchik < pervyi.razmerchik; ++shetchik) itog.massivchik[shetchik] = pervyi.massivchik[shetchik];
        for (int shetchik = 0; shetchik < vtoroi.razmerchik; ++shetchik) itog.massivchik[pervyi.razmerchik + shetchik] = vtoroi.massivchik[shetchik];
        return itog;
    }

    friend Vector operator*(double mnozhitel, const Vector& vektor) {
        Vector itog;
        itog.razmerchik = vektor.razmerchik;
        itog.massivchik = itog.razmerchik ? new double[itog.razmerchik] : nullptr;
        for (int shetchik = 0; shetchik < itog.razmerchik; ++shetchik) itog.massivchik[shetchik] = mnozhitel * vektor.massivchik[shetchik];
        return itog;
    }

    friend ostream& operator<<(ostream& potok, const Vector& vektor) {
        potok << '[';
        for (int shetchik = 0; shetchik < vektor.razmerchik; ++shetchik) {
            if (shetchik) potok << ", ";
            potok << vektor.massivchik[shetchik];
        }
        return potok << ']';
    }
};

int main() {
    double first[] = {1, 2, 3};
    double second[] = {4, 5};
    Vector a(first, 3);
    Vector b(second, 2);
    Vector joined = a + b;
    cout << "Первый: " << a << "\nВторой: " << b
         << "\nВместе: " << joined << '\n';

    joined[0] = 10;
    Vector copied;
    copied = joined;
    Vector moved(static_cast<Vector&&>(copied));
    cout << "Копия: " << moved << '\n';
    cout << "Умножение на 2: " << 2.0 * a << '\n';
}
