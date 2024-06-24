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

public:
    MissionScenario();
    MissionScenario(const std::string& scenario_name);
    ~MissionScenario();

    bool loadScenario(const std::string& scenario_name);
    bool isLoaded();

    static void loadMCSimParsNSF(const nlohmann::json& jsonData);
    static void loadNominalMissionNSF(const nlohmann::json& jsonData);
    static void loadCoMNomX0NSF(const nlohmann::json& jsonData);
    static void loadTimeStepsNSF(const nlohmann::json& jsonData);

    bool loadConfigFile(const std::string& scenario_name, const std::string& str_name, std::function<void(const nlohmann::json&)> fnct);
};