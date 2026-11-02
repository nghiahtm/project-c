#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAIKHOAN 100
#define MAX_GIAODICH 100
#define TEN_FILE "data.bin"

/* ==================== 1. CAU TRUC DU LIEU ==================== */
typedef struct {
    char loai[20];          /* "Nap", "Rut", "Chuyen", "Nhan" */
    double soTien;
} GiaoDich;

typedef struct {
    char soTK[15];                  /* So tai khoan (tu dong sinh: 10000001, 10000002...) */
    char hoTen[50];                 /* Ho va ten chu tai khoan */
    double soDu;                    /* So du tai khoan */
    GiaoDich lichSu[MAX_GIAODICH];  /* Mang luu lich su 100 giao dich */
    int soGiaoDich;                 /* So luong giao dich da thuc hien */
} TaiKhoan;

/* Mang 1 chieu luu danh sach tai khoan va bien dem so luong */
TaiKhoan dsTaiKhoan[MAX_TAIKHOAN];
int soLuongTK = 0;

/* ==================== CAC HAM PHU TRO ==================== */

/* Nhap chuoi an toan: xoa bo dem + fgets + xoa dau Enter '\n' */
void nhapChuoi(char chuoi[], int kichThuoc) {
    fflush(stdin);
    fgets(chuoi, kichThuoc, stdin);
    chuoi[strcspn(chuoi, "\n")] = 0;
}

/* Tim vi tri cua tai khoan trong mang theo STK.
   Tim thay: tra ve chi so i (tu 0 den soLuongTK - 1).
   Khong tim thay: tra ve -1. */
int timViTriTK(char stkCanTim[]) {
    for (int i = 0; i < soLuongTK; i++) {
        if (strcmp(dsTaiKhoan[i].soTK, stkCanTim) == 0) {
            return i;
        }
    }
    return -1;
}

/* Tu dong sinh So TK tang dan (10000001, 10000002...), khong bao gio trung */
void tuSinhSoTK(char stkMoi[]) {
    long stkLonNhat = 10000000;
    for (int i = 0; i < soLuongTK; i++) {
        long soHienTai = atol(dsTaiKhoan[i].soTK);
        if (soHienTai > stkLonNhat) {
            stkLonNhat = soHienTai;
        }
    }
    sprintf(stkMoi, "%ld", stkLonNhat + 1);
}

/* Ghi 1 giao dich vao mang lichSu[] cua tai khoan tai vi tri vt */
void luuLichSu(int vt, char loaiGD[], double soTien) {
    int k = dsTaiKhoan[vt].soGiaoDich;
    if (k < MAX_GIAODICH) {
        strcpy(dsTaiKhoan[vt].lichSu[k].loai, loaiGD);
        dsTaiKhoan[vt].lichSu[k].soTien = soTien;
        dsTaiKhoan[vt].soGiaoDich++;
    }
}

/* ==================== 7 CHUC NANG CHINH ==================== */

/* CHUC NANG 1: Them tai khoan moi (soDu = 0, soGiaoDich = 0) */
void themTaiKhoan() {
    if (soLuongTK >= MAX_TAIKHOAN) {
        printf("Loi: Danh sach tai khoan da day (%d tai khoan)!\n", MAX_TAIKHOAN);
        return;
    }

    TaiKhoan tkMoi;
    printf("\n--- 1. MO TAI KHOAN MOI ---\n");
    printf("Nhap ho va ten khach hang: ");
    nhapChuoi(tkMoi.hoTen, sizeof(tkMoi.hoTen));

    if (strlen(tkMoi.hoTen) == 0) {
        printf("Loi: Ho ten khong duoc de trong!\n");
        return;
    }

    tuSinhSoTK(tkMoi.soTK);
    tkMoi.soDu = 0;
    tkMoi.soGiaoDich = 0;

    /* Dua tai khoan moi vao cuoi mang va tang so luong */
    dsTaiKhoan[soLuongTK] = tkMoi;
    soLuongTK++;

    printf("=> Mo tai khoan thanh cong!\n");
    printf("   Chu TK: %s | So TK duoc cap: %s | So du: 0 VND\n", tkMoi.hoTen, tkMoi.soTK);
}

/* CHUC NANG 2: Xoa tai khoan theo STK */
void xoaTaiKhoan() {
    char stkGoi[15];
    printf("\n--- 2. XOA TAI KHOAN ---\n");
    printf("Nhap so TK can xoa: ");
    nhapChuoi(stkGoi, sizeof(stkGoi));

    int vt = timViTriTK(stkGoi);
    if (vt == -1) {
        printf("Loi: Khong tim thay tai khoan %s!\n", stkGoi);
        return;
    }

    /* Dich cac phan tu phia sau len 1 o de de len vi tri can xoa */
    for (int i = vt; i < soLuongTK - 1; i++) {
        dsTaiKhoan[i] = dsTaiKhoan[i + 1];
    }
    soLuongTK--;

    printf("=> Da xoa tai khoan %s thanh cong!\n", stkGoi);
}

/* CHUC NANG 3: Sua ho ten theo STK */
void suaHoTen() {
    char stkGoi[15];
    printf("\n--- 3. SUA HO TEN CHU TAI KHOAN ---\n");
    printf("Nhap so TK can sua: ");
    nhapChuoi(stkGoi, sizeof(stkGoi));

    int vt = timViTriTK(stkGoi);
    if (vt == -1) {
        printf("Loi: Khong tim thay tai khoan %s!\n", stkGoi);
        return;
    }

    printf("Ho ten cu : %s\n", dsTaiKhoan[vt].hoTen);
    printf("Ho ten moi: ");
    nhapChuoi(dsTaiKhoan[vt].hoTen, sizeof(dsTaiKhoan[vt].hoTen));
    printf("=> Da cap nhat ho ten thanh cong!\n");
}

/* CHUC NANG 4: Giao dich (Nap / Rut / Chuyen khoan) */
void giaoDich() {
    char stkGoi[15];
    int loai;
    double soTien;

    printf("\n--- 4. GIAO DICH NGAN HANG ---\n");
    printf("Nhap so TK cua ban: ");
    nhapChuoi(stkGoi, sizeof(stkGoi));

    int vt = timViTriTK(stkGoi);
    if (vt == -1) {
        printf("Loi: Khong tim thay tai khoan %s!\n", stkGoi);
        return;
    }

    if (dsTaiKhoan[vt].soGiaoDich >= MAX_GIAODICH) {
        printf("Loi: Lich su giao dich cua tai khoan nay da day (100 giao dich)!\n");
        return;
    }

    printf("Khach hang: %s | So du hien co: %.2lf VND\n", dsTaiKhoan[vt].hoTen, dsTaiKhoan[vt].soDu);
    printf("  1. Nap tien\n  2. Rut tien\n  3. Chuyen khoan\nChon (1-3): ");
    scanf("%d", &loai);

    if (loai == 1) {
        /* --- NAP TIEN --- */
        printf("Nhap so tien muon nap: ");
        scanf("%lf", &soTien);
        if (soTien <= 0) {
            printf("Loi: So tien phai lon hon 0!\n");
            return;
        }
        dsTaiKhoan[vt].soDu += soTien;
        luuLichSu(vt, "Nap", soTien);
        printf("=> Nap thanh cong! So du moi: %.2lf VND\n", dsTaiKhoan[vt].soDu);

    } else if (loai == 2) {
        /* --- RUT TIEN --- */
        printf("Nhap so tien muon rut: ");
        scanf("%lf", &soTien);
        if (soTien <= 0) {
            printf("Loi: So tien phai lon hon 0!\n");
            return;
        }
        if (soTien > dsTaiKhoan[vt].soDu) {
            printf("Loi: So du khong du de rut!\n");
            return;
        }
        dsTaiKhoan[vt].soDu -= soTien;
        luuLichSu(vt, "Rut", soTien);
        printf("=> Rut thanh cong! So du con lai: %.2lf VND\n", dsTaiKhoan[vt].soDu);

    } else if (loai == 3) {
        /* --- CHUYEN KHOAN --- */
        char stkNhan[15];
        printf("Nhap so TK nguoi nhan: ");
        nhapChuoi(stkNhan, sizeof(stkNhan));

        if (strcmp(dsTaiKhoan[vt].soTK, stkNhan) == 0) {
            printf("Loi: Khong the chuyen cho chinh minh!\n");
            return;
        }

        int vtNhan = timViTriTK(stkNhan);
        if (vtNhan == -1) {
            printf("Loi: Khong tim thay tai khoan nguoi nhan!\n");
            return;
        }

        printf("Nguoi nhan: %s | Nhap so tien chuyen: ", dsTaiKhoan[vtNhan].hoTen);
        scanf("%lf", &soTien);
        if (soTien <= 0) {
            printf("Loi: So tien phai lon hon 0!\n");
            return;
        }
        if (soTien > dsTaiKhoan[vt].soDu) {
            printf("Loi: So du khong du de chuyen!\n");
            return;
        }

        dsTaiKhoan[vt].soDu -= soTien;
        dsTaiKhoan[vtNhan].soDu += soTien;

        luuLichSu(vt, "Chuyen", soTien);
        luuLichSu(vtNhan, "Nhan", soTien);

        printf("=> Chuyen khoan thanh cong! So du con lai: %.2lf VND\n", dsTaiKhoan[vt].soDu);
    } else {
        printf("Loi: Lua chon khong hop le!\n");
    }
}

/* CHUC NANG 5: In thong tin 1 tai khoan va toan bo lich su giao dich */
void inThongTin() {
    char stkGoi[15];
    printf("\n--- 5. TRA CUU TAI KHOAN & LICH SU ---\n");
    printf("Nhap so TK can xem: ");
    nhapChuoi(stkGoi, sizeof(stkGoi));

    int vt = timViTriTK(stkGoi);
    if (vt == -1) {
        printf("Loi: Khong tim thay tai khoan %s!\n", stkGoi);
        return;
    }

    printf("\n================ THONG TIN TAI KHOAN ================\n");
    printf("So TK   : %s\n", dsTaiKhoan[vt].soTK);
    printf("Ho ten  : %s\n", dsTaiKhoan[vt].hoTen);
    printf("So du   : %.2lf VND\n", dsTaiKhoan[vt].soDu);
    printf("---------------- LICH SU GIAO DICH (%d) --------------\n", dsTaiKhoan[vt].soGiaoDich);
    if (dsTaiKhoan[vt].soGiaoDich == 0) {
        printf("(Chua co giao dich nao)\n");
    } else {
        for (int i = 0; i < dsTaiKhoan[vt].soGiaoDich; i++) {
            printf("  %d. %-8s : %.2lf VND\n",
                   i + 1,
                   dsTaiKhoan[vt].lichSu[i].loai,
                   dsTaiKhoan[vt].lichSu[i].soTien);
        }
    }
    printf("=====================================================\n");
}

/* CHUC NANG 6: Ham de quy tinh lai kep P * (1 + r)^n */
double tinhLaiKep(double P, double r, int n) {
    if (n == 0) {
        return P; /* Dieu kien dung de quy */
    }
    return tinhLaiKep(P * (1 + r), r, n - 1); /* Goi de quy cho ky tiep theo */
}

void tinhLaiTietKiem() {
    char stkGoi[15];
    double r;
    int n;

    printf("\n--- 6. TINH LAI KEP TIET KIEM ---\n");
    printf("Nhap so TK muon tinh lai: ");
    nhapChuoi(stkGoi, sizeof(stkGoi));

    int vt = timViTriTK(stkGoi);
    if (vt == -1) {
        printf("Loi: Khong tim thay tai khoan %s!\n", stkGoi);
        return;
    }

    if (dsTaiKhoan[vt].soDu <= 0) {
        printf("Tai khoan chua co so du de gui tiet kiem!\n");
        return;
    }

    printf("Tien goc hien co (P): %.2lf VND\n", dsTaiKhoan[vt].soDu);
    printf("Nhap lai suat 1 ky (r, vi du 0.05 la 5%%): ");
    scanf("%lf", &r);
    printf("Nhap so ky han gui (n): ");
    scanf("%d", &n);

    if (r < 0 || n < 0) {
        printf("Loi: Lai suat va ky han khong duoc am!\n");
        return;
    }

    double tongTien = tinhLaiKep(dsTaiKhoan[vt].soDu, r, n);
    printf("=> Sau %d ky han:\n", n);
    printf("   + Tong tien (Goc + Lai): %.2lf VND\n", tongTien);
    printf("   + Tien lai nhan duoc   : %.2lf VND\n", tongTien - dsTaiKhoan[vt].soDu);
}

/* CHUC NANG 7 (Tren Menu): Sap xep & In danh sach toan bo tai khoan */
void sapXepVaInDanhSach() {
    if (soLuongTK == 0) {
        printf("\nDanh sach tai khoan dang rong!\n");
        return;
    }

    /* Sap xep mang tang dan theo So TK bang 2 vong for co ban */
    for (int i = 0; i < soLuongTK - 1; i++) {
        for (int j = i + 1; j < soLuongTK; j++) {
            if (strcmp(dsTaiKhoan[i].soTK, dsTaiKhoan[j].soTK) > 0) {
                TaiKhoan tam = dsTaiKhoan[i];
                dsTaiKhoan[i] = dsTaiKhoan[j];
                dsTaiKhoan[j] = tam;
            }
        }
    }

    /* In bang danh sach tai khoan */
    printf("\n================ DANH SACH TAI KHOAN (%d TK) ================\n", soLuongTK);
    printf("%-5s | %-12s | %-25s | %15s\n", "STT", "So TK", "Ho va Ten", "So du (VND)");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < soLuongTK; i++) {
        printf("%-5d | %-12s | %-25s | %15.2lf\n",
               i + 1, dsTaiKhoan[i].soTK, dsTaiKhoan[i].hoTen, dsTaiKhoan[i].soDu);
    }
    printf("=============================================================\n");
}

/* HAM DOC / GHI FILE NHI PHAN (data.bin) */
void luuFile() {
    FILE *f = fopen(TEN_FILE, "wb");
    if (f == NULL) {
        printf("Loi: Khong mo duoc file de ghi!\n");
        return;
    }
    /* Ghi toan bo mang dsTaiKhoan (soLuongTK phan tu) xuong file */
    fwrite(dsTaiKhoan, sizeof(TaiKhoan), soLuongTK, f);
    fclose(f);
    printf("=> Da luu %d tai khoan vao file %s!\n", soLuongTK, TEN_FILE);
}

void docFile() {
    FILE *f = fopen(TEN_FILE, "rb");
    if (f == NULL) {
        return; /* Lan dau chay chua co file thi bo qua */
    }

    soLuongTK = 0;
    /* Doc tung tai khoan tu file dua vao mang dsTaiKhoan */
    while (soLuongTK < MAX_TAIKHOAN && fread(&dsTaiKhoan[soLuongTK], sizeof(TaiKhoan), 1, f) == 1) {
        soLuongTK++;
    }
    fclose(f);
    printf("=> Da tai %d tai khoan tu file %s!\n", soLuongTK, TEN_FILE);
}

/* ==================== HAM MAIN & MENU ==================== */
int main() {
    docFile(); /* Doc du lieu tu file ngay khi mo chuong trinh */

    int chon;
    do {
        printf("\n========== QUAN LY NGAN HANG ==========\n");
        printf("1. Them tai khoan moi (Tu dong cap STK)\n");
        printf("2. Xoa tai khoan theo STK\n");
        printf("3. Sua ho ten theo STK\n");
        printf("4. Giao dich (Nap / Rut / Chuyen khoan)\n");
        printf("5. Xem chi tiet 1 tai khoan & Lich su\n");
        printf("6. Tinh lai kep tiet kiem (De quy)\n");
        printf("7. Sap xep & In danh sach tai khoan\n");
        printf("0. Thoat va Luu du lieu\n");
        printf("=======================================\n");
        printf("Moi ban chon (0-7): ");

        fflush(stdin);
        int kq = scanf("%d", &chon);
        if (kq == EOF) break;
        if (kq != 1) {
            chon = -1;
        }

        switch (chon) {
            case 1: themTaiKhoan(); break;
            case 2: xoaTaiKhoan(); break;
            case 3: suaHoTen(); break;
            case 4: giaoDich(); break;
            case 5: inThongTin(); break;
            case 6: tinhLaiTietKiem(); break;
            case 7: sapXepVaInDanhSach(); break;
            case 0: printf("\nDang luu file va thoat...\n"); break;
            default: printf("Lua chon khong hop le, vui long chon lai!\n");
        }
    } while (chon != 0);

    luuFile(); /* Luu toan bo mang vao file truoc khi thoat */
    return 0;
}
