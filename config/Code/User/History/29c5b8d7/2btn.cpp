#include <iostream>
#include <fstream>

int main() {
    std::cout << "Hello, world!\n";

    auto r0 = 40.00;
    auto lon0 = 0.00;
    auto lat0 = 0.00;

    auto radius = 25.00;

    auto t = 0.00;
    auto dt = 1.00;
    auto Tsim = 290.0;

    while( t < Tsim ) {


        std::cout << t << std::endl;
        t += dt;
    }


    return 0;
}