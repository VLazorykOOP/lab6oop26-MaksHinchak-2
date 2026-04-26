#include <iostream>
#include <cmath>
using namespace std;

// Без віртуального успадкування

class A {
protected:
    int a;
public:
    A() : a(1) {}
};

class B {
protected:
    int b;
public:
    B() : b(2) {}
};

class C : public A, public B {
protected:
    int c;
public:
    C() : c(3) {}
};

class D : public A {
protected:
    int d;
public:
    D() : d(4) {}
};

class E : public C {
protected:
    int e;
public:
    E() : e(5) {}
};

class F : public C, public D, public E {
protected:
    int f;
public:
    F() : f(6) {}
};


// З віртуальним успадкуванням

class VA {
protected:
    int a;
public:
    VA() : a(1) {}
};

class VB {
protected:
    int b;
public:
    VB() : b(2) {}
};

class VC : virtual public VA, virtual public VB {
protected:
    int c;
public:
    VC() : c(3) {}
};

class VD : virtual public VA {
protected:
    int d;
public:
    VD() : d(4) {}
};

class VE : virtual public VC {
protected:
    int e;
public:
    VE() : e(5) {}
};

class VF : virtual public VC, virtual public VD, virtual public VE {
protected:
    int f;
public:
    VF() : f(6) {}
};


void task1() {
    cout << "\n========== TASK 1 ==========\n";
    cout << "Virtual and non-virtual inheritance\n\n";

    C objC;
    D objD;
    E objE;
    F objF;

    VC objVC;
    VD objVD;
    VE objVE;
    VF objVF;

    cout << "----- Without virtual inheritance -----\n";
    cout << "sizeof(objC) = " << sizeof(objC) << " bytes\n";
    cout << "sizeof(objD) = " << sizeof(objD) << " bytes\n";
    cout << "sizeof(objE) = " << sizeof(objE) << " bytes\n";
    cout << "sizeof(objF) = " << sizeof(objF) << " bytes\n";

    cout << "\n----- With virtual inheritance -----\n";
    cout << "sizeof(objVC) = " << sizeof(objVC) << " bytes\n";
    cout << "sizeof(objVD) = " << sizeof(objVD) << " bytes\n";
    cout << "sizeof(objVE) = " << sizeof(objVE) << " bytes\n";
    cout << "sizeof(objVF) = " << sizeof(objVF) << " bytes\n";
}

// ===============================
// Абстрактний клас
// ===============================

class Curve {
public:
    virtual double getY(double x) = 0; // чисто віртуальна функція
    virtual void show() = 0;
    virtual ~Curve() {}
};


// ===============================
// Пряма: y = ax + b
// ===============================

class Line : public Curve {
private:
    double a, b;

public:
    Line(double a, double b) : a(a), b(b) {}

    double getY(double x) override {
        return a * x + b;
    }

    void show() override {
        cout << "Line: y = " << a << "x + " << b << endl;
    }
};


// ===============================
// Еліпс: x^2/a^2 + y^2/b^2 = 1
// y = ± b * sqrt(1 - x^2/a^2)
// ===============================

class Ellipse : public Curve {
private:
    double a, b;

public:
    Ellipse(double a, double b) : a(a), b(b) {}

    double getY(double x) override {
        double inside = 1 - (x * x) / (a * a);
            if (inside < 0) {
                cout << "No real solution for y\n";
                return NAN;
            }
        return b * sqrt(inside); // беремо + гілку
    }

    void show() override {
        cout << "Ellipse: x^2/" << a*a << " + y^2/" << b*b << " = 1\n";
    }
};


// ===============================
// Гіпербола: x^2/a^2 - y^2/b^2 = 1
// y = ± b * sqrt(x^2/a^2 - 1)
// ===============================

class Hyperbola : public Curve {
private:
    double a, b;

public:
    Hyperbola(double a, double b) : a(a), b(b) {}

    double getY(double x) override {
        double inside = (x * x) / (a * a) - 1;
        if (inside < 0) {
            cout << "No real y (hyperbola)\n";
            return NAN;
        }
        return b * sqrt(inside);
    }

    void show() override {
        cout << "Hyperbola: x^2/" << a*a << " - y^2/" << b*b << " = 1\n";
    }
};


// ===============================
// TASK 2
// ===============================

void task2() {
    cout << "\n========== TASK 2 ==========\n";

    double x;
    cout << "Enter x: ";
    cin >> x;

    Curve* curves[3];

    curves[0] = new Line(2, 3);
    curves[1] = new Ellipse(5, 3);
    curves[2] = new Hyperbola(4, 2);

    for (int i = 0; i < 3; i++) {
        curves[i]->show();
        double y = curves[i]->getY(x);
        cout << "y = " << y << endl << endl;
    }

    // очищення пам’яті
    for (int i = 0; i < 3; i++) {
        delete curves[i];
    }
}

void task3() {
    cout << "\n========== TASK 3 ==========\n";
    cout << "Task 3 is not added yet.\n";
}

void menu() {
    int choice;

    do {
        cout << "\n==============================\n";
        cout << " Laboratory work №6\n";
        cout << "==============================\n";
        cout << "1. Task 1: Virtual inheritance\n";
        cout << "2. Task 2: Curves\n";
        cout << "3. Task 3\n";
        cout << "0. Exit\n";
        cout << "Choose task: ";
        cin >> choice;

        switch (choice) {
            case 1:
                task1();
                break;
            case 2:
                task2();
                break;
            case 3:
                task3();
                break;
            case 0:
                cout << "Program finished.\n";
                break;
            default:
                cout << "Incorrect choice.\n";
        }

    } while (choice != 0);
}

int main() {
    menu();
    return 0;
}