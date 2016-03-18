#include "states.hpp"

const char* States::get_event_str(EVENT_STATE es)
{
    const char *states[6] = {"CREATED", "READY", "RUNNG", "BLOCK", "FINISHED", "UNDEFINED"};

    switch(es)
    {
        case CREATED:
            return states[0];

        case READY:
            return states[1];        

        case RUNNING:
            return states[2];

        case BLOCKED:
            return states[3];

        case FINISHED:
            return states[4];

        default:
            return states[5];
    }
}
