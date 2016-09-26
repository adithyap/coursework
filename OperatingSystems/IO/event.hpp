#ifndef EVENT_HPP
#define EVENT_HPP

#include <iostream>
#include <cstdio>
#include <map>

#include "states.hpp"
#include "process.hpp"

class Event
{
public:
    Event(int, int, int);
    Event(int, Process*, EVENT_STATE);

    void display();

    int timestamp;
    Process *process;
    EVENT_STATE state;

    bool operator<(const Event&) const; 

    struct ProcessID
    {
      bool operator()(const Event* lhs, const Event* rhs) const
      {
        return lhs->process->process_id > rhs->process->process_id;
      }
    };
};

#endif // EVENT_HPP
