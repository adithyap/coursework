#include "sjf.hpp"

SJF::SJF(int quantum)
{

}

void SJF::add_process(Process* process)
{
    // All hail std::priority_queue for not having a stable version    

    std::queue< Process* > run_queue1(run_queue);

    // Clear queue
    while (run_queue.size() > 0)
        run_queue.pop();

    // Enter in order

    // Elements less than
    while (run_queue1.size() > 0 && (run_queue1.front())->remaining_time <= process->remaining_time )
    {
        run_queue.push(run_queue1.front());

        run_queue1.pop();
    }

    // Self
    run_queue.push(process);

    while (run_queue1.size() > 0)
    {
        run_queue.push(run_queue1.front());

        run_queue1.pop();
    }

}

Process* SJF::get_next_process()
{
    if (run_queue.size() == 0)
        return NULL;

    Process *evt = run_queue.front();

    run_queue.pop();

    return evt;
}

void SJF::display()
{
    printf("%s\n", get_name());
}

const char* SJF::get_name()
{
    return (const char*)"SJF";
}

SJF::~SJF()
{
    while (run_queue.size() > 0)
    {
        Process *proc = run_queue.front();
        run_queue.pop();

        delete proc;
    }
}
