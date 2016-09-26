#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>

#include "simulator.hpp"
#include "scheduler_factory.hpp"

// INPUTS
char *algo = NULL;
bool verbose = false;

char* inputfile;

Simulator *simulator;
Scheduler *scheduler;

// FUNCTIONS
int read_input(int argc, char *argv[]);
void initialize();
void simulate();
void deallocate();

#endif // MAIN_HPP
