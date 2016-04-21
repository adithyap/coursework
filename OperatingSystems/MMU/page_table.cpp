#include "page_table.hpp"

int PageTable::n_pages;
std::vector< PageTableEntry* > PageTable::pte_s;

void PageTable::init_page_table(int n_pages)
{
    PageTable::n_pages = n_pages;

    for (int i = 0; i < n_pages; i++)
    {
        pte_s.push_back( PageTableEntryHelper::get_page_table_entry(i) );
    }
}

bool PageTable::is_modified(int page)
{
    if (page < 0)   return false;

    return pte_s[page]->modified;
}

void PageTable::set_modified(int page, bool value)
{
    if (page < 0)   return;

    pte_s[page]->modified = value;
}


bool PageTable::is_present(int page)
{
    if (page < 0)   return false;

    return pte_s[page]->present;
}

void PageTable::set_present(int page, bool value)
{
    if (page < 0)   return;

    pte_s[page]->present = value;
}


bool PageTable::is_referenced(int page)
{
    if (page < 0)   return false;

    return pte_s[page]->referenced;
}

void PageTable::set_referenced(int page, bool value)
{
    if (page < 0)   return;

    pte_s[page]->referenced = value;
}

bool PageTable::is_swapped_out(int page)
{
    if (page < 0)   return false;

    return pte_s[page]->swapped_out;
}

void PageTable::set_swapped_out(int page, bool value)
{
    if (page < 0)   return;

    pte_s[page]->swapped_out = value;
}

int PageTable::get_frame(int page)
{
    if (page < 0)   return -1;

    return pte_s[page]->frame_id;
}

void PageTable::set_frame(int page, int frame_id)
{
    if (page < 0)   return;

    pte_s[page]->frame_id = frame_id;
}


void PageTable::display()
{
    int pt_index = 0;

    for(std::vector< PageTableEntry* >::iterator it = pte_s.begin(); it != pte_s.end(); it++, pt_index++) 
    {
        if ( (*it)->present == true )
        {
            char referenced = (*it)->referenced ? 'R' : '-';
            char modified = (*it)->modified ? 'M' : '-';
            char swapped_out = (*it)->swapped_out ? 'S' : '-';

            printf("%d:%c%c%c ", pt_index, referenced, modified, swapped_out);
        }
        else
        {
            if ( (*it)->swapped_out )
                printf("# ");
            else
                printf("* ");
        }
    }

    printf("\n");
}

int PageTable::get_n_pages()
{
    return n_pages;
}

PageTable::~PageTable() 
{
}

void PageTable::destroy_page_table()
{
    for (std::vector< PageTableEntry* >::iterator it = pte_s.begin(); it != pte_s.end(); it++)
    {
        delete (*it);
    }
}
