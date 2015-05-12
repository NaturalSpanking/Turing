#include "Tape.h"
#include "TapeMemento.h"
#include "Table.h"
#include "TableMemento.h"

#ifndef MachineH
#define MachineH
class Machine
{
	protected:
		Machine();
	private:
		int currentState;
		Tape tap;
		//Tapememento* tapMem;
		Table tab;
		static Machine* mach;
	public:
		static Machine* Create();
		int Step();
		int TraceProgram();
		int SaveTableToFile(char* pathToFile);
		int LoadTableFromFile(char* pathToFile);
		int SaveTapeToFile(char* pathToFile);
		int LoadTapeFromFile(char* pathToFile);
		rule GetTableRule(int state, char c);
		int SetTableRule(int state, char c, rule r);
		int SetTapeChar(int index, char c);
		int SetTapePosition(int position);
		int GetTapePosition();
		int Wipe();
};
#endif
