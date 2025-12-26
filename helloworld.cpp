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



int main()
{
    ve_tuong();
    
    /*
    string noi_dung = "Day la my project dau tien cua toi";
    string khoang_trang_xoa(noi_dung.length(), ' ');
    int length = noi_dung.length();
	*/
    
    
    
    int x = 50, y = 13;
    GotoXY(x, y);
    
    int xcu = x;
    int ycu = y;
    int l = 1;
    TextColor(l);
    int check = 0;
    ShowCur(0);
    while (true)
    {
        GotoXY(xcu, ycu);
        cout << khoang_trang_xoa;
        GotoXY(x, y);
        cout << noi_dung;
        xcu = x;
        ycu = y;

        // dieu khien

        if (_kbhit())
        {
            char kitu = _getch();
            if (kitu == -32)
            {
                kitu = _getch();
                if (kitu == 72)
                {
                    check = 1;
                }
                else if (kitu == 80)
                {
                    check = 0;
                }
                else if (kitu == 75)
                {
                    check = 2;
                }
                else if (kitu == 77)
                {
                    check = 3;
                }
            }
        }

        if (check == 0) // 0 la di xuong
        {
            y++;
        }
        else if (check == 1) // 1 la di len
        {
            y--;
        }
        else if (check == 2) // 2 cham vao bien phai - di qua trai
        {
            x--;
        }
        else if (check == 3) // 3 cham vao ben trai - di qua phai (tuc la 100)
        {
            x++;
        }

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
        else if (x + length >= 100) // cham phai thi qua trai
        {
            x = 100 - length;
            check = 2;
        }
        else if (x <= 11) // cham trai thi qua phai
        {
            x = 11;
            check = 3;
        }

        l++;
        TextColor(l);
        if (l >= 15)
            l = 1;
        Sleep(120);
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


