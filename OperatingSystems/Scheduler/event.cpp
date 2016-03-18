#include "event.hpp"

Event::Event(int process_id, int arrival_time, int total_cpu_time, int cpu_burst, int io_burst)
{
    Process *process = new Process(process_id, arrival_time, total_cpu_time, cpu_burst, io_burst);

    this->timestamp = arrival_time;
    this->process = process;
    this->prev_state = UNDEFINED;
    this->current_state = CREATED;

    this->t_state = TRANS_TO_READY;
}

Event::Event(int arrival_time, Process *process, EVENT_STATE prev_state, EVENT_STATE current_state, TRANSITION_STATE t_state)
{
    this->timestamp = arrival_time;
    this->process = process;
    this->prev_state = prev_state;
    this->current_state = current_state;

    this->t_state = t_state;
}

void Event::display()
{
    if (!process->b_computed)
        process->compute();

    printf("%04d: %4d %4d %4d %4d %1d | %5d %5d %5d %5d\n",
            process->process_id,
            process->arrival_time,
            process->total_cpu_time,
            process->cpu_burst,
            process->io_burst,
            process->static_priority,

            process->finish_time,
            process->turnaround_time,
            process->io_time,
            process->cpu_wait_time
            );
}
