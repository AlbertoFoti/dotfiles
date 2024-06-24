#include <iostream>
#include "path_planning.hpp"

#define T_MAX 10.00
#define DELTA_T_SIMULATION 0.001

int main(int, char**){
    std::cout << "\n\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
    std::cout << "Guided entry simulation\n";
    std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";

    // Path Planning
    

    // Path Tracking
    double simulation_time = 0.00;

    while(simulation_time < T_MAX) {
        

        simulation_time += DELTA_T_SIMULATION;
    }

    std::cout << "Simulation ended successfully.\n"; 
}
