#ifndef TapeMementoH
#define TapeMementoH

#include "Tape.h"

class TapeMemento
{
	friend class Tape;
public:
	~TapeMemento();
protected:
	TapeMemento();
	void SetState(Tape* t);
	Tape* GetState();
	Tape* tap;
};
#endif
