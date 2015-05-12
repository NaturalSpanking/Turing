#pragma hdrstop

#include "TapeMemento.h"
TapeMemento::TapeMemento(){}
void TapeMemento::SetState(std::vector<char> t)
{
	tape = t;
}

std::vector<char> TapeMemento::GetState()
{
	return tape;
}
#pragma package(smart_init)
