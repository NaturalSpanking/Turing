// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma resource "asd.res"
TMainForm *MainForm;

// ---------------------------------------------------------------------------
void __fastcall TMainForm::UpdTape() {

//	TapeOffset=machine->GetTapePosition()-StrToInt(OptForm->Edit1->Text);
	for (int i = 0; i < TapeGrid->ColCount; i++) {
		TapeGrid->Cells[i][1] =
			machine->GetTapeChar(TapeOffset + (i - TapeGrid->ColCount / 2) +
			StrToInt(OptForm->Edit1->Text));
	}
	TapeGrid->Refresh();
	TableGrid->Refresh();
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::UpdTable() {
	TableGrid->RowCount = machine->tab->RowCount() + 1;
	TableGrid->ColCount = machine->tab->ColCount();
	for (int i = 0; i < machine->tab->RowCount(); i++) {
		TableGrid->Cells[0][i + 1] = machine->GetAlphabet(i);
	}
	for (int i = 1; i < machine->tab->ColCount(); i++) {
		for (int j = 1; j <= machine->tab->RowCount(); j++) {
			TableGrid->Cells[i][j] =
				RuleToStr(machine->GetTableRule(i, TableGrid->Cells[0][j][1]));
		}
	}

}

// ---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner) : TForm(Owner) {
	TapeOffset = 0;
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::N10Click(TObject *Sender) {
	AboutForm->ShowModal();
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::N7Click(TObject *Sender) {
	OptForm->ShowModal();
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::N9Click(TObject *Sender) {
	ShowMessage("����� �������");
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::FormResize(TObject *Sender) {
	LoadTapeBtn->Left = MainForm->Width - 51;
	SaveTapeBtn->Left = MainForm->Width - 84;
	TapeGrid->ColCount = (MainForm->Width - 50) / 25 - 2;
	TapeGrid->Refresh();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::TapeGridDrawCell(TObject *Sender, int ACol, int ARow,
	TRect &Rect, TGridDrawState State) {
	TRect r;
	r = TapeGrid->CellRect(ACol, 0);
	if ((ACol == TapeGrid->ColCount / 2) && (ARow == 0)) {
		TapeGrid->Canvas->Brush->Style = bsSolid;
		TapeGrid->Canvas->Brush->Color = clYellow;
		TapeGrid->Canvas->Pen->Color = clBlack;
		TapeGrid->Canvas->MoveTo(r.left + 3, r.top + 3);
		TapeGrid->Canvas->LineTo(r.left + 3 + 17, r.top + 3);
		TapeGrid->Canvas->LineTo(r.left + 3 + 8, r.top + 3 + 17);
		TapeGrid->Canvas->LineTo(r.left + 3, r.top + 3);
		TapeGrid->Canvas->FloodFill(r.left + 8, r.top + 5, clBlack, fsBorder);
	}
	if (ACol != TapeGrid->ColCount / 2) {
		TapeGrid->Canvas->Brush->Style = bsClear;
		TapeGrid->Canvas->Font->Size = 8;
		TapeGrid->Canvas->Font->Color = clBlack;
		if ((TapeOffset - TapeGrid->ColCount / 2 + ACol >=
			-StrToInt(OptForm->Edit1->Text)) && (TapeOffset -
			TapeGrid->ColCount / 2 + ACol <= StrToInt(OptForm->Edit1->Text))) {
			TapeGrid->Canvas->TextOutW(r.left + 3, r.top + 5,
				IntToStr(TapeOffset - TapeGrid->ColCount / 2 + ACol));
		}
		else {
			TapeGrid->Canvas->TextOutW(r.left + 3, r.top + 5, "ZZZ");
		}
	}
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::TapeRightBtnClick(TObject *Sender) {
	TapeOffset++;
	UpdTape();
	machine->ShiftTape(1);
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::TapeLeftBtnClick(TObject *Sender) {
	TapeOffset--;
	UpdTape();
	machine->ShiftTape(-1);
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::TapeGridMouseWheelDown(TObject *Sender,
	TShiftState Shift, TPoint &MousePos, bool &Handled) {
	TapeRightBtnClick(MainForm);
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::TapeGridMouseWheelUp(TObject *Sender,
	TShiftState Shift, TPoint &MousePos, bool &Handled) {
	TapeLeftBtnClick(MainForm);
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::N12Click(TObject *Sender) {
	ShowMessage("�����");
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::TapeGridKeyPress(TObject *Sender,
	System::WideChar &Key)

{
	if (Key == 8) {
		Key = ' ';
	}

	if (machine->SetTapeChar(TapeOffset + (TapeGrid->Col -
		TapeGrid->ColCount / 2) + StrToInt(OptForm->Edit1->Text), Key) != 0) {
		StatusBarHint("������: ����� �� ������� �����.");
		Key = 0;
		return;

	}
	TapeGrid->Cells[TapeGrid->Col][1] = Key;
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::AddRowBtnClick(TObject *Sender) {
	// AddRowBtn->Glyph->LoadFromResourceName((int)HInstance, "LeftGreenArrow");
	UnicodeString C;
	C = InputBox("�������� ������", "������� ������", "");
	if (C == "") {
		return;
	}
	machine->tab->AddRow(C[1]);
	UpdTable();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::N6Click(TObject *Sender) {
	MainForm->Close();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::TableGridDrawCell(TObject *Sender, int ACol,
	int ARow, TRect &Rect, TGridDrawState State) {
	if ((ACol == 0) || (ARow == 0)) {
		return;
	}
	TableGrid->Cells[ACol][0] = "Q" + IntToStr(ACol);

	if (TableGrid->Cells[ACol][ARow].Length() < 3) {
		return;
	}
	TRect r;
	r = TableGrid->CellRect(ACol, ARow);

	switch (TableGrid->Cells[ACol][ARow][2]) {
	case '<':
		GreenArrow->LoadFromResourceName((int)HInstance, "LeftGreenArrow");
		break;
	case '>':
		GreenArrow->LoadFromResourceName((int)HInstance, "RightGreenArrow");
		break;
	case '.':
		GreenArrow->LoadFromResourceName((int)HInstance, "Stopp");
		break;
	}
	GreenArrow->Transparent = true;
	GreenArrow->TransparentMode = tmAuto;

	if (TableGrid->Cells[ACol][ARow].Length() * 16.25 >
		TableGrid->ColWidths[ACol]) {
		TableGrid->ColWidths[ACol] +=
			(TableGrid->Cells[ACol][ARow].Length() - 4);
	}

	GridCell->Width = r.Width();
	GridCell->Height = r.Height();
	GridCell->Canvas->Brush->Color = clWhite;
	GridCell->Canvas->Brush->Style = bsSolid;
	GridCell->Canvas->FillRect(TRect(0, 0, r.Width(), r.Height()));
	if (ACol == machine->GetCurrentState()&&(TableGrid->Cells[0][ARow].SubString(1,1)==TapeGrid->Cells[TapeGrid->ColCount / 2][1])) {
		GridCell->Canvas->Brush->Color = OptForm->Panel2->Color;
		GridCell->Canvas->FillRect(TRect(0, 0, r.Width(), r.Height()));
	}
	if (ARow == 1) {
		// GridCell->Canvas->Brush->Color = RGB(159, 182, 205);
		GridCell->Canvas->Pen->Color = OptForm->Panel1->Color;
		GridCell->Canvas->Rectangle(0, 0, r.Width(), r.Height());

	}

	GridCell->Canvas->Brush->Style = bsClear;
	GridCell->Canvas->Font->Size = 10;
	GridCell->Canvas->TextOutW(5, 4, TableGrid->Cells[ACol][ARow][1]);
	GridCell->Canvas->TextOutW(40, 4,
		"Q" + TableGrid->Cells[ACol][ARow].SubString(3,
		TableGrid->Cells[ACol][ARow].Length()));
	GridCell->Canvas->Draw(20, 4, GreenArrow);
	TableGrid->Canvas->Draw(r.left, r.top, GridCell);
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::TableGridKeyPress(TObject *Sender,
	System::WideChar &Key) {
	if (Key == 13) {
		SetRule();
	}
	TGridCracker* C;
	static unsigned int i;
	// ShowMessage(IntToStr(C->GetCaretPosition(TableGrid)));
	if (TableGrid->Cells[TableGrid->Col][TableGrid->Row].Length() > 0) {
		if ((C->GetCaretPosition(TableGrid) == 0) &&
			((TableGrid->Cells[TableGrid->Col][TableGrid->Row][1] != '.') &&
			(TableGrid->Cells[TableGrid->Col][TableGrid->Row][1] != '>') &&
			(TableGrid->Cells[TableGrid->Col][TableGrid->Row][1] != '<'))) {
			Key = 0;
			i++;
		}
	}
	if ((C->GetCaretPosition(TableGrid) == 1) && (Key != 8) && (Key != 13) &&
		(((Key != '>') && (Key != '<') && (Key != '.')) ||
		((TableGrid->Cells[TableGrid->Col][TableGrid->Row].Pos('>') != 0) ||
		(TableGrid->Cells[TableGrid->Col][TableGrid->Row].Pos('<') != 0) ||
		(TableGrid->Cells[TableGrid->Col][TableGrid->Row].Pos('.') != 0)))) {
		Key = 0;
		i++;
	}
	if ((C->GetCaretPosition(TableGrid) >= 2) && (((Key < '0') || (Key > '9'))
		&& (Key != 8) && (Key != 13))) {
		Key = 0;
		i++;
	}
	if (i == 5) {
		StatusBarHint("������������ ����. ������������ � ������ �������.");

	}
	if (i > 10) {
		ShowMessage("�������� ������� �� �����");
		i = 0;
	}
}
// ---------------------------------------------------------------------------

int __fastcall TGridCracker::GetCaretPosition(TStringGrid *Grid) {
	TGridCracker* s = reinterpret_cast<TGridCracker*>(Grid);
	if (s->InplaceEditor == NULL) {
		return -1;
	}
	return s->InplaceEditor->SelStart;
}

void __fastcall TMainForm::FormCreate(TObject *Sender) {
	GreenArrow = new Graphics::TBitmap();
	GridCell = new Graphics::TBitmap();
	if (ParamCount() > 0) {
		ShowMessage("��������� ���� " + ParamStr(1));
	}
	machine = machine->Create();
	// TapeOffset=50;
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::FormDestroy(TObject *Sender) {
	delete(GreenArrow);
	delete(GridCell);
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::N4Click(TObject *Sender) {
	SaveDialog->FilterIndex = 1;
	if (SaveDialog->Execute(MainForm->Handle)) {
		ShowMessage("������� ��� �� �����������!");
	}
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::N5Click(TObject *Sender) {
	SaveDialog->FilterIndex = 2;
	if (SaveDialog->Execute(MainForm->Handle)) {
		ShowMessage("������� ��� �� �����������!");
	}
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::N3Click(TObject *Sender) {
	if (OpenDialog->Execute(MainForm->Handle)) {
		ShowMessage("������� ��� �� �����������!");
	}
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::TapeGridFixedCellClick(TObject *Sender, int ACol,
	int ARow)

{
	if ((ACol == TapeGrid->ColCount / 2) && (ARow == 0)) {
		TapeOffset = 0;
		UpdTape();
	}
	else {
		// ShowMessage(IntToStr(TapeOffset + ACol - TapeGrid->ColCount /2));
		TapeOffset += ACol - TapeGrid->ColCount / 2;
		UpdTape();

	}
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::TapeGridExit(TObject *Sender) {
	TapeGrid->Col = TapeGrid->ColCount / 2;
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::TapeGridKeyDown(TObject *Sender, WORD &Key,
	TShiftState Shift) {
	// ShowMessage(IntToStr(Key));
	if ((TapeGrid->Col == 0) || (TapeGrid->Col == TapeGrid->ColCount - 1)) {
		if (Key == VK_LEFT) {
			TapeLeftBtnClick(MainForm);
		}
		if (Key == VK_RIGHT) {
			TapeRightBtnClick(MainForm);
		}
	}
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::StatusTimerTimer(TObject *Sender) {
	StatusBar1->SimpleText = "";
	StatusTimer->Enabled = false;
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::StatusBarHint(UnicodeString Text) {
	StatusBar1->SimpleText = Text;
	StatusTimer->Enabled = true;
}

void __fastcall TMainForm::SaveTapeBtnClick(TObject *Sender) {
	machine->SaveTape();
	StatusBarHint("����� ���������.");
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::LoadTapeBtnClick(TObject *Sender) {
	if (machine->LoadTape() == 0) {
		StatusBarHint("����� �������������.");
		UpdTape();
	}
	else {
		StatusBarHint("������: ����� �� ���� ���������.");
	}
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::AddColBtnClick(TObject *Sender) {
	machine->tab->AddCol(TableGrid->Col);
	UpdTable();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::DelColBtnClick(TObject *Sender) {
	if (machine->tab->DelCol(TableGrid->Col) != 0) {
		StatusBarHint("������ ������� ��������� �������.");
	}
	UpdTable();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::DelRowBtnClick(TObject *Sender) {
	// ShowMessage(TableGrid->Cells[TableGrid->Row][0]);
	if (machine->tab->DelRow(TableGrid->Cells[0][TableGrid->Row][1]) != 0) {
		StatusBarHint("������ ������� ��������� ������.");
	}
	UpdTable();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::TableGridSelectCell(TObject *Sender, int ACol,
	int ARow, bool &CanSelect) {
	SetRule();
}

int __fastcall TMainForm::SetRule() {
	if (TableGrid->Cells[TableGrid->Col][TableGrid->Row].Length() > 2) {
		// ShowMessage(StrToInt(TableGrid->Col));
		if (machine->SetTableRule(TableGrid->Col,
			TableGrid->Cells[0][TableGrid->Row][1],
			StrToRule(TableGrid->Cells[TableGrid->Col][TableGrid->Row])) != 0) {
			StatusBarHint("������ ��� ���������� �������.");
		}
		UpdTable();
	}
}

// ---------------------------------------------------------------------------
rule StrToRule(UnicodeString Str) {
	rule r;
	r.symbol = Str[1];
	if (Str[2] == '<') {
		r.shift = -1;
	}
	if (Str[2] == '>') {
		r.shift = 1;
	}
	if (Str[2] == '.') {
		r.shift = 0;
	}
	r.new_state = StrToInt(Str.SubString(3, Str.Length()));
	// ShowMessage(IntToStr(r.new_state));
	return r;
}

UnicodeString RuleToStr(rule Rule) {
	UnicodeString S = "";
	S += Rule.symbol;
	if (Rule.shift == -1) {
		S += '<';
	}
	if (Rule.shift == 1) {
		S += '>';
	}
	if (Rule.shift == 0) {
		S += '.';
	}
	S += IntToStr(Rule.new_state);
	if (Rule.shift == -2) {
		S = "";
	}
	return S;
}


void __fastcall TMainForm::StepBtnClick(TObject *Sender)
{
machine->SetTapePosition(TapeOffset+StrToInt(OptForm->Edit1->Text));
int ErrCode=machine->Step();
if(ErrCode==-1){
StatusBarHint("������: ������.");	
}
if(ErrCode==-2){
StatusBarHint("������: ����������� ������� ��������.");	
}
if(ErrCode==1){
MessageDlg("���������� ������� ���������.",mtInformation,TMsgDlgButtons()<<mbOK,0);	
}
if(ErrCode!=0){
if (!PauseBtn->Enabled) {
	StepTimer->Enabled=false;
}}
TapeOffset=machine->GetTapePosition()-StrToInt(OptForm->Edit1->Text);
UpdTape();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::StartBtnClick(TObject *Sender)
{
StartBtn->Enabled=false;
PauseBtn->Enabled=true;	
StepBtn->Click();
StepTimer->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::StepTimerTimer(TObject *Sender)
{
StepBtn->Click();	
}
//---------------------------------------------------------------------------

