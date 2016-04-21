#include "aging_virtual.hpp"

AgingVirtual::AgingVirtual() : MASK(1 << ( ( sizeof(int) * 8 ) - 1 ))
{
    int len = PageTable::get_n_pages();

    for ( int i = 0; i < len; i++ )
    {
        age.push_back(0);
    }
}

Frame* AgingVirtual::allocate_frame()
{
    if (frames.size() == 0)
    {
        return NULL;
    }

    // Get page ID
    int page_id = get_min_age_page_id();

    // Set it's age to 0
    age.at(page_id) = 0;

    // Get frame ID
    int frame_id = PageTable::get_frame(page_id);

    // Get corresponding frame
    Frame *frame = frames.at(frame_id);

    return frame;
}

void AgingVirtual::add_frame(Frame *frame)
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

int AgingVirtual::get_min_age_page_id()
{
    unsigned int min_age = UINT_MAX;
    int min_age_page = 0;

    int len = age.size();

    for ( int index = 0; index < len; index++ )
    {
        if ( PageTable::is_present(index) == false )
        {
            continue;
        }

        // Right shift
        age.at( index ) >>= 1;

        // Check if page is referenced
        if ( PageTable::is_referenced(index) )
        {
            // OR with the mask
            age.at( index ) |= MASK;

            // Clear reference bit
            PageTable::set_referenced(index, false);
        }

        // Check for minimum age
        if ( age.at( index ) < min_age )
        {
            min_age = age.at( index );
            min_age_page = index;
        }
    }



    return  min_age_page;
}

void AgingVirtual::display()
{
    int index = 0;

    for ( std::vector<unsigned int>::iterator it = age.begin(); it != age.end(); it++, index++ )
    {
        if ( PageTable::is_present(index) == false )
        {
            printf("* ");
        }
        else
        {
            printf("%d:%0x ", index, *it);
        }
    }

    printf("\n");
}
