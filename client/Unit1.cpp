//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
	Memo1->Lines->Clear();
	ClientSocket1->Active = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	ClientSocket1->Address = "127.0.0.1";
	ClientSocket1->Port = 9001;
	ClientSocket1->Active = true;
	Memo1->Lines->Add(ClientSocket1->Host);

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	if (!ClientSocket1->Active) {
		 Memo1->Lines->Add("Can't reach server");
		 return;
	}
	AnsiString s = IntToStr(GET_CONNECTED_USB_LIST) + ":";
	ClientSocket1->Socket->SendText(s);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientSocket1Connect(TObject *Sender, TCustomWinSocket *Socket)
{
	Memo1->Lines->Add("Server connected");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientSocket1Read(TObject *Sender, TCustomWinSocket *Socket)
{
	AnsiString s = Socket->ReceiveText();
	AnsiString code = s.SubString(0, s.Pos(":") - 1);
	if (StrToInt(code) == SUCCESS) {
		Memo1->Lines->Add("SUCCESS");
		if (s.Pos(":") == 0) {
			return;
		}
		s = s.SubString(s.Pos(":") + 1, s.Length() - s.Pos(":"));
		int devCount = 0;
		while (s.Length() > 0) {
			if (s.Pos(":") == 0) {
				break;
			}
			AnsiString vid = s.SubString(0, s.Pos(":") - 1);
			s = s.SubString(s.Pos(":") + 1, s.Length() - s.Pos(":"));
			if (s.Pos(":") == 0) {
				break;
			}
			AnsiString pid = s.SubString(0, s.Pos(":") - 1);
			s = s.SubString(s.Pos(":") + 1, s.Length() - s.Pos(":"));
			devCount++;
			Memo1->Lines->Add(IntToStr(devCount) + " USB:");
			Memo1->Lines->Add("    VID: " + vid);
			Memo1->Lines->Add("    PID: " + pid);
			if (s.Pos(":") == 0) {
				break;
			}
			if (s.Length() > 0) {
				if (s[1] == '0') {
					Memo1->Lines->Add("    (unregistered)");
				}
				if (s[1] == '1') {
					Memo1->Lines->Add("    (registered)");
				}
				s = s.SubString(s.Pos(":") + 1, s.Length() - s.Pos(":"));
			}
		}
		if (devCount == 0) {
			Memo1->Lines->Add("USB devices are not detected");
		}
		return;
	}
	Memo1->Lines->Add(s);
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	if (!ClientSocket1->Active) {
		 Memo1->Lines->Add("Can't reach server");
		 return;
	}
	AnsiString s = IntToStr(GET_USB_LIST_FROM_DB) + ":";
	ClientSocket1->Socket->SendText(s);
}
//---------------------------------------------------------------------------




void __fastcall TForm1::Button4Click(TObject *Sender)
{
	StrToInt(Edit1->Text);
	StrToInt(Edit2->Text);
	if (!ClientSocket1->Active) {
		 Memo1->Lines->Add("Can't reach server");
		 return;
	}
	AnsiString s = IntToStr(ADD_TO_DB) + ":" +
		Edit1->Text + ":" + Edit2->Text + ":";
	ClientSocket1->Socket->SendText(s);
	Memo1->Lines->Add("Request sent");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
	StrToInt(Edit1->Text);
	StrToInt(Edit2->Text);
	if (!ClientSocket1->Active) {
		 Memo1->Lines->Add("Can't reach server");
		 return;
	}
	AnsiString s = IntToStr(DELETE_FROM_DB) + ":" +
		Edit1->Text + ":" + Edit2->Text + ":";
	ClientSocket1->Socket->SendText(s);
	Memo1->Lines->Add("Request sent");
}
//---------------------------------------------------------------------------

