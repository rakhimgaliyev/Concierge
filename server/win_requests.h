//---------------------------------------------------------------------------

#ifndef win_requestsH
#define win_requestsH
//---------------------------------------------------------------------------
#include <SetupAPI.h>
#include <vector>

#include "USB.h"
#include "settings.h"

HDEVINFO GetConnectedDevicesHandle();
std::vector<USB> GetConnectedUsbList(const HDEVINFO &deviceInfoSet);

#endif
