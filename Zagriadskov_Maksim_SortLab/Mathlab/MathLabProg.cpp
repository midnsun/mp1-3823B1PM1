#include <iostream>
#include <cmath>
#include "sumseries.hpp"
#include "_math.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    size_t n;
    float x;
    int meth;
    string str;

    cout << "Welcome to MathLab programm!\n";
    cout << "What function do you want to calculate?\nsin for sin, cos for cos, exp for e^x, ln for ln\n";
    cin >> str;
    cout << "What method do you prefer to use?\n0 - standart method, 1 - direct sum, 2 - partial sum, 3 - backward sum\n";
    cin >> meth;
    cout << "Enter your variable:\n";
    cin >> x;
    if (meth == 0) {
        if (str == "sin") {
            cout << "sin(" << x << ") = " << _sin(x) << endl;
            cout << "Error is " << sin(x) - _sin(x) << endl;
        }
        if (str == "cos") {
            cout << "cox(" << x << ") = " << _cos(x) << endl;
            cout << "Error is " << cos(x) - _cos(x) << endl;
        }
        if (str == "exp") {
            cout << "exp(" << x << ") = " << _exp(x) << endl;
            cout << "Error is " << exp(x) - _exp(x) << endl;
        }
        if (str == "ln") {
            cout << "ln(" << x << ") = " << _ln(x) << endl;
            cout << "Error is " << log(x) - _ln(x) << endl;
        }
        return 0;
    }
    cout << "What count of iterations do you want to use?\n0 - standart count, any other positive number - your count\n";
    cin >> n;
    if (n == 0) {
        if (str == "sin") {
            cout << "sin(" << x << ") = " << _sin(x, meth) << endl;
            cout << "Error is " << sin(x) - _sin(x, meth) << endl;
        }
        if (str == "cos") {
            cout << "cox(" << x << ") = " << _cos(x, meth) << endl;
            cout << "Error is " << cos(x) - _cos(x, meth) << endl;
        }
        if (str == "exp") {
            cout << "exp(" << x << ") = " << _exp(x, meth) << endl;
            cout << "Error is " << exp(x) - _exp(x, meth) << endl;
        }
        if (str == "ln") {
            cout << "ln(" << x << ") = " << _ln(x, meth) << endl;
            cout << "Error is " << log(x) - _ln(x, meth) << endl;
        }
        return 0;
    }
    
    if (str == "sin") {
        cout << "sin(" << x << ") = " << _sin(x, meth, n) << endl;
        cout << "Error is " << sin(x) - _sin(x, meth, n) << endl;
    }
    if (str == "cos") {
        cout << "cox(" << x << ") = " << _cos(x, meth, n) << endl;
        cout << "Error is " << cos(x) - _cos(x, meth, n) << endl;
    }
    if (str == "exp") {
        cout << "exp(" << x << ") = " << _exp(x, meth, n) << endl;
        cout << "Error is " << exp(x) - _exp(x, meth, n) << endl;
    }
    if (str == "ln") {
        cout << "ln(" << x << ") = " << _ln(x, meth, n) << endl;
        cout << "Error is " << log(x) - _ln(x, meth, n) << endl;
    }
    return 0;
}