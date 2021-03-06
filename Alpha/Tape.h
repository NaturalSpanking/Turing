#ifndef TapeH
#define TapeH

#include <vector>
#include "TapeMemento.h"
#include <System.Classes.hpp>


class Tape
{
	friend class Machine;
	friend class TapeMemento;
public:
	Tape(unsigned length);
	int GetLenght();
	void Resize(unsigned length);

	TapeMemento* CreateMemento();
	void SetMemento(TapeMemento* m);
protected:
	std::vector<WideChar> tape;
	int position;
private:
	Tape();
};
#endif
