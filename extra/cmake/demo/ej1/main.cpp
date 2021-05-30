#include <iostream>

// Sin el include_directories de cmake debería haberlo llamado #import "./lib/greeter.h"
#include "foo.h"

int main(int argc, char const *argv[])
{
    Foo foo;
    return 0;
}