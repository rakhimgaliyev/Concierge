﻿#include <vcl.h>

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

RunThread *runThr = new RunThread(true);
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
	Memo1->Enabled = false;
	TrayIcon1->Visible = true;
	runThr->Start();
	Memo1->Lines->Clear();
	ServerSocket1->Port = 9001;
	ServerSocket1->Active = true;
	Memo1->Lines->Add("Server is running: port 9001");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientConnectEvent(TObject *Sender, TCustomWinSocket *Socket)
{
	Memo1->Lines->Add("Client connected");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientSentMessage(TObject *Sender, TCustomWinSocket *Socket)
{
	AnsiString s = Socket->ReceiveText();
	AnsiString code = s.SubString(0, s.Pos(":") - 1);
	AnsiString buff = "";
	if (code.Length() == 0) {
		Socket->SendText(IntToStr(WRONG_DATA_FORMAT) + ":");
		return;
	}
	if (code == IntToStr(GET_CONNECTED_USB_LIST)) {
		buff = IntToStr(SUCCESS) + ":";
		HDEVINFO deviceInfoSet0 = GetConnectedDevicesHandle();
		if (deviceInfoSet0 == INVALID_HANDLE_VALUE) {
			SetupDiDestroyDeviceInfoList(deviceInfoSet0);
			Memo1->Lines->Add("Error: INVALID_HANDLE_VALUE");
			Socket->SendText("Internal Server Error");
			return;
		}

		std::vector<USB> USBList = GetConnectedUsbList(deviceInfoSet0);
		for (size_t i = 0; i < USBList.size(); i++) {
			buff = buff + IntToStr(USBList[i].vid);
			buff = buff + ":";
			buff = buff + IntToStr(USBList[i].pid);
			buff = buff + ":";
			buff = buff + USBList[i].name;
			buff = buff + ":";
			AnsiString name = "";
			USB usb(NULL, USBList[i].vid, USBList[i].pid, name);
			if (USBIsOnDatabase(usb)) {
				buff = buff + "1";
			} else {
				buff = buff + "0";
			}
			buff = buff + ":";
		}
		Socket->SendText(buff);
		SetupDiDestroyDeviceInfoList(deviceInfoSet0);
		return;
	}
	if (code == GET_USB_LIST_FROM_DB) {
		buff = IntToStr(SUCCESS) + ":";
		std::vector<USB> USBList = GetUSBListFromDB();
		for (size_t i = 0; i < USBList.size(); i++) {
			buff = buff + IntToStr(USBList[i].vid);
			buff = buff + ":";
			buff = buff + IntToStr(USBList[i].pid);
			buff = buff + ":";
			buff = buff + USBList[i].name;
			buff = buff + ":";
			buff = buff + "1";
			buff = buff + ":";
		}
		Socket->SendText(buff);
		return;
	}
	if ((code == ADD_TO_DB) || (code == DELETE_FROM_DB)) {
		s = s.SubString(s.Pos(":") + 1, s.Length() - s.Pos(":"));
		if (s.Pos(":") == 0) {
			Socket->SendText("WRONG REQUEST FORMAT");
			return;
		}
		AnsiString vid = s.SubString(0, s.Pos(":") - 1);
		s = s.SubString(s.Pos(":") + 1, s.Length() - s.Pos(":"));
		if (s.Pos(":") == 0) {
			Socket->SendText("WRONG REQUEST FORMAT");
		}
		AnsiString pid = s.SubString(0, s.Pos(":") - 1);
		s = s.SubString(s.Pos(":") + 1, s.Length() - s.Pos(":"));
		if (s.Pos(":") == 0) {
			Socket->SendText("WRONG REQUEST FORMAT");
		}
		AnsiString name = s.SubString(0, s.Pos(":") - 1);
		Memo1->Lines->Add(vid + "  " + pid + " " + name);
		for (size_t i = 1; i < vid.Length(); i++) {
			if ((vid[i] >= '9') || (vid[i] <= '0')) {
				Socket->SendText("WRONG REQUEST FORMAT");
				return;
			}
		}
		for (size_t i = 1; i < pid.Length(); i++) {
			if ((pid[i] >= '9') || (pid[i] <= '0')) {
				Socket->SendText("WRONG REQUEST FORMAT");
				return;
			}
		}
		USB usb(NULL, StrToInt(vid), StrToInt(pid), name);
		runThr->Suspend();
		if (code == ADD_TO_DB) {
			AddUsbToDatabase(usb);
		} else {
			DeleteUsbFromDatabase(usb);
		}
		runThr->Resume();
		return;
	}

	Socket->SendText("WRONG REQUEST CODE");
}
//---------------------------------------------------------------------------



void __fastcall TForm1::TrayIcon1Click(TObject *Sender)
{
	ShowWindow(Form1->Handle, SW_SHOW);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	CanClose = false;
	ShowWindow(Form1->Handle, SW_HIDE);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ServerSocket1ClientDisconnect(TObject *Sender, TCustomWinSocket *Socket)

{
	Memo1->Lines->Add("Client disconnected");
}
//---------------------------------------------------------------------------

