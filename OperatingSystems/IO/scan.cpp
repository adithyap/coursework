#include "scan.hpp"

SCAN::SCAN()
{
    
}

void SCAN::add_process(Process* event)
{
    run_queue.push_back(event);
}

Process* SCAN::get_next_process(int head, DIRECTION dir)
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

        if (dir == UP && distance >= 0)
        {
            distance = abS(distance);

            if ( distance < min_distance )
            {
                min_distance = distance;
                target = it;
                process = *it;
            }
        }

        if (dir == DOWN && distance <= 0)
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

            if (dir == UP && distance <= 0)
            {
                distance = abS(distance);

                if ( distance < min_distance )
                {
                    min_distance = distance;
                    target = it;
                    process = *it;
                }
            }

            if (dir == DOWN && distance >= 0)
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

void SCAN::display()
{
    // printf(" *** ");
    // for (std::deque<Process*>::iterator it = run_queue.begin(); it != run_queue.end(); it++)
    // {
    //     printf("%d ", (*it)->track);
    // }
}

SCAN::~SCAN()
{
    // while (run_queue.size() > 0)
    // {
    //     Process *proc = run_queue.front();
    //     run_queue.pop_front();

    //     delete proc;
    // }
}
