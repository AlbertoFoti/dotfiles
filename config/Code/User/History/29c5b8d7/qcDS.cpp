#include <iostream>
#include <fstream>

int main() {
    std::ofstream outfile("xcom_profile.txt");

    auto r0 = 40.00;
    auto lon0 = 0.00;
    auto lat0 = 0.00;

    auto radius = 25.00;

    auto t = 0.00;
    auto dt = 1.00;
    auto Tsim = 290.0;

    while( t < Tsim ) {


        // Write result to file
        xcom_profile

        std::cout << t << std::endl;
        t += dt;
    }


    return 0;
}