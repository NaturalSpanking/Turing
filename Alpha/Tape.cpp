#pragma hdrstop

#include "Tape.h"
Tape::Tape(unsigned lenght)
{
	tape = std::vector<WideChar>(lenght, ' ');
	position = lenght / 2;
}
int Tape::GetLenght()
{
	return tape.size();
}
void Tape::Resize(unsigned lenght)
{
	tape.resize(lenght, ' ');
}
TapeMemento* Tape::CreateMemento()
{
	TapeMemento* newTapeMemento = new TapeMemento();
	newTapeMemento->SetState(this);
	return newTapeMemento;
}
void Tape::SetMemento(TapeMemento* m)
{
	Tape *temp = m->GetState();
	tape = temp->tape;
	position = temp->position;
}
#pragma package(smart_init)
