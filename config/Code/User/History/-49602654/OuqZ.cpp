#include <iostream>
#include "path_planning.hxx"
#include "GE_GNC.hxx"

#define T_MAX 10.00
#define DELTA_T_SIMULATION 1.00

GE_GNC_class path_tracking_gnc;

int main(int, char**){
    std::cout << "\n\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
    std::cout << "Guided entry simulation\n";
    std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n";

    // Path Planning
    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX USER CODE BEGINS HERE

    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX USER CODE ENDS HERE
    

    // Path Tracking
    double simulation_time = 0.00;

    while(simulation_time < T_MAX) {
        std::cout << "Sim time: " + std::to_string(simulation_time) + "\n";

        // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX USER CODE BEGINS HERE
        path_tracking_gnc.GE_GNC_Read();

        path_tracking_gnc.GE_GNC_Init();

        path_tracking_gnc.GE_GNC_Exec();


        // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX USER CODE ENDS HERE

        simulation_time += DELTA_T_SIMULATION;
    }

    std::cout << "Simulation ended successfully.\n"; 
}
