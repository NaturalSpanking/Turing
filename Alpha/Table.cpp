#pragma hdrstop

#include "Table.h"

Table::Table() {}
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
int Table::AddCol(unsigned index)
{
	if (table.size() == 0) return -1;
	if (table[0].size() < index) return -1;
	rule defRule;
	for(unsigned i = 0; i < table.size(); i++)
	{
		table[i].insert(table[i].begin() + index, defRule);
	}
	return 0;
}
int Table::AddRow(WideChar c)
{
	if (table.size() == 0) return -1;
	for (unsigned i = 0; i < table.size(); i++)
	{
		if (table[i][0].symbol == c) return -1;
	}
	rule defRule;
	table.push_back(std::vector<rule>(table[0].size(), defRule));
	table.back()[0].symbol = c;
	return 0;
}
int Table::DelCol()
{
	if (table.size() == 0) return -1;
	if (table[0].size() == 1) return -1;
	for(unsigned i=0; i<table.size(); i++)
	{
		table[i].pop_back();
	}
	return 0;
}
int Table::DelCol(unsigned index)
{
	if (table.size() == 0) return -1;
	if (table[0].size() <= index || index == 0) return -1;
 	for(unsigned i=0; i<table.size(); i++)
	{
		table[i].erase(table[i].begin() + index);
	}
	return 0;
}
int Table::DelRow(WideChar c)
{
	if (table.size() == 1) return -1;
	for(unsigned i=0; i<table.size(); i++)
	{
		if(table[i][0].symbol == c)
		{
			table.erase(table.begin()+i);
			return 0;
		}
	}
	return -1;
}
#pragma package(smart_init)
