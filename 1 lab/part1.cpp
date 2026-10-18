#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

struct Rezultat {
    double sum;
    int kolvo;
};

// После n слагаемых ошибка не превосходит 4 / (2*n + 1).
Rezultat raschetWhile(double tochnost) {
    Rezultat rez = {0, 0};
    int znak = 1;
    while (4.0 / (2 * rez.kolvo + 1) > tochnost) {
        rez.sum += znak * 4.0 / (2 * rez.kolvo + 1);
        znak = -znak;
        ++rez.kolvo;
    }
    return rez;
}

Rezultat raschetDoWhile(double tochnost) {
    Rezultat rez = {0, 0};
    int znak = 1;
    do {
        rez.sum += znak * 4.0 / (2 * rez.kolvo + 1);
        znak = -znak;
        ++rez.kolvo;
    } while (4.0 / (2 * rez.kolvo + 1) > tochnost);
    return rez;
}

Rezultat raschetFor(double tochnost) {
    Rezultat rez = {0, 0};
    int znak = 1;
    for (; 4.0 / (2 * rez.kolvo + 1) > tochnost; ++rez.kolvo) {
        rez.sum += znak * 4.0 / (2 * rez.kolvo + 1);
        znak = -znak;
    }
    return rez;
}

int main() {
    const double tochnost[] = {1e-2, 1e-4, 1e-6};
    cout << fixed << setprecision(10);
    for (int i = 0; i < 3; ++i) {
        Rezultat rez1 = raschetWhile(tochnost[i]);
        Rezultat rez2 = raschetDoWhile(tochnost[i]);
        Rezultat rez3 = raschetFor(tochnost[i]);
        cout << "tochnost = " << tochnost[i] << '\n';
        cout << "while:    " << rez1.sum << "  n = " << rez1.kolvo << '\n';
        cout << "do while: " << rez2.sum << "  n = " << rez2.kolvo << '\n';
        cout << "for:      " << rez3.sum << "  n = " << rez3.kolvo << "\n\n";
    }
    // Точное значение используется только для проверки после вычислений.
    cout << "pi = " << acos(-1.0) << '\n';
    return 0;
}
