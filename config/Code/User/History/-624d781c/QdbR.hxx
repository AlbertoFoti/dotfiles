#pragma once
#include <memory>
#include "MissionScenario.hxx"
#include "Log.hxx"

class GEPathPlanning {
public:
    std::shared_ptr<MissionScenario> ms;
    BRMsData nominal_traj {};

    std::vector<double> CoMNav01;
    std::vector<double> AttNav02;

    std::vector<double> xCoMNavEIP;

public:
    GEPathPlanning(std::shared_ptr<MissionScenario> ms);
    ~GEPathPlanning();

    void init();
    void initializeSeeds();
    void initializeSeeds(uint32_t seed);
    void randomizeAndInitialize(uint32_t kMon);

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

    /***
     * BUILD GUIDANCE TRAJECTORY
    */
    void buildGuidanceTrajectory();

    /***
     * SIMULATION CoM 2DOF anc 3DOF Detailed
    */
    void simCoM2dof();
    void simCoM3dof();

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

    double getMuAtTime(std::vector<TimeSeriesItem> uSim, double t);

    void randomizeNSFstr(NSFStr& inputStr);
    OptimalTimeResultStr findOptimalTime();
    void simLinSolDR(std::array<double, 6> x0, std::array<double, 6> xPDP, double TDR, uint32_t Nit);
    DRContMatOut BuildDRContMat_02(MatrixT vgh, std::vector<double> uOut, double TDR);
    double randn();
};