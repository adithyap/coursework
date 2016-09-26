#ifndef CSCAN_HPP
#define CSCAN_HPP

#include <queue>
#include "scheduler.hpp"

class CSCAN : public Scheduler
{
public:
    CSCAN();

    void add_process(Process*);
    Process* get_next_process(int, DIRECTION);

    void display();

    DIRECTION get_direction(DIRECTION, int, int);

    ~CSCAN();

private:
    std::deque<Process*> run_queue;
};

#endif // CSCAN_HPP
