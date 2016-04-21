#include "input_handler.hpp"

std::deque<Instruction*> InputHandler::instructions;

void InputHandler::init_handler(char* inputfile)
{
    if (fopen(inputfile, "r") == NULL)
    {
        printf("InputHandler::read_input - Unable to open file %s", inputfile);
        return;
    }

    std::ifstream infile(inputfile);
    std::string temp;

    while(std::getline(infile, temp))
    {
        // Check for commment
        if (temp[0] == '#')
        {
            continue;
        }

        // Get tokens
        std::vector<std::string> tokens = Helper::split(temp, ' ');

        // Process tokens
        // Handle wrong token count
        // Read into ints

        if (tokens.size() != 2)
        {
            // Wrong input
            printf("InputHandler::read_input - Wrong token length %lu", tokens.size());
            continue;
        }

        int type = (int) strtol(tokens[0].c_str(), NULL, 10);
        int instruction = (int) strtol (tokens[1].c_str(), NULL, 10);

        Instruction *instr_obj = new Instruction(type, instruction);

        instructions.push_back(instr_obj);

    }
}

Instruction* InputHandler::get_next_instruction()
{
    if (instructions.size() == 0)
    {
        // Queue is empty
        return NULL;
    }

    Instruction *instr_obj = instructions.front();

    instructions.pop_front();

    return instr_obj;
}

void InputHandler::display()
{
    for (std::deque<Instruction*>::iterator it = instructions.begin(); it != instructions.end(); it++)
    {
        std::cout << InstructionTypeHelper::get_instruction_type_str((**it).type) << " " << (**it).page_id << "\n";
    }

    printf("Total instructions: %lu\n", instructions.size());
}
