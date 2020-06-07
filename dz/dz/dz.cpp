

#include "framework.h"
#include "dz.h"
#include <math.h>

#define MAX_LOADSTRING 100
float size = 1;

HINSTANCE hInst;                                
WCHAR szTitle[MAX_LOADSTRING];                  
WCHAR szWindowClass[MAX_LOADSTRING];            


ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    

    
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DZ, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DZ));

    MSG msg;

    
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}




ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DZ));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DZ);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; 

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            
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
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;     
            HDC hdc = GetDC(hWnd);
            MoveToEx(hdc, 0, 400, NULL);
            LineTo(hdc, 10000, 400);
            MoveToEx(hdc, 600, 0, NULL);
            LineTo(hdc, 600, 10000);
            for (int i = -30; i < 30; i++) {
                MoveToEx(hdc, 590, 400 + (i * 60 * size), NULL);
                LineTo(hdc, 610, 400 + (i * 60 * size));
            }
            for (int i = -30; i < 30; i++) {
                MoveToEx(hdc, 600 + (i * 60 * size), 390, NULL);
                LineTo(hdc, 600 + (i * 60 * size), 410);
            }
           /* TextOut(hdc, 610, 410, _T("0"), 1);*/

            float  r = 7;

            /*for (size_t i = 1; i <= 78; i += 7) {
                WCHAR Coord[5];
                wsprintf(Coord, TEXT("-%d"), i);
                TextOut(hdc, 620, 400 + r*i, Coord, 3);
                TextOut(hdc, 600 - r * i, 410, Coord, 3);
                wsprintf(Coord, TEXT("%d"), i);
                TextOut(hdc, 600 + r * i, 410, Coord, 3);
                TextOut(hdc, 620, 400 - r * i, Coord, 3);*/
           /* } */
            for (float t = -77; t < 77;t += 0.1) {
                float y = (5.4 * cos(t) + 5 * cos((5.4 / 2.3) * t))*size;
                float x = (5.4 * sin(t) + 51 * sin((5.4 / 2.3) * t))*size;
                if (t == -77)
                    MoveToEx(hdc, 10 * x + 600, 10 * y + 400, NULL);
                else
                    LineTo(hdc, 10 * x + 600, 10 * y + 400);
            }

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_LBUTTONDOWN:
    {
        size -= 0.05;
        RECT rect;

        GetWindowRect(hWnd, &rect);
        rect.left = 0;
        InvalidateRect(hWnd, &rect, true);
    }
    break;
    case WM_RBUTTONDOWN:
    {
        size += 0.05;
        RECT rect;

        GetWindowRect(hWnd, &rect);
        rect.left = 0;
        InvalidateRect(hWnd, &rect, true);
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
