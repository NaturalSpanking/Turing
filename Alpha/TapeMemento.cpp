#pragma hdrstop

#include "TapeMemento.h"
TapeMemento::TapeMemento()
{
	tap = NULL;
}

TapeMemento::~TapeMemento()
{
	if(tap != NULL) delete(tap);
}

void TapeMemento::SetState(Tape *t)
{
	if(tap != NULL) delete(tap);
	tap = new Tape(t->GetLenght());
	tap->tape = t->tape;
	tap->position = t->position;
}

Tape* TapeMemento::GetState()
{
	return tap;
}
#pragma package(smart_init)
