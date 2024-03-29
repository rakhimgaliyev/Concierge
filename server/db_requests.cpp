//---------------------------------------------------------------------------

#pragma hdrstop

#include "db_requests.h"
//---------------------------------------------------------------------------


std::vector<USB> GetUSBListFromDB() {
	TStringList *list1 = new TStringList;
	list1->LoadFromFile(USBDatabaseName);
	std::vector<USB> res;

	for (int i = 0; i < list1->Count; i++) {
		AnsiString str = list1[0][i];
		//AnsiStrings always start with 1 and not 0
		int vid = StrToInt(str.SubString(1, str.Pos(" ") - 1));
		str = str.SubString(str.Pos(" ") + 1, str.Length());
		int pid = StrToInt(str.SubString(1, str.Pos(" ") - 1));
		str = str.SubString(str.Pos(" ") + 1, str.Length());
		AnsiString name = str;
		USB usb(NULL, vid, pid, name);
		res.push_back(usb);
	}
	delete list1;
	return res;
}

bool USBIsOnDatabase(USB &usb) {
	std::vector<USB> USBList = GetUSBListFromDB();
	for (size_t i = 0; i < USBList.size(); i++) {
		if (USBList[i] == usb) {
			return true;
		}
	}
	return false;
}


int AddUsbToDatabase(USB &usb) {
	if (USBIsOnDatabase(usb)) {
		return USB_IS_ON_DB;
	}

	TStringList *list1 = new TStringList;
	AnsiString USBstring = IntToStr(usb.vid) + " " + IntToStr(usb.pid)
		+ " " + usb.name;
	list1->Add(USBstring);
	if (!FileExists(USBDatabaseName)) {
		list1->SaveToFile(USBDatabaseName);
		return 0;
	}

	TStringList *list2 = new TStringList;
	list2->LoadFromFile(USBDatabaseName);

	list2->Text = list2->Text + list1->Text;
	list2->SaveToFile(USBDatabaseName);
	delete list1;
	delete list2;
	return 0;
}

int DeleteUsbFromDatabase(USB &usb) {
	if (!USBIsOnDatabase(usb)) {
		return USB_IS_NOT_ON_DB;
	}
	TStringList *list1 = new TStringList;
	list1->LoadFromFile(USBDatabaseName);
	std::vector<USB> res;

    int deletingStringIndex = -1;
	for (int i = 0; i < list1->Count; i++) {
		AnsiString str = list1[0][i];
		int vid = StrToInt(str.SubString(1, str.Pos(" ") - 1));
		str = str.SubString(str.Pos(" ") + 1, str.Length());
		int pid = StrToInt(str.SubString(1, str.Pos(" ") - 1));
		AnsiString name = "";
		USB _usb(USB_HAS_NO_DEVINST, vid, pid, name);
		if (_usb == usb) {
			deletingStringIndex = i;
			break;
		}
	}

	if (deletingStringIndex != -1) {
		list1->Delete(deletingStringIndex);
		list1->SaveToFile(USBDatabaseName);
	}

	delete list1;
	return 0;
}

#pragma package(smart_init)

