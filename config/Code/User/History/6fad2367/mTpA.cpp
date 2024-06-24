#include <iostream>
#include <string>
#include <memory>
#include "Log.hxx"
#include "SimulationManager.hxx"
#include "GE_Path_Planning.hxx"

int main(int, char**){
    system("clear");
    std::cout << "\n\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
    std::cout << "GUIDED ENTRY SIMULATION\n";
    std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n";

    Log::title("GE", "Guided entry init...");

    // Loading Mission Scenario
    std::string scenario = SimulationManager::scenarioSelection();
    auto ms = std::make_shared<MissionScenario>(scenario);
    Log::done("GE", "Scenario %s loaded.", scenario.c_str());
    ms->printScenario();

    // ------------------------
    // Path Planning
    // - Trajectory profile generation
    // ------------------------
    Log::title("GE", "Beginning Path Planning Phase...");
    GEPathPlanning path_planning(ms);

    // loadsfstructures
    path_planning.loadSfStructures();

    // build lookup tables
    path_planning.buildLookUpTables();

    // load lookup tables
    path_planning.loadLookUpTables();

    // build mission trajectory
    path_planning.buildMissionTrajectory();

    // for montecarlo: add randomize and initialize step and plan a loop
    // build guidance trajectory
    uint32_t Nmon {};
    if(ms->MCSimParsNSF.MCFlag == false) {
        Nmon = ms->MCSimParsNSF.kMonInit;
    } else {
        Nmon = ms->MCSimParsNSF.NmonOrg;
    }

    path_planning.initializeSeeds();

    for(unsigned int kMon=ms->MCSimParsNSF.kMonInit; kMon <= Nmon; kMon++) {
        Log::info("GE", "Simulation [%2d / %2d].", kMon, Nmon);
        path_planning.randomizeAndInitialize(kMon);
        path_planning.buildGuidanceTrajectory();
    }
    Log::info("GE", "End of simulations.");

    // Create output folder

    Log::warn("GE", "Path Planning Phase terminated.");

    // ------------------------
    // Path Tracking
    // - Trajectory profile tracking from EIP to PDP
    // ------------------------
    Log::spacing();
    Log::title("GE", "Beginning Path Tracking Phase...");

    Log::info("PT", "Path tracking...");

    Log::warn("GE", "Path Tracking Phase terminated.");


    Log::spacing();
    Log::spacing();
    return 0;
}
