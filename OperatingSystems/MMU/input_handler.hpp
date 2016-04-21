#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <cstdlib>

#include "instruction.hpp"
#include "helper.hpp"

#include "random.hpp"

class InputHandler
{

public:
    static void init_handler(char*);
    static Instruction* get_next_instruction();

    static void display();

private:
    static std::deque<Instruction*> instructions;

};

#endif // INPUT_HANDLER_HPP
