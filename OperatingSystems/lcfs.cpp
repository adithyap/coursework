#include "lcfs.hpp"

LCFS::LCFS(int quantum)
{

}

void LCFS::add_process(Process* event)
{
    run_queue.push(event);
}

Process* LCFS::get_next_process()
{
    if (run_queue.size() == 0)
        return NULL;

    Process *evt = run_queue.top();

    run_queue.pop();

    return evt;
}

void LCFS::display()
{
    printf("%s\n", get_name());
}

const char* LCFS::get_name()
{
    return (const char*)"LCFS";
}

LCFS::~LCFS()
{
    while (run_queue.size() > 0)
    {
        Process *proc = run_queue.top();
        run_queue.pop();

        delete proc;
    }
}
