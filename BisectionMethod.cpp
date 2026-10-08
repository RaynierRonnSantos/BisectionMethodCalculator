#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <cctype>

using namespace std;

class Parser {
private:
    string expr;
    int pos;
    double x;

    void skipSpaces() {
        while (pos < (int)expr.length() && isspace(expr[pos])) {
            pos++;
        }
    }

    double expression() {
        double result = term();

        while (true) {
            skipSpaces();

            if (pos < (int)expr.length() && expr[pos] == '+') {
                pos++;
                result += term();
            }
            else if (pos < (int)expr.length() && expr[pos] == '-') {
                pos++;
                result -= term();
            }
            else {
                break;
            }
        }

        return result;
    }

    double term() {
        double result = power();

        while (true) {
            skipSpaces();

            if (pos < (int)expr.length() && expr[pos] == '*') {
                pos++;
                result *= power();
            }
            else if (pos < (int)expr.length() && expr[pos] == '/') {
                pos++;

                double divisor = power();

                if (divisor == 0) {
                    throw runtime_error("Division by zero.");
                }

                result /= divisor;
            }
            else {
                break;
            }
        }

        return result;
    }

    double power() {
        double result = factor();

        skipSpaces();

        if (pos < (int)expr.length() && expr[pos] == '^') {
            pos++;
            result = pow(result, power());
        }

        return result;
    }

    double factor() {
        skipSpaces();

        // Positive number
        if (pos < (int)expr.length() && expr[pos] == '+') {
            pos++;
            return factor();
        }

        // Negative number
        if (pos < (int)expr.length() && expr[pos] == '-') {
            pos++;
            return -factor();
        }

        // Parentheses
        if (pos < (int)expr.length() && expr[pos] == '(') {
            pos++;

            double result = expression();

            skipSpaces();

            if (pos >= (int)expr.length() || expr[pos] != ')') {
                throw runtime_error("Missing closing parenthesis.");
            }

            pos++;
            return result;
        }

        // Variable x
        if (pos < (int)expr.length() &&
            (expr[pos] == 'x' || expr[pos] == 'X')) {
            pos++;
            return x;
        }

        // Number
        if (pos < (int)expr.length() &&
            (isdigit(expr[pos]) || expr[pos] == '.')) {

            int start = pos;

            while (pos < (int)expr.length() &&
                   (isdigit(expr[pos]) || expr[pos] == '.')) {
                pos++;
            }

            return stod(expr.substr(start, pos - start));
        }

        throw runtime_error("Invalid equation.");
    }

public:
    Parser(string equation) {
        expr = equation;
        pos = 0;
        x = 0;
    }

    double evaluate(double value) {
        x = value;
        pos = 0;

        double result = expression();

        skipSpaces();

        if (pos != (int)expr.length()) {
            throw runtime_error("Invalid equation format.");
        }

        return result;
    }
};


// ============================================================
// BISECTION METHOD
// ============================================================

void bisection(Parser& parser, double a, double b,
               double tol, int max_iter) {

    double fa, fb;

    try {
        fa = parser.evaluate(a);
        fb = parser.evaluate(b);
    }
    catch (const exception& e) {
        cout << "\nError: " << e.what() << endl;
        return;
    }

    // Check interval
    if (fa * fb >= 0) {
        cout << "\nInvalid Interval [a, b]." << endl;
        cout << "f(a) and f(b) must have opposite signs." << endl;

        cout << "f(" << a << ") = " << fa << endl;
        cout << "f(" << b << ") = " << fb << endl;

        return;
    }

    double c = 0;
    double previous_c = 0;
    double error = 100;

    cout << fixed << setprecision(6);

    cout << "\nIter\tXl\t\tXu\t\tXr\t\t"
         << "f(Xl)\t\tf(Xr)\t\tError (%)\n";

    cout << "-------------------------------------------------------------------------------\n";

    for (int iter = 0; iter < max_iter; iter++) {

        c = (a + b) / 2;

        double fc = parser.evaluate(c);
        fa = parser.evaluate(a);

        // Calculate approximate relative error
        if (iter > 0) {

            if (c != 0) {
                error = fabs((c - previous_c) / c) * 100;
            }
            else {
                error = fabs(c - previous_c) * 100;
            }
        }

        cout << iter + 1 << "\t"
             << a << "\t"
             << b << "\t"
             << c << "\t"
             << fa << "\t"
             << fc;

        if (iter == 0) {
            cout << "\tN/A" << endl;
        }
        else {
            cout << "\t" << error << endl;
        }

        // Root found
        if (fc == 0.0 || (iter > 0 && error < tol)) {

            cout << "\nRoot found at x = " << c << endl;
            cout << "Final Error Percentage: "
                 << error << "%" << endl;
            cout << "Total Iterations: "
                 << iter + 1 << endl;

            return;
        }

        // Determine new interval
        if (fa * fc < 0) {
            b = c;
        }
        else {
            a = c;
        }

        previous_c = c;
    }

    cout << "\nRoot Approximation after "
         << max_iter
         << " Iterations: x = "
         << c << endl;

    cout << "Final Error Percentage: "
         << error << "%" << endl;
}


// ============================================================
// MAIN
// ============================================================

int main() {

    string equation;
    double a, b, tol;
    int max_iter;

    cout << "============================================\n";
    cout << "        BISECTION METHOD CALCULATOR\n";
    cout << "============================================\n";

    cout << "\nEnter equation f(x): ";
    getline(cin, equation);

    // Check equation
    Parser parser(equation);

    try {
        parser.evaluate(0);
    }
    catch (const exception& e) {
        cout << "\nInvalid equation: "
             << e.what() << endl;

        return 1;
    }

    cout << "\nEnter the interval [a b]: ";
    cin >> a >> b;

    cout << "Enter Tolerance [0 (0%) - 1 (100%)]: ";
    cin >> tol;

    cout << "Enter Maximum Iterations: ";
    cin >> max_iter;

    bisection(parser, a, b, tol, max_iter);

    cout << "\nProgram finished. Press Enter to close...";
    cin.ignore();
    cin.get();

    return 0;
}
