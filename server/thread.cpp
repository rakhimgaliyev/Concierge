//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "thread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall RunThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall RunThread::RunThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall RunThread::Execute()
{
	FreeOnTerminate = true;

	std::vector<USB> USBList;
	std::vector<USB> prevUSBList;
	while (true) {
		HDEVINFO deviceInfoSet0 = GetConnectedDevicesHandle();
		if (deviceInfoSet0 == INVALID_HANDLE_VALUE) {
			Form1->Memo1->Lines->Add("Error: INVALID_HANDLE_VALUE");
			SetupDiDestroyDeviceInfoList(deviceInfoSet0);
			return;
		}
		std::vector<USB> USBList = GetConnectedUsbList(deviceInfoSet0);

		for (size_t i = 0; i < USBList.size(); i++) {
			USB usb = USBList[i];
			if (USBIsOnDatabase(usb)) {
				continue;
			}
			DEVINST DevInstParent = usb.devInst;
			WCHAR VetoNameW[MAX_PATH];
			PNP_VETO_TYPE VetoType = PNP_VetoTypeUnknown;
			for ( long tries=1; tries <= 10; tries++ ) {
				VetoNameW[0] = 0;
				CONFIGRET res = CM_Request_Device_EjectW(DevInstParent,
					&VetoType, VetoNameW, MAX_PATH, 0);

				bool bSuccess = ( res==CR_SUCCESS &&
				VetoType==PNP_VetoTypeUnknown );
				if ( bSuccess )  {
					break;
				}
				Sleep(2);
			}
		}
		SetupDiDestroyDeviceInfoList(deviceInfoSet0);
		Sleep(10);

	}
}
//---------------------------------------------------------------------------
