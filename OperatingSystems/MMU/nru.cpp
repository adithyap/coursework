#include "nru.hpp"

NRU::NRU() : FAULT_CYCLE(10)
{
    page_faults = 0;
}

Frame* NRU::allocate_frame()
{
    if (frames.size() == 0)
    {
        return NULL;
    }

    // Split the pages into classes
    std::vector< std::vector<int> > page_classes = get_page_classes();

    Frame *frame = NULL;

    int index = 0;
    int max = page_classes.size();
    int target_page_id = -1;

    // Get the target page ID
    while(index < max)
    {
        if ( page_classes.at(index).size() > 0 )
        {
            int random_index = Random::myrandom( page_classes.at(index).size() );

            target_page_id =  page_classes.at(index).at( random_index );

            break;
        }

        index++;
    }

    handle_page_fault();

    return frames.at( PageTable::get_frame(target_page_id) );
}

void NRU::add_frame(Frame *frame)
{
    // frames.push_back(frame);

    if (frames.size() < FrameTable::get_n_frames())
    {
        frames.push_back(frame);
    }
    else
    {
        frames.at( frame->frame_id ) = frame;
    }
}

std::vector< std::vector<int> > NRU::get_page_classes()
{
    std::vector< std::vector<int> > page_classes;
    page_classes.resize(4);

    int len = PageTable::get_n_pages();

    for (int i = 0; i < len; i++)
    {
        if ( PageTable::is_present(i) == false )
            continue;

        if ( PageTable::is_referenced( i ) )
        {
            if ( PageTable::is_modified( i ) )
            {
                page_classes.at(3).push_back(i);
            }
            else
            {
                page_classes.at(2).push_back(i);
            }
        }
        else
        {
            if ( PageTable::is_modified( i ) )
            {
                page_classes.at(1).push_back(i);
            }
            else
            {
                page_classes.at(0).push_back(i);
            }   
        }
    }

    return page_classes;
}

void NRU::handle_page_fault()
{
    ++page_faults;

    if (page_faults == FAULT_CYCLE)
    {
        int len = frames.size();

        for (int i = 0; i < len; i++)
        {
            PageTable::set_referenced( (frames.at(i))->page_id, false );
        }

        page_faults = 0;
    }
}

void NRU::display()
{
    printf("\n");
}
