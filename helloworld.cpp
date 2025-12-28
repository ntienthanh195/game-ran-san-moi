#include <iostream>
#include "SANKE.h"
#include <conio.h>
#include <string>
#include <ctime>

int sl = 7;
using namespace std;

void ve_tuong_tren();
void ve_tuong_duoi();
void ve_tuong_phai();
void ve_tuong_trai();
void ve_tuong();
void khoi_tao_ran(int toadox[], int toadoy[]);
void ve_ran(int toadox[], int toadoy[]);
void xu_ly_ran(int toadox[], int toadoy[], int x, int y,int &xqua, int &yqua);
bool kt_ran_cham_tuong(int x0, int y0);
bool kt_ran_cham_duoi(int toadox[], int toadoy[]);
void tao_qua(int &xqua, int &yqua, int toadox[],int toadoy[]);
bool kt_ran_de_qua(int xqua, int yqua, int toadox[], int toadoy[]);
bool kt_ran_an_qua(int xqua, int yqua, int x0, int y0);


int main()
{
    bool gameover = false;
    int toadox[100], toadoy[100];

    ve_tuong();

    khoi_tao_ran(toadox, toadoy);
    ve_ran(toadox, toadoy);

    srand(time(NULL));
    int xqua=0,yqua=0;
    tao_qua(xqua,yqua,toadox,toadoy);

    int x = 50, y = 13;
    GotoXY(x, y);
    int l = 1;
    TextColor(l);
    int check = 3;
    ShowCur(0);
    while (gameover == false)
    {

        // bảng điều khiển
        if (_kbhit())
        {
            char kitu = _getch();
            if (kitu == -32)
            {
                kitu = _getch();
                if (kitu == 72 && check != 0)
                    check = 1;
                else if (kitu == 80 && check != 1)
                    check = 0;
                else if (kitu == 75 && check != 3)
                    check = 2;
                else if (kitu == 77 && check != 2)
                    check = 3;
            }
        }

        if (check == 0)
            y++; // 0 la di xuong
        else if (check == 1)
            y--; // 1 la di len
        else if (check == 2)
            x--; // 2 cham vao bien phai - di qua trai
        else if (check == 3)
            x++; // 3 cham vao ben trai - di qua phai (tuc la 100)

        if (y >= 27) // cham bien thi di len
        {
            y = 27;
            check = 1;
        }
        else if (y <= 6) // cham tren thi di xuong
        {
            y = 6;
            check = 0;
        }
        else if (x >= 100) // cham phai thi qua trai
        {
            x = 100;
            check = 2;
        }
        else if (x <= 11) // cham trai thi qua phai
        {
            x = 11;
            check = 3;
        }
        xu_ly_ran(toadox, toadoy, x, y,xqua,yqua);
        //======= kiem tra ======
        
        if (kt_ran_cham_tuong(toadox[0], toadoy[0]) == true || kt_ran_cham_duoi(toadox, toadoy) == true)
        {
            gameover = true;

            // Bạn có thể thêm xử lý âm thanh hoặc thông báo ở đây cho gọn
            GotoXY(50, 14);
            cout << "GAME OVER!";
        }

        l++;
        TextColor(l);
        if (l >= 15)
            l = 1;
        Sleep(150);
    }

    system("pause");
    return 0;
}

void ve_tuong_tren()
{
    int x = 10, y = 5;
    while (x <= 100)
    {
        GotoXY(x, y);
        cout << "+";
        x++;
    }
}

void ve_tuong_duoi()
{
    int x = 10, y = 28;
    while (x <= 100)
    {
        GotoXY(x, y);
        cout << "+";
        x++;
    }
}

void ve_tuong_phai()
{
    int x = 100, y = 5;
    while (y <= 28)
    {
        GotoXY(x, y);
        cout << "+";
        y++;
    }
}

void ve_tuong_trai()
{
    int x = 10, y = 5;
    while (y <= 28)
    {
        GotoXY(x, y);
        cout << "+";
        y++;
    }
}

void ve_tuong()
{
    ve_tuong_tren();
    ve_tuong_duoi();
    ve_tuong_phai();
    ve_tuong_trai();
}

void khoi_tao_ran(int toadox[], int toadoy[])
{
    int x = 50, y = 13;
    for (int i = 0; i < sl; i++)
    {
        toadox[i] = x;
        toadoy[i] = y;
        x--;
    }
}

void ve_ran(int toadox[], int toadoy[])
{
    for (int i = 0; i < sl; i++)
    {
        GotoXY(toadox[i], toadoy[i]);
        if (i == 0)
        {
            cout << "0";
        }
        else
        {
            cout << "o";
        }
    }
}


   
    
void xu_ly_ran(int toadox[], int toadoy[], int x, int y, int &xqua, int &yqua)
{
    // B1: KIỂM TRA ĂN QUẢ (Kiểm tra đầu mới x,y với quả)
    if (kt_ran_an_qua(xqua, yqua, x, y) == true)
    {
        // === TRƯỜNG HỢP ĂN TÁO ===
        sl++; // Tăng dài
        tao_qua(xqua, yqua, toadox, toadoy); // Tạo quả mới
    }
    else
    {
        // === TRƯỜNG HỢP KHÔNG ĂN ===
        // QUAN TRỌNG: Phải xóa đuôi TRƯỚC KHI dịch chuyển mảng
        GotoXY(toadox[sl - 1], toadoy[sl - 1]);
        cout << " ";
    }

    // B2: Dịch chuyển thân rắn (Sau khi đã xóa đuôi xong xuôi)
    for (int i = sl - 1; i > 0; i--)
    {
        toadox[i] = toadox[i - 1];
        toadoy[i] = toadoy[i - 1];
    }

    // B3: Cập nhật đầu mới
    toadox[0] = x;
    toadoy[0] = y;

    // B4: Vẽ lại rắn
    // Đặt lại màu xanh cho rắn (nếu muốn)
    //TextColor(2); 
    ve_ran(toadox, toadoy);
}


bool kt_ran_cham_tuong(int x0, int y0)
{
    // rắn chạm tường trên
    if (y0 == 5 && (x0 >= 10 && x0 <= 100))
    {
        return true;
    }
    else if (y0 == 28 && (x0 >= 10 && x0 <= 100))
    {
        return true;
    }
    else if (x0 == 10 && (y0 >= 5 && y0 <= 28))
    {
        return true;
    }
    else if (x0 == 100 && (y0 >= 5 && y0 <= 28))
    {
        return true;
    }
    return false;
}

bool kt_ran_cham_duoi(int toadox[], int toadoy[])
{
    for (int i = 1; i < sl; i++)
    {
        if ((toadox[0] == toadox[i]) && (toadoy[0] == toadoy[i]))
        {
            return true;
        }
    }
    return false;
}


void tao_qua(int &xqua, int &yqua,int toadox[],int toadoy[])
{
  
    
    // Vẽ quả ra màn hình
    do
    {
        // Tính toán độ rộng x: Tường từ 10-100 thì táo từ 11-99
        xqua = rand() % (99 - 11 + 1) + 11;
        yqua = rand() % (27 - 6 + 1) + 6;
        // Tính toán độ rộng y: Tường từ 5-28 thì táo từ 6-27 
    } while (kt_ran_de_qua(xqua,yqua,toadox,toadoy)==true);
    int mau = rand() % (15 - 9 + 1) + 9;
    TextColor(mau);
    GotoXY(xqua, yqua);
    cout << "$"; 
    TextColor(7);
}

bool kt_ran_de_qua(int xqua, int yqua, int toadox[], int toadoy[])
{
    for(int i=0;i<sl;i++)
    {
        if((xqua == toadox[i]) && (yqua == toadoy[i]))
        {
            return true; 
        }
    }
    return false;
}


bool kt_ran_an_qua(int xqua, int yqua, int x0, int y0)
{   if((xqua ==x0) && (yqua ==y0))
    {
        return true; 
    }
    return false;
}
 