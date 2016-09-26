#include "scheduler_factory.hpp"

Scheduler* SchedulerFactory::get_scheduler(char* arg)
{
    Scheduler *scheduler = NULL;

    switch(*arg)
    {
        case 'i':
        case 'I':
            scheduler = new FIFO();
            break;

        case 'j':
        case 'J':
            scheduler = new SSTF();
            break;

        case 's':
        case 'S':
            scheduler = new SCAN();
            break;

        case 'c':
        case 'C':
            scheduler = new CSCAN();
            break;

        case 'f':
        case 'F':
            scheduler = new FSCAN();
            break;

        default:
            printf("SchedulerFactory::get_scheduler - Unknown argument %c\n.", *arg);
            break;
    }

    return scheduler;
}
