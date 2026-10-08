# Bisection Method Calculator

A C++ console-based calculator that solves nonlinear equations using the **Bisection Method**. The program accepts a user-defined equation, interval, tolerance, and maximum number of iterations, then displays the calculation process and approximated root.

## Features

* Accepts equations using `x` as the variable
* Supports:

  * Addition (`+`)
  * Subtraction (`-`)
  * Multiplication (`*`)
  * Division (`/`)
  * Exponents (`^`)
  * Parentheses
  * Decimal values
* Accepts custom intervals
* Configurable tolerance
* Configurable maximum iterations
* Displays iteration values and approximate relative error
* Reports the calculated root and number of iterations
* Detects invalid equations, invalid intervals, division by zero, and missing parentheses

## Requirements

* C++ compiler with C++11 or later support
* Windows, Linux, or another platform with a compatible C++ compiler

## Compilation

Using `g++`:

```bash
g++ BisectionMethod.cpp -o BisectionMethod
```

## Running

On Windows:

```powershell
.\BisectionMethod.exe
```

On Linux/macOS:

```bash
./BisectionMethod
```

## Example

```text
============================================
        BISECTION METHOD CALCULATOR
============================================

Enter equation f(x): x^2 - 4
Enter the interval [a b]: 0 3
Enter Tolerance [0 (0%) - 1 (100%)]: 0.001
Enter Maximum Iterations: 100
```

The program then displays the iteration table and the approximated root.

## Method

The Bisection Method is a numerical root-finding technique that repeatedly divides an interval into two subintervals. The interval containing the root is selected based on the signs of the function values until the specified tolerance is reached or the maximum number of iterations is exceeded.

## Author

Developed as a C++ numerical methods project.
