//
//  Ruvi - @ruvi-framework.git
//

#pragma once

// includes
#include <string>
#include "utils/color.hh"

// struct || todo: this will probably be useless when we have more controls that needs to use some of those variables
struct control_data {

    bool dragging;
};

namespace ruvi {

    void groupbox(int x, int y, int width, int height, std::string name);
    bool checkbox(int x, int y, bool &variable, std::string name);
    float slider(int x, int y, float min, float max, float &variable, std::string name);
}