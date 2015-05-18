// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
#include "Unit1.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOptForm *OptForm;

void TOptForm::ApplyToForm() {
	Edit1->Text = BufList->Strings[0];
	Edit2->Text = BufList->Strings[1];
	Edit3->Text = BufList->Strings[2];
	CheckBox1->Checked = BufList->Strings[3] == "1" ? true : false;
	CheckBox2->Checked = BufList->Strings[4] == "1" ? true : false;
	Panel1->Color = StrToInt(BufList->Strings[5]);
	Panel2->Color = StrToInt(BufList->Strings[6]);
	CheckBox3->Checked = BufList->Strings[7] == "1" ? true : false;
}

void TOptForm::ApplyToList() {
	BufList->Clear();
	BufList->Add(Edit1->Text);
	BufList->Add(Edit2->Text);
	BufList->Add(Edit3->Text);
	BufList->Add(CheckBox1->Checked ? "1" : "0");
	BufList->Add(CheckBox2->Checked ? "1" : "0");
	BufList->Add(IntToStr(Panel1->Color));
	BufList->Add(IntToStr(Panel2->Color));
	BufList->Add(CheckBox3->Checked ? "1" : "0");
}

void TOptForm::ApplyChanges() {
	if (CheckBox1->Checked) {
		MainForm->CommentMemo->Visible = true;
		MainForm->MemoSplitter->Visible = true;
	}
	else {
		MainForm->CommentMemo->Visible = false;
		MainForm->MemoSplitter->Visible = false;
	}
	if (CheckBox2->Checked) {
		MainForm->ProblemMemo->Visible = true;
		MainForm->MemoSplitter->Visible = true;
		MainForm->MemoSplitter->Align = alBottom;
		MainForm->CommentMemo->Align = alBottom;
		MainForm->MemoSplitter->Top = MainForm->TextPanel->Height / 2;
		MainForm->CommentMemo->Height = MainForm->TextPanel->Height / 2;
	}
	else {
		MainForm->ProblemMemo->Visible = false;
		MainForm->MemoSplitter->Visible = false;
		MainForm->CommentMemo->Align = alClient;
	}
	if ((CheckBox1->Checked) || (CheckBox2->Checked)) {
		MainForm->TextPanel->Visible = true;
		MainForm->GridSplitter->Visible = true;
		MainForm->GridSplitter->Left = MainForm->TableGrid->Width;
	}
	else {
		MainForm->TextPanel->Visible = false;
		MainForm->GridSplitter->Visible = false;
	}
	if (MainForm->Tag == 0) {
		MainForm->machine->tap->Resize(StrToInt(Edit1->Text)*2 + 1);
	}
	else {
		Edit1->Text = IntToStr((MainForm->machine->tap->GetLenght() - 1) / 2);
		MainForm->Tag = 0;
	}
	MainForm->StepTimer->Interval = StrToInt(Edit2->Text);
	MainForm->ShadowSaveTimer->Interval = StrToInt(Edit3->Text) * 60000;
	MainForm->ShadowSaveTimer->Enabled = true;
	MainForm->machine->SetTapePosition(StrToInt(OptForm->Edit1->Text));
	MainForm->UpdTable();
	MainForm->UpdTape();
}

// ---------------------------------------------------------------------------
__fastcall TOptForm::TOptForm(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
void __fastcall TOptForm::OkBtnClick(TObject *Sender) {
	try {
		if (StrToInt(Edit1->Text) < 25) {
			MessageDlg("Смещение не может быть меньше 25.", mtWarning,
				TMsgDlgButtons() << mbOK, 0);
			Edit1->Text = "25";
			return;
		}
		if (StrToInt(Edit2->Text) < 0) {
			MessageDlg("Время не может быть отрицательным.", mtWarning,
				TMsgDlgButtons() << mbOK, 0);
			Edit2->Text = "0";
			return;
		}
		if (StrToInt(Edit3->Text) < 0) {
			MessageDlg("Время не может быть отрицательным.", mtWarning,
				TMsgDlgButtons() << mbOK, 0);
			Edit3->Text = "0";
			return;
		}
	}
	catch (EConvertError *ex) {
		MessageDlg("Все значения должны быть числовыми!", mtWarning,
			TMsgDlgButtons() << mbOK, 0);
		return;
	}
	ApplyChanges();
	ApplyToList();
	BufList->SaveToFile("Options.cfg");
	OptForm->Close();
}

// ---------------------------------------------------------------------------
void __fastcall TOptForm::CancelBtnClick(TObject *Sender) {
	OptForm->Close();
}

// ---------------------------------------------------------------------------
void __fastcall TOptForm::AssocBtnClick(TObject *Sender) {
	TRegistry *R = new TRegistry;
	R->RootKey = HKEY_CLASSES_ROOT;
	try {
		R->OpenKey("Turing_Machine_File", true);
		R->WriteString("", "Файл Машины Тьюринга");
		R->OpenKey("shell\\open\\command", true);
		R->WriteString("", Application->ExeName + " \"%1\"");
		R->CloseKey();
		R->OpenKey(".mtur", true);
		R->WriteString("", "Turing_Machine_File");
		R->CloseKey();
	}
	catch (Exception *ex) {
		MessageDlg("Доступ к реестру запрещен!", mtError,
			TMsgDlgButtons() << mbOK, 0);
	}
	if (R->LastError == 0) {
		MessageDlg("Успешно", mtInformation, TMsgDlgButtons() << mbOK, 0);
	}
	delete R;
}
// ---------------------------------------------------------------------------

void __fastcall TOptForm::FormShow(TObject *Sender) {
	ApplyToList();
}

// ---------------------------------------------------------------------------
void __fastcall TOptForm::FormClose(TObject *Sender, TCloseAction &Action) {
	ApplyToForm();
}

// ---------------------------------------------------------------------------
void __fastcall TOptForm::FormCreate(TObject *Sender) {
	BufList = new TStringList;
	if (FileExists("Options.cfg")) {
		BufList->LoadFromFile("Options.cfg");
		ApplyToForm();
	}
	ApplyChanges();
}
// ---------------------------------------------------------------------------

void __fastcall TOptForm::FormDestroy(TObject *Sender) {
	delete BufList;
}

// ---------------------------------------------------------------------------
void __fastcall TOptForm::PanelClick(TObject *Sender) {
	TColorDialog *C = new TColorDialog(OptForm);
	C->Color = ((TPanel*)Sender)->Color;
	if (C->Execute()) {
		((TPanel*)Sender)->Color = C->Color;
	}
	delete C;
}
// ---------------------------------------------------------------------------
