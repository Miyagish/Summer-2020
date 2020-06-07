

#include "framework.h"
#include "Lab3.h"
#include <ctime>
#include <string>
#define MAX_LOADSTRING 100
using namespace std;


HINSTANCE hInst;  
const RECT rect = { 50, 50 , 850, 650 };
const int UpOtstup = 50;
const int LeftOtstup = 50;
int GoUp = 0;
int GoDown = 0;
int GoLeft = 0;
int GoRight = 0;
int HeadX = 5;
int HeadY = 1;
int SizeOfCell = 40;
int Snake[300][2];
int SnakeLength = 5;
int FoodX = 0;
int FoodY = 0;
int SnakeGrow = -1;
int StartGame = 0;
int Crash = 0;
int Level = 200;
int Score = 0;
wstring EndGameMessage;
COLORREF PixelColor = RGB(0, 0, 0);
COLORREF SnakeColor = RGB(175, 238, 238);
COLORREF FoodColor = RGB(70, 130, 180);
COLORREF BackgroundColor = RGB(173, 216, 230);



TCHAR szTitle[MAX_LOADSTRING] = _T("Змейка");
TCHAR szWindowClass[MAX_LOADSTRING] = _T("Windowclass1");

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

BOOL CALLBACK       FunKnopka(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

   
    for (int i = 1; i <= 5; i++)
    {
        Snake[i][0] = 1 + (5 - i);
        Snake[i][1] = 1;
    }
    for (int i = 6; i <= 255; i++)
    {
        Snake[i][0] = -1;
        Snake[i][1] = -1;
    }
    srand(time(NULL));
    FoodX = 6 + rand() % 14;
    FoodY = 2 + rand() % 13;
 
    MyRegisterClass(hInstance);

  
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB3));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDR_MENU1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_DLGFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZE,
       0, 0, 920, 800, nullptr, nullptr, hInstance, nullptr);

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
            switch (wParam)
            {
            case ID_PaleTurquoise:
                SnakeColor = RGB(175, 238, 238);
                break;

            case ID_Turquoise:
                SnakeColor = RGB(64, 224, 208);
                break;

            case ID_MediumPurple:
                SnakeColor = RGB(147, 112, 219);
                break;

            case ID_SlateBlue:
                SnakeColor = RGB(106, 90, 205);
                break;

            case ID_ROYALBLUE:
                FoodColor = RGB(65, 105, 225);
                break;

            case ID_INDIGO:
                FoodColor = RGB(75, 0, 130);
                break;

            case ID_VIOLET:
                FoodColor = RGB(238, 130, 238);
                break;

            case ID_TEAL:
                FoodColor = RGB(0, 128, 128);
                break;

            case ID_START:
                StartGame = 1;
                InvalidateRect(hWnd, &rect, TRUE);
                break;
            
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;

            case ID_RED:
                SnakeColor = RGB(255, 0, 0);
                break;

            case ID_BLUE:
                SnakeColor = RGB(0, 255, 0);
                break;

            case ID_GREEN:
                SnakeColor = RGB(0, 0, 255);
                break;
            case ID_RED1:
                FoodColor = RGB(255, 0, 0);
                break;
            case ID_BLUE1:
                FoodColor = RGB(0, 255, 0);
                break;
            case ID_GREEN1:
                FoodColor = RGB(0, 0, 255);
                break;



            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            ENDGAME:
            HDC hdc = BeginPaint(hWnd, &ps);
            HBRUSH BackgroundBrush = CreateSolidBrush(BackgroundColor);
            SelectObject(hdc, BackgroundBrush);
            Rectangle(hdc, LeftOtstup, UpOtstup, 850, 650);
            DeleteObject(BackgroundBrush);
            for (int i = 1; i <= 14; i++)
            {
                for (int j = 1; j <= 19; j++)
                {
                    SetPixel(hdc, SizeOfCell* j+LeftOtstup, SizeOfCell * i+UpOtstup, PixelColor);
                }
            }
            if (StartGame)
            {
                if (SnakeGrow > 0) SnakeGrow--;
                if (SnakeGrow == 0)
                {
                    // SnakeLength++;
                    Snake[SnakeLength][0] = Snake[SnakeLength - 1][0];
                    Snake[SnakeLength][1] = Snake[SnakeLength - 1][1];
                    SnakeGrow--;
                }
                if (GoLeft) HeadX--;
                if (GoRight) HeadX++;
                if (GoUp) HeadY--;
                if (GoDown) HeadY++;
                if (GoLeft | GoRight | GoUp | GoDown)
                {
                    for (int i = SnakeLength; i >= 2; i--)
                    {
                        Snake[i][0] = Snake[i - 1][0];
                        Snake[i][1] = Snake[i - 1][1];
                    }
                }
                Snake[1][0] = HeadX;
                Snake[1][1] = HeadY;
                for (int i = 2; i <= SnakeLength; i++)
                {
                    if ((Snake[i][0] == HeadX) && (Snake[i][1] == HeadY))
                    {
                        Crash = 1;
                    }
                }
                if ((HeadX == 21) || (HeadX == 0) || (HeadY == 16) || (HeadY == 0) || Crash)
                {
                    for (int i = 1; i <= 5; i++)
                    {
                        Snake[i][0] = 1 + (5 - i);
                        Snake[i][1] = 1;
                    }
                    for (int i = 6; i <= 255; i++)
                    {
                        Snake[i][0] = -1;
                        Snake[i][1] = -1;
                    }
                    FoodX = 6 + rand() % 14;
                    FoodY = 2 + rand() % 13;
                    GoUp = 0;
                    GoDown = 0;
                    GoLeft = 0;
                    GoRight = 0;
                    HeadX = 5;
                    HeadY = 1;
                    SnakeLength = 5;
                    Crash = 0;
                    StartGame = 0;
                    EndGameMessage = L"КОНЕЦ ИГРЫ!\nСчёт: " + to_wstring(Score);
                    Score = 0;
                    MessageBox(hWnd, EndGameMessage.c_str(), L"Произошла смерть", MB_ICONINFORMATION);
                    goto ENDGAME;
                }
                
                if (HeadX == FoodX && HeadY == FoodY)
                {
                    Score++;
                    SnakeLength++;
                    SnakeGrow = SnakeLength;
                    //srand(time(NULL));
                    int BadFood = 1;
                    while (BadFood == 1)
                    {
                        FoodX = 1 + rand() % 19;
                        FoodY = 1 + rand() % 14;
                        for (int j = 1; j <= SnakeLength - 1; j++)
                        {
                            if (!((Snake[j][0] == FoodX) && (Snake[j][1] == FoodY)))
                            {
                                BadFood = 0;
                                break;
                            }
                        }
                    }
                }
                HBRUSH SnakeBrush = CreateSolidBrush(SnakeColor);
                SelectObject(hdc, SnakeBrush);
                Rectangle(hdc,
                    LeftOtstup + SizeOfCell * Snake[1][0] - (SizeOfCell - 2),
                    UpOtstup + SizeOfCell * Snake[1][1] - (SizeOfCell - 2),
                    LeftOtstup + SizeOfCell * Snake[1][0] - (SizeOfCell - 38),
                    UpOtstup + SizeOfCell * Snake[1][1] - (SizeOfCell - 38));
                for (int i = 2; i <= SnakeLength; i++)
                {
                    Rectangle(hdc,
                        LeftOtstup + SizeOfCell * Snake[i][0] - (SizeOfCell - 8),
                        UpOtstup + SizeOfCell * Snake[i][1] - (SizeOfCell - 8),
                        LeftOtstup + SizeOfCell * Snake[i][0] - (SizeOfCell - 32),
                        UpOtstup + SizeOfCell * Snake[i][1] - (SizeOfCell - 32));
                }
                HBRUSH FoodBrush = CreateSolidBrush(FoodColor);
                SelectObject(hdc, FoodBrush);
                Ellipse(hdc,
                    LeftOtstup + SizeOfCell * FoodX - (SizeOfCell - 15),
                    UpOtstup + SizeOfCell * FoodY - (SizeOfCell - 15),
                    LeftOtstup + SizeOfCell * FoodX - (SizeOfCell - 25),
                    UpOtstup + SizeOfCell * FoodY - (SizeOfCell - 25));
                Sleep(Level);
                InvalidateRect(hWnd, &rect, TRUE);
                DeleteObject(SnakeBrush);
                DeleteObject(FoodBrush);
            }
            EndPaint(hWnd, &ps);
        }
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_LEFT:
            if (!GoRight)
            {
                GoUp = 0;
                GoDown = 0;
                GoLeft = 1;
                GoRight = 0;
            }
                break;

        case VK_RIGHT:
            if (!GoLeft)
            {
                GoUp = 0;
                GoDown = 0;
                GoLeft = 0;
                GoRight = 1;
                break;
            }
        case VK_UP:
            if (!GoDown)
            {
                GoUp = 1;
                GoDown = 0;
                GoLeft = 0;
                GoRight = 0;
            }
                break;

        case VK_DOWN:
            if (!GoUp)
            {
                GoUp = 0;
                GoDown = 1;
                GoLeft = 0;
                GoRight = 0;
                break;
            }
        default:
            break;
        }
    }
    break;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}