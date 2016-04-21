#ifndef SECOND_CHANCE_HPP
#define SECOND_CHANCE_HPP

#include <iostream>
#include <queue>

#include "pager.hpp"

class SecondChance : public Pager
{
public:
    Frame* allocate_frame();
    void add_frame(Frame*);
    void display();

private:
    std::deque<Frame*> frames;
};

#endif // SECOND_CHANCE_HPP
