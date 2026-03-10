
#pragma once // Tránh d?ng d? thu vi?n
#include <stdio.h>
#include <conio.h>
#include <ctime> 
#include<vector>
#include <windows.h> // Thu vi?n quan tr?ng nh?t d? di?u khi?n Console


#define KEY_NONE -1

void GotoXY(int x, int y);

void TextColor(int color);

void ShowCur(bool CursorVisibility);

int HienThiMenu();
void ve_tuong();
void ve_tuong_tren();
void ve_tuong_duoi();
void ve_tuong_trai();
void ve_tuong_phai();
void Ve_Nut(); 
void ve_nut(int x, int y, char chu);
void ve_sang(int phim, int &sang);
void ve_toi(int phim);
void khoi_tao_ran(int toadox[], int toadoy[]);
void ve_ran(int toadox[], int toadoy[]);
void tao_qua(int &xqua, int &yqua, int toadox[], int toadoy[]);
void xu_ly_ran(int toadox[], int toadoy[], int &xqua, int &yqua, int &sl, int x, int y, bool &AnQua);
void Tinh_Toa_Do_Moi(int &x, int &y, int check);
char XuLy_Phim_Bam(int &check, vector<int> &huong_di);
void QuanLy_Den_Phim(int &phim_sang, clock_t &thoi_gian_tat_den);
void game_over(string ten_file);
void ran_di_chuyen(int toadox[], int toadoy[], int x, int y, int sl);
bool kt_ran_cham_tuong(int x0, int y0);
bool kt_ran_cham_duoi(int toadox[], int toadoy[], int sl);
bool kt_ran_de_qua(int xqua, int yqua, int toadox[], int toadoy[], int sl);
bool kt_ran_an_qua(int x0, int y0, int xqua, int yqua);

void SaveGame(int toadox[], int toadoy[], int sl, int diem, int toc_do, string ten_file);
bool TaiGame(int toadox[], int toadoy[], int &sl, int &diem, int &toc_do, string ten_file);

void CheDo_1_CoDien();
void CheDo_2_XuyenTuong();
void CheDo_3_VatCan();
void CheDo_4_DauTruong();



int main()
{
    SetConsoleOutputCP(437);
    srand(time(NULL));
    ShowCur(0);

    while(true)
    {
        int luachon = HienThiMenu();
        switch(luachon)
        {
          case 1: 
          {
            CheDo_1_CoDien();
            break;
          }
          case 2: 
          {
            CheDo_2_XuyenTuong();
            break;
          }
          case 3: 
          {
            
            break;
          }
          case 4: 
          {
            
            break;
          }
          case 0: 
          {
            return 0;
          }


          }
    }
}
