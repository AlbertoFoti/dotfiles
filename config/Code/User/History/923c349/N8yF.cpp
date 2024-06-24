#include "type_defines.hxx"
#include "LkupTable/LkupTable.hxx"

double LookUpTable::matchAgainst(const std::string datapoint, double input_value) {
    double res {};

    for(unsigned int i=0; i<output_data.size(); i++) {
        if(datapoint == output_data.at(i).first) {
            res = LkupTable(input_value, this->input_data, this->output_data, output_data.at(i).second.size());

            return res;
        }
    }
    return res;
}