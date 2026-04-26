#include <iostream>
#include <fstream>
#include <random>
#include <string>

using namespace std;

// Базовий клас (абстрактний)
class Base {
protected:
    int data;
public:
    Base(int val) : data(val) { cout << "Base constructor called\n"; }
    virtual ~Base() { cout << "Base destructor called\n"; }
    virtual void show() = 0; // Чисто віртуальний метод
};

// ==========================================
// 1. Невіртуальне успадкування (Diamond)
// ==========================================
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

// ==========================================
// 2. Віртуальне успадкування (Diamond)
// ==========================================
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

// --- Функції введення ---
int getFromKeyboard() {
    int val;
    cout << "Введіть число: ";
    cin >> val;
    return val;
}

int getFromFile() {
    ifstream file("data.txt");
    int val = 0;
    if (file >> val) {
        cout << "Прочитано з файлу: " << val << endl;
    } else {
        cout << "Помилка файлу, беремо 0." << endl;
    }
    return val;
}

int getFromRandom() {
    static mt19937 rng(1337);
    uniform_int_distribution<int> dist(1, 100);
    int val = dist(rng);
    cout << "Випадкове число: " << val << endl;
    return val;
}

// --- Функція для Завдання 1 ---
void runTask1() {
    cout << "\n=== ЗАВДАННЯ 1: Віртуальне успадкування ===\n";
    cout << "Оберіть метод введення (1-клавіатура, 2-файл, 3-рандом): ";
    int choice;
    cin >> choice;
    int val = (choice == 1) ? getFromKeyboard() : (choice == 2 ? getFromFile() : getFromRandom());

    cout << "\n--- Non-Virtual Hierarchy (Size) ---\n";
    DerivedNV objNV(val);
    cout << "Size of DerivedNV: " << sizeof(objNV) << " bytes" << endl;

    cout << "\n--- Virtual Hierarchy (Size) ---\n";
    DerivedV objV(val);
    cout << "Size of DerivedV: " << sizeof(objV) << " bytes" << endl;
    cout << "------------------------------------\n";
}

int main() {
    int menuChoice;
    while (true) {
        cout << "\nМЕНЮ ЗАВДАНЬ:\n"
             << "1. Завдання 1 (Успадкування)\n"
             << "2. Завдання 2 ()\n"
             << "3. Завдання 3 ()\n"
             << "0. Вихід\n"
             << "Вибір: ";
        cin >> menuChoice;

        switch (menuChoice) {
            case 1: runTask1(); break;
            case 2: cout << "Завдання 2 ще не реалізовано.\n"; break;
            case 3: cout << "Завдання 3 ще не реалізовано.\n"; break;
            case 0: return 0;
            default: cout << "Невірний вибір.\n";
        }
    }
    return 0;
}