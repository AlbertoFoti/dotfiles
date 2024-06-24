#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Log.hxx"

template<typename T>
void writeTo(const std::string& filename, std::vector<T> data) {
    // Open the file for output in text mode
    std::ofstream outfile(filename);

    // Check if the file was opened successfully
    if (outfile.is_open()) {
        // Loop through each element in the data vector
        for (const T& element : data) {
            // Write the element to the file, followed by a newline character
            outfile << element << std::endl;
        }
        outfile.close();
        Log::info("DRW", "Data written to file: %s", filename.c_str());
    } else {
        std::cerr << "Error opening file: " << filename << std::endl;
        Log::info("DRW", "Data written to file: %s", filename.c_str());
        return false;
    }

    return true;
};