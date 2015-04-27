#pragma hdrstop

#include "Table.h"
Table::Table(unsigned Rows, unsigned Columns)
{
	rule defRule;
	char def = '0';
	table = std::vector<std::vector<rule> >(Rows, std::vector<rule>(Columns, defRule));
	for(unsigned i=0; i<table.size(); i++)
	{
		table[i][0].symbol = def;
		def++;
    }
}
int Table::AddCol()
{
	rule defRule;
	for(unsigned i=0; i<table.size(); i++)
	{
		table[i].push_back(defRule);
	}
	return 0;
}
int Table::AddCol(int index)
{
	rule defRule;
	for(unsigned i=0; i<table.size(); i++)
	{
		table[i].insert(&table[i][index], defRule);
	}
	return 0;
}
int Table::AddRow(char c)
{
	rule defRule;
	defRule.symbol = table.back()[0].symbol+1;
	table.push_back(std::vector<rule>(table[0].size(), defRule));
	return 0;
}
int Table::DelCol()
{
	for(unsigned i=0; i<table.size(); i++)
	{
		table[i].pop_back();
	}
}
int Table::DelCol(int index)
{
 	for(unsigned i=0; i<table.size(); i++)
	{
		table[i].erase(&table[i][index]);
	}
	return 0;
}
int Table::DelRow(char c)
{
	for(unsigned i=0; i<table.size(); i++)
	{
		if(table[i][0].symbol == c)
		{
			table.erase(&table[i]);
			return 0;
		}
	}
	return -1;
}
/*int Table::LoadMemento(char* pathToFile)
{

}
int Table::SaveMemento(char* pathToFile)
{

} */
#pragma package(smart_init)
