#ifndef CLOCK_VIRTUAL_HPP
#define CLOCK_VIRTUAL_HPP

#include <iostream>
#include <vector>

#include "pager.hpp"

class ClockVirtual : public Pager
{
public:
    ClockVirtual();
    Frame* allocate_frame();
    void add_frame(Frame*);
    void display();

private:
    std::vector<Frame*> frames;
    int hand;

    void move_hand();
    int get_frame_from_hand();
    void move_to_valid_page();
};

#endif // CLOCK_VIRTUAL_HPP
