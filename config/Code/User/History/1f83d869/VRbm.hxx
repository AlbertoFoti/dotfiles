#pragma once
#include <iostream>
#include <string>

#include "E2E_enum.hxx"

class E2E_ReadFile {

public:

    E2E_ReadFile(const char* filename, const char* extention) {
        return;
    }

    void readReal(double* value) {
        return;
    }

    void readReal(double v[3], int size) {
        return;
    }

    void readReal(double m[3][3], int size1, int size2) {
        return;
    }

    void readInteger(int* value) {
        return;
    }
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

void PrintError(const char *format, ...);

bool InputFileOpened(const char* filename, const char* currentRelease, FILE** inputFile);

void GetStrings(FILE* inputFile, int32_t* error, int32_t* eof, int32_t* fileRow, int32_t a, char strings[21][80]);

bool NumberOK(int32_t a, char strings[21][80], double readNumber[21], int32_t* error);

int32_t E2E_INT(double readNumber);
