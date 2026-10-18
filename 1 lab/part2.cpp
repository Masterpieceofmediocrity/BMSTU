#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Disciplina {
    string nazvanie;
    int ocenka;
};

struct Student {
    string fio;
    vector<Disciplina> predmety;
};

void vvodStudenta(Student& student) {
    cout << "ФИО: ";
    getline(cin >> ws, student.fio);
    student.predmety.resize(4);
    for (int j = 0; j < 4; ++j) {
        cout << "Название предмета: ";
        getline(cin >> ws, student.predmety[j].nazvanie);
        cout << "Оценка: ";
        cin >> student.predmety[j].ocenka;
    }
}

void vyvodStudenta(const Student& student) {
    cout << student.fio << '\n';
    for (int j = 0; j < 4; ++j) {
        cout << student.predmety[j].nazvanie << ": "
             << student.predmety[j].ocenka << '\n';
    }
}

int main() {
    int n;
    cout << "Количество студентов: ";
    cin >> n;
    vector<Student> gruppa(n);

    for (int i = 0; i < n; ++i) {
        cout << "Студент " << i + 1 << '\n';
        vvodStudenta(gruppa[i]);
    }

    cout << "\nВведённые данные:\n";
    for (int i = 0; i < n; ++i) {
        vyvodStudenta(gruppa[i]);
    }

    int kolvo = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (gruppa[i].predmety[j].ocenka == 5) {
                ++kolvo;
            }
        }
    }
    cout << "Количество отличных оценок: " << kolvo << '\n';
    return 0;
}
