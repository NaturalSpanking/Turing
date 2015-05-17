#ifndef TableH
#define TableH

#include<vector>
#include <System.Classes.hpp>
#include "rule.h"

class Table
{
	friend class Machine;
public:
	Table(unsigned Rows, unsigned Columns);

	int AddCol(unsigned Index);
	int AddRow(WideChar c);

	int DelCol(unsigned Index);
	int DelRow(WideChar c);

	int ColCount();
	int RowCount();

protected:
	std::vector<std::vector<rule> > table;
private:
	Table();
};
#endif
