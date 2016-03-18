#include "prio.hpp"

PRIO::PRIO(int quantum)
{
    this->quantum = quantum;
}

void PRIO::add_process(Process* process)
{
    if (process->dynamic_priority == -1)
    {
        process->dynamic_priority = process->static_priority - 1;
        add_to_expired(process);
    }

    else
    {
        add_to_active(process);
    }
}

void PRIO::add_to_active(Process* process)
{
    std::deque< Process* > active_queue1(active_queue);

    active_queue.clear();

    // Elements with higher priority
    while (active_queue1.size() > 0 && (active_queue1.front())->dynamic_priority >= process->dynamic_priority )
    {
        Process *p = active_queue1.front();

        active_queue.push_back(p);
        active_queue1.pop_front();
    }

    // Self
    active_queue.push_back(process);

    while (active_queue1.size() > 0)
    {
        Process *p = active_queue1.front();
        active_queue.push_back(p);
        active_queue1.pop_front();
    }
}

void PRIO::add_to_expired(Process* process)
{
    std::deque< Process* > expired_queue1(expired_queue);

    // Clear queue
    expired_queue.clear();

    // Elements with higher priority
    while (expired_queue1.size() > 0 && (expired_queue1.front())->dynamic_priority >= process->dynamic_priority )
    {
        Process *p = expired_queue1.front();

        expired_queue.push_back(p);
        expired_queue1.pop_front();
    }

    // Self
    expired_queue.push_back(process);

    while (expired_queue1.size() > 0)
    {
        Process *p = expired_queue1.front();
        expired_queue.push_back(p);
        expired_queue1.pop_front();
    }
}

Process* PRIO::get_next_process()
{
    if (active_queue.size() == 0)
    {
        if (expired_queue.size() == 0)
        {
            return NULL;
        }
        
        switch_queues();
    }

    Process *evt = active_queue.front();

    active_queue.pop_front();

    return evt;
}

void PRIO::switch_queues()
{
    std::swap(active_queue, expired_queue);
}

void PRIO::display()
{
    printf("%s %d\n", get_name(), quantum);
}

const char* PRIO::get_name()
{
    return (const char*)"PRIO";
}

int PRIO::get_alloted_time(int burst)
{
    if (quantum > burst)
        return burst;
    
    return quantum;
}

PRIO::~PRIO()
{
    while (active_queue.size() > 0)
    {
        Process *proc = active_queue.front();
        active_queue.pop_front();

        delete proc;
    }
}
