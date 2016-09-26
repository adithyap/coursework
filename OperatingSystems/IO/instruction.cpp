#include "instruction.hpp"

Instruction::Instruction(int time_issued, int track)
{
    this->time_issued = time_issued;
    this->track = track;
}

void Instruction::display()
{
    printf("==> inst: %d %d\n", time_issued, track);
}
