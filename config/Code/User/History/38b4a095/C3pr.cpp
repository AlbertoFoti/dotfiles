#include <iostream>
#include "CoM3DOFDetailed.hxx"

int main(int, char**){
    std::cout << "Hello, from CoMtest!\n";

    CoM3DOFDetailed_initialize();

    CoM3DOFDetailed_U.x[0] = 111;

    CoM3DOFDetailed_step();

    CoM3DOFDetailed_terminate();

    return 0;
}
