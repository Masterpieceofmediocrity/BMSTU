#include <fstream>
#include <vector>

class Pryamougolnik {
protected:
    double dlina, shirina;

public:
    Pryamougolnik(double dlina, double shirina) : dlina(dlina), shirina(shirina) {}
    virtual ~Pryamougolnik() = default;
    virtual double measure() const { return dlina * shirina; }
    virtual void print(std::ostream& vyhod) const {
        vyhod << "Прямоугольник: " << dlina << " x " << shirina
              << ", площадь=" << measure() << '\n';
    }
};

class Box : public Pryamougolnik {
    double vysota;

public:
    Box(double dlina, double shirina, double vysota)
        : Pryamougolnik(dlina, shirina), vysota(vysota) {}
    double measure() const override { return Pryamougolnik::measure() * vysota; }
    void print(std::ostream& vyhod) const override {
        vyhod << "Параллелепипед: " << dlina << " x " << shirina
              << " x " << vysota << ", объём=" << measure() << '\n';
    }
};

int main() {
    std::ifstream vhod("input.txt");
    std::ofstream vyhod("output.txt");
    double d1, s1, d2, s2, v2;
    if (!(vhod >> d1 >> s1 >> d2 >> s2 >> v2)) {
        vyhod << "Ошибка входных данных\n";
        return 1;
    }

    Pryamougolnik pryamougolnik(d1, s1);
    Box korobka(d2, s2, v2);
    vyhod << "Статика:\n";
    pryamougolnik.Pryamougolnik::print(vyhod);
    korobka.Box::print(vyhod);
    vyhod << "Площадь основания: " << korobka.Pryamougolnik::measure() << '\n';

    vyhod << "Динамика:\n";
    std::vector<Pryamougolnik*> ukazateli = {&pryamougolnik, &korobka};
    double summaPloshchadei = 0, summaObemov = 0;
    for (Pryamougolnik* shtuka : ukazateli) {
        shtuka->print(vyhod);
        if (Box* korobochka = dynamic_cast<Box*>(shtuka))
            summaObemov += korobochka->measure();
        else
            summaPloshchadei += shtuka->measure();
    }
    vyhod << "Всего площадей: " << summaPloshchadei << '\n';
    vyhod << "Всего объёмов: " << summaObemov << '\n';
}
