// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma resource "asd.res"
TMainForm *MainForm;

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
	ShowMessage("���������");
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
		TapeGrid->Canvas->Brush->Color = clYellow;
		TapeGrid->Canvas->Pen->Color = clBlack;
		TapeGrid->Canvas->MoveTo(r.left + 3, r.top + 3);
		TapeGrid->Canvas->LineTo(r.left + 3 + 17, r.top + 3);
		TapeGrid->Canvas->LineTo(r.left + 3 + 8, r.top + 3 + 17);
		TapeGrid->Canvas->LineTo(r.left + 3, r.top + 3);
		TapeGrid->Canvas->FloodFill(r.left + 8, r.top + 5, clBlack, fsBorder);
	}
	if (ACol != TapeGrid->ColCount / 2) {
		TapeGrid->Canvas->Font->Size = 8;
		TapeGrid->Canvas->TextOutW(r.left + 3, r.top + 5,
			IntToStr(TapeOffset - TapeGrid->ColCount / 2 + ACol));
	}
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::TapeRigthBtnClick(TObject *Sender) {
	TapeOffset++;
	TapeGrid->Refresh();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::TapeLeftBtnClick(TObject *Sender) {
	TapeOffset--;
	TapeGrid->Refresh();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::TapeGridMouseWheelDown(TObject *Sender,
	TShiftState Shift, TPoint &MousePos, bool &Handled) {
	TapeOffset++;
	TapeGrid->Refresh();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::TapeGridMouseWheelUp(TObject *Sender,
	TShiftState Shift, TPoint &MousePos, bool &Handled) {
	TapeOffset--;
	TapeGrid->Refresh();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::N12Click(TObject *Sender) {
	ShowMessage("�����");
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::TapeGridKeyPress(TObject *Sender,
	System::WideChar &Key)

{
	ShowMessage(IntToStr(Key));
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::AddRowBtnClick(TObject *Sender) {
	ShowMessage("������� ��� �� �����������!");
	//AddRowBtn->Glyph->LoadFromResourceName((int)HInstance, "LeftGreenArrow");
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
	TBitmap* sprite = new Graphics::TBitmap();
	switch (TableGrid->Cells[ACol][ARow][2]) {
	case '<':
		sprite->LoadFromResourceName((int)HInstance, "LeftGreenArrow");
		break;
	case '>':
		sprite->LoadFromResourceName((int)HInstance, "RightGreenArrow");
		break;
	case '.':
		sprite->LoadFromResourceName((int)HInstance, "Stopp");
		break;
	}
	if (TableGrid->Cells[ACol][ARow].Length() * 16.25 >
		TableGrid->ColWidths[ACol]) {
		TableGrid->ColWidths[ACol] +=
			(TableGrid->Cells[ACol][ARow].Length() - 4);
	}
	TBitmap* spr = new Graphics::TBitmap();
	spr->Height = 19;
	spr->Width = TableGrid->ColWidths[ACol];
	spr->Canvas->Font->Size = 10;
	spr->Canvas->TextOutW(5, 2, TableGrid->Cells[ACol][ARow][1]);
	spr->Canvas->TextOutW(40, 2, "Q" + TableGrid->Cells[ACol][ARow].SubString(3,
		TableGrid->Cells[ACol][ARow].Length()));
	BitBlt(spr->Canvas->Handle, 20, 4, 22, 22, sprite->Canvas->Handle, 0, 0,
		SRCCOPY);
	BitBlt(TableGrid->Canvas->Handle, r.left, r.top, TableGrid->ColWidths[ACol],
		22, spr->Canvas->Handle, 0, 0, SRCCOPY);
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::TableGridKeyPress(TObject *Sender,
	System::WideChar &Key) {
	if (((TableGrid->Cells[TableGrid->Col][TableGrid->Row].Length()) == 1) &&
		((Key != '>') && (Key != '<') && (Key != '.') && (Key != 8) &&
		(Key != 13))) {
		Key = 0;
	}
	if (((TableGrid->Cells[TableGrid->Col][TableGrid->Row].Length()) >= 2) &&
		(((Key < '0') || (Key > '9')) && (Key != 8) && (Key != 13))) {
		Key = 0;
	}
}
// ---------------------------------------------------------------------------
