#include <iostream>
using namespace std;
// плюсом данного кода является читабельность
bool isEven(int value){
    return !(value % 2);
}
//Использование побитовых
// операций может быть быстрее, чем использование
//операции остатка от деления (%), особенно для больших чисел.
bool isEven1(int value){
    return !(value & 1);
}
int main() {
    cout << isEven(-8) << endl; // если четное то true иначе false
    cout << isEven1(-8) << endl;
    return 0;
}
