#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <iostream>
#include <cstdio>
#include <cstring>

class Options
{
public:
    static void init_options(char*);

    static bool ohhh();
    static bool page_table();
    static bool frame_table();
    static bool summary();

    static bool dbg_page_table();
    static bool dbg_frame_table();
    static bool dbg_aging();

private:

    static bool _ohhh;
    static bool _page_table;
    static bool _frame_table;
    static bool _summary;

    static bool _dbg_page_table;
    static bool _dbg_frame_table;
    static bool _dbg_aging;
};

#endif // OPTIONS_HPP
