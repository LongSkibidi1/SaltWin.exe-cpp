#include <windows.h>
#include <stdio.h>
#include <cmath>

#ifndef IDI_SHIELD
#define IDI_SHIELD MAKEINTRESOURCE(32518)
#endif

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:WinMainCRTStartup")
#pragma comment(lib, "winmm.lib")

#define M_PI 3.14159265358979323846

typedef union _RGBQUAD {
    COLORREF rgb;
    struct {
        BYTE r;
        BYTE g;
        BYTE b;
        BYTE Reserved;
    };
}_RGBQUAD, * PRGBQUAD;

int red, green, blue;
bool ifcolorblue = false, ifblue = false;

COLORREF Hue(int length) {
    if (red != length) {
        if (red < length) red++;
        if (ifblue == true) {
            return RGB(red, 0, length);
        }
        else {
            return RGB(red, 0, 0);
        }
    }
    else {
        if (green != length) {
            if (green < length) green++;
            return RGB(length, green, 0);
        }
        else {
            if (blue != length) {
                if (blue < length) blue++;
                return RGB(0, length, blue);
            }
            else {
                red = 0; green = 0; blue = 0;
                ifblue = true;
            }
        }
    }
    return RGB(0, 0, 0);
}

DWORD WINAPI MouseErrorIcon(LPVOID lpParam) {
    int icon_x = GetSystemMetrics(SM_CXICON);
    int icon_y = GetSystemMetrics(SM_CYICON);
    while (true) {
        HDC hdc = GetDC(NULL);
        POINT cursor;
        GetCursorPos(&cursor);
        DrawIcon(hdc, cursor.x - icon_x / 2, cursor.y - icon_y / 2, LoadIcon(NULL, IDI_ERROR));
        ReleaseDC(NULL, hdc);
        Sleep(10);
    }
}

DWORD WINAPI balls(LPVOID lpParam) {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    int signX = -1;
    int signY = 1;
    int incrementor = 10;
    int x = 10;
    int y = 10;
    while (1) {
        HDC hdc = GetDC(0);
        int top_x = 0 + x;
        int top_y = 0 + y;
        int bottom_x = 100 + x;
        int bottom_y = 100 + y;
        x += incrementor * signX;
        y += incrementor * signY;
        HBRUSH brush = CreateSolidBrush(Hue(239));
        SelectObject(hdc, brush);
        Ellipse(hdc, top_x, top_y, bottom_x, bottom_y);
        if (y >= GetSystemMetrics(SM_CYSCREEN) - 100) signY = -1;
        if (x >= GetSystemMetrics(SM_CXSCREEN) - 100) signX = -1;
        if (y <= 0) signY = 1;
        if (x <= 0) signX = 1;
        Sleep(10);
        DeleteObject(brush);
        ReleaseDC(0, hdc);
    }
}

DWORD WINAPI squares(LPVOID lpParam) {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    int signX = 1;
    int signY = 1;
    int incrementor = 10;
    int x = 10;
    int y = 10;
    while (1) {
        HDC hdc = GetDC(0);
        x += incrementor * signX;
        y += incrementor * signY;
        int top_x = 0 + x;
        int top_y = 0 + y;
        int bottom_x = 100 + x;
        int bottom_y = 100 + y;
        HBRUSH brush = CreateSolidBrush(Hue(239));
        SelectObject(hdc, brush);
        Rectangle(hdc, top_x, top_y, bottom_x, bottom_y);
        if (y >= GetSystemMetrics(SM_CYSCREEN) - 100) signY = -1;
        if (x >= GetSystemMetrics(SM_CXSCREEN) - 100) signX = -1;
        if (y <= 0) signY = 3;
        if (x <= 0) signX = 2;
        Sleep(10);
        DeleteObject(brush);
        ReleaseDC(0, hdc);
    }
}

DWORD WINAPI sines1(LPVOID lpParam) {
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    double angle = 0;
    while (1) {
        HDC hdc = GetDC(0);
        for (int i = 0; i < sw; i += 4) {
            int a = (int)(sin(angle + i * 0.05) * 20);
            BitBlt(hdc, i, a, 4, sh, hdc, i, 0, SRCCOPY);
        }
        angle += 0.1;
        ReleaseDC(0, hdc);
        Sleep(15);
    }
}

DWORD WINAPI payload1(LPVOID lpParam)
{
    while (1) {
        HDC hdc = GetDC(NULL);
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
        StretchBlt(hdc, 10, 10, w - 20, h - 20, hdc, 0, 0, w, h, SRCINVERT);
        StretchBlt(hdc, -10, -10, w + 20, h + 20, hdc, 0, 0, w, h, SRCINVERT);
        ReleaseDC(NULL, hdc);
        Sleep(10);
    }
}

DWORD WINAPI payload3(LPVOID lpParam) {
    int xs = GetSystemMetrics(SM_CXSCREEN);
    int ys = GetSystemMetrics(SM_CYSCREEN);
    int waveOffset = 0;
    while (true) {
        HDC hdc = GetDC(NULL);
        for(int y = 0; y < ys; y += 4) {
            int offset = (int)((y + waveOffset) % 30 - 15);
            BitBlt(hdc, offset, y, xs, 4, hdc, 0, y, SRCCOPY);
        }
        waveOffset++;
        ReleaseDC(0, hdc);
        Sleep(10);
    }
}

DWORD WINAPI Icons(LPVOID lpvd) {
    int x = GetSystemMetrics(0);
    int y = GetSystemMetrics(1);
    while (true)
    {
        HDC hdc = GetDC(0);
        DrawIcon(hdc, rand() % x, rand() % y, LoadIcon(NULL, IDI_ERROR));
        DrawIcon(hdc, rand() % x, rand() % y, LoadIcon(NULL, IDI_WARNING));
        DrawIcon(hdc, rand() % x, rand() % y, LoadIcon(NULL, IDI_APPLICATION));
        DrawIcon(hdc, rand() % x, rand() % y, LoadIcon(NULL, IDI_SHIELD)); 
        ReleaseDC(0, hdc);
        Sleep(15);
    }
}

DWORD WINAPI train(LPVOID lpParam) {
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    while (1) {
        HDC hdc = GetDC(0);
        BitBlt(hdc, -30, 0, w, h, hdc, 0, 0, SRCCOPY);
        BitBlt(hdc, w - 30, 0, w, h, hdc, 0, 0, NOTSRCCOPY);
        ReleaseDC(0, hdc);
        Sleep(10);
    }
}

DWORD WINAPI train2(LPVOID lpParam) {
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    while (1) {
        HDC hdc = GetDC(0);
        BitBlt(hdc, -100, 0, w, h, hdc, 0, 0, SRCCOPY);
        BitBlt(hdc, w - 100, 0, w, h, hdc, 0, 0, NOTSRCCOPY);
        ReleaseDC(0, hdc);
        Sleep(10);
    }
}

VOID WINAPI sound1() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((9 * t & t >> 4 | 5 * t & t >> 15 | 3 * t & t >> 10) - 0);
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    Sleep(30000);
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound3() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t >> (t % 32 ? 4 : 3) | (t % 128 ? t >> 3 : t >> 3 | t >> 9));
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    Sleep(30000);
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound4() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(9 * t & t >> 4 | 5 * t & t >> 7 | (3 * t & t >> 10) - 1);
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    Sleep(30000);
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound5() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((15 * t & t >> 4 | 5 * t & t >> 7 | 3 * t & t >> 10) - 0);
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    Sleep(30000);
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

VOID WINAPI sound6() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * ((t >> 12 | t >> 6) & 69 & t >> 3) | t * 4 | t * (t >> 9));
    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    Sleep(30000);
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    if (MessageBoxW(NULL, L"Run GDI only?", L"SaltWin.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
    {
        ExitProcess(0);
    }
    
    if (MessageBoxW(NULL, L"Are u sure?", L"SaltWin.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
    {
        ExitProcess(0);
    }
    
    // B?m Yes c? 2 l?n th? X ð? m?i xu?t hi?n
    HANDLE hMouseThread = CreateThread(NULL, 0, MouseErrorIcon, NULL, 0, NULL);

    Sleep(1000);
    
    HANDLE P1 = CreateThread(NULL, 0, payload1, NULL, 0, NULL);
    sound1();
    TerminateThread(P1, 0);
    CloseHandle(P1);
    
    Sleep(100);
    
    HANDLE P3 = CreateThread(NULL, 0, payload3, NULL, 0, NULL);
    sound3();
    TerminateThread(P3, 0);
    CloseHandle(P3);
    
    Sleep(100);
    
    HANDLE P4 = CreateThread(NULL, 0, Icons, NULL, 0, NULL);
    HANDLE P5 = CreateThread(NULL, 0, train, NULL, 0, NULL);
    sound4();
    TerminateThread(P4, 0);
    CloseHandle(P4);
    TerminateThread(P5, 0);
    CloseHandle(P5);
    
    Sleep(100);
    
    HANDLE P6 = CreateThread(NULL, 0, train2, NULL, 0, NULL);
    HANDLE P7 = CreateThread(NULL, 0, Icons, NULL, 0, NULL);
    sound5();
    TerminateThread(P6, 0);
    CloseHandle(P6);
    TerminateThread(P7, 0);
    CloseHandle(P7);
    
    Sleep(100);
    
    HANDLE P8 = CreateThread(NULL, 0, sines1, NULL, 0, NULL);
    HANDLE P9 = CreateThread(NULL, 0, squares, NULL, 0, NULL);
    HANDLE P10 = CreateThread(NULL, 0, balls, NULL, 0, NULL);
    sound6();
    TerminateThread(P8, 0);
    CloseHandle(P8);
    TerminateThread(P9, 0);
    CloseHandle(P9);
    TerminateThread(P10, 0);
    CloseHandle(P10);
    
    return 0;
}
