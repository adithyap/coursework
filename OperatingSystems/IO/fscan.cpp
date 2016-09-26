#include "fscan.hpp"

FSCAN::FSCAN()
{
    run_queue_active = false;   
}

void FSCAN::add_process(Process* event)
{
    if (run_queue_active)
    {
        dormant_queue.push_back(event);
    }
    else
    {
        run_queue.push_back(event);
    }
}

Process* FSCAN::get_next_process(int head, DIRECTION dir)
{
    if (run_queue.size() == 0)
        switch_queues();

    if (run_queue.size() == 0)
        return NULL;

    // Subsequent adds should go to dormant queue
    run_queue_active = true;

    int min_distance = 1<<16;

    std::deque<Process*>::iterator target = run_queue.begin();
    Process *process = NULL;

    // Search favourable direction

    for (std::deque<Process*>::iterator it = run_queue.begin(); it != run_queue.end(); it++)
    {
        int distance = (*it)->track - head;

        if (distance >= 0)
        {
            distance = abS(distance);

            if ( distance < min_distance )
            {
                min_distance = distance;
                target = it;
                process = *it;
            }
        }
    }

    // If nothing was found, search in unfavourable direction
    if (process == NULL)
    {
        for (std::deque<Process*>::iterator it = run_queue.begin(); it != run_queue.end(); it++)
        {
            int distance = (*it)->track - head;

            if (distance <= 0)
            {
                distance = abS(distance);

                if ( distance < min_distance )
                {
                    min_distance = distance;
                    target = it;
                    process = *it;
                }
            }
        }
    }

    run_queue.erase(target);

    return process;
}

void FSCAN::switch_queues()
{
    std::swap(run_queue, dormant_queue);
}

void FSCAN::display()
{
    printf(" *** ");
    for (std::deque<Process*>::iterator it = run_queue.begin(); it != run_queue.end(); it++)
    {
        printf("%d ", (*it)->track);
    }
}

DIRECTION FSCAN::get_direction(DIRECTION direction, int head, int track)
{
    return UP;
}

FSCAN::~FSCAN()
{
    // while (run_queue.size() > 0)
    // {
    //     Process *proc = run_queue.front();
    //     run_queue.pop_front();

    //     delete proc;
    // }
}
