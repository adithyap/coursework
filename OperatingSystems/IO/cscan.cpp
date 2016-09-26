#include "cscan.hpp"

CSCAN::CSCAN()
{
    
}

void CSCAN::add_process(Process* event)
{
    run_queue.push_back(event);
}

Process* CSCAN::get_next_process(int head, DIRECTION dir)
{
    if (run_queue.size() == 0)
        return NULL;

    int min_distance = 1<<16;

    std::deque<Process*>::iterator target = run_queue.begin();
    Process *process = NULL;

    // Search favourable direction

    for (std::deque<Process*>::iterator it = run_queue.begin(); it != run_queue.end(); it++)
    {
        int distance = (*it)->track - head;

        if ( distance >= 0 && distance < min_distance )
        {
            min_distance = distance;
            target = it;
            process = *it;
        }
    }

    // If nothing was found, set head to 0 and search again
    if (process == NULL)
    {
        min_distance = 1<<16;

        for (std::deque<Process*>::iterator it = run_queue.begin(); it != run_queue.end(); it++)
        {
            if ( (*it)->track < min_distance )
            {
                min_distance = (*it)->track;
                target = it;
                process = *it;
            }
        }
    }

    run_queue.erase(target);

    return process;
}

void CSCAN::display()
{
    printf(" *** ");
    for (std::deque<Process*>::iterator it = run_queue.begin(); it != run_queue.end(); it++)
    {
        printf("%d ", (*it)->track);
    }
}

DIRECTION CSCAN::get_direction(DIRECTION direction, int head, int track)
{
    return UP;
}

CSCAN::~CSCAN()
{
    // while (run_queue.size() > 0)
    // {
    //     Process *proc = run_queue.front();
    //     run_queue.pop_front();

    //     delete proc;
    // }
}
