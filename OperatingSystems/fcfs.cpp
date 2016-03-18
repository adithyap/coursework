#include "fcfs.hpp"

FCFS::FCFS(int quantum)
{
    
}

void FCFS::add_process(Process* event)
{
    run_queue.push(event);
}

Process* FCFS::get_next_process()
{
    if (run_queue.size() == 0)
        return NULL;

    Process *evt = run_queue.front();

    run_queue.pop();

    return evt;
}

void FCFS::display()
{
    printf("%s\n", get_name());
}

const char* FCFS::get_name()
{
    return (const char*)"FCFS";
}

FCFS::~FCFS()
{
    while (run_queue.size() > 0)
    {
        Process *proc = run_queue.front();
        run_queue.pop();

        delete proc;
    }
}
