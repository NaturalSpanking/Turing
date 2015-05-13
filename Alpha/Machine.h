#include "Tape.h"
#include "Table.h"
#include <System.Classes.hpp>

#ifndef MachineH
#define MachineH
class Machine
{
private:
	int currentState;
	TapeMemento* tapMem;
	static Machine* mach;
	Machine();
public:
	Tape* tap;
	Table* tab;

	static Machine* Create(unsigned tapLen = 101, unsigned tabRows = 4, unsigned tabCol = 5);

	int Step();
	int TraceProgram();

	int SaveProgram(char* pathToFile);
	int LoadProgram(char* pathToFile);
	void SaveTape();
	int LoadTape();

	rule GetTableRule(unsigned state, WideChar c);
	int SetTableRule(unsigned state, WideChar c, rule r);
	int GetCurrentState();

	WideChar GetAlphabet(int index);

	int SetTapeChar(unsigned index, WideChar c);
	int SetTapePosition(unsigned index);
	int ShiftTape(int shift);
	WideChar GetTapeChar(unsigned index);
	int GetTapePosition();
	~Machine();
};
#endif
