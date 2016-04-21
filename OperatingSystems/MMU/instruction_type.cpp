#include "instruction_type.hpp"

const char* InstructionTypeHelper::get_instruction_type_str(InstructionType type)
{
    const char* itype = (type == READ) ? "READ" : "WRITE";

    return itype;
}
