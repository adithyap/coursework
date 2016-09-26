#ifndef PROCESS_HPP
#define PROCESS_HPP

#include "states.hpp"

class Process
{
public:
    Process(int, int, int);
    void compute();

    int process_id;
    int arrival_time;
    int track;

    int start_time;
    int finish_time;
};

#endif // PROCESS_HPP
