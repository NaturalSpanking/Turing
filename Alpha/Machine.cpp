#pragma hdrstop

#include "Machine.h"

Machine* Machine::Create()
{
	if(mach != NULL) return mach;
	mach = new Machine();
	return mach;
}
/*int Machine::Step();
int Machine::TraceProgram();
int Machine::SaveTableToFile(char* pathToFile);
int Machine::LoadTableFromFile(char* pathToFile);
int Machine::SaveTapeToFile(char* pathToFile);
int Machine::LoadTapeFromFile(char* pathToFile);
rule Machine::GetTableRule(int state, char c);
int Machine::SetTableRule(int state, char c, rule r);
int Machine::SetTapeChar(int index, char c);
int Machine::SetTapePosition(int position);
int Machine::GetTapePosition();
int Machine::Wipe();*/

#pragma package(smart_init)
