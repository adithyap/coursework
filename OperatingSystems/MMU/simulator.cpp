#include "simulator.hpp"

Simulator::Simulator(Pager* pager)
{
    this->pager = pager;

    this->instruction_count = 0;

    this->dev_mode = false;
    this->fatal_errors = true;

    stats.n_unmaps = 0;
    stats.n_maps = 0;
    stats.n_page_ins = 0;
    stats.n_page_outs = 0;
    stats.n_zeros = 0;
}

void Simulator::start()
{
    if (pager == NULL)
    {
        print("Simulator is not initialized with a pager, will abort.\n", this->fatal_errors);
        return;
    }

    Instruction *instruction;

    while ( (instruction = InputHandler::get_next_instruction()) != NULL )
    {
        if (Options::ohhh())
            instruction->display();

        int page_id = instruction->page_id;

        if ( PageTable::is_present(page_id) == false )
        {
            print2int("**** %d ==> Page table entry is not present for %d\n", instruction_count, page_id, this->dev_mode);

            // Virtual page doesn't exist in the frame list
            // Get some frame from the pager (or empty frame)
            Frame *frame = get_frame();

            if ( PageTable::is_swapped_out(page_id) )
            {
                page_in(page_id, frame->frame_id);
            }
            else
            {
                zero(frame->frame_id);
            }

            map_page_to_frame(page_id, frame);
        }

        update_pte(instruction->type, page_id);

        pager->referenced_event(page_id);

        print_debug_info();

        instruction_count++;

        if (dev_mode)
            getch();
    }
}

void Simulator::update_pte(InstructionType instruction, int page_id)
{
    // Update page table entry based on read or write operation

    PageTable::set_referenced(page_id, true);

    if (instruction == WRITE)
    {
        PageTable::set_modified(page_id, true);
    }
}

void Simulator::getch()
{
    std::string s;
    printf("Any char: ");
    std::cin >> s;
}

Frame* Simulator::get_frame()
{
    // Search for free spot
    Frame *frame = FrameTable::get_free_frame();

    if (frame == NULL)
    {
        frame = pager->allocate_frame();

        // Unmap the page
        print3int("%d: UNMAP   %d   %d\n", instruction_count, frame->page_id, frame->frame_id, Options::ohhh());

        stats.n_unmaps++;

        PageTable::set_present(frame->page_id, false);

        // Check if page out is needed
        if ( PageTable::is_modified(frame->page_id) )
        {
            // Modified, so page it out
            print3int("%d: OUT     %d  %d\n", instruction_count, frame->page_id, frame->frame_id, Options::ohhh());

            // Set page out flag, Reset modified flag
            // PageTable::set_paged_out(frame->page_id, true);
            PageTable::set_modified(frame->page_id, false);

            PageTable::set_swapped_out(frame->page_id, true);

            stats.n_page_outs++;

        }

        print2int("**** %d ==> Free list is empty, allocated frame %d\n", instruction_count, frame->frame_id, this->dev_mode);
    }

    print2int("**** %d ==> Returning frame %d\n", instruction_count, frame->frame_id, this->dev_mode);

    return frame;
}

void Simulator::page_in(int page_id, int frame_id)
{
    // Print status, Toggle flag
    
    print3int("%d: IN     %d   %d\n", instruction_count, page_id, frame_id, Options::ohhh());

    // PageTable::set_paged_out(page_id, false);

    stats.n_page_ins++;
}

void Simulator::zero(int frame_id)
{
    print2int("%d: ZERO        %d\n", instruction_count, frame_id, Options::ohhh());

    stats.n_zeros++;
}

void Simulator::map_page_to_frame(int page_id, Frame *frame)
{
    // Print status
    print3int("%d: MAP     %d   %d\n", instruction_count, page_id, frame->frame_id, Options::ohhh());

    // Update frame and page
    frame->page_id = page_id;
    PageTable::set_frame(page_id, frame->frame_id);
    PageTable::set_present(page_id, true);

    // Insert frame to pager
    pager->add_frame(frame);

    stats.n_maps++;
}

void Simulator::print_debug_info()
{
    if ( Options::dbg_page_table() )
    {
        PageTable::display();
    }

    if ( Options::dbg_frame_table() )
    {
        FrameTable::display();
        printf(" || ");
        this->pager->display();
    }
}

void Simulator::display()
{
    if ( Options::page_table() )
    {
        PageTable::display();
    }

    if ( Options::frame_table() )
    {
        FrameTable::display();
        printf("\n");
    }

    if ( Options::summary() )
    {
        print_statistics();
    }
}

void Simulator::print_statistics()
{
    printf("SUM %d U=%d M=%d I=%d O=%d Z=%d ===> %llu\n", 
        instruction_count, stats.n_unmaps, stats.n_maps, stats.n_page_ins, stats.n_page_outs, stats.n_zeros, get_total_cost());
}

ULL Simulator::get_total_cost()
{
    ULL access_cost = instruction_count;
    ULL map_cost = 400 * (ULL)(stats.n_unmaps + stats.n_maps);
    ULL page_cost = 3000 * (ULL)(stats.n_page_outs + stats.n_page_ins);
    ULL zero_cost = 150 * (ULL)(stats.n_zeros);

    return access_cost + map_cost + page_cost + zero_cost;
}

void Simulator::print(const char* str, bool flag)
{
    if (flag)
    {
        printf("%s", str);
    }
}

void Simulator::print1int(const char* str, int x, bool flag)
{
    if (flag)
    {
        printf(str, x);
    }
}

void Simulator::print2int(const char* str, int x, int y, bool flag)
{
    if (flag)
    {
        printf(str, x, y);
    }
}

void Simulator::print3int(const char* str, int x, int y, int z, bool flag)
{
    if (flag)
    {
        printf(str, x, y, z);
    }
}

Simulator::~Simulator()
{
    
}
