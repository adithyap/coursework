#ifndef SCAN_HPP
#define SCAN_HPP

#include <queue>
#include "scheduler.hpp"

class SCAN : public Scheduler
{
public:
    SCAN();

    void add_process(Process*);
    Process* get_next_process(int, DIRECTION);

    void display();

    ~SCAN();

private:
    std::deque<Process*> run_queue;
};

#endif // SCAN_HPP
