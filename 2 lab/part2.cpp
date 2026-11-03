#include <iostream>
#include <vector>
using namespace std;

class Pryamougolnik {
protected:
    double dlina;
    double shirina;

public:
    Pryamougolnik(double dlina, double shirina) : dlina(dlina), shirina(shirina) {}
    virtual ~Pryamougolnik() = default;

    virtual double measure() const { return dlina * shirina; }

    virtual void print() const {
        cout << "Прямоугольник: " << dlina << " x " << shirina
             << ", площадь=" << measure() << '\n';
    }
};

class Box : public Pryamougolnik {
    double vysota;

public:
    Box(double dlina, double shirina, double vysota)
        : Pryamougolnik(dlina, shirina), vysota(vysota) {}

    double measure() const override { return Pryamougolnik::measure() * vysota; }

    void print() const override {
        cout << "Параллелепипед: " << dlina << " x " << shirina
             << " x " << vysota << ", объём=" << measure() << '\n';
    }
};

int main() {
    Pryamougolnik pryamougolnik(3, 4);
    Box korobka(2, 5, 6);

    cout << "Статика:\n";
    pryamougolnik.Pryamougolnik::print();
    korobka.Box::print();
    cout << "Площадь основания: " << korobka.Pryamougolnik::measure() << '\n';

    cout << "Динамика:\n";
    vector<Pryamougolnik*> ukazateli = {&pryamougolnik, &korobka};
    double summaPloshchadei = 0;
    double summaObemov = 0;
    for (Pryamougolnik* shtuka : ukazateli) {
        shtuka->print();
        if (Box* korobochka = dynamic_cast<Box*>(shtuka))
            summaObemov += korobochka->measure();
        else
            summaPloshchadei += shtuka->measure();
    }
    cout << "Всего площадей: " << summaPloshchadei << '\n';
    cout << "Всего объёмов: " << summaObemov << '\n';
}
