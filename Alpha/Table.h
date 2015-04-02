#include<vector>

#include "rule.h"

#ifndef TableH
#define TableH
class Table
{
	friend class Machine;
public:
	Table();
	int AddCol();
	int AddCol(int Index);
	int AddRow(char c);
	int DelCol();
	int DelCol(int Index);
	int DelRow(char c);
	int LoadMemento(char* pathToFile);
	int SaveMemento(char* pathToFile);
private:
	std::vector<std::vector<rule> > table;
};
#endif
