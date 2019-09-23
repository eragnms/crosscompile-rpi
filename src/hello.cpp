#include <iostream>

#include "hello.h"

int main()
{
        std::cout << "Hello, World!" << std::endl;
        arma::vec a = {1, 2};
        a.print();
        return 0;
}
