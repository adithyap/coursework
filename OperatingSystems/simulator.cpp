#include "simulator.hpp"

Simulator::Simulator(Scheduler* s, EventManager* e, bool B_VERBOSE)
{
    this->scheduler = s;
    this->event_manager = e;
    this->B_VERBOSE = B_VERBOSE;
}

void Simulator::start()
{
    Event *evt;
    Process *CURRENT_RUNNING_PROCESS = NULL;

    int cpu_burst, io_burst, alloted_burst;
    EVENT_STATE e_to_state;
    TRANSITION_STATE t_to_state;

    int num_io_processes = 0;
    int last_time = 0, io_time = 0;

    bool CALL_SCHEDULER = false;

    while((evt = event_manager->get_event())) 
    {
        CURRENT_TIME = evt->timestamp;
        // evt->process->time_in_previous_state = CURRENT_TIME - evt->process->state_ts_time;


        // COMPUTE IO_TIME
        if (evt->current_state == BLOCKED && evt->process->remaining_time > 0)
        {
            if (num_io_processes == 0)
            {
                last_time = CURRENT_TIME;
            }

            num_io_processes++;
        }

        if (evt->prev_state == BLOCKED)
        {
            num_io_processes--;

            if (num_io_processes == 0)
            {
                io_time += CURRENT_TIME - last_time;
            }
        }
        // END COMPUTE IO_TIME


        switch(evt->t_state)
        {
            case TRANS_TO_READY:
                     // must come from BLOCKED or from PREEMPTION
                     // must add to run queue

                    if (evt->prev_state == UNDEFINED)
                    {
                        evt->prev_state = evt->current_state;
                        evt->current_state = READY;
                        evt->process->state_ts_time = CURRENT_TIME;
                    }

                    if (B_VERBOSE)
                        printf("%d %d %d: %s -> %s\n", CURRENT_TIME, evt->process->process_id, CURRENT_TIME - evt->process->state_ts_time, States::get_event_str(evt->prev_state), States::get_event_str(evt->current_state) );

                    evt->t_state = TRANS_TO_RUN;
                    evt->process->state_ts_time = CURRENT_TIME;

                    // Enqueue into scheduler
                    scheduler->add_process(evt->process);
                    evt->process->old_burst = 0;

                    CALL_SCHEDULER = true; // conditional on whether something is run
                    break;

            case TRANS_TO_RUN:
                    // create event for either preemption or blocking

                    // Process is coming from ready
                    // Increase CPU wait
                    evt->process->cpu_wait_time += (CURRENT_TIME - evt->process->state_ts_time);

                    if (evt->process->b_use_old_burst)
                    {
                        cpu_burst = evt->process->old_burst;
                    }
                    else
                    {
                        cpu_burst = Random::myrandom(evt->process->cpu_burst);
                        evt->process->old_burst = cpu_burst;
                    }

                    alloted_burst = scheduler->get_alloted_time(cpu_burst);

                    // evt->process->b_use_old_burst = alloted_burst < cpu_burst;

                    // Handle CPU burst being longer than remaining time
                    if (cpu_burst > evt->process->remaining_time)
                        cpu_burst = evt->process->remaining_time;

                    if (alloted_burst > evt->process->remaining_time)
                        alloted_burst = evt->process->remaining_time;

                    if (B_VERBOSE)
                        printf("%d %d %d: %s -> %s cb=%d rem=%d prio=%d\n", CURRENT_TIME, evt->process->process_id, CURRENT_TIME - evt->process->state_ts_time, States::get_event_str(evt->prev_state), States::get_event_str(evt->current_state), cpu_burst, evt->process->remaining_time, evt->process->dynamic_priority );

                    evt->process->state_ts_time = CURRENT_TIME;
                    evt->process->remaining_time -= alloted_burst;
                    evt->process->old_burst -= alloted_burst;

                    evt->process->b_use_old_burst = evt->process->old_burst > 0;

                    e_to_state = (evt->process->b_use_old_burst) ? READY : BLOCKED;
                    t_to_state = (evt->process->b_use_old_burst) ? TRANS_TO_PREEMPT : TRANS_TO_BLOCK;
                    
                    event_manager->add_event(new Event(CURRENT_TIME + alloted_burst, evt->process, RUNNING, e_to_state, t_to_state));

                    break;

            case TRANS_TO_BLOCK:
                    //create an event for when process becomes READY again

                    if (evt->process->remaining_time == 0)
                    {
                        evt->process->finish_time = CURRENT_TIME;

                        if (B_VERBOSE)
                            printf("%d %d %d: Done\n", CURRENT_TIME, evt->process->process_id, CURRENT_TIME - evt->process->state_ts_time);

                        event_manager->add_completed_event(evt);
                    }
                    else
                    {
                        evt->process->dynamic_priority = evt->process->static_priority - 1;

                        evt->process->old_burst = 0;

                        io_burst = Random::myrandom(evt->process->io_burst);

                        if (B_VERBOSE)
                            printf("%d %d %d: %s -> %s ib=%d rem=%d\n", CURRENT_TIME, evt->process->process_id, CURRENT_TIME - evt->process->state_ts_time, States::get_event_str(evt->prev_state), States::get_event_str(evt->current_state), io_burst, evt->process->remaining_time);

                        evt->process->io_time += io_burst;

                        evt->process->state_ts_time = CURRENT_TIME;

                        event_manager->add_event(new Event(CURRENT_TIME + io_burst, evt->process, BLOCKED, READY, TRANS_TO_READY));
                    }

                    CURRENT_RUNNING_PROCESS = NULL;
                    CALL_SCHEDULER = true;
                    break;

            case TRANS_TO_PREEMPT:
                    // add to runqueue (no event is generated)

                    if (evt->process->remaining_time == 0)
                    {
                        evt->process->finish_time = CURRENT_TIME;

                        if (B_VERBOSE)
                            printf("%d %d %d: Done\n", CURRENT_TIME, evt->process->process_id, CURRENT_TIME - evt->process->state_ts_time);

                        event_manager->add_completed_event(evt);
                    }
                    else
                    {
                        if (B_VERBOSE)
                            printf("%d %d %d: %s -> %s cb=%d rem=%d prio=%d\n", CURRENT_TIME, evt->process->process_id, CURRENT_TIME - evt->process->state_ts_time, States::get_event_str(evt->prev_state), States::get_event_str(evt->current_state), evt->process->old_burst, evt->process->remaining_time, evt->process->dynamic_priority );

                        evt->process->dynamic_priority--;

                        evt->t_state = TRANS_TO_RUN;
                        evt->process->state_ts_time = CURRENT_TIME;

                        // Enqueue into scheduler
                        scheduler->add_process(evt->process);
                    }

                    CURRENT_RUNNING_PROCESS = NULL;
                    CALL_SCHEDULER = true;
                    break;
        }

        if(CALL_SCHEDULER)
        {
            if (event_manager->get_next_event_time() == CURRENT_TIME)
            {
                continue;
            }

            CALL_SCHEDULER = false;

            if (CURRENT_RUNNING_PROCESS == NULL)
            {
                CURRENT_RUNNING_PROCESS = scheduler->get_next_process();

                if (CURRENT_RUNNING_PROCESS == NULL) 
                {
                    continue;
                }
                
                event_manager->add_event(new Event(CURRENT_TIME, CURRENT_RUNNING_PROCESS, READY, RUNNING, TRANS_TO_RUN));
            }

        }
    }

    event_manager->active_io_time = io_time;
}

void Simulator::display()
{
    scheduler->display();
    event_manager->display();
}

Simulator::~Simulator()
{
    delete scheduler;
    delete event_manager;
}
