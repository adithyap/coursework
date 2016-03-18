#ifndef FCFS_HPP
#define FCFS_HPP

#include <queue>

#include "scheduler.hpp"

class FCFS : public Scheduler
{
public:
    FCFS(int quantum = 0);

    void add_process(Process*);
    Process* get_next_process();

    const char* get_name();
    void display();

    void process_run_queue();
    void get_next_event_time();

    ~FCFS();

private:
    std::queue<Process*> run_queue;
};

#endif // FCFS_HPP
