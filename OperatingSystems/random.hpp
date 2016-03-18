#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <vector>
#include <fstream>

class Random
{
public:
    static void init_random(char*);
    static int myrandom(int);

private:
    static std::vector<int> randvals;
    static int offset;
    static char* rfile;

    static void read_file();
    static void update_offset();
};

#endif // RANDOM_HPP
