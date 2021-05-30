#include <iostream>

#include "foo.h"

Foo::Foo() {
    std::cout << "Constructor de Foo" << std::endl;
}

Foo::~Foo() {
    std::cout << "Destructor de Foo" << std::endl;
}