#ifndef FRAME_TABLE_HPP
#define FRAME_TABLE_HPP

#include <iostream>
#include <cstdio>
#include <queue>
#include <map>

#include "frame.hpp"

class FrameTable
{
public:
    static void init_frame_table(int);

    static Frame* get_free_frame();

    static void display();

    static int get_n_frames();

    static Frame* get_frame(int);

    static void destroy_frame_table();

    ~FrameTable();

private:

    FrameTable();

    static int n_frames;
    static std::deque<int> free_list;
    static std::map<int, Frame*> frame_map;
};

#endif // FRAME_TABLE_HPP
