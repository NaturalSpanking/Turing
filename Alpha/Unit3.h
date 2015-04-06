//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ValEdit.hpp>
#include <Registry.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TOptForm : public TForm
{
__published:	// IDE-managed Components
	TButton *AssocBtn;
	TButton *OkBtn;
	TButton *CancelBtn;
	TLabel *Label1;
	TEdit *Edit1;
	TEdit *Edit2;
	TLabel *Label2;
	TEdit *Edit3;
	TLabel *Label3;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox2;
	TLabel *Label4;
	TLabel *Label5;
	TPanel *Panel1;
	TPanel *Panel2;
	TColorDialog *ColorDialog1;
	void __fastcall OkBtnClick(TObject *Sender);
	void __fastcall CancelBtnClick(TObject *Sender);
	void __fastcall AssocBtnClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall PanelClick(TObject *Sender);
private:
	TStringList *BufList;
	void ApplyToForm();
	void ApplyToList();
	void ApplyChanges();
public:		// User declarations
	__fastcall TOptForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TOptForm *OptForm;
//---------------------------------------------------------------------------
#endif
