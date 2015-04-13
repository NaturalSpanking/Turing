#include <vector>

#ifndef TapeMementoH
#define TapeMementoH
class TapeMemento
{
	friend class Tape;
private:
	std::vector<char> tape;

	TapeMemento();
	void SetState(std::vector<char> t);
	std::vector<char> GetState();
};
#endif
