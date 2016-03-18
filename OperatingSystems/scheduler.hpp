#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include "process.hpp"
#include "random.hpp"

class Scheduler
{

public:
    virtual void add_process(Process*) = 0;
    virtual Process* get_next_process() = 0;

    virtual const char* get_name() = 0;
    virtual void display() = 0;

    virtual int get_alloted_time(int);

    virtual ~Scheduler();
};

#endif // SCHEDULER_HPP

