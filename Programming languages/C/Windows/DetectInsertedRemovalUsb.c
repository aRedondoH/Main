/* Common includes */
#include <windows.h>
#include <stdio.h>
#include <snok_agent.h>
#include <time.h>

/* USB includes */
#define _WIN32_WINNT 0x0501
#include <dbt.h>
#include <iomanip>

// className for USB
const char *className = "DevNotifyTest";

/* CallBack from USB*/
LRESULT CALLBACK WinProc(HWND hwnd, UINT msg,WPARAM wParam, LPARAM lParam)
{
	
	if (msg == WM_DEVICECHANGE)
	{
		switch (wParam){
		case DBT_DEVICEARRIVAL:
			cout << "new device connected \n";
			transferEvent(my_id, USB_INSERTION, "new device connected");
			break;
		case DBT_DEVICEREMOVECOMPLETE:
			cout << "a device has been removed \n";
			transferEvent(my_id, USB_REMOVAL, "a device has been removed");
			break;
		case DBT_DEVNODES_CHANGED:
			cout << "a device has been added to or removed from the system \n";
			transferEvent(my_id, USB_INSERTION, "a device has been added to or removed from the system");
			break;
		}
		cout << "WM_DEVICECHANGE, wParam = 0x"
			<< setw(4) << hex << setfill('0') << int(wParam) << dec
			<< endl;
	}//if
	//else
		//cout << "Got msg " << msg << ", " << int(wParam) << ", " << int(lParam) << endl;
	return 1;
}//WinProc

/* Check USB inserted or removal*/
void usbInsertedRemoval(){
	

	WNDCLASSA wincl = { 0 };
	wincl.hInstance = GetModuleHandle(0);
	wincl.lpszClassName = className;
	wincl.lpfnWndProc = WinProc;

	//if (!RegisterClassA(&wincl))
	//{
	//	DWORD le = GetLastError();
	//	cout << "RegisterClassA() failed, le = " << le << endl;
		//return 1;
	//}//if

	HWND parent = 0;
#ifdef USE_MESSAGE_ONLY_WINDOW
	parent = HWND_MESSAGE;
#endif
	HWND hwnd = CreateWindowExA(WS_EX_TOPMOST, className, className,
		0, 0, 0, 0, 0, parent, 0, 0, 0);
	//if (!hwnd)
	//{
	//	DWORD le = GetLastError();
	//	cout << "CreateWindowExA() failed, le = " << le << endl;
		//return 1;
	//}//if

	GUID cdromDevIntGuid =
	{ 0x53F56308, 0xB6BF, 0x11D0,
	{ 0x94, 0xF2, 0x00, 0xA0, 0xC9, 0x1E, 0xFB, 0x8B } };

	DEV_BROADCAST_DEVICEINTERFACE_A notifyFilter = { 0 };
	notifyFilter.dbcc_size = sizeof(notifyFilter);
	notifyFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	notifyFilter.dbcc_classguid = cdromDevIntGuid;

	HDEVNOTIFY hDevNotify =
		RegisterDeviceNotificationA(hwnd, &notifyFilter,
#ifndef USE_CDROM_GUID_ONLY
		DEVICE_NOTIFY_ALL_INTERFACE_CLASSES |
#endif
		DEVICE_NOTIFY_WINDOW_HANDLE);
	//if (!hDevNotify)
	//{
	//	DWORD le = GetLastError();
	//	cout << "RegisterDeviceNotificationA() failed, le = " << le << endl;
		//return 1;
	//}//if

	MSG msg;
	//for (;;) // ctrl-c to exit ;)
	//{
		BOOL bRet = PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE);

		if ((bRet == 0) || (bRet == -1))
			//break;

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	//}
}

int main(int argc, char *argv[])
{

/* Check USB insertion/removal */
	usbInsertedRemoval();

return 0;
}