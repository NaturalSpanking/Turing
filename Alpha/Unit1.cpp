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
	// ShowMessage(IntToStr(Key));
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
	if (TableGrid->Cells[ACol][ARow].Length() * 16.25 >
		TableGrid->ColWidths[ACol]) {
		TableGrid->ColWidths[ACol] +=
			(TableGrid->Cells[ACol][ARow].Length() - 4);
	}

	GridCell->Height = 28;
	GridCell->Width = TableGrid->ColWidths[ACol];
	GridCell->Canvas->Font->Size = 10;
	GridCell->Canvas->TextOutW(5, 2, TableGrid->Cells[ACol][ARow][1]);
	GridCell->Canvas->TextOutW(40, 2,
		"Q" + TableGrid->Cells[ACol][ARow].SubString(3,
		TableGrid->Cells[ACol][ARow].Length()));
	BitBlt(GridCell->Canvas->Handle, 20, 4, 22, 28, GreenArrow->Canvas->Handle,
		// 20   26
		0, 0, SRCCOPY);
	BitBlt(TableGrid->Canvas->Handle, r.left, r.top, TableGrid->ColWidths[ACol],
		22, GridCell->Canvas->Handle, 0, 0, SRCCOPY);
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::TableGridKeyPress(TObject *Sender,
	System::WideChar &Key) {
	TGridCracker* C;
	// ShowMessage(IntToStr(C->GetCaretPosition(TableGrid)));



	if (TableGrid->Cells[TableGrid->Col][TableGrid->Row].Length() > 2) {
		if ((C->GetCaretPosition(TableGrid) == 0) &&
			(TableGrid->Cells[TableGrid->Col][TableGrid->Row][1] != '.')) {
		Key = 0;
		}
	}

	if ((C->GetCaretPosition(TableGrid) == 1) && ((Key != '>') && (Key != '<')
		&& (Key != '.') && (Key != 8) && (Key != 13))&&
		((TableGrid->Cells[TableGrid->Col][TableGrid->Row].Pos('>')!=0)||(TableGrid->Cells[TableGrid->Col][TableGrid->Row].Pos('<')!=0)||(TableGrid->Cells[TableGrid->Col][TableGrid->Row].Pos('.')!=0))
		) {
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
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::FormDestroy(TObject *Sender) {
	delete(GreenArrow);
	delete(GridCell);
}
// ---------------------------------------------------------------------------
