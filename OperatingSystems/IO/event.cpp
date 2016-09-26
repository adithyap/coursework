#include "event.hpp"

Event::Event(int process_id, int arrival_time, int track)
{
    Process *process = new Process(process_id, arrival_time, track);

    this->timestamp = arrival_time;
    this->process = process;

    this->state = TRANS_TO_READY;
}

Event::Event(int arrival_time, Process *process, EVENT_STATE state)
{
    this->timestamp = arrival_time;
    this->process = process;

    this->state = state;
}

void Event::display()
{
    printf("%5d: %5d %5d %5d\n", 
        process->process_id, process->arrival_time, process->start_time, process->finish_time);
}
