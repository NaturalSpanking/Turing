//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
TapeOffset=0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::N10Click(TObject *Sender)
{
AboutForm->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::N7Click(TObject *Sender)
{
ShowMessage("���������");
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::N9Click(TObject *Sender)
{
ShowMessage("����� �������");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormResize(TObject *Sender)
{
LoadTapeBtn->Left=MainForm->Width-51;
SaveTapeBtn->Left=MainForm->Width-84;
TapeGrid->ColCount=(MainForm->Width-50)/25-2;
TapeGrid->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TapeGridDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TGridDrawState State)
{
TRect r;
r=TapeGrid->CellRect(ACol,0);
if((ACol==TapeGrid->ColCount/2)&&(ARow==0)){
	TapeGrid->Canvas->Brush->Color=clYellow;
	TapeGrid->Canvas->Pen->Color=clBlack;
	TapeGrid->Canvas->MoveTo(r.left+3,r.top+3);
	TapeGrid->Canvas->LineTo(r.left+3+17,r.top+3);
	TapeGrid->Canvas->LineTo(r.left+3+8,r.top+3+17);
	TapeGrid->Canvas->LineTo(r.left+3,r.top+3);
	TapeGrid->Canvas->FloodFill(r.left+8,r.top+5,clBlack,fsBorder);
}
if(ACol!=TapeGrid->ColCount/2){
TapeGrid->Canvas->Font->Size=8;
TapeGrid->Canvas->TextOutW(r.left+3,r.top+5,IntToStr(TapeOffset-TapeGrid->ColCount/2+ACol));
}
}
//---------------------------------------------------------------------------




void __fastcall TMainForm::TapeRigthBtnClick(TObject *Sender)
{
TapeOffset++;
TapeGrid->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TapeLeftBtnClick(TObject *Sender)
{
TapeOffset--;
TapeGrid->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TapeGridMouseWheelDown(TObject *Sender, TShiftState Shift,
          TPoint &MousePos, bool &Handled)
{
TapeOffset++;
TapeGrid->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TapeGridMouseWheelUp(TObject *Sender, TShiftState Shift,
          TPoint &MousePos, bool &Handled)
{
TapeOffset--;
TapeGrid->Refresh();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::N12Click(TObject *Sender)
{
ShowMessage("�����");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TapeGridKeyPress(TObject *Sender, System::WideChar &Key)

{
ShowMessage(IntToStr(Key));
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AddRowBtnClick(TObject *Sender)
{
ShowMessage("������� ��� �� �����������!");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N6Click(TObject *Sender)
{
MainForm->Close();
}
//---------------------------------------------------------------------------
