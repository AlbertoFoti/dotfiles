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

    // Loading Mission Scenario
    std::string scenario = SimulationManager::scenarioSelection();
    MissionScenario ms {scenario};
    Log::info("GE", "Scenario %s loaded.", scenario.c_str());

    // ------------------------
    // Path Planning
    // - Trajectory profile generation
    // ------------------------
    Log::info("GE", "Beginning Path Planning Phase...");
    GEPathPlanning path_planning;

    // loadsfstructures

    // build lookup tables

    // build nominal mission trajectory
    GEPathPlanning::buildMissionTrajectory();

    // Create output folder

    Log::info("GE", "Path Planning Phase terminated.");

    // ------------------------
    // Path Tracking
    // - Trajectory profile tracking from EIP to PDP
    // ------------------------
    Log::info("GE", "Beginning Path Tracking Phase...");



    Log::info("GE", "Path Tracking Phase terminated.");
}
