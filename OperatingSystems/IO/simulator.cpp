#include "simulator.hpp"

Simulator::Simulator(Scheduler* scheduler, bool verbose)
{
    this->scheduler = scheduler;
    this->event_manager = new EventManager();

    this->HEAD = 0;

    this->movement = 0;

    this->direction = UP;

    this->CURRENT_RUNNING_PROCESS = NULL;
    this->CALL_SCHEDULER = false;
    this->CURRENT_TIME = 0;

    this->verbose = verbose;
}

void Simulator::start()
{
    if (scheduler == NULL)
    {
        if (verbose)
        {
            printf("Simulator is not initialized with a scheduler, will abort.\n");
        }

        return;
    }

    Event *event;

    int target_time;

    if (verbose)
    {
        printf("TRACE\n");
    }

    while ( (event = event_manager->get_event()) != NULL )
    {
        CURRENT_TIME = event->timestamp;

        switch(event->state)
        {
            case TRANS_TO_READY:
                
                // Need to enqueue it

                if (verbose)
                {
                    printf("%d: %5d add %d\n", CURRENT_TIME, event->process->process_id, event->process->track);
                }

                scheduler->add_process(event->process);
                CALL_SCHEDULER = true;

                break;

            case TRANS_TO_RUN:
                // Need to set completion time

                event->process->start_time = CURRENT_TIME;

                // Update total movement and direction
                movement += scheduler->get_head_movement(HEAD, event->process->track);
                direction = scheduler->get_direction(direction, HEAD, event->process->track);

                // Calculate target arrival time
                target_time = CURRENT_TIME + scheduler->get_head_movement(HEAD, event->process->track);

                if (verbose)
                {
                    printf("%d: %5d issue %d %d\n", CURRENT_TIME, event->process->process_id, event->process->track, HEAD);
                }
                // printf("%d: %5d issue %d %d %s", CURRENT_TIME, event->process->process_id, event->process->track, HEAD, Direction::get_direction_str(direction));
                // scheduler->display();
                // printf("\n");

                event_manager->add_event(new Event(target_time, CURRENT_RUNNING_PROCESS, TRANS_TO_FINISH));

                break;

            case TRANS_TO_FINISH:
                // Set finish time
                // Set head

                if (verbose)
                {
                    printf("%d: %5d finish %d\n", CURRENT_TIME, event->process->process_id, CURRENT_TIME - event->process->arrival_time);
                }

                HEAD = event->process->track;


                event->process->finish_time = CURRENT_TIME;
                event_manager->add_completed_event(new Event(CURRENT_TIME, CURRENT_RUNNING_PROCESS, UNDEFINED_EVENT));

                CURRENT_RUNNING_PROCESS = NULL;
                CALL_SCHEDULER = true;

                // Upadte head
                break;

            default:
                if (verbose)
                {
                    printf("Unknown state encountered on event with PID %d\n", event->process->process_id);
                }
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
                CURRENT_RUNNING_PROCESS = scheduler->get_next_process(HEAD, direction);

                if (CURRENT_RUNNING_PROCESS == NULL) 
                {
                    continue;
                }

                event_manager->add_event(new Event(CURRENT_TIME, CURRENT_RUNNING_PROCESS, TRANS_TO_RUN));
            }
        }

        delete(event);
    }
}

void Simulator::display()
{
    event_manager->tot_movement = movement;

    event_manager->display(verbose);
}

Simulator::~Simulator()
{
    
}
