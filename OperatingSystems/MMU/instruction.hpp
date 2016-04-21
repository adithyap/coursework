#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <iostream>
#include <cstdio>

#include "instruction_type.hpp"

class Instruction
{

public:
    Instruction(int, int);
    Instruction(InstructionType, int);
    void display();

    InstructionType type;
    int page_id;

};

#endif // INSTRUCTION_HPP
