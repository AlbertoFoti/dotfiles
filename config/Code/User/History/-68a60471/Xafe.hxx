#pragma once
#include <memory>
#include "MissionScenario.hxx"

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
    BRMsData addMultipleBankReversals(std::vector<double> tSimNom, std::vector<double> muNomNBR, std::vector<double> tBrVNom);
};