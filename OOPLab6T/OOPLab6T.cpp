#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <utility>

using namespace std;

// ==========================================
// ЗАВДАННЯ 1: Віртуальне успадкування
// ==========================================

// Абстрактний базовий клас для завдання 1
class Base {
protected:
    int data;
public:
    Base(int val) : data(val) { cout << "Base constructor called\n"; }
    virtual ~Base() { cout << "Base destructor called\n"; }
    virtual void show() = 0;
};

// --- Невіртуальне успадкування ---
class Left : public Base {
public:
    Left(int val) : Base(val) { cout << "Left constructor\n"; }
    ~Left() { cout << "Left destructor\n"; }
    void show() override { cout << "Left data: " << data << endl; }
};

class Right : public Base {
public:
    Right(int val) : Base(val) { cout << "Right constructor\n"; }
    ~Right() { cout << "Right destructor\n"; }
    void show() override { cout << "Right data: " << data << endl; }
};

class DerivedNV : public Left, public Right {
public:
    DerivedNV(int val) : Left(val), Right(val) { cout << "DerivedNV constructor\n"; }
    ~DerivedNV() { cout << "DerivedNV destructor\n"; }
    void show() override { cout << "DerivedNV show" << endl; }
};

// --- Віртуальне успадкування ---
class VLeft : virtual public Base {
public:
    VLeft(int val) : Base(val) { cout << "VLeft constructor\n"; }
    ~VLeft() { cout << "VLeft destructor\n"; }
    void show() override { cout << "VLeft data: " << data << endl; }
};

class VRight : virtual public Base {
public:
    VRight(int val) : Base(val) { cout << "VRight constructor\n"; }
    ~VRight() { cout << "VRight destructor\n"; }
    void show() override { cout << "VRight data: " << data << endl; }
};

class DerivedV : public VLeft, public VRight {
public:
    DerivedV(int val) : Base(val), VLeft(val), VRight(val) { cout << "DerivedV constructor\n"; }
    ~DerivedV() { cout << "DerivedV destructor\n"; }
    void show() override { cout << "DerivedV show" << endl; }
};

// ==========================================
// ЗАВДАННЯ 2: Криві
// ==========================================

class Curve {
protected:
    double a, b;
public:
    Curve(double _a, double _b) : a(_a), b(_b) {}
    virtual ~Curve() {}
    virtual pair<double, double> calculateY(double x) = 0;
    virtual string getName() = 0;
};

class Line : public Curve {
public:
    Line(double a, double b) : Curve(a, b) {}
    pair<double, double> calculateY(double x) override {
        double y = a * x + b;
        return {y, y};
    }
    string getName() override { return "Пряма"; }
};

class Ellipse : public Curve {
public:
    Ellipse(double a, double b) : Curve(a, b) {}
    pair<double, double> calculateY(double x) override {
        double val = 1.0 - (x * x) / (a * a);
        if (val < 0) throw domain_error("x поза межами еліпса");
        double y = b * sqrt(val);
        return {y, -y};
    }
    string getName() override { return "Еліпс"; }
};

class Hyperbola : public Curve {
public:
    Hyperbola(double a, double b) : Curve(a, b) {}
    pair<double, double> calculateY(double x) override {
        double val = (x * x) / (a * a) - 1.0;
        if (val < 0) throw domain_error("x поза межами гіперболи");
        double y = b * sqrt(val);
        return {y, -y};
    }
    string getName() override { return "Гіпербола"; }
};

// ==========================================
// ДОПОМІЖНІ ФУНКЦІЇ ТА МЕНЮ
// ==========================================

int getVal() {
    int choice;
    cout << "Оберіть метод введення (1-клавіатура, 2-файл, 3-рандом): ";
    cin >> choice;
    if (choice == 1) {
        int val;
        cout << "Введіть число: "; cin >> val;
        return val;
    } else if (choice == 2) {
        ifstream file("data.txt");
        int val = 0;
        if (file >> val) cout << "Прочитано з файлу: " << val << endl;
        else cout << "Файл не знайдено, взято 0" << endl;
        return val;
    } else {
        static mt19937 rng(1337);
        uniform_int_distribution<int> dist(1, 100);
        int val = dist(rng);
        cout << "Випадкове число: " << val << endl;
        return val;
    }
}

void runTask1() {
    cout << "\n--- ЗАВДАННЯ 1 ---\n";
    int val = getVal();

    cout << "\nNon-Virtual Size: " << sizeof(DerivedNV(val)) << " bytes" << endl;
    cout << "Virtual Size: " << sizeof(DerivedV(val)) << " bytes" << endl;
}

void runTask2() {
    cout << "\n--- ЗАВДАННЯ 2 ---\n";
    double a, b, x;
    cout << "Введіть коефіцієнти a та b: ";
    cin >> a >> b;
    cout << "Введіть x: ";
    cin >> x;

    vector<Curve*> curves = { new Line(a, b), new Ellipse(a, b), new Hyperbola(a, b) };

    for (Curve* c : curves) {
        try {
            pair<double, double> res = c->calculateY(x);
            cout << c->getName() << ": y1 = " << res.first << ", y2 = " << res.second << endl;
        } catch (const exception& e) {
            cout << c->getName() << ": " << e.what() << endl;
        }
    }

    for (Curve* c : curves) delete c;
}

int main() {
    setlocale(LC_ALL, "Ukrainian");
    int choice;
    while (true) {
        cout << "\n========================\n"
             << "МЕНЮ:\n"
             << "1. Завдання 1 (Успадкування)\n"
             << "2. Завдання 2 (Криві)\n"
             << "0. Вихід\n"
             << "Вибір: ";
        cin >> choice;

        switch (choice) {
            case 1: runTask1(); break;
            case 2: runTask2(); break;
            case 0: return 0;
            default: cout << "Помилка вибору.\n";
        }
    }
    return 0;
}