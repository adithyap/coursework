#ifndef RANDOM_PAGER_HPP
#define RANDOM_PAGER_HPP

#include <iostream>
#include <vector>

#include "pager.hpp"

class RandomPager : public Pager
{
public:
    RandomPager();
    Frame* allocate_frame();
    void add_frame(Frame*);
    void display();

private:
    std::vector<Frame*> frames;
    int random_index;
};

#endif // RANDOM_PAGER_HPP
