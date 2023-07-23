#include <iostream>
#include <string>
#include <limits>
#include "./string_calculator.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;

    // TODO(student): implement the UI
    string input;
    string num1;
    string operation;
    string num2;
    // char singleInput;
    getline(cin, input);
    bool statusQuit = false;

    while (!statusQuit)
    {
        /*
        if (input.size() == 1)
            singleInput = input[0];
        if ((singleInput == 'q' || input == "quit"))
            break;
        if (input.size() == 1) {
            int newDecimal = digit_to_decimal(singleInput);
            cout << digit_to_decimal(singleInput) << endl;
            cout << decimal_to_digit(newDecimal) << endl;
        }
        else {
            cout << trim_leading_zeros(input) << endl;
        }

      //  cout << add("-8000", "000") << endl;
        cout << multiply ("-642", "378") << endl;
        cin >> input;
        */
        num1 = input.substr(0, input.find(' '));
        input.erase(0, input.find(' ') + 1);
        operation = input.substr(0, input.find(' '));
        input.erase(0, input.find(' ') + 1);
        num2 = input;

        if ((num1 == "q") || (num1 == "quit"))
            break;
        else
        {
            if (operation == "+")
            {
                cout << ">> " << endl;
                cout << "ans =" << endl;
                cout << "\n    "
                     << add(num1, num2) << "\n" << endl;
            }
            else if (operation == "*")
            {
                cout << ">> " << endl;
                cout << "ans =" << endl;
                cout << "\n    "
                     << multiply(num1, num2) << "\n" << endl;
            }
        }

        getline(cin, input);
    }

    cout << ">> " << endl;
    cout << "farvel!" << '\n' << endl;
    return 0;
}
