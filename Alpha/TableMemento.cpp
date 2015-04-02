#pragma hdrstop

#include "TableMemento.h"
int TableMemento::SaveToFile(std::vector<std::vector<rule> > table, char* pathToFile)
{
	ofstream OutputFile;
	OutputFile.open(pathToFile, ios::out);
	if(!OutputFile.is_open()) return 1;
	for(unsigned i=0; i<table.size(); i++)
	{
		for(unsigned ii=0; ii<table[0].size(); ii++)
		{
			OutputFile << table[i][ii].symbol;
			//OutputFile << itoa(table[i][ii].shift
		}
	}
	OutputFile.close();
	return 0;
}

/*std::vector<std::vector<rule> > TableMemento::LoadFromFile(char* pathToFile)
{
	ifstream InputFile;
	InputFile.open(pathToFile, ios::in);
	if(!InputFile.is_open()) return NULL;
	InputFile.close();
	return 0;
}                        */
#pragma package(smart_init)
