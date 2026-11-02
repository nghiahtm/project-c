#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.c"

/* Nhap chuoi: fgets + xoa dau Enter '\n' o cuoi chuoi */
void nhapChuoi(char chuoi[], int kichThuoc) {
    fgets(chuoi, kichThuoc, stdin);
    chuoi[strcspn(chuoi, "\n")] = 0;
}

/* Tim vi tri cua tai khoan trong mang theo STK.
   Tim thay: tra ve chi so i (tu 0 den soLuongTK - 1).
   Khong tim thay: tra ve -1. */
int timViTriTK(char stkCanTim[], int soLuongTK) {
    for (int i = 0; i < soLuongTK; i++) {
        if (strcmp(dsTaiKhoan[i].soTK, stkCanTim) == 0) {
            return i;
        }
    }
    return -1;
}

/* Tu dong sinh So TK tang dan (10000001, 10000002...), khong bao gio trung */
void tuSinhSoTK(char stkMoi[], int soLuongTK) {
    long stkLonNhat = 10000000;
    for (int i = 0; i < soLuongTK; i++) {
        long soHienTai = atol(dsTaiKhoan[i].soTK);
        if (soHienTai > stkLonNhat) {
            stkLonNhat = soHienTai;
        }
    }
    sprintf(stkMoi, "%ld", stkLonNhat + 1);
}


/* CHUC NANG: Them tai khoan moi (soDu = 0, soGiaoDich = 0) */
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

    tuSinhSoTK(tkMoi.soTK,soLuongTK);
    tkMoi.soDu = 0;
    tkMoi.soGiaoDich = 0;

    /* Dua tai khoan moi vao cuoi mang va tang so luong */
    dsTaiKhoan[soLuongTK] = tkMoi;
    soLuongTK++;

    printf("=> Mo tai khoan thanh cong!\n");
    printf("   Chu TK: %s | So TK duoc cap: %s | So du: 0 VND\n", tkMoi.hoTen, tkMoi.soTK);
}

/* CHUC NANG: Xoa tai khoan theo STK */
void xoaTaiKhoan() {
    char stkGoi[15];
    printf("\n--- 2. XOA TAI KHOAN ---\n");
    printf("Nhap so TK can xoa: ");
    nhapChuoi(stkGoi, sizeof(stkGoi));

    int vt = timViTriTK(stkGoi,soLuongTK);
    if (vt == -1) {
        printf("Khong tim thay tai khoan %s!\n", stkGoi);
        return;
    }

    /* Dich cac phan tu phia sau len 1 o de de len vi tri can xoa */
    for (int i = vt; i < soLuongTK - 1; i++) {
        dsTaiKhoan[i] = dsTaiKhoan[i + 1];
    }
    soLuongTK--;

    printf("=> Da xoa tai khoan %s thanh cong!\n", stkGoi);
}

/* CHUC NANG: Sua ho ten theo STK */
void suaHoTen() {
    char stkGoi[15];
    printf("\n--- 3. SUA HO TEN CHU TAI KHOAN ---\n");
    printf("Nhap so TK can sua: ");
    nhapChuoi(stkGoi, sizeof(stkGoi));

    int vt = timViTriTK(stkGoi,soLuongTK);
    if (vt == -1) {
        printf("Loi: Khong tim thay tai khoan %s!\n", stkGoi);
        return;
    }

    printf("Ho ten cu : %s\n", dsTaiKhoan[vt].hoTen);
    printf("Ho ten moi: ");
    nhapChuoi(dsTaiKhoan[vt].hoTen, sizeof(dsTaiKhoan[vt].hoTen));
    printf("=> Da cap nhat ho ten thanh cong!\n");
}
