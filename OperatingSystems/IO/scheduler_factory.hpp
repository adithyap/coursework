#ifndef SCHEDULER_FACTORY_HPP
#define SCHEDULER_FACTORY_HPP

#include <iostream>
#include "scheduler.hpp"
#include "fifo.hpp"
#include "sstf.hpp"
#include "scan.hpp"
#include "cscan.hpp"
#include "fscan.hpp"

class SchedulerFactory
{
public:
    static Scheduler* get_scheduler(char*);
};

#endif // SCHEDULER_FACTORY_HPP
