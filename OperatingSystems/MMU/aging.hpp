#ifndef AGING_HPP
#define AGING_HPP

#include <iostream>
#include <vector>
#include <climits>

#include "pager.hpp"

class Aging : public Pager
{
public:
    Aging();
    Frame* allocate_frame();
    void add_frame(Frame*);
    void display();

private:
    std::vector<Frame*> frames;
    std::vector<unsigned int> age;

    const int MASK;

    int get_min_age_frame_id();
};

#endif // AGING_HPP
