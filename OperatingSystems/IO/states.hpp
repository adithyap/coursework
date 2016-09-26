#ifndef STATES_HPP
#define STATES_HPP

#include <vector>

enum EVENT_STATE
{
    UNDEFINED_EVENT,
    TRANS_TO_RUN,
    TRANS_TO_READY,
    TRANS_TO_FINISH,
    COMPLETE
};

class States
{
public:
    static const char* get_event_str(EVENT_STATE es);
};

#endif // STATES_HPP
