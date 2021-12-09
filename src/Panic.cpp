#include "include/Panic.hpp"

#include <iostream>
#include <string>

void panic(std::string message) {
    std::cerr << "Error: " << message << std::endl;
    exit(1);
}