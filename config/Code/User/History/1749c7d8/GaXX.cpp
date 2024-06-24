#include "E2E_inpout.hxx"

void printError(const char *format, ...) {
    //va_list args;
    //va_start(args, format);
    //vfprintf(stderr, format, args);
    //va_end(args);
    std::cout << "Error. \n";
}

bool InputFileOpened(const char* filename, const char* currentRelease, FILE** inputFile) {
    return false;
}