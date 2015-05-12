#include<vector>
#include "rule.h"

#ifndef TableH
#define TableH
class Table
{
	friend class Machine;
public:
	Table(unsigned Rows, unsigned Columns);

	int AddCol();
	int AddCol(unsigned Index);
	int AddRow(char c);

	int DelCol();
	int DelCol(unsigned Index);
	int DelRow(char c);
protected:
	std::vector<std::vector<rule> > table;
private:
	Table();
};
#endif
