//---------------------------------------------------------------------------

#ifndef win_requestsH
#define win_requestsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>

#include <windows.h>
#include <SetupAPI.h>

#include <vector>

#include "USB.h"
#include "settings.h"

HDEVINFO GetConnectedDevicesHandle();
std::vector<USB> GetConnectedUsbList(const HDEVINFO &deviceInfoSet);

#endif
