#include <iostream>
#include "SNAKE.h"
#include <conio.h>
#include <string>
#include <ctime>
#include <windows.h>
#include <vector>
#include <fstream> 

int sl=7;
using namespace std;

// --- CẤU HÌNH BẢN ĐỒ ---
#define TUONG_TRAI 10
#define TUONG_PHAI 100
#define TUONG_TREN 5
#define TUONG_DUOI 28


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
void SaveGame(string ten_file, int toadox[], int toadoy[], int xqua, int yqua, int diem, int tocdo, int sl);
bool TaiGame(string ten_file, int toadox[], int toadoy[], int &xqua, int &yqua, int &diem, int &tocdo, int &sl);
void ve_nut(int x,int y,char chu);
void Ve_Nut();
void ve_sang(int phim,int &sang);
void ve_toi(int phim);
void ran_di_chuyen(int &diem, int &tocdo, int &l, int &xqua, int &yqua, int toadox[], int toadoy[], string ten_file);
void game_over(string ten_file); 
void Tinh_Toa_Do_Moi(int &x, int &y, int check);
void QuanLy_Den_Phim(int &phim_sang, clock_t &thoi_gian_tat_den);

// Sửa kiểu trả về từ void thành char để "báo cáo" phím bấm
char XuLy_Phim_Bam(int &check, vector<int> &huong_di);


void CheDo_1_CoDien();    
void CheDo_2_XuyenTuong();  
void CheDo_3_VatCan();      
void CheDo_4_DauTruong();

int HienThiMenu()
{
    string cac_muc[] = {
    "1. CO DIEN (CLASSIC)",       // Dòng đầu tiên -> Máy gán vào ô số [0]
    "2. XUYEN TUONG (NO WALL)",   // Dòng thứ 2   -> Máy gán vào ô số [1]
    "3. VAT CAN (OBSTACLES)",     // Dòng thứ 3   -> Máy gán vào ô số [2]
    "4. DAU TRUONG (PVP 2 SNAKES)", // Dòng thứ 4 -> Máy gán vào ô số [3]
    "5. THOAT GAME",              // Dòng thứ 5   -> Máy gán vào ô số [4]

}; 
    int so_luong_cac_muc=5;
    int muc_dang_chon=0; 
    while(true)
    {
        system("cls");
        TextColor(11);
        cout << "\n\n\t\t===== GAME RAN SAN MOI =====";
        cout<<"\n\t\t   (Dung phim len xuong de chon) \n\n";
       
        for(int i=0;i<so_luong_cac_muc;i++)
        {
            if(i==muc_dang_chon)
            {
                TextColor(224);
                cout<<"\n"<< cac_muc[muc_dang_chon];
                TextColor(7);
            }
            else
            {
                TextColor(7);
                cout<<"\n"<< cac_muc[i];
            }
        }

        
        
            char kitu= _getch();
            if(kitu == -32)
            {
                kitu = _getch();
                if(kitu == 72)
                {
                    muc_dang_chon--;
                    if(muc_dang_chon<0) 
                    {
                        muc_dang_chon=so_luong_cac_muc-1;
                    }
                    
                }
                else if(kitu == 80)
                {
                    muc_dang_chon++;
                    if(muc_dang_chon>=so_luong_cac_muc)
                    {
                        muc_dang_chon=0;
                    }
                }
                  
                }
                 else if(kitu == 13) 
                {
                    if(muc_dang_chon == 5) return 0;
                    return muc_dang_chon+1;
                }
        else if(kitu == '1') return 1;
        else if(kitu == '2') return 2;
        else if(kitu == '3') return 3;
        else if(kitu == '4') return 4;
        else if(kitu == '5') return 0;

            }
    }
     




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


void CheDo_1_CoDien()
{
    int diem, tocdo, l, xqua, yqua;
    int toadox[100], toadoy[100];
    int x, y;

    int check = -1;
    vector<int> huong_di;
    bool gameover = false;
    
    int sang = 0;
    int phim_sang = -1;
    clock_t thoi_gian_tat_den = 0;
   
    // ==========================================
    // 1. MENU CHUẨN BỊ TRƯỚC KHI VÀO GAME
    // ==========================================

    while(true)
    {
        system("cls");
        TextColor(11);
        cout<<"\n1. Choi moi(New Game)";
        cout<<"\n2. Tiep tuc(Continue)";
        cout<<"\n0. Thoat(Exit)";
        cout<<"\n\n\tLua chon cua ban: ";
        char luachon=_getch();
        if(luachon == '1')
        {
            sl=7;
            diem =0;
            tocdo=200;
            check=-1;
            khoi_tao_ran(toadox, toadoy);
            tao_qua(xqua, yqua, toadox, toadoy);
            break;
        }
        else if(luachon == '2')
        {
            if(TaiGame("savegame1.txt",toadox, toadoy, xqua, yqua, diem, tocdo, sl))
            {
                break;
            }
            else 
            {
                TextColor(12);
                cout<<"\n\n\t =====KHONG TIM THAY FILE SAVE!=====";
                Sleep(1000);
                continue;
            } 
        }
        else if(luachon == '0')
        {
            return ;
        }
    }

    // ==========================================
    // 2. VẼ GIAO DIỆN BAN ĐẦU
    // ==========================================
    
    system("cls");
    ve_tuong();
    Ve_Nut();
    
    TextColor(11);
    ve_ran(toadox, toadoy);

    // Vẽ quả táo
    int mau_qua = rand() % (15 - 9 + 1) + 9;
    TextColor(mau_qua);
    GotoXY(xqua, yqua); cout << "$";
    TextColor(7);
    
    // Vẽ thông tin
    GotoXY(0, 0); cout << "Diem: " << diem;
    GotoXY(0, 2);  cout << "Nhan 'x' de Save & Exit";

    clock_t thoi_gian_cu = clock(); 

    x = toadox[0];
    y = toadoy[0];
    
    // ==========================================
    // 3. VÒNG LẶP GAME CHÍNH (GAME LOOP)
    // =========================================
    
    // BẮT ĐẦU VÒNG LẶP (Chỗ này lúc nãy bạn bị thiếu)
    while (gameover == false) 
    {
        // A. Xử lý phím (Dùng chung)
        char phim= XuLy_Phim_Bam(check, huong_di);
        if(phim == 'x')
        {
            SaveGame("savegame1.txt", toadox, toadoy, xqua, yqua, diem, tocdo, sl);
            system("cls");
            GotoXY(50, 14); cout << "GAME SAVED!";
            return; // Thoát hàm luôn
        }

        // B. Quản lý đèn (Dùng chung)
        QuanLy_Den_Phim(phim_sang, thoi_gian_tat_den);

        // C. Xử lý di chuyển theo tốc độ (nhịp game)
        if (clock() - thoi_gian_cu >= tocdo)
        {
            if(huong_di.empty() == false)
            {
                check = huong_di.front();
                huong_di.erase(huong_di.begin());
                if (phim_sang != -1) ve_toi(phim_sang);
                ve_sang(check, sang);
                phim_sang = check;
                thoi_gian_tat_den = clock() + 150;
            }

            if (check != -1) Tinh_Toa_Do_Moi(x, y, check);

            // KIỂM TRA LUẬT CHƠI
            if (check != -1 && (kt_ran_cham_tuong(x, y) || kt_ran_cham_duoi(toadox, toadoy)))
            {
                gameover = true;
                game_over("savegame1.txt");  
                return;       
            }
            
            if (!gameover && check != -1) 
            {
                xu_ly_ran(toadox, toadoy, x, y, xqua, yqua, diem, tocdo);
                x = toadox[0];
                y = toadoy[0];
            }

            int mau = rand() % (15 - 9 + 1) + 9;
            TextColor(mau);
            GotoXY(0, 0); cout << "Diem: " << diem;
            TextColor(7);

            thoi_gian_cu = clock(); 
        }
        
        Sleep(1); 
    } // ĐÓNG VÒNG LẶP WHILE

} 



void CheDo_2_XuyenTuong()
{
    int diem, tocdo, l, xqua, yqua;
    int toadox[100], toadoy[100];
    int x, y;

    int check = -1;
    vector<int> huong_di;
    bool gameover = false;
    
    int sang = 0;
    int phim_sang = -1;
    clock_t thoi_gian_tat_den = 0;
   
    // ==========================================
    // 1. MENU CHUẨN BỊ TRƯỚC KHI VÀO GAME
    // ==========================================

    while(true)
    {
        system("cls");
        TextColor(11);
        cout<<"\n1. Choi moi(New Game)";
        cout<<"\n2. Tiep tuc(Continue)";
        cout<<"\n0. Thoat(Exit)";
        cout<<"\n\n\tLua chon cua ban: ";
        char luachon=_getch();
        if(luachon == '1')
        {
            sl=7;
            diem =0;
            tocdo=200;
            check=-1;
            khoi_tao_ran(toadox, toadoy);
            tao_qua(xqua, yqua, toadox, toadoy);
            break;
        }
        else if(luachon == '2')
        {
            if(TaiGame("savegame2.txt",toadox, toadoy, xqua, yqua, diem, tocdo, sl))
            {
                break;
            }
            else 
            {
                TextColor(12);
                cout<<"\n\n\t =====KHONG TIM THAY FILE SAVE!=====";
                Sleep(1000);
                continue;
            } 
        }
        else if(luachon == '0')
        {
            return ;
        }
    }

    // ==========================================
    // 2. VẼ GIAO DIỆN BAN ĐẦU
    // ==========================================
    
    system("cls");
    ve_tuong();
    Ve_Nut();
    
    TextColor(11);
    ve_ran(toadox, toadoy);

    // Vẽ quả táo
    int mau_qua = rand() % (15 - 9 + 1) + 9;
    TextColor(mau_qua);
    GotoXY(xqua, yqua); cout << "$";
    TextColor(7);
    
    // Vẽ thông tin
    GotoXY(0, 0); cout << "Diem: " << diem;
    GotoXY(0, 2);  cout << "Nhan 'x' de Save & Exit";

    clock_t thoi_gian_cu = clock(); 

    x = toadox[0];
    y = toadoy[0];
    
    // ==========================================
    // 3. VÒNG LẶP GAME CHÍNH (GAME LOOP)
    // =========================================
    
    // BẮT ĐẦU VÒNG LẶP (Chỗ này lúc nãy bạn bị thiếu)
    while (gameover == false) 
    {
        // A. Xử lý phím (Dùng chung)
        char phim= XuLy_Phim_Bam(check, huong_di);
        if(phim == 'x')
        {
            SaveGame("savegame2.txt", toadox, toadoy, xqua, yqua, diem, tocdo, sl);
            system("cls");
            GotoXY(50, 14); cout << "GAME SAVED!";
            return; // Thoát hàm luôn
        }

        // B. Quản lý đèn (Dùng chung)
        QuanLy_Den_Phim(phim_sang, thoi_gian_tat_den);

        // C. Xử lý di chuyển theo tốc độ (nhịp game)
        if (clock() - thoi_gian_cu >= tocdo)
        {
            if(huong_di.empty() == false)
            {
                check = huong_di.front();
                huong_di.erase(huong_di.begin());
                if (phim_sang != -1) ve_toi(phim_sang);
                ve_sang(check, sang);
                phim_sang = check;
                thoi_gian_tat_den = clock() + 150;
            }

            if (check != -1) Tinh_Toa_Do_Moi(x, y, check);

            if (x <= TUONG_TRAI) x = TUONG_PHAI - 1;       // Đụng tường trái -> Xuyên qua phải
            else if (x >= TUONG_PHAI) x = TUONG_TRAI + 1;  // Đụng tường phải -> Xuyên qua trái
            else if (y <= TUONG_TREN) y = TUONG_DUOI - 1;  // Đụng trần nhà -> Rớt xuống đáy
            else if (y >= TUONG_DUOI) y = TUONG_TREN + 1;  // Đụng đáy -> Trồi lên trần nhà


            // KIỂM TRA LUẬT CHƠI 2

            if (check != -1 && ( kt_ran_cham_duoi(toadox, toadoy)))
            {
                gameover = true;
                game_over("savegame2.txt");  
                return;       
            }
            


            if (!gameover && check != -1) 
            {
                xu_ly_ran(toadox, toadoy, x, y, xqua, yqua, diem, tocdo);
                x = toadox[0];
                y = toadoy[0];
            }

            int mau = rand() % (15 - 9 + 1) + 9;
            TextColor(mau);
            GotoXY(0, 0); cout << "Diem: " << diem;
            TextColor(7);

            thoi_gian_cu = clock(); 
        }
        
        Sleep(1); 
    } 

} 


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

void Ve_Nut()
{
    ve_nut(110,10,'A');
    ve_nut(115,10,'S');
    ve_nut(120,10,'D');
    ve_nut(115,6,'W');
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

void SaveGame(string ten_file, int toadox[], int toadoy[], int xqua, int yqua, int diem, int tocdo, int sl)
{
    ofstream f;
    f.open(ten_file.c_str()); // Mở file theo tên truyền vào
    f << diem << " " << tocdo << " " << sl << " " << xqua << " " << yqua << " "  << endl;
    for(int i=0; i<sl; i++) f << toadox[i] << " " << toadoy[i] << endl;
    f.close();
}

bool TaiGame(string ten_file, int toadox[], int toadoy[], int &xqua, int &yqua, int &diem, int &tocdo, int &sl)
{
    ifstream f;
    f.open(ten_file.c_str());
    if(!f) return false;
    f >> diem >> tocdo >> sl >> xqua >> yqua ;
    for(int i=0; i<sl; i++) f >> toadox[i] >> toadoy[i];
    f.close();
    return true;
}



void ve_nut(int x,int y,char chu)
{
   
    GotoXY(x,y); cout << char(218) << char(196) << char(196) << char(196) << char(191);
    GotoXY(x, y + 1); cout << char(179) << " " << chu << " " <<char(179);     
    GotoXY(x, y + 2); cout << char(192) << char(196) << char(196) << char(196) << char(217);
}
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



// Hàm này chỉ lo việc hiển thị thông báo
void game_over(string ten_file) 
{
    GotoXY(50, 14); 
    TextColor(12); cout << "GAME OVER!"; 
    TextColor(7);
    GotoXY(45, 15); cout << "Nhan phim bat ky de quay lai MENU";
    
    remove(ten_file.c_str());
    
    _getch(); 
}


void Tinh_Toa_Do_Moi(int &x, int &y, int check)
{
    // check là hướng đi hiện tại: 0-Xuống, 1-Lên, 2-Trái, 3-Phải
    switch (check) {
        case 0: y++; break;
        case 1: y--; break;
        case 2: x--; break;
        case 3: x++; break;
    }
}


void QuanLy_Den_Phim(int &phim_sang, clock_t &thoi_gian_tat_den)
{
    // Kiểm tra nếu đang có đèn sáng và đã hết giờ -> Tắt đi
    if (phim_sang != -1 && clock() >= thoi_gian_tat_den)
    {
        ve_toi(phim_sang);
        phim_sang = -1;
    }
}

char XuLy_Phim_Bam(int &check, vector<int> &huong_di)
{
    if (_kbhit())
    {
        char kitu = _getch();
        // Nếu bắt được 'x' thì trả về ngay để hàm main xử lý
        if (kitu == 'x') return 'x'; 

        if (kitu == -32) // Phím mũi tên
        {
            kitu = _getch();
            int huong_tam = -1;
            int huong_du_tinh = (huong_di.empty()) ? check : huong_di.back();

            if (kitu == 72 && huong_du_tinh != 0) huong_tam = 1;      
            else if (kitu == 80 && huong_du_tinh != 1) huong_tam = 0; 
            else if (kitu == 75 && huong_du_tinh != 3) huong_tam = 2; 
            else if (kitu == 77 && huong_du_tinh != 2) huong_tam = 3; 

            if (huong_tam != -1 && huong_di.size() < 2)
                huong_di.push_back(huong_tam);
        }
    }
    return 0; // Trả về 0 nếu không có gì đặc biệt
}




