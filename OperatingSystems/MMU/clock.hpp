#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <iostream>
#include <vector>

#include "pager.hpp"

class Clock : public Pager
{
public:
    Clock();
    Frame* allocate_frame();
    void add_frame(Frame*);
    void display();

private:
    std::vector<Frame*> frames;
    int hand;

    void move_hand();
};

#endif // CLOCK_HPP
