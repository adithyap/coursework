#ifndef AGING_VIRTUAL_HPP
#define AGING_VIRTUAL_HPP

#include <iostream>
#include <vector>
#include <climits>

#include "pager.hpp"

class AgingVirtual : public Pager
{
public:
    AgingVirtual();
    Frame* allocate_frame();
    void add_frame(Frame*);
    void display();

private:
    std::vector<Frame*> frames;
    std::vector<unsigned int> age;

    const int MASK;

    int get_min_age_page_id();
};

#endif // AGING_VIRTUAL_HPP
