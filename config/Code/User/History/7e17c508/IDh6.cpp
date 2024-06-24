#include "E2E_inpout.hxx"

void PrintError(const char *format, ...) {
    //va_list args;
    //va_start(args, format);
    //vfprintf(stderr, format, args);
    //va_end(args);
    std::cout << "Error. \n";
}

void PrintMessage(const char* message) {
    std::cout << "[MSG] " << message << "\n";
}

bool InputFileOpened(const char* filename, const char* currentRelease, FILE** inputFile) {
    return false;
}

int32_t E2E_INT(double readNumber) {
    return 0;
}
