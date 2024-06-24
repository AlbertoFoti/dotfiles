#include "E2E_inpout.hxx"

void PrintError(const char* descr) {
    std::cout << "Error: " << descr << "\n";
}

bool InputFileOpened(const char* filename, const char* currentRelease, FILE** inputFile) {
    return false;
}