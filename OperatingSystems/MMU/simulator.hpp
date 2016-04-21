#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "pager.hpp"
#include "random.hpp"
#include "options.hpp"
#include "input_handler.hpp"
#include "page_table.hpp"
#include "frame_table.hpp"

#define ULL unsigned long long

class Simulator
{
public:
    Simulator(Pager*);

    void start();
    void display();

    ~Simulator();

private:

    Pager *pager;

    int instruction_count;

    void page_in(int, int);
    void zero(int);
    void map_page_to_frame(int, Frame*);
    void update_pte(InstructionType, int);

    void getch();

    Frame* get_frame();

    void print_debug_info();
    void print_statistics();
    ULL get_total_cost();

    void print(const char*, bool);
    void print1int(const char*, int, bool);
    void print2int(const char*, int, int, bool);
    void print3int(const char*, int, int, int, bool);

    bool dev_mode;
    bool fatal_errors;

    struct Statistics
    {
        int n_unmaps;
        int n_maps;
        int n_page_ins;
        int n_page_outs;
        int n_zeros;
    }stats;
};

#endif  // SIMULATOR_HPP
