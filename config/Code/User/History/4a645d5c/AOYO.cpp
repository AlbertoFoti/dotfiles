#include <iostream>
#include <string>
#include <memory>
#include "Log.hxx"
#include "SimulationManager.hxx"
#include "GE_Path_Planning.hxx"

int main(int, char**){
    std::cout << "\n\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
    std::cout << "GUIDED ENTRY SIMULATION\n";
    std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n";

    Log::title("GE", "Guided entry init...");

    // Loading Mission Scenario
    std::string scenario = SimulationManager::scenarioSelection();
    auto ms = std::make_shared<MissionScenario>(scenario);
    Log::done("GE", "Scenario %s loaded.", scenario.c_str());

    // ------------------------
    // Path Planning
    // - Trajectory profile generation
    // ------------------------
    Log::spacing();
    Log::title("GE", "Beginning Path Planning Phase...");
    GEPathPlanning path_planning(ms);

    // loadsfstructures

    // build lookup tables

    // build nominal mission trajectory
    path_planning.buildMissionTrajectory();

    // Create output folder

    Log::done("GE", "Path Planning Phase terminated.");

    // ------------------------
    // Path Tracking
    // - Trajectory profile tracking from EIP to PDP
    // ------------------------
    Log::spacing();
    Log::title("GE", "Beginning Path Tracking Phase...");



    Log::done("GE", "Path Tracking Phase terminated.");


    Log::spacing();
    Log::spacing();
    return 0;
}
