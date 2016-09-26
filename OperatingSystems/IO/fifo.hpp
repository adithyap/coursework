#ifndef FIFO_HPP
#define FIFO_HPP

#include <queue>

#include "scheduler.hpp"

class FIFO : public Scheduler
{
public:
    FIFO();

    void add_process(Process*);
    Process* get_next_process(int, DIRECTION);

    void display();

    ~FIFO();

private:
    std::queue<Process*> run_queue;
};

#endif // FIFO_HPP
