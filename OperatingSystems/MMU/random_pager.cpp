#include "random_pager.hpp"

RandomPager::RandomPager()
{
    random_index = Random::myrandom(FrameTable::get_n_frames());
}

Frame* RandomPager::allocate_frame()
{
    if (frames.size() == 0)
    {
        return NULL;
    }

    Frame* frame = frames[random_index];

    return frame;
}

void RandomPager::add_frame(Frame *frame)
{
    if (frames.size() < FrameTable::get_n_frames())
    {
        frames.push_back(frame);
    }
    else
    {
        frames[random_index] = frame;

        random_index = Random::myrandom(frames.size());
    }
}

void RandomPager::display()
{
    printf("random = %d\n", this->random_index);
}
