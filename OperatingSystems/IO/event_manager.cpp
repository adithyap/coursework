#include "event_manager.hpp"

EventManager::EventManager()
{
    Instruction *instruction;

    int process_id = 0;

    while ( (instruction = InputHandler::get_next_instruction()) != NULL )
    {
        events.push(new Event(process_id++, instruction->time_issued, instruction->track));

        delete(instruction);
    }
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

void EventManager::display(bool verbose)
{
    int total_time = -1;
    int turnaround = 0;
    int waittime = 0;
    int max_waittime = -1;

    int num_procs = 0;

    if (verbose)
    {
        printf("IOREQS INFO\n");
    }

    while(completed_events.size() > 0)
    {
        Event* event = completed_events.top();
        
        if (verbose)
        {
            event->display();
        }

        // Total time
        if (event->process->finish_time > total_time)
            total_time = event->process->finish_time;

        // Max wait time
        if ((event->process->start_time - event->process->arrival_time) > max_waittime)
            max_waittime = event->process->start_time - event->process->arrival_time;

        turnaround += (event->process->finish_time - event->process->arrival_time);
        waittime += (event->process->start_time - event->process->arrival_time);

        completed_events.pop();

        num_procs++;
    }

    printf("SUM: %d %d %.2lf %.2lf %d\n", 
        total_time, tot_movement, (double)turnaround / num_procs, (double)waittime / num_procs, max_waittime);
}
