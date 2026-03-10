#include"CheDo4_PvP.h"
#include"SNAKE.h"
#include<iostream>
#include<vector>
using namespace std;

// --- CẤU HÌNH BẢN ĐỒ ---
#define TUONG_TRAI 10
#define TUONG_PHAI 100
#define TUONG_TREN 5
#define TUONG_DUOI 28


void XuLy_Phim_PVP(int check1, int check2, vector<int> &hd1, vector<int> &hd2)
{
    // --- NGƯỜI CHƠI 1 (MŨI TÊN) ---
    // Xem thử hướng dự tính tiếp theo là gì (Nếu ống rỗng thì lấy hướng hiện tại)
    int dt1 = hd1.empty() ? check1 : hd1.back(); 
    
    if (hd1.size() < 2) // Chỉ cho nhớ trước tối đa 2 bước để chống lạng lách mất kiểm soát
    {
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) { if (dt1 != 1 && dt1 != 0) hd1.push_back(0); }
        else if (GetAsyncKeyState(VK_UP) & 0x8000) { if (dt1 != 0 && dt1 != 1) hd1.push_back(1); }
        else if (GetAsyncKeyState(VK_LEFT) & 0x8000) { if (dt1 != 3 && dt1 != 2) hd1.push_back(2); }
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { if (dt1 != 2 && dt1 != 3) hd1.push_back(3); }
    }

    // --- NGƯỜI CHƠI 2 (W A S D) ---
    int dt2 = hd2.empty() ? check2 : hd2.back();
    
    if (hd2.size() < 2)
    {
        if (GetAsyncKeyState('S') & 0x8000) { if (dt2 != 1 && dt2 != 0) hd2.push_back(0); }
        else if (GetAsyncKeyState('W') & 0x8000) { if (dt2 != 0 && dt2 != 1) hd2.push_back(1); }
        else if (GetAsyncKeyState('A') & 0x8000) { if (dt2 != 3 && dt2 != 2) hd2.push_back(2); }
        else if (GetAsyncKeyState('D') & 0x8000) { if (dt2 != 2 && dt2 != 3) hd2.push_back(3); }
    }
}


// 2. Khởi tạo rắn độc lập (Cho phép chọn tọa độ sinh ra và dùng biến chiều dài riêng)
void khoi_tao_ran_pvp(int toadox[], int toadoy[], int start_x, int start_y, int sl_ran)
{
    for (int i = 0; i < sl_ran; i++)
    {
        toadox[i] = start_x;
        toadoy[i] = start_y;
        start_x--; // Xếp đuôi về phía trái
    }
}

// 3. Vẽ rắn PVP (Tùy biến màu sắc và hình dáng đầu)
void ve_ran_pvp(int toadox[], int toadoy[], int sl_ran, int mau_sac, string kieu_dau)
{
    TextColor(mau_sac);
    for (int i = 0; i < sl_ran; i++)
    {
        GotoXY(toadox[i], toadoy[i]);
        if (i == 0) cout << kieu_dau;
        else cout << "o";
    }
    TextColor(7);
}


bool kt_ran_de_qua_pvp(int xqua, int yqua, int toadox[], int toadoy[], int sl_ran)
{
    for(int i =0;i<sl_ran;i++)
    {
        if(toadox[i] == xqua && toadoy[i] == yqua)
        {
            return true;
        }
    }
    return false;
}

void tao_qua_pvp(int &xqua, int &yqua, int toadox1[], int toadoy1[], int sl1, int toadox2[], int toadoy2[], int sl2)
{
    do
    {
        // Random tọa độ táo y như cũ
        xqua = rand() % (99 - 11 + 1) + 11;
        yqua = rand() % (27 - 6 + 1) + 6;
        
    // Vòng lặp do-while này sẽ chạy liên tục NẾU quả táo đè lên Rắn 1 HOẶC đè lên Rắn 2
    } while (kt_ran_de_qua_pvp(xqua, yqua, toadox1, toadoy1, sl1) == true || 
             kt_ran_de_qua_pvp(xqua, yqua, toadox2, toadoy2, sl2) == true);

    // Vượt qua được vòng lặp tức là chỗ đó trống trải, in quả táo ra thôi!
    int mau = rand() % (15 - 9 + 1) + 9;
    TextColor(mau);
    GotoXY(xqua, yqua);
    cout << "$";
    TextColor(7);
}

// 4. Xử lý di chuyển & ăn quả độc lập cho từng rắn
void xu_ly_ran_pvp(int toadox[], int toadoy[], int x, int y, int &xqua, int &yqua, int &diem, int &tocdo, int &sl_ran, int toadox_dich[], int toadoy_dich[], int sl_dich)
{
    if (kt_ran_an_qua(xqua, yqua, x, y) == true)
    {
        sl_ran++;
        diem++;
        tao_qua_pvp(xqua, yqua, toadox, toadoy, sl_ran, toadox_dich, toadoy_dich, sl_dich);;
    }
    else
    {
        GotoXY(toadox[sl_ran - 1], toadoy[sl_ran - 1]); cout << " ";
    }

    for (int i = sl_ran - 1; i > 0; i--)
    {
        toadox[i] = toadox[i - 1];
        toadoy[i] = toadoy[i - 1];
    }
    toadox[0] = x;
    toadoy[0] = y;
}


void Ve_8_Nut_PvP()
{
    // --- KHU VỰC HIỂN THỊ CỦA PLAYER 2 (ĐỎ) ---
    TextColor(12);
    GotoXY(105, 4); cout << "PLAYER 2";
    
    // Vẽ 4 ô nút W A S D
    ve_nut(108, 6, 'W');
    ve_nut(103, 9, 'A');
    ve_nut(108, 9, 'S');
    ve_nut(113, 9, 'D');

    // --- KHU VỰC HIỂN THỊ CỦA PLAYER 1 (XANH) ---
    TextColor(10);
    GotoXY(105, 14); cout << "PLAYER 1";
    
    // Vẽ 4 ô nút Mũi tên
    // Sử dụng mã ASCII: 24 (↑), 25 (↓), 26 (→), 27 (←)
    ve_nut(108, 16, '^'); 
    ve_nut(103, 19, '<'); 
    ve_nut(108, 19, 'v'); 
    ve_nut(113, 19, '>'); 
    
    TextColor(7); // Trả lại màu mặc định cho console
}

void ve_sang_pvp(int phim, int player)
{
    TextColor(228); 
    if (player == 1) // Phím của P1 (Mũi tên)
    {
        if (phim == 1) { GotoXY(109, 17); cout << " ^ "; }      // LÊN
        else if (phim == 0) { GotoXY(109, 20); cout << " v "; } // XUỐNG
        else if (phim == 2) { GotoXY(104, 20); cout << " < "; } // TRÁI
        else if (phim == 3) { GotoXY(114, 20); cout << " > "; } // PHẢI
    }
    else if (player == 2) // Phím của P2 (WASD)
    {
        if (phim == 1) { GotoXY(109, 7); cout << " W "; }
        else if (phim == 0) { GotoXY(109, 10); cout << " S "; }
        else if (phim == 2) { GotoXY(104, 10); cout << " A "; }
        else if (phim == 3) { GotoXY(114, 10); cout << " D "; }
    }
    TextColor(7);
}

void ve_toi_pvp(int phim, int player)
{
    TextColor(7);
    if (player == 1) 
    {
        if (phim == 1) { GotoXY(109, 17); cout << " ^ "; }
        else if (phim == 0) { GotoXY(109, 20); cout << " v "; }
        else if (phim == 2) { GotoXY(104, 20); cout << " < "; }
        else if (phim == 3) { GotoXY(114, 20); cout << " > "; }
    }
    else if (player == 2)
    {
        if (phim == 1) { GotoXY(109, 7); cout << " W "; }
        else if (phim == 0) { GotoXY(109, 10); cout << " S "; }
        else if (phim == 2) { GotoXY(104, 10); cout << " A "; }
        else if (phim == 3) { GotoXY(114, 10); cout << " D "; }
    }
}

bool kt_ran_cham_than_doi_thu(int x_dau, int y_dau, int toadox_dich[], int toadoy_dich[], int sl_dich)
{
    // Bắt đầu vòng lặp từ i = 1 (Vì i = 0 là cái ĐẦU. Nếu húc vào 0 thì là luật Đầu tông Đầu, ta sẽ xử lý riêng sau)
    for (int i = 1; i < sl_dich; i++)
    {
        if (x_dau == toadox_dich[i] && y_dau == toadoy_dich[i])
        {
            return true; // Trúng thân rồi!
        }
    }
    return false;
}

bool kt_ran_cham_duoi_pvp(int toadox[], int toadoy[], int sl_ran)
{
    for (int i = 1; i < sl_ran; i++)
    {
        if (toadox[0] == toadox[i] && toadoy[0] == toadoy[i])
        {
            return true;
        }
    }
    return false;
}

void CheDo_4_DauTruong()
{
    // --- KHAI BÁO BIẾN CHO 2 NGƯỜI CHƠI ---
    int diem1 = 0, diem2 = 0;
    int tim1 = 3, tim2 = 3;
    int sl1 = 5, sl2 = 5;
    int toadox1[100], toadoy1[100], toadox2[100], toadoy2[100];
    int check1 = -1, check2 = -1;
    int x1, y1, x2, y2;
    int tocdo = 150; // Chế độ này set tốc độ cố định để 2 người công bằng
    int xqua, yqua;
    bool gameover = false;
    vector<int> huong_di_1;
    vector<int> huong_di_2;


    int phim_sang_1 = -1, phim_sang_2 = -1;
    clock_t thoi_gian_tat_den_1 = 0, thoi_gian_tat_den_2 = 0;

    bool bat_tu_1 = false, bat_tu_2 = false; // Cờ đánh dấu tàng hình
    clock_t thoi_gian_bat_tu_1 = 0, thoi_gian_bat_tu_2 = 0; // Hẹn giờ tắt tàng hình

    // --- SETUP BẢN ĐỒ BAN ĐẦU ---
    system("cls");
    ve_tuong();
    Ve_8_Nut_PvP();
    
    // Khởi tạo vị trí: P1 bên phải, P2 bên trái
    khoi_tao_ran_pvp(toadox1, toadoy1, 80, 15, sl1); // P1 Xanh lá
    khoi_tao_ran_pvp(toadox2, toadoy2, 30, 15, sl2); // P2 Đỏ
    
    ve_ran_pvp(toadox1, toadoy1, sl1, 10, "0"); // Màu 10: Xanh lá nhạt
    ve_ran_pvp(toadox2, toadoy2, sl2, 12, "X"); // Màu 12: Đỏ nhạt
    
    tao_qua_pvp(xqua,yqua,toadox1,toadoy1,sl1,toadox2, toadoy2, sl2);



    clock_t thoi_gian_cu = clock(); 
 
    x1 = toadox1[0]; y1 = toadoy1[0];
    x2 = toadox2[0]; y2 = toadoy2[0];

    // --- GAME LOOP ---
    while (!gameover)
    {
        // Hiển thị HUD (Bảng điểm & Máu)
        TextColor(10); GotoXY(10, 2); cout << "P1 (XANH): " << diem1 << " | Tim: " << tim1;
        TextColor(12); GotoXY(70, 2); cout << "P2 (DO): " << diem2 << " | Tim: " << tim2;
        TextColor(7);

        // Kiểm tra điều kiện thua cuộc
        if (tim1 <= 0 || tim2 <= 0)
        {
            gameover = true;
            GotoXY(45, 14);
            if (tim1 <= 0 && tim2 > 0) { TextColor(12); cout << "PLAYER 2 (DO) THANG!"; }
            else if (tim2 <= 0 && tim1 > 0) { TextColor(10); cout << "PLAYER 1 (XANH) THANG!"; }
            else { TextColor(14); cout << "HOA NHAU (DRAW)!"; }

            while (_kbhit()) 
            {
                _getch(); 
            }
            

            _getch();
            return;
        }

        // Thoát game bằng phím ESC (Mã 27) thay vì 'x' để không kẹt bàn phím
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) return;

        if (phim_sang_1 != -1 && clock() >= thoi_gian_tat_den_1)
         {
            ve_toi_pvp(phim_sang_1, 1);
             phim_sang_1 = -1;
        }
        if (phim_sang_2 != -1 && clock() >= thoi_gian_tat_den_2)
         {
            ve_toi_pvp(phim_sang_2, 2); 
            phim_sang_2 = -1;
        }

        
        // 1. Quét phím liên tục cho cả 2 người

          XuLy_Phim_PVP(check1, check2, huong_di_1, huong_di_2);
       

        // 2. Cập nhật di chuyển theo nhịp game
        if (clock() - thoi_gian_cu >= tocdo)
        {
            // --- XỬ LÝ ỐNG NHỚ & BẬT ĐÈN CHO P1 ---
            if (!huong_di_1.empty()) 
            {
                check1 = huong_di_1.front();      // Lấy phím đầu tiên trong ống ra xài
                huong_di_1.erase(huong_di_1.begin()); // Xóa phím đó khỏi ống
                
                // Bật đèn
                if (phim_sang_1 != -1) ve_toi_pvp(phim_sang_1, 1); 
                ve_sang_pvp(check1, 1);                            
                phim_sang_1 = check1;
                thoi_gian_tat_den_1 = clock() + 150;               
            }

            // --- XỬ LÝ ỐNG NHỚ & BẬT ĐÈN CHO P2 ---
            if (!huong_di_2.empty()) 
            {
                check2 = huong_di_2.front();
                huong_di_2.erase(huong_di_2.begin());
                
                if (phim_sang_2 != -1) ve_toi_pvp(phim_sang_2, 2);
                ve_sang_pvp(check2, 2);
                phim_sang_2 = check2;
                thoi_gian_tat_den_2 = clock() + 150;
            }

            // --- RẮN BƯỚC ĐI TỚI THEO CHECK ---
            if (check1 != -1) Tinh_Toa_Do_Moi(x1, y1, check1);
            if (check2 != -1) Tinh_Toa_Do_Moi(x2, y2, check2);

          

            // ==========================================
            // QUẢN LÝ ĐỒNG HỒ TÀNG HÌNH
            // ==========================================
            if (bat_tu_1 && clock() >= thoi_gian_bat_tu_1) bat_tu_1 = false; // Hết 3 giây -> Hiện nguyên hình
            if (bat_tu_2 && clock() >= thoi_gian_bat_tu_2) bat_tu_2 = false;

            // ==========================================
            // NẾU ĐANG TÀNG HÌNH -> ĐƯỢC PHÉP XUYÊN TƯỜNG
            // ==========================================
            if (bat_tu_1) {
                if (x1 <= TUONG_TRAI) x1 = TUONG_PHAI - 1; else if (x1 >= TUONG_PHAI) x1 = TUONG_TRAI + 1;
                else if (y1 <= TUONG_TREN) y1 = TUONG_DUOI - 1; else if (y1 >= TUONG_DUOI) y1 = TUONG_TREN + 1;
            }
            if (bat_tu_2) {
                if (x2 <= TUONG_TRAI) x2 = TUONG_PHAI - 1; else if (x2 >= TUONG_PHAI) x2 = TUONG_TRAI + 1;
                else if (y2 <= TUONG_TREN) y2 = TUONG_DUOI - 1; else if (y2 >= TUONG_DUOI) y2 = TUONG_TREN + 1;
            }

            // ==========================================
            // CÁC LUẬT SÁT THƯƠNG (CHỈ BỊ PHẠT NẾU KHÔNG TÀNG HÌNH)
            // ==========================================
            
            // 1. ĐẦU TÔNG ĐẦU (Chỉ nổ khi CẢ 2 ĐỀU HIỆN HÌNH)
            if (!bat_tu_1 && !bat_tu_2 && check1 != -1 && check2 != -1 && 
               ((x1 == x2 && y1 == y2) || (x1 == toadox2[0] && y1 == toadoy2[0] && x2 == toadox1[0] && y2 == toadoy1[0])))
            {
                if (sl1 < sl2) { tim1--; bat_tu_1 = true; thoi_gian_bat_tu_1 = clock() + 3000; } 
                else if (sl2 < sl1) { tim2--; bat_tu_2 = true; thoi_gian_bat_tu_2 = clock() + 3000; } 
                else { 
                    tim1--; bat_tu_1 = true; thoi_gian_bat_tu_1 = clock() + 3000; 
                    tim2--; bat_tu_2 = true; thoi_gian_bat_tu_2 = clock() + 3000; 
                }
                
                TextColor(14); GotoXY(x1, y1); cout << "BUM"; TextColor(7);
                Beep(1000, 200); Sleep(500); GotoXY(x1, y1); cout << "   "; ve_tuong();
                check1 = -1; huong_di_1.clear(); x1 = toadox1[0]; y1 = toadoy1[0];
                check2 = -1; huong_di_2.clear(); x2 = toadox2[0]; y2 = toadoy2[0];
            }

           // 2. GỘP CHUNG: TÔNG TƯỜNG || TÔNG ĐỊCH || TỰ CẮN ĐUÔI
            if (!bat_tu_1 && check1 != -1 && (kt_ran_cham_tuong(x1, y1) || kt_ran_cham_than_doi_thu(x1, y1, toadox2, toadoy2, sl2) || kt_ran_cham_duoi_pvp(toadox1, toadoy1, sl1))) 
            {
                tim1--; 
                bat_tu_1 = true; 
                thoi_gian_bat_tu_1 = clock() + 3000; 
                check1 = -1; 
                huong_di_1.clear(); 
                x1 = toadox1[0]; 
                y1 = toadoy1[0]; 
                Beep(500, 100);
            }

            if (!bat_tu_2 && check2 != -1 && (kt_ran_cham_tuong(x2, y2) || kt_ran_cham_than_doi_thu(x2, y2, toadox1, toadoy1, sl1) || kt_ran_cham_duoi_pvp(toadox2, toadoy2, sl2))) 
            {
                tim2--; 
                bat_tu_2 = true; 
                thoi_gian_bat_tu_2 = clock() + 3000;
                check2 = -1; 
                huong_di_2.clear(); 
                x2 = toadox2[0]; 
                y2 = toadoy2[0]; 
                Beep(500, 100);
            }

          

            // Vẽ lại quả táo (chống giật)
            TextColor(14); GotoXY(xqua, yqua); cout << "$"; TextColor(7);

            // Cập nhật thân rắn nếu còn sống và có di chuyển
            if (check1 != -1) 
            {
                xu_ly_ran_pvp(toadox1, toadoy1, x1, y1, xqua, yqua, diem1, tocdo, sl1, toadox2, toadoy2, sl2);
                x1 = toadox1[0]; y1 = toadoy1[0];
            }
            
            if (check2 != -1)
            {
                xu_ly_ran_pvp(toadox2, toadoy2, x2, y2, xqua, yqua, diem2, tocdo, sl2, toadox1, toadoy1, sl1);
                x2 = toadox2[0]; y2 = toadoy2[0];
            }

            int mau_p1 = 10; // Xanh lá
            // Nếu đang bất tử, đổi luân phiên giữa màu Xanh và Xám (Mã màu 8) mỗi 100 mili giây
            if (bat_tu_1) mau_p1 = (clock() % 200 < 100) ? 10 : 8; 
            ve_ran_pvp(toadox1, toadoy1, sl1, mau_p1, "0");

            int mau_p2 = 12; // Đỏ
            if (bat_tu_2) mau_p2 = (clock() % 200 < 100) ? 12 : 8;
            ve_ran_pvp(toadox2, toadoy2, sl2, mau_p2, "X");
      
            thoi_gian_cu = clock();
        }
        Sleep(1);
    }
}