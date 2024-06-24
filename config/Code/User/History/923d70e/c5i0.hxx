#pragma once
#include <string>
#include <cstdint>
#include <array>
#include <vector>
#include <iostream>
#include <functional>

class TimeSeriesItem {
public:
    double t {};
    double value {};
};

class BRMsData {
public:
    BRMsData() {}
    BRMsData(
        std::vector<double> tSim,
        std::vector<TimeSeriesItem>  mu,
        std::vector<double> tBrInit, 
        std::vector<double> tBrEnd, 
        std::vector<double> dirBr, 
        std::vector<double> brFlag ) 
        : tSim {tSim}, mu {mu}, tBrInit {tBrInit}, tBrEnd {tBrEnd}, dirBr {dirBr}, brFlag {brFlag}
    {}

public:
    std::vector<double> tSim;
    std::vector<TimeSeriesItem> mu;
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
        std::cout << "  {CoMNomX0NSFStr}: [" 
            << "r0Nom:" << r0Nom << "," 
            << "lon0Nom:" << lon0Nom << "," 
            << "lat0Nom:" << lat0Nom << "," 
            << "vAbs0Nom:" << vAbs0Nom << "," 
            << "fpa0Nom:" << fpa0Nom << "," 
            << "head0Nom:" << head0Nom << ",\n" 
            << "    xCoMNomEIP(6),posNom_EIP_RM(3),xRLLNom(3)" << "]\n";
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
            << "TNom:" << TNom << "," 
            << "uNom:" << uNom << "," 
            << "GravIDNom:" << GravIDNom << "," 
            << "massNom:" << massNom << ","
            << "rCelBodyNom:" << rCelBodyNom << ","
            << "SrefNom:" << SrefNom << ","
            << "LrefNom:" << LrefNom << ","
            << "omgCelBodyNom:" << omgCelBodyNom << ",\n"
            << "    "
            << "ugNom:" << ugNom << ","
            << "tPDPNom:" << tPDPNom << ","
            << "MmaxNom:" << MmaxNom << ","
            << "JNom:" << JNom << ","
            << "khfNom:" << khfNom << ","
            << "aMax:" << aMax << ","
            << "parNom(4),tBrVNomOrg(8),"
            << "NbrOrg:" << NbrOrg << ","
            << "NbrNom:" << NbrNom << ","
            << "tBrVNom()"
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
            << "StFdbkS2:" << StFdbkS2 << ","
            << "STPDWNDUR:" << STPDWNDUR << ","
            << "TSTPDWN:" << TSTPDWN << ","
            << "\n    "
            << "ugMax:" << ugMax << ","
            << "ugMin:" << ugMin << ","
            << "DistF_H:" << DistF_H << ","
            << "DistF_S:" << DistF_S << ","
            << "StateFF_H:" << StateFF_H << ","
            << "StateFF_S:" << StateFF_S << ","
            << "DrObsFlagH:" << DrObsFlagH << ","
            << "DrObsFlagS:" << DrObsFlagS << ","
            << "CrClFlag:" << CrClFlag << ","
            << "GuiFlag:" << GuiFlag << ","
            << "]\n";
    }
};

class InputVariablesControlNSFStr {
public:
    double Jl {};
    double Jm {};
    double Jn {};
    double yaCoM {};
    double xaCoM {};
    double FmaxTh {};
    double FminTh {};
    double FmaxSat {};
    double FminSat {};
    double xIMUb {};
    double yIMUb {};
    double zIMUb {};

    void print() {
        std::cout << "  {InputVariablesControlNSF}: [" 
            << "Jl:" << Jl << "," 
            << "Jm:" << Jm << "," 
            << "Jn:" << Jn << "," 
            << "yaCoM:" << yaCoM << ","
            << "xaCoM:" << xaCoM << ","
            << "FmaxTh:" << FmaxTh << ","
            << "FminTh:" << FminTh << ","
            << "FmaxSat:" << FmaxSat << ","
            << "FminSat:" << FminSat << ",\n"
            << "    xIMUb:" << xIMUb << ","
            << "yIMUb:" << yIMUb << ","
            << "zIMUb:" << zIMUb
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
        std::cout << "\t{SimEDL}: [SimEDLPars, Thrusters, EnvData, AeroData]\n";
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