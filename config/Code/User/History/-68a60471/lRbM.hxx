#pragma once

class GEPathPlanning {
public:


public:
    GEPathPlanning(MissionScenario ms);

    void init();
    void randomizeAndInitialize();
    void buildGuidanceTrajectory();
    void exit();
};