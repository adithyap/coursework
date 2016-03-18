#include "event_manager.hpp"

EventManager::EventManager(char* inputfile)
{
    if (fopen(inputfile, "r") == NULL)
    {
        printf("EventManager::EventManager - Unable to open file %s", inputfile);
        return;
    }

    std::ifstream infile(inputfile);

    int pid = 0, at, tc, cb, io, prio;

    while (infile >> at >> tc >> cb >> io)
    {
        events.push(new Event(pid++, at, tc, cb, io));
    }

    active_io_time = 0;
}

void EventManager::add_event(Event* event)
{
    // All hail std::priority_queue for not having a stable version
    
    std::queue< Event* > events1(events);

    // Destroy events queue
    while (events.size() > 0)
        events.pop();

    // Enter in order

    // Elements less than
    while (events1.size() > 0 && (events1.front())->timestamp <= event->timestamp )
    {
        events.push(events1.front());
        events1.pop();
    }

    // Self
    events.push(event);

    while (events1.size() > 0)
    {
        events.push(events1.front());
        events1.pop();
    }
}

Event* EventManager::get_event()
{
    if (events.size() == 0)
        return NULL;

    Event *event = events.front();

    events.pop();

    return event;
}

int EventManager::get_next_event_time()
{
    if (events.size() > 0)
    {
        return (events.front())->timestamp;
    }

    return -1;
}

void EventManager::add_completed_event(Event* event)
{
    completed_events.push(event);
}

void EventManager::display()
{
    int finish_time = -1;
    int cpu_util_time = 0;
    int cpu_wait_time = 0;
    int turnaround_time = 0;
    int throughput = 0;

    int num_procs = completed_events.size();


    while(completed_events.size() > 0)
    {
        Event* event = completed_events.top();
        Process *process = event->process;

        event->display();

        if (process->finish_time > finish_time)
            finish_time = process->finish_time;

        cpu_util_time += process->total_cpu_time;
        cpu_wait_time += process->cpu_wait_time;
        turnaround_time += process->turnaround_time;

        completed_events.pop();
    }

    double avg_io = ((double) active_io_time / (double) finish_time) * 100;
    double avg_cpu_util = ((double) cpu_util_time / (double) finish_time) * 100;
    double avg_cpu_wait = (double) cpu_wait_time / (double) num_procs;
    double avg_turnaround = (double) turnaround_time / (double) num_procs;
    double avg_throughput = ((double) num_procs * 100) / (double) finish_time;

    printf("SUM: %d %.2lf %.2lf %.2lf %.2lf %.3lf\n", finish_time, avg_cpu_util, avg_io, avg_turnaround, avg_cpu_wait, avg_throughput);
}
