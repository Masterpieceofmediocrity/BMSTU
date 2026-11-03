#include "Vector.h"
#include <istream>
#include <ostream>
#include <stdexcept>

Vector::Vector() : massivchik(nullptr), razmerchik(0) {}

Vector::Vector(const double* chisla, int razmer) : massivchik(nullptr), razmerchik(razmer) {
    if (razmer < 0 || (razmer > 0 && chisla == nullptr)) throw std::invalid_argument("Vector size");
    massivchik = razmer ? new double[razmer] : nullptr;
    for (int shetchik = 0; shetchik < razmer; ++shetchik) massivchik[shetchik] = chisla[shetchik];
}

Vector::Vector(const Vector& drugoi) : Vector(drugoi.massivchik, drugoi.razmerchik) {}

Vector::Vector(Vector&& drugoi) noexcept : massivchik(drugoi.massivchik), razmerchik(drugoi.razmerchik) {
    drugoi.massivchik = nullptr;
    drugoi.razmerchik = 0;
}

Vector::~Vector() { delete[] massivchik; }

Vector& Vector::operator=(const Vector& drugoi) {
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

Vector& Vector::operator=(Vector&& drugoi) noexcept {
    if (this != &drugoi) {
        delete[] massivchik;
        massivchik = drugoi.massivchik;
        razmerchik = drugoi.razmerchik;
        drugoi.massivchik = nullptr;
        drugoi.razmerchik = 0;
    }
    return *this;
}

double& Vector::operator[](int nomer) {
    if (nomer < 0 || nomer >= razmerchik) throw std::out_of_range("Vector index");
    return massivchik[nomer];
}

const double& Vector::operator[](int nomer) const {
    if (nomer < 0 || nomer >= razmerchik) throw std::out_of_range("Vector index");
    return massivchik[nomer];
}

int Vector::size() const { return razmerchik; }

Vector operator+(const Vector& pervyi, const Vector& vtoroi) {
    Vector itog;
    itog.razmerchik = pervyi.razmerchik + vtoroi.razmerchik;
    itog.massivchik = itog.razmerchik ? new double[itog.razmerchik] : nullptr;
    for (int shetchik = 0; shetchik < pervyi.razmerchik; ++shetchik) itog.massivchik[shetchik] = pervyi.massivchik[shetchik];
    for (int shetchik = 0; shetchik < vtoroi.razmerchik; ++shetchik) itog.massivchik[pervyi.razmerchik + shetchik] = vtoroi.massivchik[shetchik];
    return itog;
}

Vector operator*(double mnozhitel, const Vector& vektor) {
    Vector itog;
    itog.razmerchik = vektor.razmerchik;
    itog.massivchik = itog.razmerchik ? new double[itog.razmerchik] : nullptr;
    for (int shetchik = 0; shetchik < itog.razmerchik; ++shetchik) itog.massivchik[shetchik] = mnozhitel * vektor.massivchik[shetchik];
    return itog;
}

std::ostream& operator<<(std::ostream& potok, const Vector& vektor) {
    potok << '[';
    for (int shetchik = 0; shetchik < vektor.razmerchik; ++shetchik) {
        if (shetchik) potok << ", ";
        potok << vektor.massivchik[shetchik];
    }
    return potok << ']';
}

std::istream& operator>>(std::istream& potok, Vector& vektor) {
    int razmer;
    if (!(potok >> razmer)) return potok;
    if (razmer < 0) { potok.setstate(std::ios::failbit); return potok; }
    Vector novyi;
    novyi.razmerchik = razmer;
    novyi.massivchik = razmer ? new double[razmer] : nullptr;
    for (int shetchik = 0; shetchik < razmer; ++shetchik) {
        if (!(potok >> novyi.massivchik[shetchik])) return potok;
    }
    vektor = static_cast<Vector&&>(novyi);
    return potok;
}
