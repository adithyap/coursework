#ifndef NRU_HPP
#define NRU_HPP

#include <iostream>
#include <queue>

#include "pager.hpp"

class NRU : public Pager
{
public:
    NRU();
    Frame* allocate_frame();
    void add_frame(Frame*);
    void display();

private:
    std::deque<Frame*> frames;
    std::vector< std::vector<int> > get_page_classes();

    int page_faults;
    const int FAULT_CYCLE;

    void handle_page_fault();
};

#endif // NRU_HPP
