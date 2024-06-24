#pragma once
#include <string>

class E2E_ReadFile {

};

typedef enum class Initialization_type_enum {
    INITFLAG,
    EXEFLAG,
    ENDFLAG,
} Initialization_type;

class E2E_PrintOutput {

public:

    void E2E_writeVar(double timingInfoTime, const char* a, const char* b, const char* descr) {
        return;
    }

    void set_group(const char* group_name, Initialization_type initflg) {
        return;
    }
};