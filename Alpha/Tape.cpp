#pragma hdrstop

#include "Tape.h"
Tape::Tape(unsigned len)
{
	tape = std::vector<WideChar>(len, ' ');
	position = len / 2;
}
int Tape::GetLenght()
{
	return tape.size();
}
TapeMemento* Tape::CreateMemento()
{
	TapeMemento* newTapeMemento = new TapeMemento();
	newTapeMemento->SetState(tape);
	return newTapeMemento;
}
void Tape::SetMemento(TapeMemento* m)
{
	tape = m->GetState();
}
#pragma package(smart_init)
