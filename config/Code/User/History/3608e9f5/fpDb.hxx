#pragma once
#include "type_defines.hxx"
#include "json.hpp"

class MissionScenario {
private:
    bool loaded {false};

public:
    std::string scenario_name;

    MCSimParsNSFStr MCSimParsNSF;
    TimeStepsNSFStr TimeStepsNSF;
    NominalMissionNSFStr NominalMissionNSF;
    CoMControlParsNSFStr CoMControlParsNSF;
    DRAppParsNSFStr DRAppParsNSF;
    SimEDLStr edl;
    CoMNomX0NSFStr CoMNomX0NSF;

    LookUpTable machLookUpTable;
    LookUpTable radiusLookUpTable;

public:
    MissionScenario(const std::string& scenario_name);
    ~MissionScenario();

    bool loadScenario(const std::string& scenario_name);
    bool isLoaded();

    bool loadConfigFile(const std::string& scenario_name, const std::string& str_name, std::function<void(const nlohmann::json&)> fnct);
    LookUpTable loadLookUpTable(const std::string& filename, const std::string& input_value, std::vector<std::string> datapoints);

    void printScenario();
};