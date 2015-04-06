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
		TapeGrid->Canvas->TextOutW(r.left + 3, r.top + 5,
			IntToStr(TapeOffset - TapeGrid->ColCount / 2 + ACol));
	}
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::TapeRightBtnClick(TObject *Sender) {
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
	// ShowMessage(IntToStr(Key));
	TapeGrid->Cells[TapeGrid->Col][1] = Key;
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::AddRowBtnClick(TObject *Sender) {
	ShowMessage("������� ��� �� �����������!");
	// AddRowBtn->Glyph->LoadFromResourceName((int)HInstance, "LeftGreenArrow");
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
	if (ACol == 1) {
		GridCell->Canvas->Brush->Color = RGB(0, 255, 255);
		// GridCell->Canvas->Brush->Color=clYellow;
	}
	GridCell->Canvas->FillRect(TRect(0, 0, r.Width(), r.Height()));
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
	TGridCracker* C;
	// ShowMessage(IntToStr(C->GetCaretPosition(TableGrid)));

	if (TableGrid->Cells[TableGrid->Col][TableGrid->Row].Length() > 1) {
		if ((C->GetCaretPosition(TableGrid) == 0) &&
			((TableGrid->Cells[TableGrid->Col][TableGrid->Row][1] != '.') &&
			(TableGrid->Cells[TableGrid->Col][TableGrid->Row][1] != '>') &&
			(TableGrid->Cells[TableGrid->Col][TableGrid->Row][1] != '<'))) {
			Key = 0;
		}
	}

	if ((C->GetCaretPosition(TableGrid) == 1) &&
		(((Key != '>') && (Key != '<') && (Key != '.') && (Key != 8) &&
		(Key != 13)) || ((TableGrid->Cells[TableGrid->Col][TableGrid->Row].Pos
		('>') != 0) || (TableGrid->Cells[TableGrid->Col][TableGrid->Row].Pos
		('<') != 0) || (TableGrid->Cells[TableGrid->Col][TableGrid->Row].Pos
		('.') != 0)))) {
		Key = 0;
	}
	if ((C->GetCaretPosition(TableGrid) >= 2) && (((Key < '0') || (Key > '9'))
		&& (Key != 8) && (Key != 13))) {
		Key = 0;
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
		TapeGrid->Refresh();
	}
	else {
		TapeOffset += ACol - TapeGrid->ColCount / 2;
		TapeGrid->Refresh();

	}
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::TapeGridExit(TObject *Sender) {
	TapeGrid->Col = TapeGrid->ColCount / 2;
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::TapeGridKeyDown(TObject *Sender, WORD &Key,
	TShiftState Shift)
{
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
