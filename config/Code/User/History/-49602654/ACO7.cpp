#include <iostream>
#include "path_planning.hxx"
#include "timing_E2E.hxx"
#include "DHS_GE.hxx"

#define T_MAX 10.00
#define DELTA_T_SIMULATION 1.00

INT32 Reset         = 1;
timing_type  TimingVar;
timing_type* TimingInfo = &TimingVar;

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
        DHS_GE_Read();

        //DHS_GE_Init();

        //DHS_GE_Exec();

        DHS_GE_Exit();

        // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX USER CODE ENDS HERE

        simulation_time += DELTA_T_SIMULATION;
    }

    std::cout << "Simulation ended successfully.\n"; 
}
