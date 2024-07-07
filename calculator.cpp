#include <iostream>
#include <regex>
#include <string>
#include <limits>
using namespace std;

struct fraction_structure {
    int numerator;
    int denominator;
};

//take the string input and extract numerator and denominator from each fraction
fraction_structure extract_numer_denom (const string& equation) {
    regex pattern("([+-]?[0-9]+)\\s*/\\s*([+-]?[0-9]+)|([+-]?[0-9]+)");//numerator and denominator pattern
    //make a class to store the extracted numerator and denominator
    smatch extracted;

    //if the input doesn't match right display error message
    if (regex_match(equation, extracted, pattern) == false) {
        throw invalid_argument("ERROR! input should be in the format (x/y / z/w) only ");
    }
        //if the input matches right extract numerator and denominator
    else {
        if (extracted[1].matched && extracted[2].matched) {
            //the form "x/y"
            int numerator = stoi(extracted[1]);
            int denominator = stoi(extracted[2]);
            return {numerator, denominator};
        } else if (extracted[3].matched) {
            //the form "x" (x/1)
            int numerator = stoi(extracted[3]);
            return {numerator, 1};
        }

    }
}

fraction_structure divide(const string& input) {
    int result_numer;
    int result_denom;
    regex pattern("\\s*([+-]?[0-9]+\\s*/\\s*[+-]?[0-9]+|[+-]?[0-9]+)\\s*/\\s*/\\s*([+-]?[0-9]+\\s*/\\s*[+-]?[0-9]+|[+-]?[0-9]+)\\s*");
    smatch extracted;
    if (regex_match(input, extracted, pattern) == false) {
        throw invalid_argument("ERROR! input should be in the format (x/y / z/w) only ");
        //if the input matches right extract the two fractions and divide them
    } else {
        fraction_structure fraction_one = extract_numer_denom(extracted[1]);
        fraction_structure fraction_two = extract_numer_denom(extracted[2]);
        // Check for division by zero
        if (fraction_two.numerator == 0) {
            throw invalid_argument("ERROR!Division by zero");
        }
        result_numer=fraction_one.numerator * fraction_two.denominator;
        result_denom=fraction_one.denominator * fraction_two.numerator;
        return {result_numer,result_denom};

    }
}
//take the string input and extract each fraction then multiply the two
fraction_structure multiply(const string& input) {
    int result_numer;
    int result_denom;
    regex pattern("\\s*([+-]?[0-9]+\\s*/\\s*[+-]?[0-9]+|[+-]?[0-9]+)\\s*\\*\\s*([+-]?[0-9]+\\s*/\\s*[+-]?[0-9]+|[+-]?[0-9]+)\\s*"); //multiplication pattern
    //make a class to store the extracted fractions
    smatch extracted;
    //if the input doesn't match right display error message
    if (regex_match(input, extracted, pattern) == false) {
        throw invalid_argument("ERROR! input should be in the format (x/y * z/w) only");
    }
        //if the input matches right multiply the two fractions
    else {
        fraction_structure fraction_one = extract_numer_denom(extracted[1]);
        fraction_structure fraction_two = extract_numer_denom(extracted[2]);
        //multiply fractions
        result_numer = fraction_one.numerator * fraction_two.numerator;
        result_denom= fraction_one.denominator * fraction_two.denominator;
        return {result_numer,result_denom};
    }
}
void displayResult(const fraction_structure& result) {
    cout << "Result: " << result.numerator << "/" << result.denominator << endl;
}
int main() {
    string userInput;
    int choice = 0;

    while (true) {
        cout << "Enter 1 for multiply, 2 for division, 3 for exit: ";
        cin >> choice;

        if (cin.fail() || (choice != 1 && choice != 2 && choice != 3)) {
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid option. Please enter 1 for multiply, 2 for division, 3 for exit." << endl;
            continue; // prompt again
        }

        if (choice == 3) {
            cout << "Exiting the program." << endl;
            break; // exit the loop
        }

        cout << "Enter fractions in the form (x/y / z/w) or (x/y * z/w): ";
        cin.ignore(); // ignore the newline character left in the input buffer
        getline(cin, userInput);

        try {
            fraction_structure result;
            if (choice == 1) {
                result = multiply(userInput);
            } else {
                result = divide(userInput);
            }
            displayResult(result);
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    return 0;
}
