#ifndef INSTRUCTION_TYPE_HPP
#define INSTRUCTION_TYPE_HPP

enum InstructionType
{
    READ,
    WRITE
};

class InstructionTypeHelper
{
public:
    static const char* get_instruction_type_str(InstructionType);
};


#endif // INSTRUCTION_HPP
