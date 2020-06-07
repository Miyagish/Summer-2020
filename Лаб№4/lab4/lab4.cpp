

#include "framework.h"
#include "lab4.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

#define MAX_LOADSTRING 100
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
    LoadStringW(hInstance, IDC_LAB4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

  
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB4));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB4));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB4);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


HWND hWnd;
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; 

   srand(time(0));
   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}



HANDLE thread_1;
HANDLE thread_2;

bool t1 = true;
bool t2 = true;

std::vector<int> v;
DWORD WINAPI thread1(LPVOID t) {
    Sleep(1000);
    std::srand(time(NULL));
    std::ofstream f("DATA.txt");
    for (int i = 0; i < 20; i++) f <<50 + rand() % 500 << " ";
    f.close();
    std::ifstream openf("DATA.txt");
    while (!openf.eof())
    {
        int a;
        openf >> a;
        v.push_back(a);
    }

    RECT rect;
    GetClientRect(hWnd, &rect);
    HDC hdc = GetDC(hWnd);
    while (t1) {
        for (size_t i = 0; i < v.size(); i++) {
            WCHAR m[10];
            wsprintf(m, TEXT("%d"), v[i]);
            TextOut(hdc, rect.right - 200, rect.top/2+50 + i*20, (LPWSTR)m, 3);
        }
    Sleep(200);
    }
    return 0;
}

int red = 0, g = 0, b = 0;


DWORD WINAPI thread2(LPVOID t) {
    HDC hdc = GetDC(hWnd);
    float x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    while (t2) {
        for (size_t i = 0; i < v.size(); i++) {
            red = rand() % 255;
            g = rand() % 255;
            b = rand() % 255;

            HBRUSH brush = CreateSolidBrush(RGB(red, g, b));
            SelectObject(hdc, brush);
            
            Rectangle(hdc, 50+i*20, 10, 60+i*20, 10+v[i]);

            DeleteObject(brush);
        }
        Sleep(200);
    }
    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case ID_THREAD1ON:
                t1 = true;
                thread_1 = CreateThread(NULL, 0, &thread1, NULL, 0, NULL);
                break;
            case ID_THREAD1OFF:
                v.clear();
                TerminateThread(thread_1, NULL);
                TerminateThread(thread_2, NULL);
                t2 = false;
                t1 = false;
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            case ID_THREAD2ON:
                t2 = true;
                thread_2 = CreateThread(NULL, 0, &thread2, NULL, 0, NULL);
                break;
            case ID_THREAD2OFF:
                TerminateThread(thread_2, NULL);
                t2 = false;
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
      
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
