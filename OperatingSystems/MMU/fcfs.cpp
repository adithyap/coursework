#include "fcfs.hpp"

Frame* FCFS::allocate_frame()
{
    if (frames.size() == 0)
    {
        return NULL;
    }

    // Remove the first physical frame in queue and return it
    Frame* frame = frames.front();

    frames.pop_front();

    return frame;
}

void FCFS::add_frame(Frame *frame)
{
    frames.push_back(frame);
}

void FCFS::display()
{
    for ( std::deque<Frame*>::iterator it = frames.begin(); it != frames.end(); it++ )
    {
        printf("%d ", (*it)->frame_id);
    }

    printf("\n");
}
