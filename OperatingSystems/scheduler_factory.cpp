#include "scheduler_factory.hpp"

Scheduler* SchedulerFactory::get_scheduler(char* arg, int quantum)
{
    Scheduler *scheduler = NULL;

    switch(*arg)
    {
        case 'f':
        case 'F':
            scheduler = new FCFS(quantum);
            break;
        
        case 'l':
        case 'L':
            scheduler = new LCFS(quantum);
            break;

        case 's':
        case 'S':
            scheduler = new SJF(quantum);
            break;

        case 'r':
        case 'R':
            scheduler = new RR(quantum);
            break;

        case 'p':
        case 'P':
            scheduler = new PRIO(quantum);
            break;

        default:
            printf("SchedulerFactory::get_scheduler - Unknown argument %c\n.", *arg);
            break;
    }

    return scheduler;
}
