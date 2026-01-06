#include <iostream>
#include "SNAKE.h"
#include <conio.h>
#include <string>
#include <ctime>
#include <windows.h>
#include <vector>
#include <fstream> 

int sl = 7;
using namespace std;

void ve_tuong_tren();
void ve_tuong_duoi();
void ve_tuong_phai();
void ve_tuong_trai();
void ve_tuong();
void khoi_tao_ran(int toadox[], int toadoy[]);
void ve_ran(int toadox[], int toadoy[]);
void xu_ly_ran(int toadox[], int toadoy[], int x, int y, int &xqua, int &yqua, int &diem, int &tocdo);
bool kt_ran_cham_tuong(int x0, int y0);
bool kt_ran_cham_duoi(int toadox[], int toadoy[]);
void tao_qua(int &xqua, int &yqua, int toadox[], int toadoy[]);
bool kt_ran_de_qua(int xqua, int yqua, int toadox[], int toadoy[]);
bool kt_ran_an_qua(int xqua, int yqua, int x0, int y0);
void SaveGame(int toadox[], int toadoy[], int &xqua, int &yqua, int &diem, int &tocdo, int &sl);
bool TaiGame(int toadox[], int toadoy[], int &xqua, int &yqua, int &diem, int &tocdo, int &sl);


void ve_nut(int x,int y,char chu)
{
   
    GotoXY(x,y); cout << char(218) << char(196) << char(196) << char(196) << char(191);
    GotoXY(x, y + 1); cout << char(179) << " " << chu << " " <<char(179);     
    GotoXY(x, y + 2); cout << char(192) << char(196) << char(196) << char(196) << char(217);
}
/*
void VeNutControl(int x, int y, string chu, int mau)
{
    TextColor(mau); // Đặt màu (14: Vàng, 7: Trắng)
    GotoXY(x, y);     cout << char(218) << char(196) << char(196) << char(196) << char(191); // Nắp trên
    GotoXY(x, y + 1); cout << char(179) << " " << chu << " " << char(179);                 // Thân
    GotoXY(x, y + 2); cout << char(192) << char(196) << char(196) << char(196) << char(217); // Đáy dưới
    TextColor(7); // Trả lại màu trắng để không ảnh hưởng cái khác
}
*/

void ve_sang(int phim,int &sang)
{
	if(phim == 1)  //lên
    {
        TextColor(228);
        GotoXY(116,7);
        cout<<" W "; 
        sang=1;
        TextColor(7);
    }
    
    if(phim == 0)  
    {
        TextColor(228);
        GotoXY(116,11); 
        cout<<" S ";
        sang=1;
        TextColor(7);
    }
    
    if(phim == 2)  
    {
        TextColor(228);
        GotoXY(111,11); 
        cout<<" A ";
        sang=1;
        TextColor(7);
    }
    
    if(phim == 3)  
    {
        TextColor(228);
        GotoXY(121,11); 
        cout<<" D ";
        sang=1;
        TextColor(7);
    }
        
    
}

void ve_toi(int phim)
{
	if(phim == 1)  //lên
    {
        TextColor(7);
        GotoXY(116,7);
        cout<<" W ";   
    }
    
    if(phim == 0)  
    {
        TextColor(7);
        GotoXY(116,11); 
        cout<<" S ";
        TextColor(7);
    }
    
    if(phim == 2)  
    {
        TextColor(7);
        GotoXY(111,11); 
        cout<<" A ";
        
    }
    
    if(phim == 3)  
    {
        TextColor(7);
        GotoXY(121,11); 
        cout<<" D ";
    }
        
    
}

int main()
{

    SetConsoleOutputCP(437);
    srand(time(NULL));
    ShowCur(0);

    int x = 50, y = 13;
    int diem = 0;
    bool gameover = false;
    int toadox[100], toadoy[100];
    int tocdo = 200; 
    int check = -1;
    int l = 1;
    int xqua = 0, yqua = 0;
    int sang=0;
    
    int phim_sang=-1;
    clock_t thoi_gian_tat_den =0;

    while(true)
    {
        system("cls");
        TextColor(11);
        cout << "\n\n\t\t===== GAME RAN SAN MOI =====";
        cout << "\n\t1. Choi moi (New Game)";
        cout << "\n\t2. Tiep tuc (Continue)";
        cout << "\n\t0. Thoat";
        cout << "\n\n\tLua chon: ";
        TextColor(7);
        char luachon = _getch(); // Dùng getch để không cần ấn Enter

        if(luachon =='1')
        {
            sl=7;
            diem=0;
            tocdo=200;
            check=-1;
            khoi_tao_ran(toadox, toadoy);
            tao_qua(xqua, yqua, toadox, toadoy);
            break;
        }
        else if(luachon =='2')
        {
            if(TaiGame(toadox, toadoy, xqua, yqua, diem, tocdo, sl))
            {

                break;
            }
            else
            {
                cout<<"\n\n\t =====KHONG TIM THAY FILE SAVE!=====";
                Sleep(1000);
            }


        }
        else if(luachon =='0')
        {
            return 0;
        }
    }
    
    // --- VÀO GAME ---
    system("cls");
    ve_tuong();
    ve_nut(110,10,'A');
    ve_nut(115,10,'S');
    ve_nut(120,10,'D');
    ve_nut(115,6,'W');
    
    // Vẽ lại rắn
    TextColor(11);
    ve_ran(toadox, toadoy);
    
    // Vẽ quả táo (vẽ lại vì system cls đã xóa)
    int mau_qua = rand() % (15 - 9 + 1) + 9;
    TextColor(mau_qua);
    GotoXY(xqua, yqua); cout << "$";
    TextColor(7);
    
    
    // Vẽ thông tin
    GotoXY(0, 0); cout << "Diem: " << diem;

    GotoXY(0, 2);  cout << "Nhan 'x' de Save & Exit";

    

    clock_t thoi_gian_cu = clock(); // Bấm giờ mốc thời gian bắt đầu

    x = toadox[0];
    y = toadoy[0];
    

    vector<int> huong_di;
    
    
    while (gameover == false)
    {

        GotoXY(0, 0);

        // bảng điều khiển
        if (_kbhit())
        {
            char kitu = _getch();
            if(kitu == 'x')
            {
                SaveGame(toadox, toadoy, xqua, yqua, diem, tocdo, sl);
                system("cls");
                GotoXY(50, 14); cout << "GAME SAVED! BYE BYE!";
                return 0; // Thoát game
            }
            if (kitu == -32)
            {
                kitu = _getch();

                int huong_tam=-1; 
              
                int huong_du_tinh= (huong_di.empty()==true) ? check : huong_di.back();
                

                if (kitu == 72 && huong_du_tinh != 0) //Muốn LÊN (1), kỵ XUỐNG (0)
                    huong_tam = 1;
                else if (kitu == 80 && huong_du_tinh != 1) // Muốn XUỐNG (0), kỵ LÊN (1)
                    huong_tam = 0;
                else if (kitu == 75 && huong_du_tinh != 3) // Muốn TRÁI (2), kỵ PHẢI (3)
                    huong_tam = 2;
                else if (kitu == 77 && huong_du_tinh != 2) // Muốn PHẢI (3), kỵ TRÁI (2)
                    huong_tam = 3;

                if(huong_tam != -1 && huong_di.size() <2 )
                {
                    huong_di.push_back(huong_tam);              
                }
            }
        }

        if(phim_sang != -1)
        {
            if(clock() >= thoi_gian_tat_den)
            {
                ve_toi(phim_sang);
                phim_sang=-1;
            }
        }

        if (clock() - thoi_gian_cu >= tocdo)
        {

            if(huong_di.empty() == false)
            {
                check= huong_di.front();
                huong_di.erase(huong_di.begin());
                if (phim_sang != -1) ve_toi(phim_sang);
                ve_sang(check, sang);
                phim_sang = check;
                thoi_gian_tat_den = clock() + 150;
            }

            
                
            
           
            if (check != -1)
            {
                if (check == 0)
                    y++; // 0 la di xuong
                else if (check == 1)
                    y--; // 1 la di len
                else if (check == 2)
                    x--; // 2 cham vao bien phai - di qua trai
                else if (check == 3)
                    x++; // 3 cham vao ben trai - di qua phai (tuc la 100)
            
                xu_ly_ran(toadox, toadoy, x, y, xqua, yqua, diem, tocdo);
            }
            if (kt_ran_cham_tuong(toadox[0], toadoy[0]) == true || kt_ran_cham_duoi(toadox, toadoy) == true)
            {
                gameover = true;

                // Bạn có thể thêm xử lý âm thanh hoặc thông báo ở đây cho gọn
                // 1. In thông báo Game Over
                GotoXY(50, 14);
                cout << "GAME OVER!";

                // 2. In hướng dẫn thoát
                GotoXY(45, 15);
                cout << "Nhan phim bat ky de thoat...";

                // 3. Đưa con trỏ ra chỗ khuất (để không nhấp nháy xấu màn hình)
                GotoXY(0, 35);

                // 4. Dùng lệnh này thay cho system("pause")
                _getch(); // Đợi người chơi bấm 1 phím bất kỳ thì mới tắt, KHÔNG hiện chữ rác
                remove("save.txt");
                break;
            }
            thoi_gian_cu = clock();
            //======= kiem tra ======

            int mau = rand() % (15 - 9 + 1) + 9;
            TextColor(mau);
            GotoXY(0, 0);
            cout << "Diem: " << diem;
            

            
        }
        
        Sleep(1);
    }
 
    GotoXY(0, 35);
    return 0;
}

// x= 10 ->100
// y= 5 ->28
/*
góc phần tư thứ 1: (10,5)
góc phần tư thứ 2: (100,5)
góc phần tư thứ 3: (10,28)
góc phần tư thứ 4: (100,28)
*/
void ve_tuong_tren()
{
    int x = 11, y = 5;
    while (x < 100)
    {
        GotoXY(x, y);
        cout << char(205);
        x++;
    }
    GotoXY(10, 5);
    cout << char(201);
    GotoXY(100, 5);
    cout << char(187);
}

void ve_tuong_duoi()
{
    int x = 11, y = 28;
    while (x < 100)
    {
        GotoXY(x, y);
        cout << char(205);
        x++;
    }
    GotoXY(10, 28);
    cout << char(200);
    GotoXY(100, 28);
    cout << char(188);
}

/*
góc phần tư thứ 1: (10,5)
góc phần tư thứ 2: (100,5)
góc phần tư thứ 3: (10,28)
góc phần tư thứ 4: (100,28)
*/
void ve_tuong_phai()
{
    int x = 100, y = 6;
    while (y < 28)
    {
        GotoXY(x, y);
        cout << char(186);
        y++;
    }
}

void ve_tuong_trai()
{
    int x = 10, y = 6;
    while (y < 28)
    {
        GotoXY(x, y);
        cout << char(186);
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
    TextColor(10);
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

void xu_ly_ran(int toadox[], int toadoy[], int x, int y, int &xqua, int &yqua, int &diem, int &tocdo)
{
    // B1: KIỂM TRA ĂN QUẢ (Kiểm tra đầu mới x,y với quả)
    if (kt_ran_an_qua(xqua, yqua, x, y) == true)
    {
        // === TRƯỜNG HỢP ĂN TÁO ===
        sl++;
        diem++;
        tao_qua(xqua, yqua, toadox, toadoy); // Tạo quả mới
        if ((tocdo <= 200) && (tocdo >= 150))
            tocdo -= 5;
        else if ((tocdo < 150) && (tocdo >= 120))
            tocdo -= 10;
        else if ((tocdo < 120) && (tocdo >= 50))
            tocdo -= 15;
        if (tocdo <= 50)
            tocdo = 50;
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
    TextColor(10);
  
    // B4: Vẽ lại rắn
    // Đặt lại màu xanh cho rắn (nếu muốn)
    // TextColor(2);
    GotoXY(toadox[0], toadoy[0]);
    cout << "0";

    if (sl > 1)
    {
        GotoXY(toadox[1], toadoy[1]);
        cout << "o";
    }

    
    TextColor(7);

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

void tao_qua(int &xqua, int &yqua, int toadox[], int toadoy[])
{

    // Vẽ quả ra màn hình
    do
    {
        // Tính toán độ rộng x: Tường từ 10-100 thì táo từ 11-99
        xqua = rand() % (99 - 11 + 1) + 11;
        yqua = rand() % (27 - 6 + 1) + 6;
        // Tính toán độ rộng y: Tường từ 5-28 thì táo từ 6-27
    } while (kt_ran_de_qua(xqua, yqua, toadox, toadoy) == true);
    int mau = rand() % (15 - 9 + 1) + 9;
    TextColor(mau);
    GotoXY(xqua, yqua);
    cout << "$";
    TextColor(7);
}

bool kt_ran_de_qua(int xqua, int yqua, int toadox[], int toadoy[])
{
    for (int i = 0; i < sl; i++)
    {
        if ((xqua == toadox[i]) && (yqua == toadoy[i]))
        {
            return true;
        }
    }
    return false;
}

bool kt_ran_an_qua(int xqua, int yqua, int x0, int y0)
{
    if ((xqua == x0) && (yqua == y0))
    {
        return true;
    }
    return false;
}


void SaveGame(int toadox[], int toadoy[], int &xqua, int &yqua, int &diem, int &tocdo, int &sl)
{
    ofstream f;
    f.open("save.txt");
    f << diem << " " << tocdo << " " << sl << " " << xqua << " " << yqua << " "  << endl;

    for(int i=0;i<sl;i++)
    {
        f << toadox[i] <<" " << toadoy[i]<<endl;
    }
    f.close();

}

bool TaiGame(int toadox[], int toadoy[], int &xqua, int &yqua, int &diem, int &tocdo, int &sl)
{
    ifstream f;
    f.open("save.txt");

    if(!f) return false;

    f >> diem >> tocdo >> sl >> xqua >> yqua;

    for(int i=0;i<sl;i++)
    {
        f >> toadox[i] >> toadoy[i];
    }
    f.close();
    return true;
}
