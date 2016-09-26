#ifndef DIRECTION_HPP
#define DIRECTION_HPP

#include <vector>

enum DIRECTION
{
    UNDEFINED_DIRECTION,
    UP,
    DOWN
};

class Direction
{
public:
    static const char* get_direction_str(DIRECTION dir);
};

#endif // DIRECTION_HPP
