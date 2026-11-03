#include "Vector.h"
#include <fstream>

int main() {
    std::ifstream vhod("input.txt");
    std::ofstream vyhod("output.txt");
    Vector a, b;
    double chislo;
    if (!(vhod >> a >> b >> chislo)) {
        vyhod << "Ошибка входных данных\n";
        return 1;
    }

    Vector kopiya(a);
    Vector perenos(static_cast<Vector&&>(kopiya));
    Vector prisvoenie;
    prisvoenie = b;
    Vector perenosPrisvoeniem;
    perenosPrisvoeniem = static_cast<Vector&&>(prisvoenie);
    Vector vmeste = a + b;

    vyhod << "Первый: " << a << '\n';
    vyhod << "Второй: " << b << '\n';
    vyhod << "Вместе: " << vmeste << '\n';
    vyhod << "Копирование: " << perenos << '\n';
    vyhod << "Присваивание: " << perenosPrisvoeniem << '\n';
    vyhod << "После переноса: " << kopiya.size() << ", " << prisvoenie.size() << '\n';
    vyhod << "Умножение: " << chislo * a << '\n';
    if (vmeste.size() > 0) {
        vmeste[0] = 10;
        vyhod << "После []: " << vmeste << '\n';
    }
}
