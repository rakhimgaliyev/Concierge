//---------------------------------------------------------------------------

#ifndef threadH
#define threadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
#include "Unit1.h"

class RunThread : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall RunThread(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
