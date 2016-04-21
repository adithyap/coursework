#include "page_table_entry.hpp"

PageTableEntry* PageTableEntryHelper::get_page_table_entry(int page_id)
{
    PageTableEntry* pte = new PageTableEntry;

    pte->present = false;
    pte->modified = false;
    pte->referenced = false;
    pte->swapped_out = false;

    pte->frame_id = 0;

    return pte;
}
