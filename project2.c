#include <stdio.h>
#include <string.h>
#include "config.c"
#include "tinh_lai_kep.c"
#include "quan_ly_tk.c"

/* ==================== CAC HAM PHU TRO ==================== */

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

/* CHUC NANG 4: Giao dich (Nap / Rut / Chuyen khoan) */
void giaoDich() {
    char stkGoi[15];
    int loai;
    double soTien;

    printf("\n--- 4. GIAO DICH NGAN HANG ---\n");
    printf("Nhap so TK cua ban: ");
    nhapChuoi(stkGoi, sizeof(stkGoi));

    int vt = timViTriTK(stkGoi,soLuongTK);
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
    xoaBoDem();

    if (loai == NAP_TIEN) {
        /* --- NAP TIEN --- */
        printf("Nhap so tien muon nap: ");
        scanf("%lf", &soTien);
        xoaBoDem();
        if (soTien <= 0) {
            printf("Loi: So tien phai lon hon 0!\n");
            return;
        }
        dsTaiKhoan[vt].soDu += soTien;
        luuLichSu(vt, "Nap", soTien);
        printf("=> Nap thanh cong! So du moi: %.2lf VND\n", dsTaiKhoan[vt].soDu);

    } else if (loai == RUT_TIEN) {
        /* --- RUT TIEN --- */
        printf("Nhap so tien muon rut: ");
        scanf("%lf", &soTien);
        xoaBoDem();
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

    } else if (loai == CHUYEN_KHOAN) {
        /* --- CHUYEN KHOAN --- */
        char stkNhan[15];
        printf("Nhap so TK nguoi nhan: ");
        nhapChuoi(stkNhan, sizeof(stkNhan));

        if (strcmp(dsTaiKhoan[vt].soTK, stkNhan) == 0) {
            printf("Loi: Khong the chuyen cho chinh minh!\n");
            return;
        }

        int vtNhan = timViTriTK(stkNhan,soLuongTK);
        if (vtNhan == -1) {
            printf("Loi: Khong tim thay tai khoan nguoi nhan!\n");
            return;
        }

        printf("Nguoi nhan: %s | Nhap so tien chuyen: ", dsTaiKhoan[vtNhan].hoTen);
        scanf("%lf", &soTien);
        xoaBoDem();
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

    int vt = timViTriTK(stkGoi,soLuongTK);
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

void tinhLaiTietKiem() {
    char stkGoi[15];
    double r;
    int n;

    printf("\n--- 6. TINH LAI KEP TIET KIEM ---\n");
    printf("Nhap so TK muon tinh lai: ");
    nhapChuoi(stkGoi, sizeof(stkGoi));

    int vt = timViTriTK(stkGoi,soLuongTK);
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
    xoaBoDem();
    printf("Nhap so ky han gui (n): ");
    scanf("%d", &n);
    xoaBoDem();

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
            sortTK(&dsTaiKhoan[i],&dsTaiKhoan[j]);
        
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

        if (scanf("%d", &chon) != 1) {
            chon = -1;
        }
        xoaBoDem();

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
