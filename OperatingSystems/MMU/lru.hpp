#ifndef LRU_HPP
#define LRU_HPP

#include <iostream>
#include <queue>

#include "pager.hpp"

class LRU : public Pager
{
public:
    LRU();
    Frame* allocate_frame();
    void add_frame(Frame*);
    void referenced_event(int);
    void display();

private:
    std::deque<Frame*> frames;
};

#endif // LRU_HPP
