//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.Win.ScktComp.hpp>
#include <Vcl.ExtCtrls.hpp>

/*
#include <windows.h>
#include <SetupAPI.h>
#include <cfgmgr32.h>
#include <initguid.h>
#include <winioctl.h>
*/
#include <vector>
#include <string>
#include <thread>

#include "USB.h"
#include "win_requests.h"
#include "db_requests.h"
#include "settings.h"
#include "thread.h"
//---------------------------------------------------------------------------
enum {
	GET_CONNECTED_USB_LIST = 0,
	GET_USB_LIST_FROM_DB = 1,
	ADD_TO_DB = 2,
	DELETE_FROM_DB = 3,

	WRONG_DATA_FORMAT = 100,
	SUCCESS = 200,
};

class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMemo *Memo1;
	TServerSocket *ServerSocket1;
	TTrayIcon *TrayIcon1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ClientConnectEvent(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ClientSentMessage(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall TrayIcon1Click(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall ServerSocket1ClientDisconnect(TObject *Sender, TCustomWinSocket *Socket);




private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
