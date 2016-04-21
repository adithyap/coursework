#ifndef PAGE_TABLE_ENTRY_HPP
#define PAGE_TABLE_ENTRY_HPP

#include <iostream>

struct PageTableEntry
{
    unsigned int present:1;
    unsigned int modified:1;
    unsigned int referenced:1;
    // unsigned int paged_out:1;

    unsigned int swapped_out:1;

    unsigned int frame_id:28;
};

class PageTableEntryHelper
{
public:
    static PageTableEntry* get_page_table_entry(int);
};

#endif // PAGE_TABLE_ENTRY_HPP
