#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <iostream>
#include <cstdio>

#include "process.hpp"
#include "direction.hpp"

#define abS(x)                  ((x)<0?-(x):(x))

class Scheduler
{

public:
    virtual void add_process(Process*) = 0;
    virtual Process* get_next_process(int, DIRECTION) = 0;

    virtual void display();

    virtual DIRECTION get_direction(DIRECTION, int, int);
    virtual int get_head_movement(int, int);

    virtual ~Scheduler();
};

#endif // SCHEDULER_HPP

