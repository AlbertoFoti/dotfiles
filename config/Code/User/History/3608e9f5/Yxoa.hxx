#pragma once
#include "type_defines.hxx"
#include "json.hpp"

class MissionScenario {
private:
    bool loaded {false};

public:
    std::string scenario_name;

    MCSimParsNSFStr MCSimParsNSF;
    NominalMissionNSFStr NominalMissionNSF;
    CoMNomX0NSFStr CoMNomX0NSF;
    TimeStepsNSFStr TimeStepsNSF;
    DRAppParsNSFStr DRAppParsNSF;
    SimEDLStr edl;

public:
    MissionScenario(const std::string& scenario_name);
    ~MissionScenario();

    bool loadScenario(const std::string& scenario_name);
    bool isLoaded();

    bool loadConfigFile(const std::string& scenario_name, const std::string& str_name, std::function<void(const nlohmann::json&)> fnct);

    void printScenario();

private:
    void printStruct();
};