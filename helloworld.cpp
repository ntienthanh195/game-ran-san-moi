#include <iostream>
#include "SANKE.h"
#include <conio.h>
#include <string>

int sl=4;
using namespace std;

void ve_tuong_tren();
void ve_tuong_duoi();
void ve_tuong_phai();
void ve_tuong_trai();
void ve_tuong();
void khoi_tao_ran(int toadox[], int toadoy[]);
void ve_ran(int toadox[],int toadoy[]);
void xu_ly_ran(int toadox[],int toadoy[],int x,int y);




int main()
{
    int toadox[100],toadoy[100];
	ve_tuong();
    khoi_tao_ran(toadox,toadoy);
    ve_ran(toadox,toadoy);
  
    
    

    
    
    
    int x = 50, y = 13;
    GotoXY(x, y);
    int l = 1;
    TextColor(l);
    int check = 2;
    ShowCur(0);
    while (true)
    {       
        
        // bảng điều khiển 
        if (_kbhit())
        {
            char kitu = _getch();
            if (kitu == -32)
            {
                kitu = _getch();
                if (kitu == 72) check = 1;
                else if (kitu == 80) check = 0;
                else if (kitu == 75) check = 2;
                else if (kitu == 77) check = 3;
            }
        }

        if (check == 0)  y++; // 0 la di xuong
        else if (check == 1) y--; // 1 la di len
        else if (check == 2) x--; // 2 cham vao bien phai - di qua trai
        else if (check == 3) x++; // 3 cham vao ben trai - di qua phai (tuc la 100)
        
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
        xu_ly_ran(toadox, toadoy, x, y);
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
	int x=50,y=13;
	for(int i=0;i<sl;i++)
	{
		toadox[i]=x;
		toadoy[i]=y;
		x--;
	}
}

void ve_ran(int toadox[],int toadoy[])
{
	for(int i=0;i<sl;i++)
	{
		GotoXY(toadox[i],toadoy[i]);
		if(i==0)
		{
			cout<<"0";
		}
		else
		{
			cout<<"o";
		}
	} 
}


/*
void xu_ly_ran(int toadox[],int toadoy[],int x,int y)
{
    //b1: xóa tọa độ cuối cùng
    GotoXY(toadox[sl-1],toadoy[sl-1]);
    cout<<" ";
	//b2: thêm tọa độ mới vào đầu rắn
	for(int i=sl-1;i>0;i--)
    {
        toadox[i]=toadox[i-1];
        toadoy[i]=toadoy[i-1];
    }
	
	
	//b3: Cập nhật ví trí - vẽ rắn 
    toadox[0]=x;
    toadoy[0]=y;
	ve_ran(toadox,toadoy);
}
*/

void xu_ly_ran(int toadox[], int toadoy[], int x, int y)
{
    // B1: Xóa đuôi cũ 
    GotoXY(toadox[sl-1], toadoy[sl-1]);
    cout << " "; 

    // B2: Dịch chuyển dữ liệu trong mảng 
    for(int i = sl-1; i > 0; i--)
    {
        toadox[i] = toadox[i-1];
        toadoy[i] = toadoy[i-1];
    }
    
    // B3: Cập nhật tọa độ đầu mới
    toadox[0] = x;
    toadoy[0] = y;
    
    // B4: VẼ TỐI ƯU 
    
    // Vẽ đầu mới
    GotoXY(toadox[0], toadoy[0]);
    cout << "0";
    
    // Biến cái đầu cũ (giờ là đốt thứ 1) thành thân
    GotoXY(toadox[1], toadoy[1]);
    cout << "o";
}