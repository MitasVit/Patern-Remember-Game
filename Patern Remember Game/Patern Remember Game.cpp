// Patern Remember Game.cpp : Definuje vstupní bod pro aplikaci.
//

#include "framework.h"
#include "Patern Remember Game.h"
#include "resource.h"

#pragma comment(lib, "Dwmapi.lib")

#define _CRT_SECURE_NO_WARNINGS

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"") 

#define MAX_LOADSTRING 100

// Globální proměnné:
HINSTANCE g_hinst;
HINSTANCE hInst;                                // aktuální instance
WCHAR szTitle[MAX_LOADSTRING];                  // Text záhlaví
WCHAR szWindowClass[MAX_LOADSTRING];            // název třídy hlavního okna
const wchar_t CLASS_NAME[] = L"Sample Window Class";


HWND hWnd1;
HWND hWnd2;

HWND Button, Text, Button2;
HWND check, dif1, dif2, dif3;
HWND hWndProgressBar;
string txt1, txt2;

 bool draw = false;
 bool draw0 = true;
 bool draw2 = false;
 bool usedR = false;
 bool usedB = false;
 bool usedG = false;
 bool usedY = false;
 bool usedGy = false;
 bool load = false;
 bool load2 = false;
 bool draw3 = false;
 int diff_time = 0;

// Předat dál deklarace funkcí zahrnuté v tomto modulu kódu:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    No(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Right(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK    WindowProc(HWND, UINT, WPARAM, LPARAM);



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Inicializovat globální řetězce
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PATERNREMEMBERGAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Provést inicializaci aplikace:

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PATERNREMEMBERGAME));

    MSG msg;

    // Hlavní smyčka zpráv:
    while (GetMessage(&msg, nullptr, 0, 0))
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


    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = g_hinst;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    WNDCLASSEXW wcex;
    HBRUSH br = CreateSolidBrush(RGB(255, 255, 255));
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PATERNREMEMBERGAME));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = br;
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PATERNREMEMBERGAME);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Uloží popisovač instance do naší globální proměnné.
    hWnd1 = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
    COLORREF NewColor = RGB(255, 255, 255);
    int flag = COLOR_CAPTIONTEXT;
    ::SetSysColors(1, &flag, &NewColor);
    if (!hWnd1)
    {
        return FALSE;
    }

    hWnd2 = CreateWindowW(CLASS_NAME, L"loading", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 250, 250, nullptr, nullptr, g_hinst, nullptr);

    ShowWindow(hWnd2, nCmdShow);

    ShowWindow(hWnd1, SW_HIDE);
    UpdateWindow(hWnd1);


    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    RECT rc;
    HDC hdc;
    POINT cursor;
    RECT pos;
    RECT size;
 
    static POINT p;
    static int sec = 0;
    static int pres2 = 0;
    bool onB = false;

    switch (message)
    {
    case WM_CREATE:
    {

#ifdef INDEX_DEBUG
        IndexFileCreate3(enter);
        IndexFileCreate();
#endif
//#ifdef MUJ_COMP
        HBITMAP play = LoadBitmap((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDB_PLAY)); //Here we have to use the executable module to load our bitmap resource
       /* HBITMAP play = (HBITMAP)LoadImage(0, TEXT("C:\\Users\\Uzivatel\\Desktop\\2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
#else
#pragma warning(suppress : 4996)
        string tm = "C:/Program Files/Patern Remember Game/2.bmp";
        HBITMAP play = (HBITMAP)LoadImageA(0, tm.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
#endif */

       
      //  Generate();

        GetClientRect(hWnd, &rc);
        int tmpW = rc.bottom;
        int tmpH = rc.right;
        Button = CreateWindow(
            L"BUTTON",
            L"Play",
              WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_VCENTER | BS_BITMAP,
            350,         // x position 
            200,         // y position 
            125,        // Button width
            50,        // Button height
            hWnd,
            NULL,
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);
        SendMessageA(Button, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)play);
#ifdef DEBUG
        string client_area = to_string(rc.bottom);
        string client_area2 = to_string(rc.right);
        wstring stemp = stringToWstring(client_area);
        LPCWSTR result = stemp.c_str();
        wstring stemp2 = stringToWstring(client_area2);
        LPCWSTR result2 = stemp2.c_str();

        MessageBox(NULL, result, L"vyska", MB_OK);
        MessageBox(NULL, result2, L"sirka", MB_OK);
#endif // DEBUG


        hdc = BeginPaint(hWnd, &ps);
    }break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case ID_BLUE:
            draw2 = false;
            usedR = false;
            usedB = true;
            usedG = false;
            usedY = false;
            usedGy = false;
            InvalidateRect(hWnd, NULL, FALSE);
            break;
        case ID_RED:
            draw2 = false;
            usedR = true;
            usedB = false;
            usedG = false;
            usedY = false;
            usedGy = false;
            InvalidateRect(hWnd, NULL, FALSE);
            break;
        case ID_YELLOW:
            draw2 = false;
            usedR = false;
            usedB = false;
            usedG = false;
            usedY = true;
            usedGy = false;
            InvalidateRect(hWnd, NULL, FALSE);
            break;
        case ID_GREEN:
            draw2 = false;
            usedR = false;
            usedB = false;
            usedG = true;
            usedY = false;
            usedGy = false;
            InvalidateRect(hWnd, NULL, FALSE);
            break;
        case ID_ERASE:
            draw2 = false;
            usedR = false;
            usedB = false;
            usedG = false;
            usedY = false;
            usedGy = true;
            InvalidateRect(hWnd, NULL, FALSE);
            break;
        case IDM_ABOUT: //104
#ifdef DEBUG
            MessageBox(NULL, L"about button in menu pressed", L"IDM_ABOUT", MB_OK);
#endif 
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_NO:
          //  load_text(txt1, txt2);
            DialogBox(hInst, MAKEINTRESOURCE(IDD_NO), hWnd, No);
            break;
        case IDM_RIGHT:
          //  load_text(txt1, txt2);
            DialogBox(hInst, MAKEINTRESOURCE(IDD_RIGHT), hWnd, Right);
            break;
        case ID_DIF1:
            diff = 1;
            load2 = true;
            SendMessage(hWnd, WM_COMMAND, BN_CLICKED, 0);
            break;
        case ID_DIF2:
            diff = 2;
            load2 = true;
            SendMessage(hWnd, WM_COMMAND, BN_CLICKED, 0);
            break;
        case ID_DIF3:
            diff = 3;
            load2 = true;
            SendMessage(hWnd, WM_COMMAND, BN_CLICKED, 0);
            break;
        case IDM_EXIT: //105
#ifdef DEBUG
            MessageBox(NULL, L"exitting app", L"IDM_EXIT", MB_OK);
#endif 
            DestroyWindow(hWnd);
            break;
        case BN_CLICKED: //0
#ifdef DEBUG
            MessageBox(NULL, L"play pressed", L"BN_CLICKED", MB_OK);
#endif

            if (load == false) {
                if (load2 == false) {
                    draw0 = false;
                    draw3 = true;
                    RedrawWindow(hWnd, 0, 0, RDW_INVALIDATE);
                    DestroyWindow(Button);
                    dif1 = CreateWindow(
                        L"BUTTON",
                        L"difficulty 1",
                        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_VCENTER,
                        350,         // x position 
                        200,         // y position 
                        125,        // Button width
                        50,        // Button height
                        hWnd,
                        (HMENU)ID_DIF1,
                        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                        NULL);
                    dif2 = CreateWindow(
                        L"BUTTON",
                        L"difficulty 2",
                        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_VCENTER,
                        350,         // x position 
                        260,         // y position 
                        125,        // Button width
                        50,        // Button height
                        hWnd,
                        (HMENU)ID_DIF2,
                        NULL,
                        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                        NULL);
                    dif3 = CreateWindow(
                        L"BUTTON",
                        L"difficulty 3",
                        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_VCENTER,
                        350,         // x position 
                        320,         // y position 
                        125,        // Button width
                        50,        // Button height
                        hWnd,
                        (HMENU)ID_DIF3,
                        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                        NULL);
                }if (load2 == true) {
                    Generate();
#ifdef INDEX_DEBUG
                    IndexFileCreate5();
                    IndexFileCreate2();
#endif
#pragma warning(suppress : 4996)
                    //C:\Program Files
                    string tm = "C:/Program Files/Patern Remember Game/play.txt";
                    if (FileExist(tm.c_str()) == false) {
                        MessageBox(NULL, L"You have to remember the squares\nin the table(the color and position-by the numlock).\nYou have 5 seconds to do it.\nIf the screen is loaded and you see the\nempty table you will click the \"A\", this means\nyou have started to performancing the tabel\nto do this pres the letter for color and then number\non numlock for pos(pos in numlock keyboard).\nIf you are done you will click on \"check\".\nYou will see if you have all answers right and you \ncan quit or play again or show the right answers.", L"How to play", MB_OK);
                    }
                    draw3 = false;
                    RedrawWindow(hWnd, 0, 0, RDW_INVALIDATE);
                    DestroyWindow(dif1);
                    DestroyWindow(dif2);
                    DestroyWindow(dif3);
                    check = CreateWindow(
                        L"BUTTON",
                        L"check",
                        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_VCENTER,
                        400,         // x position 
                        270,         // y position 
                        200,        // Button width
                        100,        // Button height
                        hWnd,
                        NULL,
                        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
                        NULL);
                    draw = true;

                    load = true;
                    RedrawWindow(hWnd, 0, 0, RDW_INVALIDATE);
                }
            }
            else {
#ifdef INDEX_DEBUG
                IndexFileCreate4(enter);
#endif
                if (Good(enter) == true) {
                    SendMessage(hWnd1, WM_COMMAND, IDM_RIGHT, 0);
                   // MessageBoxA(NULL, "You have all answers right, congratulation!", "Info", MB_OK);
                }
                else {
                    SendMessage(hWnd1, WM_COMMAND, IDM_NO, 0);
                   // MessageBoxA(NULL, "You haven't got all answers right, never mind, it will be better next time!", "Info", MB_OK);
                }
            }
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_TIMER:
    {
        switch ((UINT)wParam)
        {
        case IDT_TIMER2:
        {
            KillTimer(hWnd, IDT_TIMER2);
            sec++;
            RedrawWindow(hWnd, 0, 0, RDW_INVALIDATE);

        }break;
        }
    }break;
    case WM_CONTEXTMENU:
    {
        pos.left = 0;
        pos.bottom = 0;
        pos.right = 0;
        pos.top = 0;
        cursor.x = 0;
        cursor.y = 0;

        GetCursorPos(&cursor);
        GetWindowRect(hWnd, &pos);
        HMENU hPopupMenu = CreatePopupMenu();
        InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, IDM_ABOUT, _T("About"));
        InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, IDM_EXIT, _T("Exit"));
        if (cursor.y > (pos.top + 195) && cursor.x > (pos.left + 55) && cursor.y < (pos.top + 235) && cursor.x < (pos.left + 95)) {
            pres2 = 1;
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_BLUE, _T("Create Blue square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_YELLOW, _T("Create Yellow square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_GREEN, _T("Create Green square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_RED, _T("Create Red square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_ERASE, _T("Erase square"));
        }
        else if (cursor.y > (pos.top + 195) && cursor.x > (pos.left + 105) && cursor.y < (pos.top + 235) && cursor.x < (pos.left + 145)) {
            pres2 = 2;
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_BLUE, _T("Create Blue square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_YELLOW, _T("Create Yellow square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_GREEN, _T("Create Green square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_RED, _T("Create Red square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_ERASE, _T("Erase square"));
        }
        else if (cursor.y > (pos.top + 195) && cursor.x > (pos.left + 155) && cursor.y < (pos.top + 235) && cursor.x < (pos.left + 195)) {
            pres2 = 3;
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_BLUE, _T("Create Blue square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_YELLOW, _T("Create Yellow square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_GREEN, _T("Create Green square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_RED, _T("Create Red square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_ERASE, _T("Erase square"));
            
        }
        else if (cursor.y > (pos.top + 155) && cursor.x > (pos.left + 55) && cursor.y < (pos.top + 195) && cursor.x < (pos.left + 95)) {
            pres2 = 4;
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_BLUE, _T("Create Blue square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_YELLOW, _T("Create Yellow square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_GREEN, _T("Create Green square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_RED, _T("Create Red square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_ERASE, _T("Erase square"));
            
        }
        else if (cursor.y > (pos.top + 155) && cursor.x > (pos.left + 105) && cursor.y < (pos.top + 185) && cursor.x < (pos.left + 145)) {
            pres2 = 5;
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_BLUE, _T("Create Blue square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_YELLOW, _T("Create Yellow square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_GREEN, _T("Create Green square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_RED, _T("Create Red square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_ERASE, _T("Erase square"));
            
        }
        else if (cursor.y > (pos.top + 145) && cursor.x > (pos.left + 155) && cursor.y < (pos.top + 195) && cursor.x < (pos.left + 195)) {
            pres2 = 6;
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_BLUE, _T("Create Blue square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_YELLOW, _T("Create Yellow square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_GREEN, _T("Create Green square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_RED, _T("Create Red square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_ERASE, _T("Erase square"));
            
        }
        else if (cursor.y > (pos.top + 95) && cursor.x > (pos.left + 55) && cursor.y < (pos.top + 135) && cursor.x < (pos.left + 95)) {
            pres2 = 7;
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_BLUE, _T("Create Blue square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_YELLOW, _T("Create Yellow square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_GREEN, _T("Create Green square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_RED, _T("Create Red square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_ERASE, _T("Erase square"));
            
        }
        else if (cursor.y > (pos.top + 95) && cursor.x > (pos.left + 105) && cursor.y < (pos.top + 135) && cursor.x < (pos.left + 145)) {
            pres2 = 8;
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_BLUE, _T("Create Blue square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_YELLOW, _T("Create Yellow square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_GREEN, _T("Create Green square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_RED, _T("Create Red square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_ERASE, _T("Erase square"));
            
        }
        else if (cursor.y > (pos.top + 95) && cursor.x > (pos.left + 155) && cursor.y < (pos.top + 135) && cursor.x < (pos.left + 195)) {
            pres2 = 9;
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_BLUE, _T("Create Blue square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_YELLOW, _T("Create Yellow square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_GREEN, _T("Create Green square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_RED, _T("Create Red square"));
                InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, ID_ERASE, _T("Erase square"));
            
        }
        SetForegroundWindow(hWnd);
        TrackPopupMenu(hPopupMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN, cursor.x, cursor.y, 0, hWnd, NULL);
    }break;
    case WM_LBUTTONDOWN:
    {
        pos.left = 0;
        pos.bottom = 0;
        pos.right = 0;
        pos.top = 0;
        cursor.x = 0;
        cursor.y = 0;
        
        GetCursorPos(&cursor);
        GetWindowRect(hWnd, &pos);
        string tmp4 = ToString(pos.left);
        tmp4 = tmp4 + "-left, " + ToString(pos.bottom) + "-bottom, " + ToString(pos.right) + "-right, " + ToString(pos.top) + "-top";
        string tmp1 = ToString(cursor.x), tmp2 = ToString(cursor.y);
        tmp1 = tmp1 + "x";
        tmp2 = tmp2 + "y";
        string tmp3 = tmp1 + tmp2;

#ifdef DEBUG
        MessageBoxA(NULL, tmp3.c_str(), "Cursor position", MB_OK);//DEBUG
        MessageBoxA(NULL, tmp4.c_str(), "Window position", MB_OK);//DEBUG
#endif
        if (cursor.y > (pos.top + 100 +40) && cursor.x > (pos.left + 500 ) && cursor.y < (pos.top + 150+40) && cursor.x < (pos.left + 550)) {
#ifdef DEBUG
            MessageBoxA(NULL, "YES", "YES", MB_OK);
#endif
            draw2 = false;
            usedR = true;
            usedB = false;
            usedG = false;
            usedY = false;
            usedGy = false;
            InvalidateRect(hWnd, NULL, FALSE);
        }else if (cursor.y > (pos.top + 200 + 40) && cursor.x > (pos.left + 500) && cursor.y < (pos.top + 250 +40) && cursor.x < (pos.left + 550)) {
            draw2 = false;
            usedR = false;
            usedB = false;
            usedG = true;
            usedY = false;
            usedGy = false;
            InvalidateRect(hWnd, NULL, FALSE);
        }
        else if (cursor.y > (pos.top + 200 + 40) && cursor.x > (pos.left + 600) && cursor.y < (pos.top + 250 + 40) && cursor.x < (pos.left + 650)) {
            draw2 = false;
            usedR = false;
            usedB = false;
            usedG = false;
            usedY = true;
            usedGy = false;
            InvalidateRect(hWnd, NULL, FALSE);
        }
        else if (cursor.y > (pos.top + 140) && cursor.x > (pos.left + 600) && cursor.y < (pos.top + 190) && cursor.x < (pos.left + 650)) {
            draw2 = false;
            usedR = false;
            usedB = true;
            usedG = false;
            usedY = false;
            usedGy = false;
            InvalidateRect(hWnd, NULL, FALSE);
        }
        else if (cursor.y > (pos.top + 140) && cursor.x > (pos.left + 700) && cursor.y < (pos.top + 190) && cursor.x < (pos.left + 750)) {
            draw2 = false;
            usedR = false;
            usedB = false;
            usedG = false;
            usedY = false;
            usedGy = true;
            InvalidateRect(hWnd, NULL, FALSE);
        }
        else if (cursor.y > (pos.top + 195) && cursor.x > (pos.left + 55) && cursor.y < (pos.top + 235) && cursor.x < (pos.left + 95)) {
            pres2 = 1;
            if (usedR == true || usedB == true || usedY == true || usedG == true || usedGy == true) {
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        else if (cursor.y > (pos.top + 195) && cursor.x > (pos.left + 105) && cursor.y < (pos.top + 235) && cursor.x < (pos.left + 145)) {
            pres2 = 2;
            if (usedR == true || usedB == true || usedY == true || usedG == true || usedGy == true) {
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        else if (cursor.y > (pos.top + 195) && cursor.x > (pos.left + 155) && cursor.y < (pos.top + 235) && cursor.x < (pos.left + 195)) {
            pres2 = 3;
            if (usedR == true || usedB == true || usedY == true || usedG == true || usedGy == true) {
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        else if (cursor.y > (pos.top + 155) && cursor.x > (pos.left + 55) && cursor.y < (pos.top + 195) && cursor.x < (pos.left + 95)) {
            pres2 = 4;
            if (usedR == true || usedB == true || usedY == true || usedG == true || usedGy == true) {
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        else if (cursor.y > (pos.top + 155) && cursor.x > (pos.left + 105) && cursor.y < (pos.top + 185) && cursor.x < (pos.left + 145)) {
            pres2 = 5;
            if (usedR == true || usedB == true || usedY == true || usedG == true || usedGy == true) {
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        else if (cursor.y > (pos.top + 145) && cursor.x > (pos.left + 155) && cursor.y < (pos.top + 195) && cursor.x < (pos.left + 195)) {
            pres2 = 6;
            if (usedR == true || usedB == true || usedY == true || usedG == true || usedGy == true) {
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        else if (cursor.y > (pos.top + 95) && cursor.x > (pos.left + 55) && cursor.y < (pos.top + 135) && cursor.x < (pos.left + 95)) {
            pres2 = 7;
            if (usedR == true || usedB == true || usedY == true || usedG == true || usedGy == true) {
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        else if (cursor.y > (pos.top + 95) && cursor.x > (pos.left + 105) && cursor.y < (pos.top + 135) && cursor.x < (pos.left + 145)) {
            pres2 = 8;
            if (usedR == true || usedB == true || usedY == true || usedG == true || usedGy == true) {
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        else if (cursor.y > (pos.top + 95) && cursor.x > (pos.left + 155) && cursor.y < (pos.top + 135) && cursor.x < (pos.left + 195)) {
            pres2 = 9;
            if (usedR == true || usedB == true || usedY == true || usedG == true || usedGy == true) {
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }

    }break;
    case WM_KEYDOWN:
    {
        if (wParam == 0x41)//A
        {
            draw2 = false;
            usedR = true;
            usedB = false;
            usedG = false;
            usedY = false;
            usedGy = false;
            InvalidateRect(hWnd, NULL, FALSE);
        }
        else if (wParam == 0x42) {//B
            draw2 = false;
            usedB = false;
            usedR = false;
            usedG = true;
            usedY = false;
            usedGy = false;
            InvalidateRect(hWnd, NULL, FALSE);
        }
        else if (wParam == 0x43) {//C
            usedR = false;
            usedB = true;
            usedG = false;
            usedY = false;
            usedGy = false;
            InvalidateRect(hWnd, NULL, FALSE);
        }
        else if (wParam == 0x44) {//D
            usedR = false;
            usedB = false;
            usedG = false;
            usedGy = false;
            usedY = true;
            InvalidateRect(hWnd, NULL, FALSE);
        }
        else if (wParam == 0x45) {//E
            usedR = false;
            usedB = false;
            usedG = false;
            usedY = false;
            usedGy = true;
            InvalidateRect(hWnd, NULL, FALSE);
        }
        else if (wParam == 0x31 || wParam == 0x61) {//1
            pres2 = 1;
           if (usedR == true || usedB == true || usedY == true || usedG == true || usedGy == true) {
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        else if (wParam == 0x32 || wParam == 0x62) {//2
            pres2 = 2;
            if (usedR == true || usedB == true || usedY == true || usedG == true || usedGy == true) {
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        else if (wParam == 0x33 || wParam == 0x63) {//3
            pres2 = 3;
            if (usedR == true || usedB == true || usedY == true || usedG == true || usedGy == true) {
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        else if (wParam == 0x34 || wParam == 0x64) {//4
            pres2= 4;
            if (usedR == true || usedB == true || usedY == true || usedG == true || usedGy == true) {
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        else if (wParam == 0x35 || wParam == 0x65) {//5
            pres2 = 5;
            if (usedR == true || usedB == true || usedY == true || usedG == true || usedGy == true) {
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        else if (wParam == 0x36 || wParam == 0x66) {//6
            pres2 = 6;
            if (usedR == true || usedB == true || usedY == true || usedG == true || usedGy == true) {
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        else if (wParam == 0x37 || wParam == 0x67) {//7
            pres2 = 7;
            if (usedR == true || usedB == true || usedY == true || usedG == true || usedGy == true) {
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        else if (wParam == 0x38 || wParam == 0x68) {//8
            pres2 = 8;
            if (usedR == true || usedB == true || usedY == true || usedG == true || usedGy == true) {
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        else if (wParam == 0x39 || wParam == 0x69) {//9
            pres2 = 9;
            if (usedR == true || usedB == true || usedY == true || usedG == true || usedGy == true) {
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }

    }break;
    case WM_PAINT:
    {

        HFONT hFont = CreateFont(48, 0, 0, 0, FW_DONTCARE, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
            CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Times New Roman"));
        hdc = BeginPaint(hWnd, &ps);
        if (draw3) {
            SelectObject(hdc, hFont);
            SetTextColor(hdc, RGB(29, 181, 34));
            RECT rect = RECT{ 200,100,400,125 };
            DrawText(hdc, TEXT("Select a difficult"), -1, &rect, DT_NOCLIP);
            SetTextColor(hdc, RGB(255, 255, 255));

        }
        if (draw0) {

            SelectObject(hdc, hFont);
            SetTextColor(hdc, RGB(29, 181, 34));
            RECT rect = RECT{200,100,400,125};
            DrawText(hdc, TEXT("Patern Remember Game"), -1, &rect, DT_NOCLIP);
            SetTextColor(hdc, RGB(255, 255, 255));
        }
        if (draw)
        {
            GetClientRect(hWnd, &rc);
            Rectangle(hdc, 0, 0, rc.right, rc.bottom);
            Draw3x3matrix(hdc);
            DrawRight(hdc);
            if (diff == 1) {
                diff_time = 8;
            }
            else if (diff == 2) {
                diff_time = 6;
            }
            else if (diff == 3) {
                diff_time = 4;
            }
            if (sec < diff_time) {
                string _sec = to_string(sec) + "/" + to_string(diff_time);
                wstring stemp = stringToWstring(_sec);
                LPCWSTR result = stemp.c_str();
                TextOut(hdc, 300, 150, result, 3);
                SetTimer(hWnd, IDT_TIMER2, 1000, (TIMERPROC)NULL);
            }
            else {
#ifdef DEBUG
                MessageBox(NULL, L"Now you have to test your brain", L"INFO", MB_OK);
#endif 
                draw = false;
                draw2 = true;
                InvalidateRect(hWnd, NULL, TRUE);
                RedrawWindow(hWnd, 0, 0, RDW_INVALIDATE);
            }
        }
        else if (draw2) {
            Draw3x3matrix(hdc);
            DrawHelp(hdc);
        }
        else if (usedR) { 
            Erase2(hdc);
            Draw3x3matrix(hdc);
            RECT rect = { 480 , 80 , 670,270 };
            HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
            FillRect(hdc, &rect, brush);
            DeleteObject(brush);
            DrawHelp(hdc);
            DrawRedUsed(hdc);
            if (pres2 != 0) {
                DrawRc(hdc, pres2, red);
                enter[RED] = pres2;
                pres2 = 0;
            }
        }
        else if (usedB) { 
            Erase2(hdc);
            Draw3x3matrix(hdc);
            RECT rect = { 480 , 80 , 670,270 };
            HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
            FillRect(hdc, &rect, brush);
            DeleteObject(brush);
            DrawHelp(hdc);
            DrawBlueUsed(hdc);
            if (pres2 != 0) {
                DrawRc(hdc, pres2, blue);
                enter[BLUE] = pres2;
                pres2 = 0;
            }
        }
        else if (usedG) { 
            Erase2(hdc);
            Draw3x3matrix(hdc);
            RECT rect = { 480 , 80 , 670,270 };
            HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
            FillRect(hdc, &rect, brush);
            DeleteObject(brush);
            DrawHelp(hdc);
            DrawGreenUsed(hdc);
            if (pres2 != 0) {
                DrawRc(hdc, pres2, green);
                enter[GREEN] = pres2;
                pres2 = 0;
            }
        }
        else if (usedY) {
            Erase2(hdc);
            Draw3x3matrix(hdc);
            RECT rect = { 480 , 80 , 670,270 };
            HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
            FillRect(hdc, &rect, brush);
            DeleteObject(brush);
            DrawHelp(hdc);
            DrawYellowUsed(hdc);
            if (pres2 != 0) {
                DrawRc(hdc, pres2, yellow);
                enter[YELLOW] = pres2;
                pres2 = 0;
            }
        }
        else if (usedGy) { 
            Erase2(hdc);
            Draw3x3matrix(hdc);
            // + squares to game
            RECT rect = { 480 , 80 , 870,470 };
            HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
            FillRect(hdc, &rect, brush);
            DeleteObject(brush);
            DrawHelp(hdc);
            // DrawRed(hdc);
            DrawGrayUsed(hdc);
            if (pres2 != 0) {
                DrawRc(hdc, pres2, white);
                for (int i = 0; i < 4; i++) {
                    if (enter[i] == pres2) {
                        enter[i] = 0;
                    }
                }
                pres2 = 0;
            }
        }
        DeleteObject(hFont);
        EndPaint(hWnd, &ps);

    }break;
    case WM_DESTROY:

        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    };
    return 0;
}

// Obslužná rutina zprávy pro pole O produktu
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

INT_PTR CALLBACK Right(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
       // SetDlgItemTextA(hDlg, ID_TX2, txt1.c_str());
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDLOAD) {
            HDC hd = GetDC(hDlg);
            Draw3x3matrix(hd);
            DrawRight(hd);
        }
        else if (LOWORD(wParam) == IDPLAY) {
            draw = false;
            draw0 = true;
            draw2 = false;
            usedR = false;
            usedB = false;
            usedG = false;
            usedY = false;
            usedGy = false;
            load = false;
            load2 = false;
            diff_time = 0;
            EndDialog(hDlg, LOWORD(wParam));
            DestroyWindow(check);
            EraseAll(hWnd1);
            SendMessage(hWnd1, WM_CREATE, 0, 0);
            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDQUIT)
        {
            DestroyWindow(hWnd1);
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
       /* else if (LOWORD(wParam) == IDPA) {
            MessageBox(NULL, L"T1", L"T1", MB_OK);
            system("Patern Remember Game.exe");
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }*/
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK No(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
       // SetDlgItemTextA(hDlg, ID_TX, txt2.c_str());
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDLOAD) {
            HDC hd = GetDC(hDlg);
            Draw3x3matrix(hd);
            DrawRight(hd);
        }
        else if (LOWORD(wParam) == IDPLAY) {
             draw = false;
             draw0 = true;
             draw2 = false;
             usedR = false;
             usedB = false;
             usedG = false;
             usedY = false;
             usedGy = false;
             load = false;
             load2 = false;
             diff_time = 0;
            EndDialog(hDlg, LOWORD(wParam));
            DestroyWindow(check);
            EraseAll(hWnd1);
            SendMessage(hWnd1, WM_CREATE, 0, 0);
            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDQUIT)
        {
            DestroyWindow(hWnd1);
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
      /*  else if (LOWORD(wParam) == IDPA) {
            MessageBox(NULL, L"T2", L"T2", MB_OK);
            system("Patern Remember Game.exe");
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }*/
        break;
    case WM_DESTROY:
        EndDialog(hDlg, LOWORD(wParam));
        return (INT_PTR)TRUE;
        break;
    }
    return (INT_PTR)FALSE;
}



LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
    {
        hWndProgressBar = CreateWindowEx(0, PROGRESS_CLASS, NULL, WS_VISIBLE | WS_CHILD, 10, 50, 200, 20, hWnd, (HMENU)IDPB_PROGRESS_BAR, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);

        if (!hWndProgressBar) {
            MessageBox(NULL, L"Progress Bar Failed.", L"Error", MB_OK | MB_ICONERROR);
        }
#pragma warning(disable: 4996)
        string path = getenv("PRG path");
        string git = path + "/gitupdate.exe";
        ShellExecuteA(NULL, "open", git.c_str(), NULL, NULL, SW_SHOWNORMAL);

        SendMessage(hWndProgressBar, PBM_SETRANGE, 0, MAKELPARAM(0, 9));
        SendMessage(hWndProgressBar, PBM_SETSTEP, (WPARAM)1, 0);
        SendMessage(hWndProgressBar, PBM_SETBARCOLOR, 0, RGB(219, 33, 189)); // RGB barvy progresbaru

        if (SetTimer(hWnd, IDT_TIMER, 5000, (TIMERPROC)NULL)) {
            SetTimer(hWnd, IDT_PROGRESS_TIMER, 500, (TIMERPROC)NULL);
            // MessageBox(NULL, L"Timer set for 5 seconds", L"Success", MB_OK | MB_ICONINFORMATION);
        }
        else {
            MessageBox(NULL, L"Timer failed", L"Error", MB_OK | MB_ICONERROR);
        }
        break;
    }
    case WM_TIMER:
    {
        switch ((UINT)wParam)
        {
        case IDT_TIMER:
        {
            KillTimer(hWnd, IDT_TIMER);
            KillTimer(hWnd, IDT_PROGRESS_TIMER);
            //  MessageBox(NULL, L"Timer Activated", L"Success", MB_OK | MB_ICONINFORMATION);
            ShowWindow(hWnd1, SW_SHOWNORMAL);
            UpdateWindow(hWnd1);

            ShowWindow(hWnd2, SW_HIDE);
            break;
        }
        case IDT_PROGRESS_TIMER:

            SendMessage(hWndProgressBar, PBM_STEPIT, 0, 0);
            break;
        }
        break;
    }
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return (DefWindowProc(hWnd, message, wParam, lParam));

    };
    return 0;
}




