#include "second_chance.hpp"

Frame* SecondChance::allocate_frame()
{
    if (frames.size() == 0)
    {
        return NULL;
    }

    Frame* frame = frames.front();

    while ( PageTable::is_referenced(frame->page_id) == true )
    {
        frames.pop_front();
        
        PageTable::set_referenced(frame->page_id, false);
        add_frame(frame);

        frame = frames.front();
    }

    frames.pop_front();

    return frame;
}

void SecondChance::add_frame(Frame *frame)
{
    frames.push_back(frame);
}

void SecondChance::display()
{
    for ( std::deque<Frame*>::iterator it = frames.begin(); it != frames.end(); it++ )
    {
        printf("%d ", (*it)->frame_id);
    }

    printf("\n");
}
