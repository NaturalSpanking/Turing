//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAboutForm *AboutForm;
//---------------------------------------------------------------------------
__fastcall TAboutForm::TAboutForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAboutForm::Label8Click(TObject *Sender)
{
ShellExecute(AboutForm->Handle,L"open",L"https://github.com/NaturalSpanking/Turing",L"",L"",SW_SHOW);
//ShellExecute(MainForm->Handle, L"open", L"TuringHelp.chm", L"", L"", SW_SHOW);
}
//---------------------------------------------------------------------------

