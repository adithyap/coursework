#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <cmath>
#include <cstdio>

#include "event_manager.hpp"
#include "scheduler.hpp"
#include "states.hpp"


#define ULL unsigned long long

class Simulator
{
public:
    Simulator(Scheduler*, bool);

    void start();
    void display();

    ~Simulator();

private:

    Scheduler *scheduler;

    bool verbose;

    int HEAD;
    bool CALL_SCHEDULER;
    int CURRENT_TIME;

    DIRECTION direction;

    int movement;

    Process* CURRENT_RUNNING_PROCESS;
    EventManager *event_manager;
};

#endif  // SIMULATOR_HPP
