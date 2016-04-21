#ifndef PAGE_TABLE_HPP
#define PAGE_TABLE_HPP

#include <iostream>
#include <cstdio>
#include <map>
#include <vector>

#include "page_table_entry.hpp"

class PageTable
{

private:
    PageTable();

    static int n_pages;

    static std::vector< PageTableEntry* > pte_s;

public:

    static void init_page_table(int);

    static bool is_modified(int);
    static void set_modified(int, bool);

    static bool is_present(int);
    static void set_present(int, bool);

    static bool is_referenced(int);
    static void set_referenced(int, bool);

    static bool is_swapped_out(int);
    static void set_swapped_out(int, bool);

    static int get_frame(int);
    static void set_frame(int, int);
    
    static int get_n_pages();

    static void display();

    static void destroy_page_table();

    ~PageTable();

};

#endif // PAGE_TABLE_HPP
