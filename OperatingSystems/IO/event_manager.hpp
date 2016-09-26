#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <iostream>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <queue>

#include "instruction.hpp"
#include "input_handler.hpp"
#include "event.hpp"

#define CE_PQ std::priority_queue< Event*, std::vector<Event*>, Event::ProcessID >

class EventManager
{
public:
    std::queue< Event* > events;
    CE_PQ completed_events;

    EventManager();
    void add_event(Event*);
    Event* get_event();
    int get_next_event_time();

    int tot_movement;

    void add_completed_event(Event*);
    void display(bool);
};

#endif // EVENTMANAGER_HPP
