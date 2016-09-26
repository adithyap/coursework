#include "direction.hpp"

const char* Direction::get_direction_str(DIRECTION dir)
{
    std::vector<const char*> states;

    states.push_back("DOWN");
    states.push_back("UP");
    states.push_back("UNDEFINED_DIRECTION");

    switch(dir)
    {
        case DOWN:
            return states[0];

        case UP:
            return states[1];

        default:
            return states[2];
    }
}
