#pragma once
#include <string>
#include <cstdint>
#include <array>
#include <vector>
#include <iostream>
#include <functional>
#include <random>
#include "Matrix.hxx"
#include "Tensor.hpp"
#include "Random.hxx"

class Location {
public:
    std::string site_name {};
    std::array<double, 3> location {}; 
};

class TimeSeries {
public:
    std::vector<double> t;
    std::vector<double> values;
};

class TimeSeriesItem {
public:
    double t {};
    double value {};
};

class NSFStr {
public:
    std::vector<std::string> ids;
    std::vector<uint32_t> unctype {};
    std::vector<double> values {};
    std::vector<double> valuesR {};
    std::vector<double> uncminv {};
    std::vector<double> uncmaxv {};

    double getR(const std::string& id) {
        for(unsigned int i=0; i<this->ids.size(); i++) {
            if(this->ids.at(i) == id) {
                return this->valuesR.at(i);
            }
        }
        
        return 0.00;
    }
};

class BRMsData {
public:
    std::vector<double> collectMu() {
        std::vector<double> res;
        
        for(unsigned int i=0; i<this->mu.size(); i++) {
            res.push_back(this->mu.at(i).value);
        }

        return res;
    }

public:
    std::vector<double> tSim;
    std::vector<TimeSeriesItem> mu;
    std::vector<double> tBrInit;
    std::vector<double> tBrEnd;
    std::vector<double> dirBr;
    std::vector<double> brFlag;

    MatrixT xCoM;
    std::vector<double> cDNomProf;
    std::vector<double> cLNomProf;
    std::vector<double> rhoNomProf; 
    std::vector<double> FDNom;
    std::vector<double> FLNom;
    MatrixT xCoMDotNom;
    std::vector<double> machNom;
    std::vector<std::array<double, 3>> gNEDNom;
    //FaWASNom;

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

    // A flag to turn off the path-plannig algorithm is included. If 'GuiFlag'
    // is zero, then the path-planning trajectory coincides with the Nominal trajectory
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

class SimEDLStr {
public:
    NSFStr SimEDLParsNSF;
    NSFStr SimEDLX0NSF;
    NSFStr ThrusterAllocParsSimNSF;
    NSFStr EnvDataNSF;
    NSFStr AeroDataNSF;

    void print() {
        std::cout << "\t{SimEDL}: [SimEDLPars, Thrusters, EnvData, AeroData]\n";
    }
};

class PlanetGravStr {
public:
    double SimT {};
    uint32_t GRAVID {};
    double MU {};
    double J2 {};
    double J3 {};
    double J4 {};
    double REQ {};

    void print() {
        std::cout << "  {PlanetGravStr}: [" 
            << "SimT:" << SimT << "," 
            << "GRAVID:" << GRAVID << "," 
            << "J2:" << J2 << "," 
            << "J3:" << J3 << ","
            << "J4:" << J4 << ","
            << "REQ:" << REQ << ","
            << "]\n";
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

    double matchAgainst(const std::string datapoint, double input_value);

    bool isEmpty() {
        if(input_data.size() == 0) {
            return true;
        } else {
            return false;
        }
    }
};

class NAVStr {
public:
    NSFStr AttNavX0NSF;

    void print() {
        std::cout << "\t{NAVStr}: [AttNavX0NSF, ]\n";
    }
};

class SimLinSolDRInStr {
public:
    uint32_t Ndisc {};
    double t1 {};
    std::vector<double> tSim {};
    std::vector<double> uSim {};
};

class SimLinSolDROutStr {
public:
    std::vector<double> tSim {};
    std::vector<double> uOut {};
    MatrixT xOut {};
    std::vector<double> duOut {};
};

class Sim2DOF_02InStr {
public:
    double t1 {};
    double Tgui {};

    std::array<double, 4> x0DR;
    std::vector<double> tSim;
    std::vector<TimeSeriesItem> uSim;
};

class Sim2DOF_02OutStr {
public:
    std::vector<double> uOut;
    MatrixT xDROut;

    void clear() {
        xDROut.clear();
        uOut.clear();
    }
};

class Sim3DOF_Out {
public:
    std::vector<double> collectMu() {
        std::vector<double> res;
        
        for(unsigned int i=0; i<this->mu.size(); i++) {
            res.push_back(this->mu.at(i).value);
        }

        return res;
    }

public:
    std::vector<double> tSim;
    std::vector<TimeSeriesItem> mu;
    std::vector<double> tBrInit;
    std::vector<double> tBrEnd;
    std::vector<double> dirBr;
    std::vector<double> brFlag;

    MatrixT xCoM;
    std::vector<double> cDProf;
    std::vector<double> cLProf;
    std::vector<double> rhoProf; 
    std::vector<double> FD;
    std::vector<double> FL;
    MatrixT xCoMDot;
    std::vector<double> mach;
    std::vector<std::array<double, 3>> gNED;
    //FaWAS;
};

class DRContMatOut {
public:
    MatrixT ContMat;
    TensorT A;
    std::vector<double> B;
    std::vector<double> gProf;
};

class parDRStr {
public:
    DRAppParsNSFStr drapp;
    double massDR;
    double rCelBodyDR;
    double SrefDR;
    double omgCelBodyDR;
    double headDR;
    double latDR;
};

class parDRCellStr {
public:
    double gravDR;
    double massDR;
    double SrefDR;
    double Raeroid;
    double R0;
    double cHatm;
};

class OptimalTimeResultStr {
public:
    std::vector<double> tSim;
    double tPDPDRSol;
    double dtPDP;
    double tPDPGui;
    double Ndisc;
    std::vector<double> tSimDRSol;
    size_t N;
    //
    std::vector<double> tBrVNom2;
    double t1;
};

class GuidanceProfileOutStr {
public:
    std::vector<double> tSim;
    std::vector<TimeSeriesItem> muSim;
    // muLastNBR
    std::vector<double> tBrV;
    std::vector<double> dirBr;
    MatrixT xSim;

    std::vector<double> cDProf;
    std::vector<double> cLProf;
    std::vector<double> rhoProf; 
    std::vector<double> FD;
    std::vector<double> FL;
    MatrixT xCoMDot;
    std::vector<double> mach;
    std::vector<std::array<double, 3>> gNED;

    double tPDPGui;

    MatrixT xCoMRs;
    std::vector<double> uMuRs;
};