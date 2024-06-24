#pragma once
#include <string>
#include <cstdint>
#include <array>
#include <vector>
#include <iostream>
#include <functional>

class BRMsData {
public:
    BRMsData() {}
    BRMsData(
        std::vector<double> tSim,
        std::vector<double>  mu,
        std::vector<double> tBrInit, 
        std::vector<double> tBrEnd, 
        std::vector<double> dirBr, 
        std::vector<double> brFlag ) 
        : tSim {tSim}, mu {mu}, tBrInit {tBrInit}, tBrEnd {tBrEnd}, dirBr {dirBr}, brFlag {brFlag}
    {}

public:
    std::vector<double> tSim;
    std::vector<double> mu;
    std::vector<double> tBrInit;
    std::vector<double> tBrEnd;
    std::vector<double> dirBr;
    std::vector<double> brFlag;

    void print() {
        std::cout << "\t{BRMsData}: []\n";
    }
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

    void print() {
        std::cout << "  {MCSimParsNSF}: [" 
            << "kMonInit:" << kMonInit << "," 
            << "NmonOrg:" << NmonOrg << "," 
            << "kMonInit:" << kMonInit << "," 
            << "decimation:" << decimation << "," 
            << "decimation_th:" << decimation_th << "," 
            << "SmartTriggF:" << SmartTriggF << "," 
            << "PulsedF:" << PulsedF << ","
            << "MCFlag:" << MCFlag << "]\n";
    }
};

class CoMNomX0NSFStr {
public:
    double r0Nom {};
    double lon0Nom {};
    double lat0Nom {};
    double vAbs0Nom {};
    double fpa0Nom {};
    double head0Nom {};

    std::array<double, 6> xCoMNomEIP {};
    std::array<double, 3> posNom_EIP_RM {};
    std::array<double, 3> xRLLNom {};

    void print() {
        std::cout << "  {CoMNomX0NSFStr}: []\n";
    }
};

class TimeStepsNSFStr {
public:
    double Tgui {};
    double Tatt {};
    double Tnav {};
    double TCoM {};
    double Ts {};

    void print() {
        std::cout << "  {TimeStepsNSF}: [" 
            << "Tgui:" << Tgui << "," 
            << "Tatt:" << Tatt << "," 
            << "Tnav:" << Tnav << "," 
            << "TCoM:" << TCoM << ","
            << "Ts:" << Ts << "]\n";
    }
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

    void print() {
        std::cout << "  {NominalMissionNSF}: [" 
            << "BUGMAX:" << BUGMAX << "," 
            << "GHVMAX:" << GHVMAX << "," 
            << "ObsDs:" << ObsDs << "," 
            << "ObsDh:" << ObsDh << ","
            << "ObsDfpa:" << ObsDfpa << ","
            << "StFdbkH:" << StFdbkH << ","
            << "StFdbkS1:" << StFdbkS1 << ","
            << "StFdbkS2:" << StFdbkS2 << ",\n"
            << "    "
            << "STPDWNDUR:" << STPDWNDUR << ","
            << "TSTPDWN:" << TSTPDWN << ","
            << "ugMax:" << ugMax << ","
            << "ugMin:" << ugMin << ","
            << "DistF_H:" << DistF_H << ","
            << "DistF_S:" << DistF_S << ","
            << "StateFF_H:" << StateFF_H << ","
            << "StateFF_S:" << StateFF_S << ","
            << "DrObsFlagH:" << DrObsFlagH << ","
            << "DrObsFlagS:" << DrObsFlagS << ",\n"
            << "    "
            << "CrClFlag:" << CrClFlag << ","
            << "GuiFlag:" << GuiFlag << ","
            << "]\n";
    }
};

class CoMControlParsNSFStr {
public:
    double BUGMAX {};
    double GHVMAX {};
    double ObsDs {};
    double ObsDv {};
    double ObsDh {};
    double ObsDfpa {};
    double StFdbkH {};
    double StFdbkS1 {};
    double StFdbkS2 {};
    double STPDWNDUR {};
    double TSTPDWN {};
    double ugMax {};
    double ugMin {};
    bool DistF_H {};
    bool DistF_S {};
    bool StateFF_H {};
    bool StateFF_S {};
    bool DrObsFlagH {};
    bool DrObsFlagS {};
    bool CrClFlag {};
    bool GuiFlag {};

    void print() {
        std::cout << "  {CoMControlParsNSF}: [" 
            << "BUGMAX:" << BUGMAX << "," 
            << "GHVMAX:" << GHVMAX << "," 
            << "ObsDs:" << ObsDs << "," 
            << "ObsDh:" << ObsDh << ","
            << "ObsDfpa:" << ObsDfpa << ","
            << "StFdbkH:" << StFdbkH << ","
            << "StFdbkS1:" << StFdbkS1 << ","
            << "StFdbkS2:" << StFdbkS2 << ",\n"
            << "    "
            << "STPDWNDUR:" << STPDWNDUR << ","
            << "TSTPDWN:" << TSTPDWN << ","
            << "ugMax:" << ugMax << ","
            << "ugMin:" << ugMin << ","
            << "DistF_H:" << DistF_H << ","
            << "DistF_S:" << DistF_S << ","
            << "StateFF_H:" << StateFF_H << ","
            << "StateFF_S:" << StateFF_S << ","
            << "DrObsFlagH:" << DrObsFlagH << ","
            << "DrObsFlagS:" << DrObsFlagS << ",\n"
            << "    "
            << "CrClFlag:" << CrClFlag << ","
            << "GuiFlag:" << GuiFlag << ","
            << "]\n";
    }
};

class DRAppParsNSFStr {
public:
    double gravDR {};
    double cDDR {};
    double cLDR {};
    double rhosDR {};
    double HatmDR {};

    void print() {
        std::cout << "  {DRAppParsNSF}: [" 
            << "gravDR:" << gravDR << "," 
            << "cDDR:" << cDDR << "," 
            << "cLDR:" << cLDR << "," 
            << "rhosDR:" << rhosDR << ","
            << "HatmDR:" << HatmDR << "]\n";
    }
};

class SimEDLParsNSFStr {
public:
    double xaCoM {};
    double yaCoM {};
    double zaCoM {};
    double xIMUbSim {};
    double yIMUbSim {};
    double zIMUbSim {};
    double mass {};
    double Jxx {};
    double Jyy {};
    double Jzz {};
    double Jxy {};
    double Jxz {};
    double Jyz {};

    void print() {
        std::cout << "\t{SimEDLParsNSF}: []\n";
    }
};

class ThrusterAllocParsSimNSFStr {
public:
    double FSatMaxSim {};
    double FSatMinSim {};
    double thxSim0 {};
    double thxSim1 {};
    double thxSim2 {};
    double thxSim3 {};
    double thySim0 {};
    double thySim1 {};
    double thySim2 {};
    double thySim3 {};
    double xThSim0 {};
    double xThSim1 {};
    double xThSim2 {};
    double xThSim3 {};
    double yThSim0 {};
    double yThSim1 {};
    double yThSim2 {};
    double yThSim3 {};
    double zThSim0 {};
    double zThSim1 {};
    double zThSim2 {};
    double zThSim3 {};
    double thrNoiseStd {};

    void print() {
        std::cout << "\t{ThrusterAllocParsSimNSF}: []\n";
    }
};

class EnvDataNSFStr {
public:

    void print() {
        std::cout << "\t{EnvDataNSF}: []\n";
    }
};

class AeroDataNSFStr {
public:

    void print() {
        std::cout << "\t{AeroDataNSF}: \n";
    }
};

class SimEDLStr {
public:
    SimEDLParsNSFStr SimEDLParsNSF;
    ThrusterAllocParsSimNSFStr ThrusterAllocParsSimNSF;
    EnvDataNSFStr EnvDataNSF;
    AeroDataNSFStr AeroDataNSF;

    void print() {
        std::cout << "\t{SimEDL}: \n";
    }
};

class LookUpTable {
public:
    std::vector<double> input_data {};
    std::vector<std::pair<std::string, std::vector<double>>> output_data {};

public:
    LookUpTable() {}

    LookUpTable(std::vector<double> input_data, std::vector<std::pair<std::string, std::vector<double>>> output_data) 
        : input_data {input_data}, output_data {output_data}
    {}

    double matchAgainst(double input_value) {
        return 0.00;
    }

    bool isEmpty() {
        if(input_data.size() == 0) {
            return true;
        } else {
            return false;
        }
    }
};