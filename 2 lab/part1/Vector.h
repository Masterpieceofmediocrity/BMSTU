#ifndef VECTOR_H
#define VECTOR_H

#include <iosfwd>

class Vector {
    double* massivchik;
    int razmerchik;

public:
    Vector();
    Vector(const double* chisla, int razmer);
    Vector(const Vector& drugoi);
    Vector(Vector&& drugoi) noexcept;
    ~Vector();

    Vector& operator=(const Vector& drugoi);
    Vector& operator=(Vector&& drugoi) noexcept;
    double& operator[](int nomer);
    const double& operator[](int nomer) const;
    int size() const;

    friend Vector operator+(const Vector& pervyi, const Vector& vtoroi);
    friend Vector operator*(double mnozhitel, const Vector& vektor);
    friend std::ostream& operator<<(std::ostream& potok, const Vector& vektor);
    friend std::istream& operator>>(std::istream& potok, Vector& vektor);
};

#endif
