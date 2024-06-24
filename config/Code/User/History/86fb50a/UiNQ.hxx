#pragma once
#include "type_defines.hxx"
#include "json.hpp"
#include <random>

class MissionScenario {
private:
    bool loaded {false};

public:
    bool first {true};
    std::string scenario_name;
    Location target;
    RandomGen rg;

    MCSimParsNSFStr MCSimParsNSF;
    TimeStepsNSFStr TimeStepsNSF;
    NominalMissionNSFStr NominalMissionNSF;
    CoMControlParsNSFStr CoMControlParsNSF;
    InputVariablesControlNSFStr InputVariablesControlNSF;
    DRAppParsNSFStr DRAppParsNSF;
    SimEDLStr edl;
    NAVStr nav;
    PlanetGravStr PlanetGrav;
    CoMNomX0NSFStr CoMNomX0NSF;

    LookUpTable machLookUpTable;
    LookUpTable radiusLookUpTable;

    // Other data
    double OrderHatm;
    double R0;
    double cHatm;

    // Simulation structures

    SimLinSolDRInStr  sim_lin_sol_input;
    SimLinSolDROutStr sim_lin_sol_output;

    Sim2DOF_02InStr sim_2dof_input;
    Sim2DOF_02OutStr sim_2dof_output;

    parDRStr parDR;
    parDRCellStr parDRCell;

public:
    MissionScenario(const std::string& scenario_name);
    ~MissionScenario();

    bool loadScenario(const std::string& scenario_name);
    bool isLoaded();

    bool loadConfigFile(const std::string& scenario_name, const std::string& str_name, std::function<void(const nlohmann::json&)> fnct);
    bool loadConfigFileNSF(const std::string& scenario_name, const std::string& str_name, NSFStr& out, std::vector<std::string> ids);
    LookUpTable loadLookUpTable(const std::string& filename, const std::string& input_value, std::vector<std::string> datapoints);

    void printScenario();
};