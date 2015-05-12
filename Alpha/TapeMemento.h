#include <vector>
#include <System.Classes.hpp>

#ifndef TapeMementoH
#define TapeMementoH
class TapeMemento
{
	friend class Tape;
protected:
	TapeMemento();
	void SetState(std::vector<WideChar> t);
	std::vector<WideChar> GetState();
private:
	std::vector<WideChar> tape;
};
#endif