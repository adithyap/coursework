#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "scheduler.hpp"

#include "event_manager.hpp"
#include "random.hpp"
#include "states.hpp"

class Simulator
{
private:
    Scheduler *scheduler;
    EventManager *event_manager;

    int CURRENT_TIME;
    bool B_VERBOSE;

public:
    Simulator(Scheduler*, EventManager*, bool);
    void start();
    void display();
    ~Simulator();
};

#endif // SIMULATOR_HPP

