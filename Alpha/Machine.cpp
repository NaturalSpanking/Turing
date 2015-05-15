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
	mach->tapMemSys = NULL;
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
//-2 - ������ ������� � ������������ ������ �������
//-1 - �� ������� �������� ������ �� �����(����� �� ������� �����)
// 0 - ��� ������� ��������
// 1 - ��� ������� �������� � ��������� ������ � 0-� ���������(��������� ���������)
// 2 - ��� ������� �������� � ������� �� ������ � ������ ��������
int Machine::Step()
{
	rule errRule;
	WideChar tempChar = GetTapeChar(GetTapePosition());
	if (tempChar == '\0') return -1;
	rule tempRule = GetTableRule(currentState, tempChar);
	if (tempRule == errRule)
	{
		currentState = 1;
		return -2;
	}

	SetTapeChar(GetTapePosition(), tempRule.symbol);
	ShiftTape(tempRule.shift);
	currentState = tempRule.new_state;
	if (currentState == 0)
	{
		currentState = 1;
		return 1;
	}
	if(tempRule.is_breakpoint == 0) return 0;
	else return 2;
}

/*int Machine::TraceProgram()
{
	while (true)
	{
		rule errRule;
		WideChar tempChar = GetTapeChar(GetTapePosition());
		if (tempChar == '\0') return -1;
		rule tempRule = GetTableRule(currentState, tempChar);
		if (tempRule == errRule)
		{
			currentState = 1;
			return -2;
		}

		if (tempRule.is_breakpoint == 1) return 0;

		SetTapeChar(GetTapePosition(), tempRule.symbol);
		ShiftTape(tempRule.shift);
		currentState = tempRule.new_state;
		if (currentState == 0)
		{
			currentState = 1;
			return 1;
		}
	}
}*/
//��������� ���������� ��������� � ������
int Machine::SetInitialState()
{
	currentState = 1;
}

//int Machine::SaveProgram(char* pathToFile);
//int Machine::LoadProgram(char* pathToFile);

//���������� ����� � ��������� ���������
//isUser == U - ���������� � ���������������� ���������
//isUser != U - ���������� � ��������� ���������
void Machine::SaveTape(WideChar isUser)
{
	if (isUser == 'U') tapMem = tap->CreateMemento();
	else tapMemSys = tap->CreateMemento();
}
//isUser == U - �������� �� ����������������� ����������
//isUser != U - �������� �� ���������� ����������
//������������ ��������:
//-1 - �� ������� ���������(����� �� ���� �� ���������)
// 0 - �������� �������
int Machine::LoadTape(WideChar isUser)
{
	if (isUser == 'U') {
		if (tapMem == NULL) return -1;
		tap->SetMemento(tapMem);
		return 0;
	}
	else
	{
		if (tapMemSys == NULL) return -1;
		tap->SetMemento(tapMemSys);
		return 0;
	}
}
//�������� ������ �� ������� ����� ��������
//������������ ��������:
// -1 - ����� ������ ���\������� �����
//0\1 - �������� �������\���������� ����� ��������
int Machine::IsBreakepoint(unsigned state, WideChar c)
{
	if (tab->table.size() == 0) return -1;
	if (state > tab->table[0].size()) return -1;

	for (unsigned i = 0; i < tab->table.size(); i++)
	{
		if (tab->table[i][0].symbol == c && tab->table[i][state].is_breakpoint == 1) return 1;
	}
	return 0;
}

//��������� �������� ������� 1-�� �������(������� ��������) �� ��� �������
WideChar Machine::GetAlphabet(int index){
	if (tab->table.size() == 0) return 0;
	if (index > tab->table.size()) return 0;
	return tab->table[index][0].symbol;
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

	if (tab->table.size() == 0) return -1;
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
	if ((int)tap->position + shift > tap->tape.size() && shift > 0) return -1;
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
