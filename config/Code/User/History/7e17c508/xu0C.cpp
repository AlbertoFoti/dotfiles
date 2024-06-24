#include "E2E_inpout.hxx"

void PrintError(const char *format, ...) {
    //va_list args;
    //va_start(args, format);
    //vfprintf(stderr, format, args);
    //va_end(args);
    std::cout << "Error. \n";
}

void PrintMessage(const char *format, ...) {
    //std::cout << "[INFO] " << message << "\n";
}

void PrintWarning(const char *format, ...) {
    //std::cout << "[WARN] " << message << "\n";
}

bool InputFileOpened(const char* filename, const char* currentRelease, FILE** inputFile) {
    return false;
}

int32_t E2E_INT(double readNumber) {
    return 0;
}

void WriteTimeOnScreen(int32_t rst,  const char* msg,  double a, double time) {
    std::cout << msg << time << "\n";
}
