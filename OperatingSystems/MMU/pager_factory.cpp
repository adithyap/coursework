#include "pager_factory.hpp"

PagerFactory::PagerFactory()
{

}

Pager* PagerFactory::get_pager(char *algo)
{
    Pager *pager = NULL;

    switch(*algo)
    {
        case 'f':
        case 'F':
            pager = new FCFS();
            break;

        case 's':
        case 'S':
            pager = new SecondChance();
            break;

        case 'c':
        case 'C':
            pager = new Clock();
            break;

        case 'x':
        case 'X':
            pager = new ClockVirtual();
            break;

        case 'r':
        case 'R':
            pager = new RandomPager();
            break;

        case 'l':
        case 'L':
            pager = new LRU();
            break;

        case 'n':
        case 'N':
            pager = new NRU();
            break;

        case 'a':
        case 'A':
            pager = new Aging();
            break;

        case 'y':
        case 'Y':
            pager = new AgingVirtual();
            break;

        default:
            printf("PagerFactory::get_pager - Unknown argument %c\n", *algo);
            break;
    }

    return pager;
}
