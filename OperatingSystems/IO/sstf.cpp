#include "sstf.hpp"

SSTF::SSTF()
{
    
}

void SSTF::add_process(Process* event)
{
    run_queue.push_back(event);
}

Process* SSTF::get_next_process(int head, DIRECTION dir)
{
    if (run_queue.size() == 0)
        return NULL;

    int min_distance = 1<<16;

    std::deque<Process*>::iterator target = run_queue.begin();
    Process *process = NULL;

    for (std::deque<Process*>::iterator it = run_queue.begin(); it != run_queue.end(); it++)
    {
        int distance = abS( (*it)->track - head );

        if ( distance < min_distance )
        {
            min_distance = distance;
            target = it;
            process = *it;
        }
    }

    run_queue.erase(target);

    return process;
}

void SSTF::display()
{
}

SSTF::~SSTF()
{
    // while (run_queue.size() > 0)
    // {
    //     Process *proc = run_queue.front();
    //     run_queue.pop_front();

    //     delete proc;
    // }
}
