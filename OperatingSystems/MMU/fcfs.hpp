#ifndef FCFS_HPP
#define FCFS_HPP

#include <iostream>
#include <queue>

#include "pager.hpp"
// #include "page_table_entry.hpp"

class FCFS : public Pager
{
public:
    Frame* allocate_frame();
    void add_frame(Frame*);
    void display();

private:
    std::deque<Frame*> frames;
};

#endif // FCFS_HPP
