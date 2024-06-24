#include "SimulationManager.hxx"
#include "Log.hxx"

std::string SimulationManager::scenarioSelection() {
    Log::ask("GE", "Which scenario do you want to load? [EXM, MSR, MPL, MPL_TN5]: ");
    std::string scenario {};
    std::cin >> scenario;

    return scenario;
};