#include "config.h"
#include <sstream>
#include <fstream>
#include <algorithm>
#include "constants.h"
#include "utils.h"
#include "logging.h"

namespace config {
    float grid_square_scale = 40.0; // Distance between points
    float grid_hex_scale = 35.0;

    float infinity_stop_size = 3;
}

bool config::load_config() {
    std::ifstream inFile;
    std::string filename = GetProperPath(CONFIG_FILE);
    inFile.open(filename);
    if(!inFile.is_open()) {
        logging::AddToLog("Config file not found! Using default values.");
        return false;
    }

    std::string line;

    bool retval = true;

    while (std::getline(inFile, line))
    {
        std::string original = line;
        // Empty line or comment
        if (line.length() == 0 || line[0] == '#')
            continue;

        // Remove whitespace
        line.erase (std::remove_if (line.begin(), line.end(), ::isspace), line.end());
        size_t eqloc = std::find(line.begin(), line.end(), '=') - line.begin();

        // No equals in line
        if(eqloc >= line.length()) {
            logging::AddToLog("Config Error: No equals sign in line: " + original);
            retval = false;
            continue;
        }

        std::string param = line.substr(0, eqloc);
        std::string value_str = line.substr(eqloc + 1, std::string::npos);
        std::istringstream iss(value_str);
        float value;

        // Invalid value
        if(!(iss >> value)) {
            logging::AddToLog("Config Error: Value '" + value_str + "' is not a float in line: " + original);
            retval = false;
            continue;
        }

        if(param == "grid_square_scale") {
            logging::AddToLog("Setting parameter " + param + " to value " + value_str);
            grid_square_scale = value;
        }
        else if(param == "grid_hex_scale") {
            logging::AddToLog("Setting parameter " + param + " to value " + value_str);
            grid_hex_scale = value;
        }
        else if(param == "infinity_stop_size") {
            logging::AddToLog("Setting parameter " + param + " to value " + value_str);
            infinity_stop_size = value;
        }
        else {
            logging::AddToLog("Config Error: Unrecognized parameter " + param + " in line: " + original);
            retval = false; // Invalid parameter
        }
    }
    return retval;
}
