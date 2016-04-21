#include "instruction.hpp"

Instruction::Instruction(int type, int page_id)
{
    this->type = (type == 0) ? READ : WRITE;
    this->page_id = page_id;
}

Instruction::Instruction(InstructionType type, int page_id)
{
    this->type = type;
    this->page_id = page_id;
}

void Instruction::display()
{
    printf("==> inst: %d %d\n", type, page_id);
}
