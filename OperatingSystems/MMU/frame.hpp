#ifndef FRAME_HPP
#define FRAME_HPP

class Frame
{
public:

    Frame(int);

    int frame_id;
    int page_id;

    int reference_count;
};

#endif // FRAME_HPP
