#pragma once
#include "type_defines.hxx"


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

    bool loadMCSimParsNSF();
    bool loadNominalMissionNSF();
    bool loadCoMNomX0NSF();
    bool loadTimeStepsNSF();

    bool loadConfigFile(const std::string& scenario_name, const std::string& str_name, std::function<void(void)> fnct);
};