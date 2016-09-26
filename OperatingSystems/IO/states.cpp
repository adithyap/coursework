#include "states.hpp"

const char* States::get_event_str(EVENT_STATE es)
{
    std::vector<const char*> states;

    states.push_back("TRANS_TO_RUN");
    states.push_back("TRANS_TO_READY");
    states.push_back("TRANS_TO_FINISH");
    states.push_back("COMPLETE");
    states.push_back("UNDEFINED_EVENT");


    switch(es)
    {
        case TRANS_TO_RUN:
            return states[0];

        case TRANS_TO_READY:
            return states[1];

        case TRANS_TO_FINISH:
            return states[2];

        case COMPLETE:
            return states[3];

        default:
            return states[4];
    }
}
