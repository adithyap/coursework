#ifndef STATES_HPP
#define STATES_HPP

enum TRANSITION_STATE
{
    TRANS_TO_READY,
    TRANS_TO_RUN,
    TRANS_TO_BLOCK,
    TRANS_TO_PREEMPT
};

enum EVENT_STATE
{
    UNDEFINED,
    CREATED,
    READY,
    RUNNING,
    BLOCKED,
    FINISHED
};

class States
{
public:
    static const char* get_event_str(EVENT_STATE es);
};

#endif // STATES_HPP

