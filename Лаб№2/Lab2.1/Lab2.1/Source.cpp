#include <Windows.h>
#include <tchar.h>
#define MAX_LOADSTRING 100
#define IDS_APP_TITLE			103

#define IDR_MAINFRAME			128
#define IDD_LAB22_DIALOG	102
#define IDD_ABOUTBOX			103
#define IDM_ABOUT				104
#define IDM_EXIT				105
#define IDI_LAB22			107
#define IDI_SMALL				108
#define IDC_LAB22			109
#define IDC_MYICON				2
#ifndef IDC_STATIC
#define IDC_STATIC				-1
#endif

#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS

#define _APS_NO_MFC					130
#define _APS_NEXT_RESOURCE_VALUE	129
#define _APS_NEXT_COMMAND_VALUE		32771
#define _APS_NEXT_CONTROL_VALUE		1000
#define _APS_NEXT_SYMED_VALUE		110
#endif
#endif

HINSTANCE hInst;								
TCHAR szTitle[MAX_LOADSTRING] = _T("Title2");					
TCHAR szWindowClass[MAX_LOADSTRING] = _T("Windowclass2");
int flag1 = 0;
int flag2 = 0;
int mov = 0;
int vverh = 1;
int vniz = 0;
RECT clientRect;


ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	MSG msg;
	HACCEL hAccelTable;

	MyRegisterClass(hInstance);

	
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB22));


	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}




ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB22));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_LAB22);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance;

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}


//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_USER + 1:
	{
		flag1 = 1;
		flag2 = 0;
		InvalidateRect(hWnd, 0, FALSE);
	}
	break;
	case WM_USER + 2:
	{
		flag2 = 1;
		flag1 = 0;
		mov = 0;
		vverh = 1;
		vniz = 0;
		InvalidateRect(hWnd, 0, FALSE);
	}
	break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
	
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
	
		if (flag1)
		{
			RECT WinCoord = {};
			GetClientRect(hWnd, &clientRect);
			Ellipse(hdc, clientRect.right / 2 - 20, clientRect.bottom - 40, clientRect.right / 2 + 20, clientRect.bottom);
		}
		if (flag2)
		{
			RECT WinCoord = {};
			GetClientRect(hWnd, &clientRect);
			if (vverh)
			{
				Ellipse(hdc, clientRect.right / 2 - 20, clientRect.bottom - 40 - mov, clientRect.right / 2 + 20, clientRect.bottom - mov);
				Sleep(1);
				InvalidateRect(hWnd, 0, TRUE);
				mov++;
				if (clientRect.bottom - 40 - mov == -1)
				{
					vverh = 0;
					vniz = 1;
					mov--;
				}
			}
			if (vniz)
			{
				Ellipse(hdc, clientRect.right / 2 - 20, clientRect.bottom - 40 - mov, clientRect.right / 2 + 20, clientRect.bottom - mov);
				Sleep(1);
				InvalidateRect(hWnd, 0, TRUE);
				mov--;
				if (mov == -1)
				{
					vverh = 1;
					vniz = 0;
					mov++;
				}
			}
		}
		

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}