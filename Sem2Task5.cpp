#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using std::cin;
using std::endl;
using std::cout;

enum Type {
    CAR, BOAT
};

struct Vehicle
{
    char model[20];
    Type type;
    union 
    {
        struct
        {
            float area;
        } deck;
        struct
        {
            double pressure;
            int width;
        } wheels;
    };
};

Vehicle db[1000];
int size = 0;

void printAll () 
{
    cout << "----------------\n";
    for (int i = 0; i < size; i++)
    {
        cout << db[i].model << endl;
        if (db[i].type == BOAT)
        {
            cout << db[i].deck.area << endl;
        }
        else
        {
            cout << db[i].wheels.pressure << endl;
            cout << db[i].wheels.width << endl;
        }
        cout << "----------------\n";
    }
}

void add(const char model[], float area)
{
    Vehicle newBoat;
    strcpy(newBoat.model,model);
    newBoat.type = BOAT;
    newBoat.deck.area = area;
    db[size++] = newBoat;
}

void add(const char model[], double pressure, int width)
{
    Vehicle newCar;
    strcpy(newCar.model, model);
    newCar.type = CAR;
    newCar.wheels.pressure = pressure;
    newCar.wheels.width = width;
    db[size++] = newCar;
}

void removeAt(int index)
{
    size--;
    for (int i = index; i < size; i++)
        db[i] = db[i + 1];
}

int main()
{
    setlocale(LC_ALL, "Rus");
    add("Stormline", 3.3);
    add("Mercedes-Benz", 1.2 , 3);

    cout<< "Типо работа с бд:" <<endl;

    while (true)
    {
        cout << "0 - выести все элементы; 1 - добавить элемент, 2 -удалить элемент; всё остальное - выход" << endl;
        int op;
        cin >> op;
        if (cin.fail())
            goto label;

        switch (op)
        {
            case 0:
                printAll();
                break;
            case 1:
                cout << "0 - лодка; 1 - машина; всё остальное - выход" << endl;
                cin >> op;
                if (cin.fail())
                    goto label;
                if (op == 0)
                {
                    cout << "Модель и площадь палубы:" << endl;
                    char model[20];
                    cin >> model;
                    float area;
                    cin >> area;
                    add(model, area);
                }
                else if (op==1)
                {
                    cout << "Модель, давление и ширина колёс:" << endl;
                    char model[20];
                    cin >> model;
                    double pressure;
                    cin >> pressure;
                    int width;
                    cin >> width;
                    add(model, pressure, width);
                }
                else
                    goto label;
                break;
            case 2:
                cout << "Кого?" << endl;
                cin >> op;
                if (cin.fail() || op<0 ||op>=size)
                    goto label;
                removeAt(op);
                break;
            default:
                goto label;
        }
    }
label:
    cout<<"The end"<<endl;
}