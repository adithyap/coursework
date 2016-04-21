#include "clock_virtual.hpp"

ClockVirtual::ClockVirtual()
{
    this->hand = 0;
}

Frame* ClockVirtual::allocate_frame()
{
    if (frames.size() == 0)
    {
        return NULL;
    }

    // Get that frame
    Frame* frame = frames[ get_frame_from_hand() ];

    while ( PageTable::is_referenced(frame->page_id) == true )
    {
        PageTable::set_referenced(frame->page_id, false);
        move_hand();

        frame = frames[ get_frame_from_hand() ];
    }

    move_hand();

    return frame;
}

void ClockVirtual::add_frame(Frame *frame)
{
    if (frames.size() < FrameTable::get_n_frames())
    {
        frames.push_back(frame);
    }
    else
    {
        frames[ PageTable::get_frame(hand - 1) ] = frame;
    }
}

void ClockVirtual::move_hand()
{
    ++hand;

    if(hand == PageTable::get_n_pages())
    {
        hand = 0;
    }
}

int ClockVirtual::get_frame_from_hand()
{
    move_to_valid_page();
    return PageTable::get_frame(hand);
}

void ClockVirtual::move_to_valid_page()
{
    int tries = PageTable::get_n_pages() * 2;

    while ( PageTable::is_present(hand) == false )
    {
        move_hand();

        tries--;

        if (tries == 0)
        {
            printf("No valid page found!!!");
            break;
        }
    }
}

void ClockVirtual::display()
{
    printf("hand = %d\n", hand);
}
