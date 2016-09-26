#include "scheduler.hpp"

Scheduler::~Scheduler()
{
    
}

int Scheduler::get_head_movement(int head, int track)
{
    return abS(track - head);
}

DIRECTION Scheduler::get_direction(DIRECTION direction, int head, int track)
{
    if (track < head)
    {
        return DOWN;
    }
    else if (track > head)
    {
        return UP;
    }

    return direction;
}

void Scheduler::display()
{
    
}
