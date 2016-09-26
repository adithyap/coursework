#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <iostream>
#include <cstdio>

class Instruction
{

public:
    Instruction(int, int);
    void display();

    int time_issued;
    int track;

};

#endif // INSTRUCTION_HPP
