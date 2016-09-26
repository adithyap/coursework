#include "fifo.hpp"

FIFO::FIFO()
{
    
}

void FIFO::add_process(Process* event)
{
    run_queue.push(event);
}

Process* FIFO::get_next_process(int head, DIRECTION dir)
{
    if (run_queue.size() == 0)
        return NULL;

    Process *evt = run_queue.front();

    run_queue.pop();

    return evt;
}

void FIFO::display()
{
}

FIFO::~FIFO()
{
    // while (run_queue.size() > 0)
    // {
    //     Process *proc = run_queue.front();
    //     run_queue.pop();

    //     delete proc;
    // }
}
