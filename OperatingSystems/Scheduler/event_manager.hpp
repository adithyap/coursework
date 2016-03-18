#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <iostream>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <queue>

#include "event.hpp"
#include "random.hpp"



class EventManager
{
public:
    std::queue< Event* > events;
    std::priority_queue< Event*, std::vector<Event*>, Event::ProcessID > completed_events;

    EventManager(char*);
    void add_event(Event*);
    Event* get_event();
    int get_next_event_time();

    int active_io_time;

    void add_completed_event(Event*);
    void display();
};

#endif // EVENTMANAGER_HPP
