#include "clock.hpp"

Clock::Clock()
{
    this->hand = 0;
}

Frame* Clock::allocate_frame()
{
    if (frames.size() == 0)
    {
        return NULL;
    }

    Frame* frame = frames[hand];

    while ( PageTable::is_referenced(frame->page_id) == true )
    {
        PageTable::set_referenced(frame->page_id, false);
        move_hand();

        frame = frames[hand];
    }

    move_hand();

    return frame;
}

void Clock::add_frame(Frame *frame)
{
    if (frames.size() < FrameTable::get_n_frames())
    {
        frames.push_back(frame);
    }
    else
    {
        frames[hand - 1] = frame;
    }
}

void Clock::move_hand()
{
    ++hand;

    if(hand == frames.size())
    {
        hand = 0;
    }
}

void Clock::display()
{
    printf("hand = %d\n", hand);
}
