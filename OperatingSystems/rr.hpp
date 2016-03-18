#ifndef RR_HPP
#define RR_HPP

#include <queue>

#include "scheduler.hpp"

class RR : public Scheduler
{
public:
    RR(int);

    void add_process(Process*);
    Process* get_next_process();

    const char* get_name();
    void display();

    void process_run_queue();
    void get_next_event_time();

    int get_alloted_time(int);

    ~RR();

private:
    std::queue< Process* > run_queue;
    int quantum;
};

#endif // RR_HPP
