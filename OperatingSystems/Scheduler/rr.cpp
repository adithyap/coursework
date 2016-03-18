#include "rr.hpp"

RR::RR(int quantum)
{
    this->quantum = quantum;
}

void RR::add_process(Process* event)
{
    run_queue.push(event);
}

Process* RR::get_next_process()
{
    if (run_queue.size() == 0)
        return NULL;

    Process *evt = run_queue.front();

    run_queue.pop();

    return evt;
}

void RR::display()
{
    printf("%s %d\n", get_name(), quantum);
}

const char* RR::get_name()
{
    return (const char*)"RR";
}

int RR::get_alloted_time(int burst)
{
    if (quantum > burst)
        return burst;
    
    return quantum;
}

RR::~RR()
{
    while (run_queue.size() > 0)
    {
        Process *proc = run_queue.front();
        run_queue.pop();

        delete proc;
    }
}
