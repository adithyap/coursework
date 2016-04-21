#include "random.hpp"

std::vector<int> Random::randvals;
int Random::offset;
char* Random::rfile;

void Random::init_random(char *rfile)
{
    Random::rfile = rfile;

    read_file();
}

void Random::read_file()
{
    if (fopen(Random::rfile, "r") == NULL)
    {
        printf("Unable to open file %s", Random::rfile);
        return;
    }

    // Begin reading
    std::ifstream infile(Random::rfile);
    int size, t;

    // Read number of random numbers
    infile >> size;

    randvals.reserve(size);

    for (int i = 0; i < size; i++)
    {
        infile >> t;
        Random::randvals.push_back(t);
    }
}

int Random::myrandom(int burst)
{
    int randval = Random::randvals[offset] % burst;

    update_offset();

    return randval;
}

void Random::update_offset()
{
    offset++;

    if (offset >= Random::randvals.size())
        offset = 0;
}
