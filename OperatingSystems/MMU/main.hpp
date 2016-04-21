#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>

#include "random.hpp"
#include "pager_factory.hpp"
#include "input_handler.hpp"
#include "simulator.hpp"
#include "options.hpp"

// INPUTS
char *algo = NULL;
char *options = NULL;
char *frames = NULL;

char* inputfile;
char* randomfile;

Simulator *simulator;
Pager *pager;

// FUNCTIONS
int read_input(int argc, char *argv[]);
void initialize();
void simulate();
void deallocate();

#endif // MAIN_HPP
