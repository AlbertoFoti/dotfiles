#include "type_defines.hxx"
#include "../UtilsLib"

double LookUpTable::matchAgainst(const std::string datapoint, double input_value) {
    double res {};

    for(unsigned int i=0; i<output_data.size(); i++) {
        if(datapoint == output_data.at(i).first) {
            res = LkupTable(input_value, output_data.at(i).second.size());

            return res;
        }
    }
    return res;
}