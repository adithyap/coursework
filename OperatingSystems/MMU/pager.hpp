#ifndef PAGER_HPP
#define PAGER_HPP

#include "random.hpp"
#include "frame_table.hpp"
#include "page_table.hpp"

class Pager
{
public:
    virtual Frame* allocate_frame() = 0;

    virtual void add_frame(Frame*) = 0;

    virtual void display() = 0;

    virtual void referenced_event(int);

    virtual ~Pager();
};

#endif // PAGER_HPP
