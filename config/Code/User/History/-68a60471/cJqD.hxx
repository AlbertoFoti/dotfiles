#pragma once
#include <memory>
#include "MissionScenario.hxx"
#include "Log.hxx"

class GEPathPlanning {
public:
    std::shared_ptr<MissionScenario> ms;
    BRMsData nominal_traj {};

public:
    GEPathPlanning(std::shared_ptr<MissionScenario> ms);
    ~GEPathPlanning();

    void init();
    void randomizeAndInitialize();

    /***
     * LOAD SF STRUCTURES
    */
    void loadSfStructures();

    /***
     * BUILD LOOKUP TABLES
    */
    void buildLookUpTables();

    /***
     * LOAD LOOKUP TABLES
    */
    void loadLookUpTables();

    /***
     * BUILD MISSION TRAJECTORY
    */
    void buildMissionTrajectory();
    BRMsData buildNominalMissionTrajectory();
    
    void buildGuidanceTrajectory();
    void clean();

private:
    BRMsData addMultipleBankReversals(std::vector<double>& tu, std::vector<double>& mu, std::vector<double>& tbrV, double aMax);
    BRMsData AddBankReversalKeep(std::vector<double>& tu, std::vector<double>& mu, double tbr, double aMax, double dirBr);
    BRMsData FixBankReversalProfKeep_02(
        std::vector<double>& tu, std::vector<double>& mu, 
        std::vector<double>& tBrInitV, std::vector<double>& tBrEndV,
        std::vector<double>& brFlag, double aMax
    );
    void GetReversedLeftAndRigthBankSt(
        double mu0, double muP0, 
        std::pair<double, double>& mu10, std::pair<double, double>& muP10, std::pair<double, double>& m
    );
    double UnNBR(double muNBR, int mCurr, double sign);

    void sim3dofDetailed();
};