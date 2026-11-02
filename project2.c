#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GIAODICH 100
#define TEN_FILE "data.bin"

/* ==================== 1. CAU TRUC DU LIEU (DUNG CHUAN DE BAI) ==================== */
typedef struct {
    char loai[20];          /* "Nap", "Rut", "Chuyen", "Nhan" */
    double soTien;
} GiaoDich;

typedef struct TaiKhoan {
    char soTK[15];          /* So tai khoan (he thong tu sinh: 10000001, 10000002...) */
    char hoTen[50];         /* Ho va ten chu tai khoan */
    double soDu;            /* So du tai khoan */
    GiaoDich lichSu[100];   /* Mang luu lich su 100 giao dich */
    int soGiaoDich;         /* So luong giao dich da thuc hien */
    struct TaiKhoan *next;  /* Con tro tro sang tai khoan tiep theo */
} TaiKhoan;

/* Bien toan cuc: Con tro dau cua Danh sach lien ket don */
TaiKhoan *dsTaiKhoan = NULL;

/* ==================== CAC HAM PHU TRO DON GIAN ==================== */

/* Ham nhap chuoi theo dung yeu cau: fflush(stdin) + fgets + strcspn */
void nhapChuoi(char chuoi[], int kichThuoc) {
    fflush(stdin);
    fgets(chuoi, kichThuoc, stdin);
    chuoi[strcspn(chuoi, "\n")] = 0; /* Xoa dau Enter o cuoi chuoi */
}

/* Ham tim tai khoan theo STK: Tim thay tra ve node do, khong thay tra ve NULL */
TaiKhoan *timTaiKhoan(char stkCanTim[]) {
    TaiKhoan *p = dsTaiKhoan;
    while (p != NULL) {
        if (strcmp(p->soTK, stkCanTim) == 0) {
            return p; /* Tim thay */
        }
        p = p->next;
    }
    return NULL; /* Khong tim thay */
}

/* Ham tu dong sinh STK tang dan: 10000001, 10000002... */
void tuSinhSoTK(char stkMoi[]) {
    long stkLonNhat = 10000000;
    TaiKhoan *p = dsTaiKhoan;
    while (p != NULL) {
        long soHienTai = atol(p->soTK); /* Doi chuoi STK sang so nguyen de so sanh */
        if (soHienTai > stkLonNhat) {
            stkLonNhat = soHienTai;
        }
        p = p->next;
    }
    sprintf(stkMoi, "%ld", stkLonNhat + 1); /* Cong 1 va doi nguoc lai thanh chuoi */
}

/* Ham ghi 1 giao dich vao mang lichSu[] cua tai khoan */
void luuLichSu(TaiKhoan *tk, char loaiGD[], double soTien) {
    if (tk->soGiaoDich < MAX_GIAODICH) {
        strcpy(tk->lichSu[tk->soGiaoDich].loai, loaiGD);
        tk->lichSu[tk->soGiaoDich].soTien = soTien;
        tk->soGiaoDich++;
    }
}

/* ==================== 7 CHUC NANG CHINH ==================== */

/* CHUC NANG 1: Them tai khoan moi (soDu = 0, soGiaoDich = 0) */
void themTaiKhoan() {
    TaiKhoan *node = (TaiKhoan *)malloc(sizeof(TaiKhoan));
    if (node == NULL) {
        printf("Loi: Khong du bo nho!\n");
        return;
    }

    printf("\n--- 1. MO TAI KHOAN MOI ---\n");
    printf("Nhap ho va ten khach hang: ");
    nhapChuoi(node->hoTen, sizeof(node->hoTen));

    if (strlen(node->hoTen) == 0) {
        printf("Loi: Ho ten khong duoc de trong!\n");
        free(node);
        return;
    }

    tuSinhSoTK(node->soTK);
    node->soDu = 0;
    node->soGiaoDich = 0;

    /* Chen node moi vao dau danh sach lien ket */
    node->next = dsTaiKhoan;
    dsTaiKhoan = node;

    printf("=> Mo tai khoan thanh cong!\n");
    printf("   Chu TK: %s | So TK duoc cap: %s | So du: 0 VND\n", node->hoTen, node->soTK);
}

/* CHUC NANG 2: Xoa tai khoan theo STK */
void xoaTaiKhoan() {
    char stkGoi[15];
    printf("\n--- 2. XOA TAI KHOAN ---\n");
    printf("Nhap so TK can xoa: ");
    nhapChuoi(stkGoi, sizeof(stkGoi));

    TaiKhoan *hienTai = dsTaiKhoan;
    TaiKhoan *truoc = NULL;

    while (hienTai != NULL && strcmp(hienTai->soTK, stkGoi) != 0) {
        truoc = hienTai;
        hienTai = hienTai->next;
    }

    if (hienTai == NULL) {
        printf("Loi: Khong tim thay tai khoan %s!\n", stkGoi);
        return;
    }

    /* Noi day lien ket truoc khi xoa de khong bi dut gay DSLK */
    if (truoc == NULL) {
        dsTaiKhoan = hienTai->next; /* Xoa node dau tien */
    } else {
        truoc->next = hienTai->next; /* Xoa node o giua hoac cuoi */
    }

    free(hienTai); /* Giai phong bo nho */
    printf("=> Da xoa tai khoan %s thanh cong!\n", stkGoi);
}

/* CHUC NANG 3: Sua ho ten theo STK */
void suaHoTen() {
    char stkGoi[15];
    printf("\n--- 3. SUA HO TEN CHU TAI KHOAN ---\n");
    printf("Nhap so TK can sua: ");
    nhapChuoi(stkGoi, sizeof(stkGoi));

    TaiKhoan *tk = timTaiKhoan(stkGoi);
    if (tk == NULL) {
        printf("Loi: Khong tim thay tai khoan %s!\n", stkGoi);
        return;
    }

    printf("Ho ten cu : %s\n", tk->hoTen);
    printf("Ho ten moi: ");
    nhapChuoi(tk->hoTen, sizeof(tk->hoTen));
    printf("=> Da cap nhat ho ten thanh cong!\n");
}

/* CHUC NANG 4: Giao dich (Gom chung Nap / Rut / Chuyen khoan vao 1 ham de doc) */
void giaoDich() {
    char stkGoi[15];
    int loai;
    double soTien;

    printf("\n--- 4. GIAO DICH NGAN HANG ---\n");
    printf("Nhap so TK cua ban: ");
    nhapChuoi(stkGoi, sizeof(stkGoi));

    TaiKhoan *tk = timTaiKhoan(stkGoi);
    if (tk == NULL) {
        printf("Loi: Khong tim thay tai khoan %s!\n", stkGoi);
        return;
    }

    if (tk->soGiaoDich >= MAX_GIAODICH) {
        printf("Loi: Lich su giao dich cua tai khoan nay da day (100 giao dich)!\n");
        return;
    }

    printf("Khach hang: %s | So du hien co: %.2lf VND\n", tk->hoTen, tk->soDu);
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
        tk->soDu += soTien;
        luuLichSu(tk, "Nap", soTien);
        printf("=> Nap thanh cong! So du moi: %.2lf VND\n", tk->soDu);

    } else if (loai == 2) {
        /* --- RUT TIEN --- */
        printf("Nhap so tien muon rut: ");
        scanf("%lf", &soTien);
        if (soTien <= 0) {
            printf("Loi: So tien phai lon hon 0!\n");
            return;
        }
        if (soTien > tk->soDu) {
            printf("Loi: So du khong du de rut!\n");
            return;
        }
        tk->soDu -= soTien;
        luuLichSu(tk, "Rut", soTien);
        printf("=> Rut thanh cong! So du con lai: %.2lf VND\n", tk->soDu);

    } else if (loai == 3) {
        /* --- CHUYEN KHOAN --- */
        char stkNhan[15];
        printf("Nhap so TK nguoi nhan: ");
        nhapChuoi(stkNhan, sizeof(stkNhan));

        if (strcmp(tk->soTK, stkNhan) == 0) {
            printf("Loi: Khong the chuyen cho chinh minh!\n");
            return;
        }

        TaiKhoan *tkNhan = timTaiKhoan(stkNhan);
        if (tkNhan == NULL) {
            printf("Loi: Khong tim thay tai khoan nguoi nhan!\n");
            return;
        }

        printf("Nguoi nhan: %s | Nhap so tien chuyen: ", tkNhan->hoTen);
        scanf("%lf", &soTien);
        if (soTien <= 0) {
            printf("Loi: So tien phai lon hon 0!\n");
            return;
        }
        if (soTien > tk->soDu) {
            printf("Loi: So du khong du de chuyen!\n");
            return;
        }

        tk->soDu -= soTien;
        tkNhan->soDu += soTien;

        luuLichSu(tk, "Chuyen", soTien);
        luuLichSu(tkNhan, "Nhan", soTien);

        printf("=> Chuyen khoan thanh cong! So du con lai: %.2lf VND\n", tk->soDu);
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

    TaiKhoan *tk = timTaiKhoan(stkGoi);
    if (tk == NULL) {
        printf("Loi: Khong tim thay tai khoan %s!\n", stkGoi);
        return;
    }

    printf("\n================ THONG TIN TAI KHOAN ================\n");
    printf("So TK   : %s\n", tk->soTK);
    printf("Ho ten  : %s\n", tk->hoTen);
    printf("So du   : %.2lf VND\n", tk->soDu);
    printf("---------------- LICH SU GIAO DICH (%d) --------------\n", tk->soGiaoDich);
    if (tk->soGiaoDich == 0) {
        printf("(Chua co giao dich nao)\n");
    } else {
        for (int i = 0; i < tk->soGiaoDich; i++) {
            printf("  %d. %-8s : %.2lf VND\n", i + 1, tk->lichSu[i].loai, tk->lichSu[i].soTien);
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

    TaiKhoan *tk = timTaiKhoan(stkGoi);
    if (tk == NULL) {
        printf("Loi: Khong tim thay tai khoan %s!\n", stkGoi);
        return;
    }

    if (tk->soDu <= 0) {
        printf("Tai khoan chua co so du de gui tiet kiem!\n");
        return;
    }

    printf("Tien goc hien co (P): %.2lf VND\n", tk->soDu);
    printf("Nhap lai suat 1 ky (r, vi du 0.05 la 5%%): ");
    scanf("%lf", &r);
    printf("Nhap so ky han gui (n): ");
    scanf("%d", &n);

    if (r < 0 || n < 0) {
        printf("Loi: Lai suat va ky han khong duoc am!\n");
        return;
    }

    double tongTien = tinhLaiKep(tk->soDu, r, n);
    printf("=> Sau %d ky han:\n", n);
    printf("   + Tong tien (Goc + Lai): %.2lf VND\n", tongTien);
    printf("   + Tien lai nhan duoc   : %.2lf VND\n", tongTien - tk->soDu);
}

/* CHUC NANG 7 (Tren Menu): Sap xep Bubble Sort & In danh sach toan bo tai khoan */
void sapXepVaInDanhSach() {
    if (dsTaiKhoan == NULL) {
        printf("\nDanh sach tai khoan dang rong!\n");
        return;
    }

    /* Sap xep tang dan theo So TK bang 2 vong for long nhau (Hoan vi data) */
    for (TaiKhoan *p = dsTaiKhoan; p != NULL; p = p->next) {
        for (TaiKhoan *q = p->next; q != NULL; q = q->next) {
            if (strcmp(p->soTK, q->soTK) > 0) {
                /* Hoan doi noi dung data giua 2 node p va q, giu nguyen con tro next */
                TaiKhoan tam = *p;
                TaiKhoan *nextP = p->next;
                TaiKhoan *nextQ = q->next;

                *p = *q;
                *q = tam;

                p->next = nextP;
                q->next = nextQ;
            }
        }
    }

    /* In bang danh sach sau khi da sap xep */
    printf("\n================ DANH SACH TAI KHOAN (DA SAP XEP) ================\n");
    printf("%-5s | %-12s | %-25s | %15s\n", "STT", "So TK", "Ho va Ten", "So du (VND)");
    printf("------------------------------------------------------------------\n");
    int stt = 1;
    for (TaiKhoan *p = dsTaiKhoan; p != NULL; p = p->next) {
        printf("%-5d | %-12s | %-25s | %15.2lf\n", stt++, p->soTK, p->hoTen, p->soDu);
    }
    printf("==================================================================\n");
}

/* HAM DOC / GHI FILE NHI PHAN (data.bin) */
void luuFile() {
    FILE *f = fopen(TEN_FILE, "wb");
    if (f == NULL) {
        printf("Loi: Khong mo duoc file de ghi!\n");
        return;
    }
    for (TaiKhoan *p = dsTaiKhoan; p != NULL; p = p->next) {
        fwrite(p, sizeof(TaiKhoan), 1, f);
    }
    fclose(f);
    printf("=> Da luu du lieu vao file %s!\n", TEN_FILE);
}

void docFile() {
    FILE *f = fopen(TEN_FILE, "rb");
    if (f == NULL) {
        return; /* Lan dau chay chua co file thi bo qua */
    }

    TaiKhoan tam;
    TaiKhoan *cuoi = NULL;
    while (fread(&tam, sizeof(TaiKhoan), 1, f) == 1) {
        TaiKhoan *node = (TaiKhoan *)malloc(sizeof(TaiKhoan));
        if (node == NULL) break;

        *node = tam;
        node->next = NULL;

        if (dsTaiKhoan == NULL) {
            dsTaiKhoan = node;
        } else {
            cuoi->next = node;
        }
        cuoi = node;
    }
    fclose(f);
    printf("=> Da tai du lieu tu file %s!\n", TEN_FILE);
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
        if (scanf("%d", &chon) != 1) {
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

    luuFile(); /* Luu toan bo DSLK vao file truoc khi thoat */

    /* Giai phong toan bo bo nho dong */
    while (dsTaiKhoan != NULL) {
        TaiKhoan *xoa = dsTaiKhoan;
        dsTaiKhoan = dsTaiKhoan->next;
        free(xoa);
    }

    return 0;
}
