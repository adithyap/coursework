#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>

#include "random.hpp"
#include "event_manager.hpp"
#include "scheduler_factory.hpp"
#include "simulator.hpp"

int main(int argc, char *argv[])
{
    char* inputfile;
    char* randomfile;
    
    
    char *arg = NULL;
    int c;
    int random_size;
    bool B_VERBOSE = false;
    int quantum = 0;
    
    while ((c = getopt(argc, argv, "vs:")) != -1)
    {
        switch (c)
        {
            case 's':
                arg = optarg;
                break;

            case 'v':
                B_VERBOSE = true;
                break;

            case '?':
                if (optopt == 's')
                    printf("Option -%c requires an argument.\n", optopt);
                else if (isprint(optopt))
                    printf("Unknown option -'%c'.\n", optopt);
                else
                    printf("Unknown option character '\\x%x'.\n",optopt);
                return 1;
                
            default:
                abort();
        }
    }

    int len = strlen(arg);
    if (len > 1)
    {
        int i = 1;
        while (i < len)
        {
            quantum = (quantum * 10) + (arg[i++] - '0');
        }
    }

    int I_INDEX = 2 + B_VERBOSE;
    int R_INDEX = 3 + B_VERBOSE;

    inputfile = argv[I_INDEX];
    randomfile = argv[R_INDEX];

    Random::init_random(randomfile);
    EventManager *e = new EventManager(inputfile); 
    Scheduler *s = SchedulerFactory::get_scheduler(arg, quantum);

    Simulator sim(s, e, B_VERBOSE);
    sim.start();
    sim.display();
    
    return 0;
    
}
