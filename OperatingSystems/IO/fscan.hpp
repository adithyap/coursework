#ifndef FSCAN_HPP
#define FSCAN_HPP

#include <queue>
#include "scheduler.hpp"

class FSCAN : public Scheduler
{
public:
    FSCAN();

    void add_process(Process*);
    Process* get_next_process(int, DIRECTION);

    void display();

    DIRECTION get_direction(DIRECTION, int, int);

    ~FSCAN();

private:
    std::deque<Process*> run_queue;
    std::deque<Process*> dormant_queue;

    bool run_queue_active;

    void switch_queues();
};

#endif // FSCAN_HPP
