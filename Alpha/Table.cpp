#pragma hdrstop

#include "Table.h"

Table::Table() {}
//Инициализация таблицы
Table::Table(unsigned Rows, unsigned Columns)
{
	if(Columns < 1) return;
	rule defRule;
	WideChar def = '0';
	table = std::vector<std::vector<rule> >(Rows, std::vector<rule>(Columns, defRule));
	table[0][0].symbol = ' ';
	for(unsigned i=1; i<table.size(); i++)
	{
		table[i][0].symbol = def;
		def++;
	}
}
//Добавление столбца вместо столбца по индексу(со смещением его вперед)
//Возвращаемые значения:
//-1 - добавление за место несуществующего столбца\пустая таблицы
// 0 - успешно добавлен
int Table::AddCol(unsigned index)
{
	if (table[0].size() < index) return -1;
	rule defRule;
	for(unsigned i = 0; i < table.size(); i++)
	{
		table[i].insert(table[i].begin() + index, defRule);
	}
	return 0;
}
//Добавление строки в конец с символом "c"
//Возвращаемые значения:
//-1 - попытка добавить строку с уже существующим символом алфавита
// 0 - успешно добавлена
int Table::AddRow(WideChar c)
{
	if (c == ' ') return -1;
	for (unsigned i = 0; i < table.size(); i++)
	{
		if (table[i][0].symbol == c) return -1;
	}
	rule defRule;
	table.push_back(std::vector<rule>(table[0].size(), defRule));
	table.back()[0].symbol = c;
	return 0;
}
//Удаление столбца по индексу
//Возвращаемые значения:
//-1 - попытка удалить не существующий толбец
// 0 - успешно удалена
int Table::DelCol(unsigned index)
{
	if (index >= table[0].size() || index == 0 || table[0].size() == 2) return -1;
	for(unsigned i=0; i<table.size(); i++)
	{
		table[i].erase(table[i].begin() + index);
	}
	return 0;
}
//Удаление строки с символом "c"
//Возвращаемые значения:
//-1 - попытка удалить не существующую строку
// 0 - успешно удалена
int Table::DelRow(WideChar c)
{
	if (table.size() == 1 || c == ' ') return -1;
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
//Получение количества столбцов
int Table::ColCount(){
	return table[0].size();
}
//Получение количества строк
int Table::RowCount(){
	return table.size();
}

#pragma package(smart_init)
