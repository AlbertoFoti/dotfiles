#include "LkupTable.hxx"
#include "LkupTable20.hxx"
#include "LkupTable1000.hxx"
#include <iostream>

double LkupTable(double input_value, std::vector<double> lkupIn, std::vector<double> lkupOut, std::size_t lkupTableSize) {
    if(lkupTableSize == 20) {
        LkupTable20_initialize();

        for(unsigned int i=0; i<lkupIn.size(); i++) {
            LkupTable20_U.lkup_in[i] = lkupIn.at(i);
            LkupTable20_U.lkup_out[i] = lkupOut.at(i);
        }

        LkupTable20_terminate();
    } else if(lkupTableSize == 1000) {

    } else {
        // error
        std::cout << "ERROR SIZE OF LKUPTABLE NOT AMONG THE OPTIONS.\n";
    }
    return 0.00;
}