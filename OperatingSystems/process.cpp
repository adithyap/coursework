#include "process.hpp"

Process::Process(int process_id, int arrival_time, int total_cpu_time, int cpu_burst, int io_burst)
{
    this->process_id = process_id ;
    this->arrival_time = arrival_time;
    this->total_cpu_time = total_cpu_time;
    this->cpu_burst = cpu_burst;
    this->io_burst = io_burst;
    
    static_priority = Random::myrandom(4);
    dynamic_priority = static_priority - 1;

    finish_time = -1;
    turnaround_time = 0;

    io_time = 0;
    cpu_wait_time = 0;

    old_burst = 0;
    b_use_old_burst = false;

    state_ts_time = 0;

    remaining_time = total_cpu_time;
}

void Process::compute()
{
    turnaround_time = finish_time - arrival_time;
    b_computed = true;
}
