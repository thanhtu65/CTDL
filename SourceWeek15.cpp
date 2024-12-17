#include <iostream>
#include <string>
using namespace std;

// Cấu trúc cho Bài
struct Bai {
    string tenBai;
    int soTrang;
    Bai* tiepTheo; // Con trỏ đến bài tiếp theo
};

// Cấu trúc cho Chương
struct Chuong {
    string tenChuong;
    Bai* danhSachBai; // Danh sách các bài trong chương
    Chuong* tiepTheo; // Con trỏ đến chương tiếp theo
};

// Cấu trúc cho Sách
struct Sach {
    string tenSach;  // Tên sách
    Chuong* danhSachChuong; // Danh sách các chương trong sách
};

// Hàm tạo bài mới
Bai* taoBai() {
    Bai* bai = new Bai;
    cout << "      Nhap ten bai: ";
    getline(cin, bai->tenBai);
    cout << "      Nhap so trang: ";
    cin >> bai->soTrang;
    cin.ignore(); // Xử lý dấu Enter sau khi nhập số trang
    bai->tiepTheo = nullptr;
    return bai;
}

// Hàm tạo chương mới
Chuong* taoChuong() {
    Chuong* chuong = new Chuong;
    cout << "    Nhap ten chuong: ";
    getline(cin, chuong->tenChuong);
    chuong->danhSachBai = nullptr;
    chuong->tiepTheo = nullptr;

    int soBai;
    cout << "    Nhap so bai trong chuong: ";
    cin >> soBai;
    cin.ignore(); // Xử lý dấu Enter sau khi nhập số bài

    Bai* baiTruoc = nullptr;
    for (int i = 0; i < soBai; i++) {
        Bai* baiMoi = taoBai();
        if (chuong->danhSachBai == nullptr) {
            chuong->danhSachBai = baiMoi; // Bài đầu tiên
        }
        else {
            baiTruoc->tiepTheo = baiMoi; // Liên kết bài trước
        }
        baiTruoc = baiMoi;
    }
    return chuong;
}

// Hàm kiểm tra xem chương có bài hay không
bool kiemTraChuongRong(Chuong* chuong) {
    return chuong->danhSachBai == nullptr;
}

// Hàm in thông tin chương có tổng số trang nhiều nhất
void inChuongTrangMax(Chuong* danhSachChuong) {
    Chuong* chuongHienTai = danhSachChuong;
    Chuong* chuongMax = nullptr;
    int soTrangMax = 0;

    while (chuongHienTai != nullptr) {
        int tongTrang = 0;
        Bai* baiHienTai = chuongHienTai->danhSachBai;

        // Tính tổng số trang trong chương
        while (baiHienTai != nullptr) {
            tongTrang += baiHienTai->soTrang;
            baiHienTai = baiHienTai->tiepTheo;
        }

        // Kiểm tra nếu chương hiện tại có số trang nhiều hơn
        if (tongTrang > soTrangMax) {
            soTrangMax = tongTrang;
            chuongMax = chuongHienTai;
        }

        chuongHienTai = chuongHienTai->tiepTheo;
    }

    // In chương có tổng số trang nhiều nhất
    if (chuongMax != nullptr) {
        cout << "\nChuong co so trang nhieu nhat: " << chuongMax->tenChuong << endl;
        Bai* baiHienTai = chuongMax->danhSachBai;
        while (baiHienTai != nullptr) {
            cout << "    Bai: " << baiHienTai->tenBai << " (" << baiHienTai->soTrang << " trang)\n";
            baiHienTai = baiHienTai->tiepTheo;
        }
        cout << "Tong so trang: " << soTrangMax << " trang\n";
    }
}

// Hàm nhập thông tin sách
Sach* taoSach() {
    Sach* sach = new Sach;
    cout << "Nhap ten sach: ";
    getline(cin, sach->tenSach);
    sach->danhSachChuong = nullptr;

    int soChuong;
    cout << "Nhap so chuong trong sach: ";
    cin >> soChuong;
    cin.ignore(); // Xử lý dấu Enter sau khi nhập số chương

    Chuong* chuongTruoc = nullptr;
    for (int i = 0; i < soChuong; i++) {
        Chuong* chuongMoi = taoChuong();
        if (chuongTruoc == nullptr) {
            sach->danhSachChuong = chuongMoi; // Chương đầu tiên
        }
        else {
            chuongTruoc->tiepTheo = chuongMoi; // Liên kết chương trước
        }
        chuongTruoc = chuongMoi;
    }

    return sach;
}

// Hàm in nội dung sách
void inSach(Sach* sach) {
    cout << "\n--- NOI DUNG CUA SACH: " << sach->tenSach << " ---\n";

    Chuong* chuongHienTai = sach->danhSachChuong;
    while (chuongHienTai != nullptr) {
        cout << "  Chuong: " << chuongHienTai->tenChuong << "\n";

        Bai* baiHienTai = chuongHienTai->danhSachBai;
        while (baiHienTai != nullptr) {
            cout << "    Bai: " << baiHienTai->tenBai
                << " (" << baiHienTai->soTrang << " trang)\n";
            baiHienTai = baiHienTai->tiepTheo;
        }

        chuongHienTai = chuongHienTai->tiepTheo;
    }
}
// Hàm in ra số chương của cuốn sách
void inSoChuong(Sach* sach) {
    int soChuong = 0;
    Chuong* chuongHienTai = sach->danhSachChuong;
    while (chuongHienTai != nullptr) {
        soChuong++;
        chuongHienTai = chuongHienTai->tiepTheo;
    }
    cout << "\n Tong so chuong : " << soChuong << endl;
}

// Hàm tìm kiếm chương theo tên và xóa chương đó
void timVaXoaChuong(Sach* sach, const string& tenChuong) {
    Chuong* chuongHienTai = sach->danhSachChuong;
    Chuong* chuongTruoc = nullptr;

    while (chuongHienTai != nullptr) {
        if (chuongHienTai->tenChuong == tenChuong) {
            if (chuongTruoc == nullptr) {
                // Xóa chương đầu tiên
                sach->danhSachChuong = chuongHienTai->tiepTheo;
            }
            else {
                // Liên kết chương trước với chương sau khi xóa
                chuongTruoc->tiepTheo = chuongHienTai->tiepTheo;
            }
            delete chuongHienTai; // Giải phóng bộ nhớ
            cout << "Chuong '" << tenChuong << "' da bi xoa.\n";
            return;
        }
        chuongTruoc = chuongHienTai;
        chuongHienTai = chuongHienTai->tiepTheo;
    }

    cout << "Chuong '" << tenChuong << "' khong ton tai.\n";
}

int main() {
    // Tạo sách từ bàn phím
    Sach* sach = taoSach();

    // In toàn bộ nội dung của sách
    inSach(sach);

    // In số chương của sách
    inSoChuong(sach);

    // Kiểm tra và in ra chương có trang nhiều nhất
    inChuongTrangMax(sach->danhSachChuong);

    // Tìm kiếm và xóa chương theo tên
    string tenChuongCanXoa;
    cout << "Nhap ten chuong muon xoa: ";
    getline(cin, tenChuongCanXoa);
    timVaXoaChuong(sach, tenChuongCanXoa);

    // In lại nội dung sách sau khi xóa chương
    cout << "\nSau khi xoa chuong:\n";
    inSach(sach);

    return 0;
}


