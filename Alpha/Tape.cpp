#pragma hdrstop

#include "Tape.h"
Tape::Tape(int length)
{
	tape.resize(length);
}

Tape::Tape(Tape &X)
{
	tape = X.tape;
}

#pragma package(smart_init)
