#include "Ciphertext.hpp"

#include <iostream>

int factorial(int n) {
    if (n < 2) {
        return 1;
    }
    return n * factorial(n-1);
}

void hello() {
    std::cout << "Hello world!\n";
}
