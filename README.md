# Modern-Only C++ Course - Homework

This repository contains the homework for Lesson 7.

## Rational number type

Finish the Rational number type from the Lesson 7.

Put your implementation into `rational/rational.h` and `rational/rational.cc` (for now, it is OK to define all member functions and friends inline).

You should support the following operations:

```
Rational v(10,20); // Rational numbers, i.e. 1/2
Rational v(10); // Integers, i.e. 10/1

a + b; // addition
a - b; // substraction
a * b; // multiplication
a / b; // division

a += b; // compound assigments (also: -=, *=, /=)

a < b; // comparisons (also: >, <=, =>, ==, !=)

int64_t x = int64_t{v}; // explicit conversion to integral types (int64_t is good enough)
double y = double{v}; // explicit conversion to floating point types (double is good enough)

auto w = v.normalized(); // get the normalized form of the rational number (it is OK if this is deliberately a no-op)
int64_t i = v.numerator(); // get the numerator
int64_t j = v.denominator(); // get the denominator

std::cin >> v; // stream extraction
std::cout << v; // stream insertion
```

The goal is to have the following commands pass without errors:

```
bazel test //rational/...
bazel test --config=addrsan //rational/...
bazel test --config=ubsan //rational/...
```

## Solutions

If you wish to have a look at the solutions, you can find the commented code in the `solutions` directory.