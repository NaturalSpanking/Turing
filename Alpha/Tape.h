#include <vector>
#include "TapeMemento.h"
#include <System.Classes.hpp>

#ifndef TapeH
#define TapeH
class Tape
{
	friend class Machine;
public:
	Tape(unsigned length);
	int GetLenght();

	TapeMemento* CreateMemento();
	void SetMemento(TapeMemento* m);
protected:
	std::vector<WideChar> tape;
private:
	int position;
	Tape();
};
#endif
