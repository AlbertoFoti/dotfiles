#include "LkupTable.hxx"
#include "LkupTable20.hxx"
#include "LkupTable1000.hxx"
#include <iostream>

double LkupTable(double input_value, std::vector<double> lkupIn, std::vector<double> lkupOut) {
    if(lkupIn.size() == 20) {
        LkupTable20_initialize();

        LkupTable20_U.data_in = input_value;

        for(unsigned int i=0; i<lkupIn.size(); i++) {
            LkupTable20_U.lkup_in[i] = lkupIn.at(i);
            LkupTable20_U.lkup_out[i] = lkupOut.at(i);
        }

        LkupTable20_step();

        double res = LkupTable20_Y.data_out;

        LkupTable20_terminate();

        return res;
    } else if(lkupIn.size() == 1000) {
        LkupTable1000_initialize();

        LkupTable1000_U.data_in = input_value;

        for(unsigned int i=0; i<lkupIn.size(); i++) {
            LkupTable1000_U.lkup_in[i] = lkupIn.at(i);
            LkupTable1000_U.lkup_out[i] = lkupOut.at(i);
        }

        LkupTable1000_step();

        double res = LkupTable1000_Y.data_out;

        LkupTable1000_terminate();

        return res;
    } else {
        // error
        std::cout << "ERROR SIZE OF LKUPTABLE NOT AMONG THE OPTIONS.\n";
    }
    return 0.00;
}