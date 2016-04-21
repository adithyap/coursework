#include "aging.hpp"

Aging::Aging() : MASK(1 << ( ( sizeof(int) * 8 ) - 1 ))
{

}

Frame* Aging::allocate_frame()
{
    if (frames.size() == 0)
    {
        return NULL;
    }

    // Get frame ID
    int frame_id = get_min_age_frame_id();

    // Get corresponding frame
    Frame *frame = frames.at(frame_id);

    // Set it's age to 0
    age.at(frame_id) = 0;

    return frame;
}

void Aging::add_frame(Frame *frame)
{
    if (frames.size() < FrameTable::get_n_frames())
    {
        frames.push_back(frame);
    }
    else
    {
        frames.at( frame->frame_id ) = frame;
    }

    if (age.size() < FrameTable::get_n_frames())
    {
        age.push_back(0);
    }
}

int Aging::get_min_age_frame_id()
{
    unsigned int min_age = UINT_MAX;
    int min_age_index = 0;

    int len = age.size();

    for ( int index = 0; index < len; index++ )
    {
        // Right shift
        age.at( index ) >>= 1;

        // Check if page is referenced
        if ( PageTable::is_referenced( frames.at( index )->page_id ) )
        {
            // OR with the mask
            age.at( index ) |= MASK;

            // Clear reference bit
            PageTable::set_referenced( frames.at( index )->page_id, false );
        }

        // Check for minimum age
        if ( age.at( index ) < min_age )
        {
            min_age = age.at( index );
            min_age_index = index;
        }
    }

    return min_age_index;
}

void Aging::display()
{
    int index = 0;

    for ( std::vector<unsigned int>::iterator it = age.begin(); it != age.end(); it++, index++ )
    {
        printf("%d:%0x ", index, *it);
    }

    printf("\n");
}
