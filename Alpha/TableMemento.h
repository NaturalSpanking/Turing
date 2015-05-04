#include <vector>
#include <fstream>
#include <iostream>

#include "rule.h"

#ifndef TableMementoH
#define TableMementoH
class TableMemento
{
	friend class Table;

private:
	int SaveToFile(std::vector<std::vector<rule> > table, char* pathToFile);
	std::vector<std::vector<rule> > LoadFromFile(char* pathToFile);
};
#endif
