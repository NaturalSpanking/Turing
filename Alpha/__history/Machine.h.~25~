#ifndef MachineH
#define MachineH

#include "Tape.h"
#include "Table.h"
#include <fstream>
#include <streambuf>

#define BUFF_SIZE 1024

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
//	int TraceProgram();
	void SetInitialState();

	int SaveProgram(UnicodeString pathToFile, UnicodeString Problem, UnicodeString Comment);
	int LoadProgram(UnicodeString pathToFile, UnicodeString &Problem, UnicodeString &Comment);
	void SaveTape();
	int LoadTape();
	int CheckTable();

	rule GetTableRule(unsigned state, WideChar c);
	int SetTableRule(unsigned state, WideChar c, rule r);
	int GetCurrentState();
	int IsBreakepoint(unsigned state, WideChar c);
	bool InAlphabet(WideChar c);
	WideChar GetAlphabet(int index);

	int SetTapeChar(unsigned index, WideChar c);
	int SetTapePosition(unsigned index);
	int ShiftTape(int shift);
	WideChar GetTapeChar(unsigned index);
	int GetTapePosition();
	~Machine();
};
#endif
