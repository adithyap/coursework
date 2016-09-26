#include "process.hpp"

Process::Process(int process_id, int arrival_time, int track)
{
    this->process_id = process_id ;
    this->arrival_time = arrival_time;
    this->track = track;

    this->start_time = -1;
    this->finish_time = -1;
}

void Process::compute()
{
}
