#ifndef PROCESS_HPP
#define PROCESS_HPP

#include "states.hpp"
#include "random.hpp"

class Process
{
public:
    Process(int, int, int, int, int);
    void compute();

    int process_id;
    int arrival_time;
    int total_cpu_time;
    int cpu_burst;
    int io_burst;

    int static_priority;
    int dynamic_priority;

    int finish_time;
    int turnaround_time;

    int io_time;
    int cpu_wait_time;

    int old_burst;
    bool b_use_old_burst;

    int state_ts_time;
    // int time_in_previous_state;

    int remaining_time;

    bool b_computed;

    struct SJF
    {
      bool operator()(const Process* lhs, const Process* rhs) const
      {
        return lhs->remaining_time > rhs->remaining_time;
      }
    };
};

#endif // PROCESS_HPP
