#pragma hdrstop

#include "TapeMemento.h"
TapeMemento::TapeMemento(){}
void TapeMemento::SetState(std::vector<WideChar> t)
{
	tape = t;
}

std::vector<WideChar> TapeMemento::GetState()
{
	return tape;
}
#pragma package(smart_init)