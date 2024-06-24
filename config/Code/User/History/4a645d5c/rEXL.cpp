#include <iostream>
#include <string>
#include "Log.hxx"
#include "SimulationManager.hxx"
#include "GE_Path_Planning.hxx"

int main(int, char**){
    std::cout << "\n\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
    std::cout << "GUIDED ENTRY SIMULATION\n";
    std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n";

    Log::info("GE", "Guided entry init...");
    Log::ask("GE", "Which scenario do you want to load? [EXM, MSR, MPL, MPL_TN5]: ");
    std::string scenario {};
    std::cin >> scenario;
    
    Log::info("GE", "Scenario loaded.");

    // ------------------------
    // Path Planning
    // - Trajectory profile generation
    // ------------------------
    Log::info("GE", "Beginning Path Planning Phase...");

    Log::info("GE", "Path Planning Phase terminated.");

    // ------------------------
    // Path Tracking
    // - Trajectory profile tracking from EIP to PDP
    // ------------------------
    Log::info("GE", "Beginning Path Tracking Phase...");



    Log::info("GE", "Path Tracking Phase terminated.");
}
