#ifndef PRIO_HPP
#define PRIO_HPP

#include <queue>

#include "scheduler.hpp"

class PRIO : public Scheduler
{
public:
    PRIO(int);

    void add_process(Process*);
    Process* get_next_process();

    const char* get_name();
    void display();

    void process_run_queue();
    void get_next_event_time();

    int get_alloted_time(int);

    ~PRIO();

private:
    // std::queue< Process* > run_queue;
    std::deque< Process* > active_queue;
    std::deque< Process* > expired_queue;
    int quantum;

    void add_to_active(Process*);
    void add_to_expired(Process*);
    void switch_queues();
};

#endif // PRIO_HPP
