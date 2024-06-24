#include <iostream>
#include "Log.hxx"
#include "GE_Path_Planning.hxx"

int main(int, char**){
    std::cout << "\n\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
    std::cout << "GUIDED ENTRY SIMULATION\n";
    std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n";

    Log::info("GE", "Guided entry init...");

    // ------------------------
    // Path Planning
    // - Trajectory profile generation
    // ------------------------
    Log::info("GE", "Beginning Path Planning Phase.");


    // ------------------------
    // Path Tracking
    // - Trajectory profile tracking from EIP to PDP
    // ------------------------
    Log::info("GE", "Beginning Path Tracking Phase");
}
