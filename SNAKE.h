
#pragma once // Tránh d?ng d? thu vi?n
#include <stdio.h>
#include <conio.h>
#include <ctime> 
#include <windows.h> // Thu vi?n quan tr?ng nh?t d? di?u khi?n Console

#define KEY_NONE -1

// Hàm d?ch chuy?n con tr? d?n t?a d? (x, y)
// Ðây là hàm quan tr?ng nh?t d? v? R?n và M?i
void GotoXY(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Hàm d?i màu ch?
// Giúp r?n có màu s?c d?p hon
void TextColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Hàm ?n/hi?n con tr? chu?t nh?p nháy
// Khi choi game nên ?n di cho d?p (truy?n vào 0 d? ?n, 1 d? hi?n)
void ShowCur(bool CursorVisibility)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
    SetConsoleCursorInfo(handle, &cursor);
}

// Hàm l?y t?a d? X hi?n t?i c?a con tr?
int WhereX()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return csbi.dwCursorPosition.X;
    return -1;
}

// Hàm l?y t?a d? Y hi?n t?i c?a con tr?
int WhereY()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return csbi.dwCursorPosition.Y;
    return -1;
}
