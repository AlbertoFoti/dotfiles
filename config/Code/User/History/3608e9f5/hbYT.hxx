#pragma once
#include <string>
#include <cstdint>
#include <array>
#include <vector>

class BRMsData {
public:
    BRMsData() {}
    BRMsData(
        std::vector<double>  mu,
        std::vector<double> tBrInit, 
        std::vector<double> tBrEnd, 
        std::vector<double> dirBr, 
        std::vector<double> brFlag ) 
        : mu {mu}, tBrInit {tBrInit}, tBrEnd {tBrEnd}, dirBr {dirBr}, brFlag {brFlag}
    {}

public:
    std::vector<double> mu;
    std::vector<double> tBrInit;
    std::vector<double> tBrEnd;
    std::vector<double> dirBr;
    std::vector<double> brFlag;
};

class MCSimParsNSFStr {
public:
    uint32_t kMonInit {};
    uint32_t NmonOrg {};
    uint32_t decimation {};
    uint32_t decimation_th {};
    bool SmartTriggF {};
    bool PulsedF {};
    bool MCFlag {};
};

class NominalMissionNSFStr {
public:
    double TNom {};
    uint32_t N_Nom {};
    uint32_t uNom {};

    uint32_t GravIDNom {};
    double massNom {};
    double rCelBodyNom {};
    double SrefNom {};
    double LrefNom {};
    double omgCelBodyNom {};
    double ugNom {};
    double tPDPNom {};
    double MmaxNom {};
    double JNom {};
    double khfNom {};

    double aMax {};
    std::array<double, 4> parNom {};

    std::array<double, 8> tBrVNomOrg {};

    uint32_t NbrOrg {};
    uint32_t NbrNom {};
    std::vector<double> tBrVNom {};
};

class CoMNomX0NSFStr {
    double r0Nom {};
    double lon0Nom {};
    double lat0Nom {};
    double vAbsNom {};
    double fpa0Nom {};
    double head0Nom {};
};

class MissionScenario {
private:
    bool loaded {false};

public:
    std::string scenario_name;

    MCSimParsNSFStr MCSimParsNSF;
    NominalMissionNSFStr NominalMissionNSF;
    CoMNomX0NSFStr CoMNomX0NSF;

public:
    MissionScenario();
    MissionScenario(const std::string& scenario_name);
    ~MissionScenario();

    bool loadScenario(const std::string& scenario_name);
    bool isLoaded();

    bool loadMCSimParsNSF();
    bool loadNominalMissionNSF();
    bool loadCoMNomX0NSF();
};