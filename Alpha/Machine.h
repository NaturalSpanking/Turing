#include "Tape.h"
#include "Table.h"

#ifndef MachineH
#define MachineH
class Machine
{
private:
	int currentState;
	Tape* tap;
	Table* tab;
	TapeMemento* tapMem;
	static Machine* mach;
	Machine();
public:
	static Machine* Create(unsigned tapLen = 100, unsigned tabRows = 4, unsigned tabCol = 5);

	int Step();
	int TraceProgram();

	int SaveProgram(char* pathToFile);
	int LoadProgram(char* pathToFile);
	void SaveTape();
	int LoadTape();

	rule GetTableRule(unsigned state, char c);
	int SetTableRule(unsigned state, char c, rule r);
	int GetCurrentState();

	int SetTapeChar(unsigned index, char c);
	int ShiftTape(int shift);
	char GetTapeChar(unsigned index);
	int GetTapePosition();
	~Machine();
};
#endif
