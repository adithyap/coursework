#include "frame.hpp"

Frame::Frame(int frame_id)
{
    this->frame_id = frame_id;

    this->page_id = -1;
    this->reference_count = 0;
}
