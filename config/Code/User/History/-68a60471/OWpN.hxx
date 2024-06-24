#pragma once
#include <memory>
#include "MissionScenario.hxx"
#include "Log.hxx"

class GEPathPlanning {
public:
    std::shared_ptr<MissionScenario> ms;

public:
    GEPathPlanning(std::shared_ptr<MissionScenario> ms);
    ~GEPathPlanning();

    void init();
    void randomizeAndInitialize();

    /***
     * BUILD MISSION TRAJECTORY NOMINAL
    */
    void buildMissionTrajectory();
    
    void buildGuidanceTrajectory();
    void exit();

private:
    BRMsData addMultipleBankReversals(std::vector<double>& tu, std::vector<double>& mu, std::vector<double>& tbrV, double aMax);
    BRMsData AddBankReversalKeep(std::vector<double>& tu, std::vector<double>& mu, double tbr, double aMax, double dirBr);
    BRMsData FixBankReversalProfKeep_02(
        std::vector<double>& tu, std::vector<double>& mu, 
        std::vector<double>& tBrInitV, std::vector<double>& tBrEndV,
        std::vector<double>& brFlag, double aMax
    );

    double GetReversedLeftAndRigthBankSt(
        double mu0, double muP0, 
        std::pair<double, double>& mu10, std::pair<double, double>& muP10, std::pair<double, double>& m
    );

    double UnNBR(double muNBR, int mCurr, double sign);
};