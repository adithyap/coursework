#include "main.hpp"

int main(int argc, char *argv[])
{
    // Read input and check for return code
    int return_code = read_input(argc, argv);

    // Return failure if reading input failed
    if (return_code != 0)
        return -1;

    // Initialize, simulate and deallocate
    initialize();
    simulate();
    deallocate();

    return 0;
}

int read_input(int argc, char *argv[])
{
    int c;
    
    while ((c = getopt(argc, argv, "vs:")) != -1)
    {
        switch (c)
        {
            case 's':
                algo = optarg;
                break;

            case 'v':
                verbose = true;
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

    // Can't proceed if not even 2 arguments are provided
    // Using (3) for (2) arguments since the first argument is the executable
    if (argc < 3)
    {
        printf("Invalid number of arguments %d, minimum required is 2", argc - 1);
        return -1;
    }

    // Read input file location
    inputfile = argv[argc - 1];

    return 0;
}

void initialize()
{
    // Initialize Input handler, Random handler and Options handler
    InputHandler::init_handler(inputfile);

    // Initialize Scheduler
    scheduler = SchedulerFactory::get_scheduler(algo);
}

void simulate()
{
    simulator = new Simulator(scheduler, verbose);
    simulator->start();
    simulator->display();
}

void deallocate()
{
    delete(simulator);

    delete(scheduler);
}
