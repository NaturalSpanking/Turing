#pragma hdrstop

#include "Machine.h"

Machine::Machine() {}

Machine* Machine::mach = NULL;

//�������� ������ � ����������� ������� � ����� ��������� � ����������
Machine* Machine::Create(unsigned tapLen, unsigned tabRows, unsigned tabCol)
{
	if (mach != NULL) return mach;
	mach = new Machine();
	mach->tab = new Table(tabRows, tabCol);
	mach->tap = new Tape(tapLen);
	mach->currentState = 1;
	mach->tapMem = NULL;
	return mach;
}
//����������
Machine::~Machine()
{
	if (mach == NULL) return;
	delete mach->tab;
	delete mach->tap;
	mach = NULL;
}
//��� ������
//������������ ��������:
//-4 - ��������� � ������� ����� ������� �� ����������
//-3 - ������ � ����� ��� ������ � ������� �� ���������� � ��������
//-2 - ������ ������� � ������������ ������ �������
//-1 - �� ������� �������� ������ �� �����(����� �� ������� �����)
// 0 - ��� ������� ��������
// 1 - ��� ������� �������� � ��������� ������ � 0-� ���������(��������� ���������)
// 2 - ��� ������� ��������, ��������� ������ - ����� ��������
int Machine::Step()
{
	//��������� ������ � �������� �� ������
	rule errRule;
	WideChar tempChar = GetTapeChar(GetTapePosition());
	if (tempChar == '\0') return -1;
	if (!InAlphabet(tempChar)) return -3;
	rule tempRule = GetTableRule(currentState, tempChar);
	if (tempRule == errRule)
	{
		currentState = 1;
		return -2;
	}
	if (!InAlphabet(tempRule.symbol)) return -3;
	if (tempRule.new_state < 0 || tempRule.new_state > (int)tab->table[0].size()) return -4;

	//��������� ��������� � ������
	SetTapeChar(GetTapePosition(), tempRule.symbol);
	ShiftTape(tempRule.shift);
	currentState = tempRule.new_state;

	//��������� ����� ��������
	tempChar = GetTapeChar(GetTapePosition());
	if(IsBreakepoint(currentState, tempChar) == 1) return 2;

	if (currentState == 0)
	{
		currentState = 1;
		return 1;
	}
	else return 0;
}

//��������� ���������� ��������� � ������
void Machine::SetInitialState()
{
	currentState = 1;
}
//���������� ���������(����� + �������) � ����
//������������ ��������:
//-1 - �� ������� ������� ���� ��� ������
// 0 - ���������� �������
int Machine::SaveProgram(UnicodeString pathToFile, UnicodeString Problem, UnicodeString Comment)
{
	std::ofstream file;
	unsigned Rows = tab->table.size();
	unsigned Columns = tab->table[0].size();
	AnsiString A;
	A=pathToFile;
	file.open(A.c_str());
	if (!file.is_open()) return -1;

	file << tap->tape.size() << " " << Rows << " " << Columns << " " <<Problem.Length() << " " << Comment.Length() << "\n";

	//������ �����
	for (unsigned i = 0; i < tap->tape.size(); i++)
	{
		file << tap->tape[i];
		file << " ";
	}
	file << "\n";

	//������ �������
	for (unsigned i = 0; i < Rows; i++)
	{
		for (unsigned ii = 0; ii < Columns; ii++)
		{
			if (ii != 0)
			{
				if (tab->table[i][ii].symbol != ' ') file << tab->table[i][ii].symbol;
				else file << 32;
				if (tab->table[i][ii].shift != -2)
				{
					if (tab->table[i][ii].shift == 1) file << ">";
					if (tab->table[i][ii].shift == -1) file << "<";
					if (tab->table[i][ii].shift == 0) file << ".";
				}
				else file << " ";
				if (tab->table[i][ii].new_state != -1) file << tab->table[i][ii].new_state;
				else file << " ";
			}
			else
			{
				file << tab->table[i][ii].symbol;
			}
			if (ii+1 < Columns) file << " ";
		}
		file << "\n";
	}
	A=Problem;
	file << A.c_str();
	A=Comment;
	file << A.c_str();
	file.close();
	return 0;
}
//�������� ���������(����� + �������) � ����
//������������ ��������:
//-3 - ������� �� ����� ������������
//-2 - BadFile
//-1 - �� ������� ������� ���� ��� ������
// 0 - ���������� �������
int Machine::LoadProgram(UnicodeString pathToFile, UnicodeString &Problem, UnicodeString &Comment){
	std::ifstream file;
	AnsiString A;
	A=pathToFile;
	file.open(A.c_str());
	if (!file.is_open()) return -1;
	//1 - tapLen
	//2 - Rows
	//3 - Columns
	unsigned params[5] = {0};
	char buff[BUFF_SIZE];

	//��������� ���������� ����� � �������
	for (int i = 0; i < 5; i++){
		if (!file.good()) return -2;
		file >> buff;
		params[i] = atoi(buff);
		if (params[i] <= 0) return -2;
	}

	//��������� ���������� � ������� ������
	tap->tape.resize(params[0], ' ');

	rule defRule;
	tab->table.resize(params[1]);
	for (unsigned i = 0; i < params[1]; i++){
		tab->table[i].resize(params[2], defRule);
	}

	//��������� �����
	file.ignore();
	if (!file.good()) return -2;

	for (unsigned i = 0; i < params[0]; i++)
	{
		file >> buff;
		file.ignore();
		tap->tape[i] = atoi(buff);
	}

	//��������� �������
	int intTemp;
	for (unsigned i = 0; i < params[1]; i++)
	{
		if (!file.good()) return -2;
		for (unsigned ii = 0; ii < params[2]; ii++)
		{
			rule tempRule;
			if (!file.good()) return -2;
			if (ii != 0)
			{
				int counter = 0;
				do
				{
					buff[counter+1] = '\0';
					file.read(buff+counter, 1);
					counter++;
				}while(file.peek() != ' ' && file.peek() != '>' && file.peek() != '<' && file.peek() != '.');
				tempRule.symbol = atoi(buff);

				buff[0] = '\0';
				buff[1] = '\0';
				file.read(buff, 1);
				if (buff[0] != '>' && buff[0] != '<' && buff[0] != '.' && buff[0] != ' ') return -2;
				if (buff[0] == '>') tempRule.shift = 1;
				if (buff[0] == '<') tempRule.shift = -1;
				if (buff[0] == '.') tempRule.shift = 0;
				if (buff[0] == ' ') tempRule.shift = -2;

				if (file.peek() == ' ')
				{
					file.ignore();
					intTemp = -1;
				}
				else
				{
					file >> buff;
					intTemp = atoi(buff);
					if (intTemp < 0) return -2;
				}
				tempRule.new_state = intTemp;

				tempRule.is_breakpoint = 0;

				if (ii + 1 == params[2] && file.peek() != '\n') return -2;
				else file.ignore();
			}
			else
			{
				buff[0] = '\0';
				buff[1] = '\0';
				file >> buff;
				file.ignore();
				tempRule.symbol = atoi(buff);
			}
			tab->table[i][ii] = tempRule;
		}
	}
	if (CheckTable() == -1){
		for (unsigned i = 0; i < tab->table.size(); i++)
		{
			for (unsigned ii = 1; ii < tab->table[0].size(); ii++)
			{
				tab->table[i][ii] = defRule;
			}
		}
		return -3;
	}

	char *p = new char[params[3]];
	file.read(p,params[3]-1);
	Problem = p;
	char* c = new char[params[4]];
	file.read(c,params[4]);
	c[params[4]] = '\0';
	Comment = c;
	delete [] p;
	delete [] c;
	file.close();
	return 0;
}
//���������� ����� � ��������� ���������
void Machine::SaveTape()
{
	tapMem = tap->CreateMemento();
}
//������������ ��������:
//-1 - �� ������� ���������(����� �� ���� �� ���������)
// 0 - �������� �������
int Machine::LoadTape()
{
		if (tapMem == NULL) return -1;
		tap->SetMemento(tapMem);
		return 0;
}
//�������� ������������ �������
//������������ ��������:
//-1 - �������� �� ��������
// 0 - �������� �������
int Machine::CheckTable()
{
	for (unsigned i = 0; i < tab->table.size(); i++)
	{
		for (unsigned ii = 1; ii < tab->table[0].size(); ii++)
		{
			if (!InAlphabet(tab->table[i][ii].symbol)) return -1;
		}
	}
	return 0;
}
//��������� ������� �� ������
//������������ ��������:
//errRule - ����� ������ �� ����������
rule Machine::GetTableRule(unsigned state, WideChar c)
{
	rule errRule;
	if (tab->table.size() == 0) return errRule;
	if (state > tab->table[0].size()) return errRule;

	for (unsigned i = 0; i < tab->table.size(); i++)
	{
		if (tab->table[i][0].symbol == c) return tab->table[i][state];
	}

	return errRule;
}
//��������� ������� � ������ �������
//������������ ��������:
//-1 - ����� ������ ���\������� �����
// 0 - ������� �����������
int Machine::SetTableRule(unsigned state, WideChar c, rule r)
{
	if (state > tab->table[0].size()) return -1;

	for (unsigned i = 0; i < tab->table.size(); i++)
	{
		if (tab->table[i][0].symbol == c){
			tab->table[i][state] = r;
			return 0;
		}
	}

	return -1;
}
//��������� �������� ��������� ������
int Machine::GetCurrentState()
{
	return currentState;
}
//�������� ������ �� ������� ����� ��������
//������������ ��������:
// -1 - ����� ������ ���\������� �����
//0\1 - �������� �������\���������� ����� ��������
int Machine::IsBreakepoint(unsigned state, WideChar c)
{
	if (state > tab->table[0].size()) return -1;

	for (unsigned i = 0; i < tab->table.size(); i++)
	{
		if (tab->table[i][0].symbol == c && tab->table[i][state].is_breakpoint == 1) return 1;
	}
	return 0;
}
//�������� ������� ������� � ��������
//������������ ��������:
//0 - ������ ������� ���
//1 - ����� ������ ����
bool Machine::InAlphabet(WideChar c)
{
	for (unsigned i = 0; i < tab->table.size(); i++)
	{
		if (tab->table[i][0].symbol == c) return 1;
	}
	return 0;
}
//��������� �������� ������� 1-�� �������(������� ��������) �� ��� �������
WideChar Machine::GetAlphabet(int index){
	if (tab->table.size() == 0) return 0;
	if (index >(int)tab->table.size()) return 0;
	return tab->table[index][0].symbol;
}
//��������� �������� ������ � ����� �� �������
//������������ ��������:
//-1 - ����� �� ������� �����
// 0 - ������� �����������
int Machine::SetTapeChar(unsigned index, WideChar c)
{
	if (index >= tap->tape.size()) return -1;
	tap->tape[index] = c;
	return 0;
}
//��������� ��������� ������� ������� � �����
//������������ ��������:
//-1 - ����� �� ������� �����
// 0 - ������� �����������
int Machine::SetTapePosition(unsigned position)
{
	if (position >= tap->tape.size()) return -1;
	tap->position = position;
	return 0;
}
//����� ��������� ������� ������� � �����
//������������ ��������:
//-1 - ����� �� ������� �����
// 0 - ������� �����������
int Machine::ShiftTape(int shift)
{
	if ((int)tap->position + shift > (int)tap->tape.size() && shift > 0) return -1;
	if (shift == 0) return 0;
	if ((int)tap->position + shift < 0 && shift < 0) return -1;
	tap->position += shift;
	return 0;
}
//��������� �������� ������ ����� �� �������
//������������ ��������:
//'\0' - ����� �� ������� �����
WideChar Machine::GetTapeChar(unsigned index)
{
	if (index >= tap->tape.size()) return '\0';
	return tap->tape[index];
}
//��������� �������� ��������� ������� ������� � �����
int Machine::GetTapePosition()
{
	return tap->position;
}

#pragma package(smart_init)
