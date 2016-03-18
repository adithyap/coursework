#ifndef SCHEDULER_FACTORY_HPP
#define SCHEDULER_FACTORY_HPP

#include <iostream>
#include "scheduler.hpp"
#include "lcfs.hpp"
#include "fcfs.hpp"
#include "sjf.hpp"
#include "rr.hpp"
#include "prio.hpp"

class SchedulerFactory
{
public:
    static Scheduler* get_scheduler(char*, int);
};

#endif // SCHEDULER_FACTORY_HPP
