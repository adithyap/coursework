#include "frame_table.hpp"

int FrameTable::n_frames;
std::deque<int> FrameTable::free_list;
std::map<int, Frame*> FrameTable::frame_map;

void FrameTable::init_frame_table(int n_frames)
{
    FrameTable::n_frames = n_frames;

    for ( int i = 0; i < n_frames; i++ )
    {
        free_list.push_back(i);

        frame_map[i] = new Frame(i);
    }
}

Frame* FrameTable::get_free_frame()
{
    if ( free_list.empty() == true )
    {
        return NULL;
    }

    int frame_id = free_list.front();

    Frame *frame = frame_map[frame_id];

    free_list.pop_front();

    return frame;
}

void FrameTable::display()
{
    for ( int i = 0; i < n_frames; i++ )
    {
        if ( frame_map[i]->page_id == -1 )
            printf("* ");
        else
            printf("%d ", frame_map[i]->page_id);
    }
}

int FrameTable::get_n_frames()
{
    return n_frames;
}

Frame* FrameTable::get_frame(int frame_id)
{
    if ( frame_id < 0 || frame_id >= n_frames )
    {
        return NULL;
    }

    return frame_map[frame_id];
}

FrameTable::~FrameTable() 
{
}

void FrameTable::destroy_frame_table()
{
    for ( int i = 0; i < n_frames; i++ )
    {
        delete (frame_map[i]);
    }
}
