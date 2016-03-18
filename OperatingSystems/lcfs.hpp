#ifndef LCFS_HPP
#define LCFS_HPP

#include <stack>

#include "scheduler.hpp"

class LCFS : public Scheduler
{
public:
    LCFS(int quantum = 0);

    void add_process(Process*);
    Process* get_next_process();

    const char* get_name();
    void display();

    void process_run_queue();
    void get_next_event_time();

    ~LCFS();

private:
    std::stack<Process*> run_queue;
};

#endif // LCFS_HPP
