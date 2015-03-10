//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N5;
	TMenuItem *N6;
	TMenuItem *N7;
	TMenuItem *N8;
	TMenuItem *N9;
	TMenuItem *N10;
	TPanel *ControlPanel;
	TBitBtn *StartBtn;
	TBitBtn *PauseBtn;
	TBitBtn *StopBtn;
	TBitBtn *StepBtn;
	TBitBtn *SaveTapeBtn;
	TBitBtn *LoadTapeBtn;
	TStatusBar *StatusBar1;
	TStringGrid *TapeGrid;
	TPanel *TapePanel;
	TBitBtn *TapeLeftBtn;
	TBitBtn *TapeRigthBtn;
	TPanel *GridPanel;
	TBitBtn *AddRowBtn;
	TBitBtn *DelRowBtn;
	TBitBtn *AddColBtn;
	TBitBtn *DelColBtn;
	TSplitter *GridSplitter;
	TStringGrid *TableGrid;
	TPanel *TextPanel;
	TMemo *CommentMemo;
	TSplitter *MemoSplitter;
	TMemo *ProblemMemo;
	TMenuItem *N11;
	TMenuItem *N12;
	TMenuItem *N13;
	TMenuItem *N14;
	TMenuItem *N15;
	void __fastcall N10Click(TObject *Sender);
	void __fastcall N7Click(TObject *Sender);
	void __fastcall N9Click(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall TapeGridDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TGridDrawState State);
	void __fastcall TapeRigthBtnClick(TObject *Sender);
	void __fastcall TapeLeftBtnClick(TObject *Sender);
	void __fastcall TapeGridMouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
		  bool &Handled);
	void __fastcall TapeGridMouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
		  bool &Handled);
	void __fastcall N12Click(TObject *Sender);
	void __fastcall TapeGridKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall AddRowBtnClick(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
private:	// User declarations
int TapeOffset;
public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif