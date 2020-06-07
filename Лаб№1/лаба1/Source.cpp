#include <Windows.h>
#include <tchar.h>
#include <cstdlib>
#include <ctime>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");
RECT clientRect;
int flagSun = 1;
int flagNight = 0;
int flagStars = 0;
const int nstar = 750;
int star[nstar][2];


int WINAPI _tWinMain(HINSTANCE This,		 
	HINSTANCE Prev, 	
	LPTSTR cmd, 		
	int mode) 		
{
	HWND hWnd;		
	MSG msg; 		
	WNDCLASS wc; 	
	srand(time(NULL));
	for (int i = 0; i < nstar - 1; i++)
	{
		star[i][1] = rand() % 1920;
		star[i][2] = rand() % 1080;
	}


	wc.hInstance = This;
	wc.lpszClassName = WinName; 				
	wc.lpfnWndProc = WndProc; 					
	wc.style = CS_HREDRAW | CS_VREDRAW; 			
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		 
	wc.lpszMenuName = NULL; 					
	wc.cbClsExtra = 0; 						
	wc.cbWndExtra = 0; 						
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); 	


	if (!RegisterClass(&wc)) return 0;

	
	hWnd = CreateWindow(WinName,			
		_T("Звездочки"), 		
		WS_OVERLAPPEDWINDOW, 		
		CW_USEDEFAULT,				
		CW_USEDEFAULT, 				
		CW_USEDEFAULT, 				
		CW_USEDEFAULT, 				
		HWND_DESKTOP, 				
		NULL, 						
		This, 						
		NULL); 					

	ShowWindow(hWnd, mode); 				

	 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		
		DispatchMessage(&msg); 		
	}

	return 0;
}




LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)		
	{
	case WM_CREATE:
	{
	}
	break;
	case WM_PAINT:
	{

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &clientRect);


		if ((flagSun == 1) && (flagNight == 0) && (flagStars == 0))
		{

			int SizeOfSun = 100;


			FillRect(hdc, &clientRect, CreateSolidBrush(RGB(0, 0, 255)));
			HPEN newPen = CreatePen(PS_SOLID, 15, RGB(255, 0, 0));
			HBRUSH newBrush = CreateSolidBrush(RGB(255, 0, 0));

			HGDIOBJ oldBrush = SelectObject(hdc, newBrush);
			HGDIOBJ oldPen = SelectObject(hdc, newPen);
			oldBrush = SelectObject(hdc, GetStockObject(BLACK_BRUSH));
			MoveToEx(hdc, clientRect.right / 2, clientRect.bottom, NULL);
			LineTo(hdc, 0, 0);
			MoveToEx(hdc, clientRect.right / 2, clientRect.bottom, NULL);
			LineTo(hdc, clientRect.right, 0);
			MoveToEx(hdc, clientRect.right / 2, clientRect.bottom, NULL);
			LineTo(hdc, clientRect.right / 2, 0);
			MoveToEx(hdc, clientRect.right / 2, clientRect.bottom, NULL);
			LineTo(hdc, 0, clientRect.bottom / 2);
			MoveToEx(hdc, clientRect.right / 2, clientRect.bottom, NULL);
			LineTo(hdc, clientRect.right, clientRect.bottom / 2);
			MoveToEx(hdc, clientRect.right / 2, clientRect.bottom, NULL);
			LineTo(hdc, clientRect.right / 4, 0);
			MoveToEx(hdc, clientRect.right / 2, clientRect.bottom, NULL);
			LineTo(hdc, 3 * clientRect.right / 4, 0);

			MoveToEx(hdc, clientRect.right / 2, clientRect.bottom, NULL);
			LineTo(hdc, 0, 3 * clientRect.bottom / 4);
			MoveToEx(hdc, clientRect.right / 2, clientRect.bottom, NULL);
			LineTo(hdc, clientRect.right, 3 * clientRect.bottom / 4);

			MoveToEx(hdc, clientRect.right / 2, clientRect.bottom, NULL);
			LineTo(hdc, 0, clientRect.bottom);
			MoveToEx(hdc, clientRect.right / 2, clientRect.bottom, NULL);
			LineTo(hdc, clientRect.right, clientRect.bottom);
			SelectObject(hdc, newBrush);



			Chord(
				hdc,
				clientRect.right / 2 - SizeOfSun,
				clientRect.bottom + SizeOfSun,
				clientRect.right / 2 + SizeOfSun,
				clientRect.bottom - SizeOfSun,
				clientRect.right / 2 + SizeOfSun,
				clientRect.bottom,
				clientRect.right / 2 - SizeOfSun,
				clientRect.bottom);

			SelectObject(hdc, oldPen);
			SelectObject(hdc, oldBrush);

			DeleteObject(newPen);
			DeleteObject(newBrush);
		}

		if ((flagSun == 0) && (flagNight == 0) && (flagStars == 0))
		{
			FillRect(hdc, &clientRect, CreateSolidBrush(RGB(0, 0, 255)));
		}

		if ((flagSun == 0) && (flagNight == 1) && (flagStars == 0))
		{
			FillRect(hdc, &clientRect, CreateSolidBrush(RGB(0, 0, 0)));
		}

		if ((flagSun == 0) && (flagNight == 1) && (flagStars == 1))
		{
			int i;
			for (i = 0; i < nstar - 1; i++)
			{
				SetPixel(hdc, star[i][1], star[i][2], RGB(255, 255, 255));
			}
		}

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		if (flagSun == 1)
		{
			GetClientRect(hWnd, &clientRect);
			flagSun = 0;
			InvalidateRect(hWnd, &clientRect, FALSE);
		}

	}
	break;
	case WM_RBUTTONDOWN:
	{
		if ((flagStars == 0) && (flagNight == 1) && (flagSun == 0))
		{
			flagStars = 1;
			GetClientRect(hWnd, &clientRect);
			InvalidateRect(hWnd, &clientRect, FALSE);
		}
		if ((flagStars == 0) && (flagNight == 0) && (flagSun == 0))
		{
			flagNight = 1;
			GetClientRect(hWnd, &clientRect);
			InvalidateRect(hWnd, &clientRect, FALSE);
		}

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