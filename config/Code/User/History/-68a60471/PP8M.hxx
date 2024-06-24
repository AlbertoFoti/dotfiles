#pragma once
#include "MissionScenario.hxx"

class GEPathPlanning {
public:
    MissionScenario ms;

public:
    GEPathPlanning(MissionScenario ms);
    ~GEPathPlanning();

    void init();
    void randomizeAndInitialize();
    void buildGuidanceTrajectory();
    void exit();
};