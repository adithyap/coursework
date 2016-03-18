#ifndef SJF_HPP
#define SJF_HPP

#include <queue>

#include "scheduler.hpp"

class SJF : public Scheduler
{
public:
    SJF(int quantum = 0);

    void add_process(Process*);
    Process* get_next_process();

    const char* get_name();
    void display();

    void process_run_queue();
    void get_next_event_time();

    ~SJF();

private:
    std::queue< Process* > run_queue;
};

#endif // SJF_HPP
