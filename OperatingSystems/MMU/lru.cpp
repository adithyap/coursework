#include "lru.hpp"

LRU::LRU()
{    
}

Frame* LRU::allocate_frame()
{
    if (frames.size() == 0)
    {
        return NULL;
    }

    Frame *frame = frames.back();
    frames.pop_back();

    return frame;
}

void LRU::add_frame(Frame *frame)
{
    frames.push_back(frame);
}

void LRU::referenced_event(int page_id)
{
    // Find the page ID and move it to the front
    Frame *frame = NULL;

    for ( std::deque<Frame*>::iterator it = frames.begin(); it != frames.end(); it++ )
    {
        if ( (*it)->page_id == page_id )
        {
            frame = (*it);
            frames.erase(it);
            break;
        }
    }

    frames.push_front(frame);

}

void LRU::display()
{
    printf("\n");
}
