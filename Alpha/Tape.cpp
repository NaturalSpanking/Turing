#pragma hdrstop

#include "Tape.h"
Tape::Tape(int len)
{
	tape = std::vector<char>(len, ' ');
}
Tape::Tape(Tape &X)
{
	tape = std::vector<char>(X.tape);
}
int Tape::GetLenght()
{
	return tape.size();
}
TapeMemento* Tape::CreateMemento()
{
	TapeMemento* newTapeMemento = new TapeMemento;
	newTapeMemento->SetState(tape);
	return newTapeMemento;
}
int Tape::SetMemento(TapeMemento* m)
{
	tape = m->GetState();
	return 0;
}
#pragma package(smart_init)
