#pragma once
#include <memory>
#include "MissionScenario.hxx"

class GEPathPlanning {
public:
    std::shared_ptr<MissionScenario> ms;

public:
    GEPathPlanning(MissionScenario ms);
    ~GEPathPlanning();

    void init();
    void randomizeAndInitialize();
    void buildMissionTrajectory();
    void buildGuidanceTrajectory();
    void exit();
};