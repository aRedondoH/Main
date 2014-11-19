#include <windows.h>
#include <stdio.h>

int main(void)
{
	UINT nDevices;
	PRAWINPUTDEVICELIST pRawInputDeviceList;
	auto retval = GetRawInputDeviceList(NULL, &nDevices, sizeof(RAWINPUTDEVICELIST));
	auto errval = GetLastError();
	printf("sizeof (RAWINPUTDEVICELIST) is %d\n", (int)sizeof(RAWINPUTDEVICELIST));
	printf("offsetof (RAWINPUTDEVICELIST::hDevice) is %d\n", (char*)(&pRawInputDeviceList->hDevice) - (char*)pRawInputDeviceList);
	printf("sizeof (RAWINPUTDEVICELIST::hDevice) is %d\n", (int)(sizeof pRawInputDeviceList->hDevice));
	printf("offsetof (RAWINPUTDEVICELIST::dwType) is %d\n", (char*)(&pRawInputDeviceList->dwType) - (char*)pRawInputDeviceList);
	printf("sizeof (RAWINPUTDEVICELIST::dwType) is %d\n", (int)(sizeof pRawInputDeviceList->dwType));
	printf("\nGetRawInputDeviceList() returned %d\n", (int)retval);
	printf("GetLastError() returned %d\n", (int)errval);
	printf("nDevices = %u\n", (unsigned int)nDevices);
	return 0;
}