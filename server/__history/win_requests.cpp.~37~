//---------------------------------------------------------------------------

#pragma hdrstop

#include "win_requests.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


HDEVINFO GetConnectedDevicesHandle()
{
	DWORD error,
		dwPropertyRegDataType,
		dwSize;
	CONST GUID *pClassGuid = &GUID_DEVINTERFACE_USB_DEVICE;
	TCHAR szDeviceInstanceID [MAX_DEVICE_ID_LEN];
	PCWSTR enumerator = TEXT("USB");
	TCHAR szDesc[1024],
		szHardwareIDs[4096];
	LPTSTR pszToken,
		pszNextToken;
	TCHAR szVid[MAX_DEVICE_ID_LEN],
		szPid[MAX_DEVICE_ID_LEN],
			szMi[MAX_DEVICE_ID_LEN];
	rsize_t *strmax = NULL;

	SP_DEVINFO_DATA deviceInfoData;
	ZeroMemory(&deviceInfoData, sizeof(SP_DEVINFO_DATA));
	deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

	HDEVINFO deviceInfoSet = SetupDiGetClassDevs(
		pClassGuid,
		enumerator,
		NULL,
		// DIGCF_PRESENT Возвращайте только устройства, которые в
		// настоящее время присутствуют в системе.
		DIGCF_ALLCLASSES | DIGCF_PRESENT
	);
	return deviceInfoSet;
}


std::vector<USB> GetConnectedUsbList(const HDEVINFO &deviceInfoSet)
{
	std::vector<USB> USBlist;

	DWORD error,
		dwPropertyRegDataType,
		dwSize;
	TCHAR szDeviceInstanceID [MAX_DEVICE_ID_LEN];
	TCHAR szDesc[1024],
		szHardwareIDs[4096];
	LPTSTR pszToken,
		pszNextToken;
	TCHAR szVid[MAX_DEVICE_ID_LEN],
		szPid[MAX_DEVICE_ID_LEN],
			szMi[MAX_DEVICE_ID_LEN];
	rsize_t *strmax = NULL;

	SP_DEVINFO_DATA deviceInfoData;
	ZeroMemory(&deviceInfoData, sizeof(SP_DEVINFO_DATA));
	deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    	for (DWORD i = 0; ; i++) {
		deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
		if (!SetupDiEnumDeviceInfo(deviceInfoSet, i, &deviceInfoData)) {
			break;
		}

		CONFIGRET status = CM_Get_Device_ID(deviceInfoData.DevInst, szDeviceInstanceID , MAX_PATH, 0);
		if (status != CR_SUCCESS) {
			continue;
		}


		if (SetupDiGetDeviceRegistryProperty(deviceInfoSet, &deviceInfoData, SPDRP_DEVICEDESC,
											  &dwPropertyRegDataType, (BYTE*)szDesc,
											  sizeof(szDesc),   // The size, in bytes
											  &dwSize)) {
		}

		if (WideCharToString(szDesc) != "USB Mass Storage Device") {
			continue;
		}

		int vid = 0;
		int pid = 0;
		GetUSBVidAndPid(szDeviceInstanceID, vid, pid);
		USB usb(deviceInfoData.DevInst, vid, pid);
		USBlist.push_back(usb);
	}
	SetupDiDestroyDeviceInfoList(deviceInfoSet);
   /*


	for (DWORD i = 0; ; i++) {
		if (!SetupDiEnumDeviceInfo(deviceInfoSet, i, &deviceInfoData)) {
			break;
		}

		CONFIGRET status = CM_Get_Device_ID(deviceInfoData.DevInst, szDeviceInstanceID , MAX_PATH, 0);
		if (status != CR_SUCCESS) {
			continue;
		}


		if (SetupDiGetDeviceRegistryProperty(deviceInfoSet, &deviceInfoData, SPDRP_DEVICEDESC,
											  &dwPropertyRegDataType, (BYTE*)szDesc,
											  sizeof(szDesc),   // The size, in bytes
											  &dwSize)) {
		}

		if (WideCharToString(szDesc) != "USB Mass Storage Device") {
			continue;
		}

		int vid = 0;
		int pid = 0;
		GetUSBVidAndPid(szDeviceInstanceID, vid, pid);
		USB usb(deviceInfoData.DevInst, vid, pid);
		USBlist.push_back(usb);
	}
     */
	return USBlist;
}
