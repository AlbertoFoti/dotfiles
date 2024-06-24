#pragma once
#include <string>

class E2E_ReadFile {

public:

    void readReal(double* value) {
        return;
    }

    void readReal(double* v, int size) {
        return;
    }

    void readReal(double[3][3], int size1, int size2) {
        return;
    }

    void readInteger(int* value) {
        return;
    }
};

enum Initialization_type {
    INIFLAG,
    EXEFLAG,
    ENDFLAG,
};

class E2E_PrintOutput {

public:

    void E2E_writeVar(double value, const char* a, const char* b, const char* descr) {
        return;
    }

    void E2E_writeVar(double* value, int32_t a, const char* descr) {
        return;
    }

    void E2E_writeVar(double value) {
        return;
    }

    void set_group(const char* group_name, Initialization_type initflg) {
        return;
    }
};