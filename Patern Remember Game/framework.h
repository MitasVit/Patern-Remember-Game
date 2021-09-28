// header.h: soubor k zahrnutí pro standardní systémové soubory k zahrnutí,
// nebo soubory k zahrnutí specifické pro projekt
//

#pragma once

#include "targetver.h"
#define _WIN32_WINNT 0x0601

// Hlavičkové soubory Windows
#include <windows.h>
// Hlavičkové soubory C RunTime
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <wingdi.h>
#include <windowsx.h>
#include <fstream>
#include <sstream>
#include <commctrl.h>
#include <uxtheme.h>
#include <strsafe.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <conio.h>
#include <dwmapi.h>
#include <string>
#include <sstream>

using namespace std;

string ToString(int x) {
    stringstream ss;
    ss << x;
    return ss.str();
}


using namespace std;


#define MUJ_COMP
//#define INDEX_DEBUG
//#define DEBUG


extern HBRUSH red = CreateSolidBrush(RGB(219, 37, 24));
extern HBRUSH green = CreateSolidBrush(RGB(37, 219, 24));
extern HBRUSH blue = CreateSolidBrush(RGB(24, 60, 219));
extern HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
extern HBRUSH yellow = CreateSolidBrush(RGB(227, 223, 11));
extern HBRUSH gray = CreateSolidBrush(RGB(71, 79, 73));
extern int good1[9] = { 0,0,0,0,0,0,0,0,0 };
//3ctverecky, 1 pozice u kazdeho
extern int good2[9] = { 0,0,0,0,0,0,0,0,0 };
//radky sloupce
extern int enter[9] = { 0,0,0,0,0,0,0,0,0 };
extern int diff = 1;
int index = 0;
#define IDT_TIMER2    1005
#define IDT_TIMER3 1006
#define IDT_TIMER          1002
#define IDT_PROGRESS_TIMER 1003
#define IDPB_PROGRESS_BAR  1004

#define RED 0
#define BLUE 1
#define YELLOW 2
#define GREEN 3


void DrawRc(HDC hdc, int ps, HBRUSH br);

wstring stringToWstring(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}
LPCWSTR stringToLPCWSTR(const std::string& tmp){
    int len;
    int slength = (int)tmp.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, tmp.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, tmp.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    wstring stemp = r;
    LPCWSTR result = stemp.c_str();
    return result;
}
LPCWSTR intToLPCWSTR(int _tmp) {
    string tmp = to_string(_tmp);
    int len;
    int slength = (int)tmp.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, tmp.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, tmp.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    wstring stemp = r;
    LPCWSTR result = stemp.c_str();
    return result;
}
LPCWSTR LONGToLPCWSTR(LONG _tmp) {
    string tmp = to_string(_tmp);
    int len;
    int slength = (int)tmp.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, tmp.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, tmp.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    wstring stemp = r;
    LPCWSTR result = stemp.c_str();
    return result;
}



void Draw3x3matrix(HDC hdc) {
    MoveToEx(hdc, 50, 50, NULL);
    LineTo(hdc, 200, 50); // 1 -vrchni cara
    LineTo(hdc, 200, 200);//2
    LineTo(hdc, 50, 200);//3
    LineTo(hdc, 50, 50);//4
    MoveToEx(hdc, 50, 100, NULL);
    LineTo(hdc, 100, 100);//5
    LineTo(hdc, 100, 50);//6
    MoveToEx(hdc, 50, 150, NULL);
    LineTo(hdc, 100, 150);//7
    LineTo(hdc, 100, 200);//8
    LineTo(hdc, 100, 100);//9
    LineTo(hdc, 200, 100);//10
    MoveToEx(hdc, 150, 50, NULL);
    LineTo(hdc, 150, 200);//11
    MoveToEx(hdc, 50, 150, NULL);
    LineTo(hdc, 200, 150);//12

}

void DrawRight(HDC hdc) {
   /* RECT rc = RECT{ 55,55,95,95 };//vlevo nahore x +y vpravo dole x+ y
    RECT rc2 = RECT{ 155,55,195,95 };
    RECT rc3 = RECT{ 105,105,145,145 };
    FillRect(hdc, &rc, red);
    FillRect(hdc, &rc2, green);
    FillRect(hdc, &rc3, blue);*/
    if (diff == 1) {
        DrawRc(hdc, good2[RED], red);
        DrawRc(hdc, good2[BLUE], blue);
        DrawRc(hdc, good2[YELLOW], yellow);
        DrawRc(hdc, good2[GREEN], green);
    }
    else if (diff == 2 || diff == 3) {
        DrawRc(hdc, good2[RED], red);
        DrawRc(hdc, good2[BLUE], blue);
        DrawRc(hdc, good2[YELLOW], yellow);
        DrawRc(hdc, good2[GREEN], green);
        DrawRc(hdc, good2[RED + 5], red);
        DrawRc(hdc, good2[BLUE + 5], blue);
        DrawRc(hdc, good2[YELLOW + 5], yellow);
        DrawRc(hdc, good2[GREEN + 5], green);
    }
    
}

void DrawRc(HDC hdc, int ps, HBRUSH br) {
    if (ps == 1) {//op
        RECT rc = RECT{ 55,155,95,195 };
        FillRect(hdc, &rc, br);
    }
    else if (ps == 2) {//op
        RECT rc = RECT{ 105,155,145,195 };
        FillRect(hdc, &rc, br);
    }
    else if (ps == 3) {//op
        RECT rc = RECT{ 155,155,195,195 };
        FillRect(hdc, &rc, br);

    }
    else if (ps == 4) {
        RECT rc = RECT{ 55,105,95,145 };
        FillRect(hdc, &rc, br);
    }
    else if (ps == 5) {
        RECT rc = RECT{ 105,105,145,145 };
        FillRect(hdc, &rc, br);
    }
    else if (ps == 6) {
        RECT rc = RECT{ 155,105,195,145 };
        FillRect(hdc, &rc, br);
    }
    else if (ps == 7) {//op
        RECT rc = RECT{ 55,55,95,95 };
        FillRect(hdc, &rc, br);

    }
    else if (ps == 8) {//op

        RECT rc = RECT{ 105,55,145,95 };
        FillRect(hdc, &rc, br);
    }
    else if (ps == 9) {//op
        RECT rc = RECT{ 155,55,195,95 };
        FillRect(hdc, &rc, br);
    }
}

void DrawRedUsed(HDC hdc) {
    RECT rc = RECT{490,90,560,160};
    RECT rc2 = RECT{ 500,100,550,150 };
    Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
    FillRect(hdc, &rc2, red);
    TextOutA(hdc, 500, 150, "A", 2);
}

void DrawBlueUsed(HDC hdc) {
    RECT rc = RECT{ 590,90,660,160 };
    RECT rc2 = RECT{ 600,100,650,150 };
    Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
    FillRect(hdc, &rc2, blue);
    TextOutA(hdc, 600, 150, "C", 2);
}

void DrawGreenUsed(HDC hdc) {
    RECT rc = RECT{ 490,190,560,260 };
    RECT rc2 = RECT{ 500,200,550,250 };
    Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
    FillRect(hdc, &rc2, green);
    TextOutA(hdc, 500, 250, "B", 2);
}
/*
void DrawGrayUsed(HDC hdc) {
    RECT rc = RECT{ 490,190,560,260 };
    RECT rc2 = RECT{ 700,100,750,150 };
    Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
    FillRect(hdc, &rc2, green);
    TextOutA(hdc, 600, 250, "E", 2);
}*/

void DrawYellowUsed(HDC hdc) {
    RECT rc = RECT{ 590,190,660,260 };
    RECT rc2 = RECT{ 600,200,650,250 };
    Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
    FillRect(hdc, &rc2, yellow);
    TextOutA(hdc, 600, 250, "D", 2);
}

void DrawGrayUsed(HDC hdc) {
    RECT rc = RECT{ 690,90,760,160 };
    RECT rc2 = RECT{ 700,100,750,150 };
    Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
    FillRect(hdc, &rc2, gray);
    TextOutA(hdc, 700, 150, "E", 2);
}

void DrawVoid(HDC hdc) {
    RECT rc = RECT{ 55,55,95,95 };//vlevo nahore x +y vpravo dole x+ y
    RECT rc2 = RECT{ 155,55,195,95 };
    RECT rc3 = RECT{ 105,105,145,145 };
    FillRect(hdc, &rc, white);
    FillRect(hdc, &rc2, white);
    FillRect(hdc, &rc3, white);
}

void DrawHelp(HDC hdc) {
    RECT rc = RECT{ 500,100,550,150 };//vlevo nahore x +y vpravo dole x+ y
    RECT rc2 = RECT{ 500,200,550,250 };
    RECT rc3 = RECT{ 600,100,650,150 };
    RECT rc4= RECT{ 600,200,650,250 };
    RECT rc5 = RECT{ 700,100,750,150 };
    FillRect(hdc, &rc, red);
    FillRect(hdc, &rc2, green);
    FillRect(hdc, &rc3, blue);
    FillRect(hdc, &rc4, yellow);
    FillRect(hdc, &rc5, gray);
    TextOutA(hdc, 500, 150, "A", 2);
    TextOutA(hdc, 500, 250, "B", 2);
    TextOutA(hdc, 600, 150, "C", 2);
    TextOutA(hdc, 600, 250, "D", 2);
    TextOutA(hdc, 700, 150, "E", 2);
}

// //debug message  - bez ok
void mBox(string text, string nadpis, UINT tlacitka) {
    MessageBoxA(NULL, text.c_str(), nadpis.c_str(), tlacitka);
}
//debug message with ok - bez kontorly
void dBox(string text, string nadpis) {
    MessageBoxA(NULL, text.c_str(), nadpis.c_str(), MB_OK);
}
//debug message with ok - kontrola zda je debug definovan
void deBox(string text, string nadpis){
#ifdef DEBUG
    MessageBoxA(NULL, text.c_str(), nadpis.c_str(), MB_OK);
#endif
}

#define IDC_EXIT_BUTTON 101
#define IDC_PUSHLIKE_BUTTON 102

HBRUSH CreateGradientBrush(COLORREF top, COLORREF bottom, LPNMCUSTOMDRAW item)
{
    HBRUSH Brush = NULL;
    HDC hdcmem = CreateCompatibleDC(item->hdc);
    HBITMAP hbitmap = CreateCompatibleBitmap(item->hdc, item->rc.right - item->rc.left, item->rc.bottom - item->rc.top);
    SelectObject(hdcmem, hbitmap);

    int r1 = GetRValue(top), r2 = GetRValue(bottom), g1 = GetGValue(top), g2 = GetGValue(bottom), b1 = GetBValue(top), b2 = GetBValue(bottom);
    for (int i = 0; i < item->rc.bottom - item->rc.top; i++)
    {
        RECT temp;
        int r, g, b;
        r = int(r1 + double(i * (r2 - r1) / item->rc.bottom - item->rc.top));
        g = int(g1 + double(i * (g2 - g1) / item->rc.bottom - item->rc.top));
        b = int(b1 + double(i * (b2 - b1) / item->rc.bottom - item->rc.top));
        Brush = CreateSolidBrush(RGB(r, g, b));
        temp.left = 0;
        temp.top = i;
        temp.right = item->rc.right - item->rc.left;
        temp.bottom = i + 1;
        FillRect(hdcmem, &temp, Brush);
        DeleteObject(Brush);
    }
    HBRUSH pattern = CreatePatternBrush(hbitmap);

    DeleteDC(hdcmem);
    DeleteObject(Brush);
    DeleteObject(hbitmap);

    return pattern;
}

void Generate() {
    srand(time(NULL));
    if (diff == 1) {
        for (int i = 0; i < 3; i++) {
            int pos = rand() % 9;
            int col = rand() % 3;//barva
            good1[col] = pos;
            good2[col] = pos;
        }
    }
    else if (diff == 2) {
        for (int i = 0; i < 5; i++) {
            int pos = rand() % 9;
            int col = rand() % 3;//barva
            int y = rand() % 2;
            if (y == 2) {
                good1[col] = pos;
                good2[col] = pos;
            }
            else {
                good1[col + 5] = pos;
                good2[col + 5] = pos;
            }
        }
    }
    else if (diff == 3) {
        for (int i = 0; i < 7; i++) {
            int pos = rand() % 9;
            int col = rand() % 3;//barva
            int y = rand() % 2;
            if (y == 2) {
                good1[col] = pos;
                good2[col] = pos;
            }
            else {
                good1[col + 5] = pos;
                good2[col + 5] = pos;
            }
        }
    }
}


bool Good(int in[8]) {
    for (int i = 0; i < 8; i++) {
        if (in[i] != good1[i]) {
            return false;
       }
    }
    return true;
}


void EraseHdc(HDC hdc, HWND hwnd) {
    RECT rc;
    GetClientRect(hwnd, &rc);
    Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}
void Erase2(HDC hdc) {
    RECT rc = { 490,90,760,260 };
    //Rectangle(hdc, 490, 90, 760, 260);
    FillRect(hdc, &rc, white);
}

void IndexFileCreate() {
    ofstream file("index.txt");
    for (int i = 0; i < 8; i++) {
        file << i << ": " << good2[i] <<endl;
    }
    for (int i = 0; i < 8; i++) {
        file << i << ": " << good1[i] << endl;
    }
    file.close();
}
void IndexFileCreate2() {
    ofstream file("index2.txt");
    for (int i = 0; i < 8; i++) {
        file << i << ": " << good2[i] << endl;
    }
    for (int i = 0; i < 8; i++) {
        file << i <<  ": " << good1[i] << endl;
    }
    file.close();
}
void IndexFileCreate3(int in[4]) {
    ofstream file("index3.txt");
    for (int i = 0; i < 8; i++) {
        file << i << ": " << good2[i] << endl;
    }
    for (int i = 0; i < 8; i++) {
         file << i << ": " << good1[i] << endl;
    }
    for (int i = 0; i < 8; i++) {
          file << i << ": " << in[i] << endl;
    }
    file.close();
}
void IndexFileCreate4(int in[4]) {
    ofstream file("index4.txt");
    for (int i = 0; i < 8; i++) {
        file << i << ": " << good2[i] << endl;
    }
    for (int i = 0; i < 8; i++) {
            file << i << ": " << good1[i] << endl;
    }
    for (int i = 0; i < 8; i++) {
        for (int y = 0; y < 9; y++) {
            file << i  << ": " << in[i] << endl;
        }
    }
    file.close();
}

void IndexFileCreate5() {
    ofstream file("index5.txt");
    for (int i = 0; i < 9; i++) {
        file << i << ": " << good2[i] << endl;
    }
    for (int i = 0; i < 9; i++) {
        file << i << ": " << good1[i] << endl;
    }
    file.close();
}
void EraseAll(HWND hwnd1_) {
    for (int i = 0; i < 8; i++) {
        good1[i] = 0;
        good2[i] = 0;
        enter[i] = 0;
    }
    HDC hd = GetDC(hwnd1_);
    Rectangle(hd, 0, 0, 1000, 1000);
}

inline bool FileExist(const std::string& name) {
#pragma warning(suppress : 4996)
    if (FILE* file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    }
    else {
        return false;
    }
}

//text1 - good, text2 - bad
//
void load_text(string text1, string text2) {
    string gpath = "C:/Program Files/Patern Remember Game/good.txt";
    string bpath = "C:/Program Files/Patern Remember Game/bad.txt";
    string tmp[6];
    string tmp2[6];
    if (FileExist(gpath) == false) {
        MessageBox(NULL, L"The C:/Program Files/Patern Remember Game/good.txt doesn't exist!\nThis application may not work properly, please contact application support.", L"Alert", MB_OK | MB_ICONWARNING);
        text1 = "Excellent!";
    }
    else if (FileExist(bpath) == false) {
        MessageBox(NULL, L"The C:/Program Files/Patern Remember Game/bad.txt doesn't exist!\nThis application may not work properly, please contact application support.", L"Alert", MB_OK | MB_ICONWARNING);
        text2 = "Bad...";
    }
    else {
        ifstream good(gpath);
        ifstream bad(bpath);
        for (int i = 0; i < 6; i++) {
            getline(good, tmp[i]);
            getline(bad, tmp2[i]);
        }
        good.close();
        bad.close();
    }

}

HRESULT EnableBlurBehind(HWND hwnd)
{
    HRESULT hr = S_OK;

    // Create and populate the blur-behind structure.
    DWM_BLURBEHIND bb = { 0 };

    // Specify blur-behind and blur region.
    bb.dwFlags = DWM_BB_ENABLE;
    bb.fEnable = true;
    bb.hRgnBlur = NULL;

    // Enable blur-behind.
    hr = DwmEnableBlurBehindWindow(hwnd, &bb);
    if (SUCCEEDED(hr))
    {
        // ...
    }
    return hr;
}

