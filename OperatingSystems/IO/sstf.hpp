#ifndef SSTF_HPP
#define SSTF_HPP

#include <queue>
#include "scheduler.hpp"

class SSTF : public Scheduler
{
public:
    SSTF();

    void add_process(Process*);
    Process* get_next_process(int, DIRECTION);

    void display();

    ~SSTF();

private:
    std::deque<Process*> run_queue;
};

#endif // SSTF_HPP
