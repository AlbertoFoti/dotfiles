#pragma once

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