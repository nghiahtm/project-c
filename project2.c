#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GIAODICH 100
#define DATA_FILE "data.bin"

/* ==================== 1. CAU TRUC DU LIEU CHUAN DE BAI ==================== */
typedef struct {
    char loai[20];      /* "Nap", "Rut", "Chuyen", "Nhan" */
    double soTien;
} GiaoDich;

typedef struct TaiKhoan {
    char soTK[15];          /* He thong tu dong sinh (VD: 10000001, 10000002...) */
    char hoTen[50];         /* Nguoi dung nhap: Ho va ten */
    double soDu;            /* So du khoi tao = 0.0 */
    GiaoDich lichSu[100];   /* Mang 100 giao dich */
    int soGiaoDich;         /* So giao dich khoi tao = 0 */
    struct TaiKhoan *next;  /* Con tro toi node ke tiep (DSLK don) */
} TaiKhoan;

/* Con tro quan ly danh sach lien ket don */
TaiKhoan *dsTaiKhoan = NULL;

/* ==================== CAC HAM TIEN ICH ==================== */

/* Xoa toan bo ky tu con lai trong dong dem ban phim */
void xoaBoDem(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/* Nhap chuoi an toan: fflush + fgets + strcspn xoa '\n' theo dung de bai */
void nhapChuoi(char *dest, int size) {
    fflush(stdin);
    if (fgets(dest, size, stdin) != NULL) {
        dest[strcspn(dest, "\n")] = '\0';
    }
}

/* Tim tai khoan theo So Tai Khoan (STK), tra ve con tro hoac NULL */
TaiKhoan *timTaiKhoan(const char *stk) {
    TaiKhoan *cur = dsTaiKhoan;
    while (cur != NULL) {
        if (strcmp(cur->soTK, stk) == 0) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

/* 
 * Ham tu dong sinh So Tai Khoan (Auto-generate STK):
 * Khoi tao tu 10000001 (8 chu so).
 * Duyet qua danh sach tim STK lon nhat hien tai roi cong 1.
 * Dam bao STK tang dan deu va KHONG BAO GIO TRUNG LAP.
 */
void sinhSoTaiKhoan(char *dest) {
    long maxVal = 10000000L;
    TaiKhoan *cur = dsTaiKhoan;
    while (cur != NULL) {
        long val = atol(cur->soTK);
        if (val > maxVal) {
            maxVal = val;
        }
        cur = cur->next;
    }
    sprintf(dest, "%ld", maxVal + 1);
}

/* Nhap so tien hop le (> 0) */
int nhapSoTien(const char *thongBao, double *soTien) {
    printf("%s", thongBao);
    if (scanf("%lf", soTien) != 1) {
        xoaBoDem();
        printf("Loi: So tien nhap vao khong hop le.\n");
        return 0;
    }
    xoaBoDem();
    if (*soTien <= 0) {
        printf("Loi: So tien phai lon hon 0.\n");
        return 0;
    }
    return 1;
}

/* Ghi nhan 1 giao dich vao mang lich su */
int ghiGiaoDich(TaiKhoan *tk, const char *loai, double soTien) {
    if (tk->soGiaoDich >= MAX_GIAODICH) {
        printf("Canh bao: Lich su giao dich cua TK %s da day (%d)!\n", tk->soTK, MAX_GIAODICH);
        return 0;
    }
    strcpy(tk->lichSu[tk->soGiaoDich].loai, loai);
    tk->lichSu[tk->soGiaoDich].soTien = soTien;
    tk->soGiaoDich++;
    return 1;
}

/* ==================== 7 CHUC NANG CHINH ==================== */

/* 
 * HAM 1: Them tai khoan moi (soDu = 0, soGiaoDich = 0)
 * Nguoi dung chi can nhap Ho ten.
 * He thong tu dong sinh So TK duy nhat.
 */
void themTaiKhoan(void) {
    TaiKhoan *node = (TaiKhoan *)malloc(sizeof(TaiKhoan));
    if (node == NULL) {
        printf("Loi: Khong du bo nho RAM de cap phat!\n");
        return;
    }

    printf("\n--- 1. MO TAI KHOAN NGAN HANG MOI ---\n");
    printf("Nhap ho va ten chu tai khoan: ");
    nhapChuoi(node->hoTen, sizeof(node->hoTen));

    if (strlen(node->hoTen) == 0) {
        printf("Loi: Ho ten khong duoc de trong!\n");
        free(node);
        return;
    }

    /* He thong tu dong cap so tai khoan */
    sinhSoTaiKhoan(node->soTK);
    node->soDu = 0.0;
    node->soGiaoDich = 0;

    /* Chen vao dau danh sach lien ket */
    node->next = dsTaiKhoan;
    dsTaiKhoan = node;

    printf("\n>>> MO TAI KHOAN THANH CONG! <<<\n");
    printf("  + Chu tai khoan : %s\n", node->hoTen);
    printf("  + SO TAI KHOAN  : %s (He thong tu dong sinh)\n", node->soTK);
    printf("  + So du ban dau : 0.00 VND\n");
}

/* HAM 2: Xoa tai khoan theo STK */
void xoaTaiKhoan(void) {
    char stkGoi[15];
    printf("\n--- 2. DONG / XOA TAI KHOAN THEO STK ---\n");
    printf("Nhap so TK can xoa: ");
    nhapChuoi(stkGoi, sizeof(stkGoi));

    TaiKhoan *cur = dsTaiKhoan;
    TaiKhoan *prev = NULL;

    while (cur != NULL && strcmp(cur->soTK, stkGoi) != 0) {
        prev = cur;
        cur = cur->next;
    }

    if (cur == NULL) {
        printf("Loi: Khong tim thay tai khoan co so TK [%s]!\n", stkGoi);
        return;
    }

    if (cur->soDu > 0) {
        printf("Canh bao: Tai khoan van con so du %.2lf VND. Vui long rut het tien truoc khi dong!\n", cur->soDu);
        return;
    }

    if (prev == NULL) {
        dsTaiKhoan = cur->next;
    } else {
        prev->next = cur->next;
    }

    printf("=> Da dong va giai phong bo nho cho tai khoan [%s] cua [%s]!\n", cur->soTK, cur->hoTen);
    free(cur);
}

/* HAM 3: Sua ho ten theo STK */
void suaHoTen(void) {
    char stkGoi[15];
    printf("\n--- 3. SUA HO TEN CHU TAI KHOAN ---\n");
    printf("Nhap so TK can sua ho ten: ");
    nhapChuoi(stkGoi, sizeof(stkGoi));

    TaiKhoan *cur = timTaiKhoan(stkGoi);
    if (cur == NULL) {
        printf("Loi: Khong tim thay tai khoan [%s]!\n", stkGoi);
        return;
    }

    printf("Ho ten hien tai : %s\n", cur->hoTen);
    printf("Nhap ho ten moi : ");
    nhapChuoi(cur->hoTen, sizeof(cur->hoTen));
    printf("=> Da cap nhat ho ten moi thanh cong cho TK [%s]!\n", cur->soTK);
}

/* HAM 4: Giao dich (Nap / Rut / Chuyen khoan) */
void napTien(TaiKhoan *tk) {
    double soTien;
    if (!nhapSoTien("Nhap so tien can nap: ", &soTien)) return;
    if (tk->soGiaoDich >= MAX_GIAODICH) {
        printf("Loi: Lich su giao dich da day, khong the nap them!\n");
        return;
    }
    tk->soDu += soTien;
    ghiGiaoDich(tk, "Nap", soTien);
    printf("=> Nap tien thanh cong! So du hien tai: %.2lf VND\n", tk->soDu);
}

void rutTien(TaiKhoan *tk) {
    double soTien;
    if (!nhapSoTien("Nhap so tien can rut: ", &soTien)) return;
    if (soTien > tk->soDu) {
        printf("Loi: So du khong du (Hien co: %.2lf VND)!\n", tk->soDu);
        return;
    }
    if (tk->soGiaoDich >= MAX_GIAODICH) {
        printf("Loi: Lich su giao dich da day, khong the rut!\n");
        return;
    }
    tk->soDu -= soTien;
    ghiGiaoDich(tk, "Rut", soTien);
    printf("=> Rut tien thanh cong! So du con lai: %.2lf VND\n", tk->soDu);
}

void chuyenKhoan(TaiKhoan *src) {
    char stkDen[15];
    double soTien;
    printf("Nhap so TK nguoi nhan: ");
    nhapChuoi(stkDen, sizeof(stkDen));

    if (strcmp(src->soTK, stkDen) == 0) {
        printf("Loi: Khong the tu chuyen tien cho chinh minh!\n");
        return;
    }

    TaiKhoan *dst = timTaiKhoan(stkDen);
    if (dst == NULL) {
        printf("Loi: Khong tim thay tai khoan nguoi nhan [%s]!\n", stkDen);
        return;
    }

    if (!nhapSoTien("Nhap so tien can chuyen: ", &soTien)) return;

    if (soTien > src->soDu) {
        printf("Loi: So du khong du (Hien co: %.2lf VND)!\n", src->soDu);
        return;
    }

    if (src->soGiaoDich >= MAX_GIAODICH || dst->soGiaoDich >= MAX_GIAODICH) {
        printf("Loi: Lich su giao dich cua mot trong hai tai khoan da day!\n");
        return;
    }

    /* Thuc hien tru va cong tien */
    src->soDu -= soTien;
    dst->soDu += soTien;

    /* Ghi lich su cho ca 2 ben */
    ghiGiaoDich(src, "Chuyen", soTien);
    ghiGiaoDich(dst, "Nhan", soTien);

    printf("=> Chuyen khoan thanh cong den [%s - %s]!\n", dst->soTK, dst->hoTen);
    printf("   So du moi cua ban [%s]: %.2lf VND\n", src->soTK, src->soDu);
}

void giaoDich(void) {
    char stkGoi[15];
    int luaChon;
    printf("\n--- 4. GIAO DICH NGAN HANG ---\n");
    printf("Nhap so TK thuc hien giao dich: ");
    nhapChuoi(stkGoi, sizeof(stkGoi));

    TaiKhoan *tk = timTaiKhoan(stkGoi);
    if (tk == NULL) {
        printf("Loi: Khong tim thay tai khoan [%s]!\n", stkGoi);
        return;
    }

    printf("Khach hang: %s | So du hien co: %.2lf VND\n", tk->hoTen, tk->soDu);
    printf("  1. Nap tien vao tai khoan\n");
    printf("  2. Rut tien khoi tai khoan\n");
    printf("  3. Chuyen khoan sang tai khoan khac\n");
    printf("Chon thao tac (1-3): ");
    if (scanf("%d", &luaChon) != 1) {
        xoaBoDem();
        printf("Loi: Nhap khong hop le!\n");
        return;
    }
    xoaBoDem();

    switch (luaChon) {
        case 1: napTien(tk); break;
        case 2: rutTien(tk); break;
        case 3: chuyenKhoan(tk); break;
        default: printf("Loi: Thao tac khong hop le!\n");
    }
}

/* HAM 5: In thong tin 1 tai khoan va toan bo lich su giao dich */
void inThongTin(void) {
    char stkGoi[15];
    printf("\n--- 5. IN THONG TIN TAI KHOAN & LICH SU GIAO DICH ---\n");
    printf("Nhap so TK can tra cuu: ");
    nhapChuoi(stkGoi, sizeof(stkGoi));

    TaiKhoan *tk = timTaiKhoan(stkGoi);
    if (tk == NULL) {
        printf("Loi: Khong tim thay tai khoan [%s]!\n", stkGoi);
        return;
    }

    printf("\n============================================\n");
    printf("       THONG TIN CHI TIET TAI KHOAN         \n");
    printf("============================================\n");
    printf("So tai khoan : %s\n", tk->soTK);
    printf("Chu tai khoan: %s\n", tk->hoTen);
    printf("So du hien co: %.2lf VND\n", tk->soDu);
    printf("Tong so GD   : %d\n", tk->soGiaoDich);
    printf("--------------------------------------------\n");
    printf("LICH SU GIAO DICH:\n");
    if (tk->soGiaoDich == 0) {
        printf("  (Chua phat sinh giao dich nao)\n");
    } else {
        printf("%-5s | %-12s | %-18s\n", "STT", "Loai GD", "So tien (VND)");
        printf("--------------------------------------------\n");
        for (int i = 0; i < tk->soGiaoDich; i++) {
            printf("%-5d | %-12s | %18.2lf\n",
                   i + 1,
                   tk->lichSu[i].loai,
                   tk->lichSu[i].soTien);
        }
    }
    printf("============================================\n");
}

/* HAM 6: Ham de quy tinh lai kep: P * (1 + r)^n */
double tinhLaiKep(double P, double r, int n) {
    if (n == 0) return P;
    return tinhLaiKep(P * (1.0 + r), r, n - 1);
}

void tinhLaiTietKiemMenu(void) {
    char stkGoi[15];
    double r;
    int n;

    printf("\n--- 6. TINH LAI KEP TIET KIEM (DE QUY) ---\n");
    printf("Nhap so TK muon tinh lai: ");
    nhapChuoi(stkGoi, sizeof(stkGoi));

    TaiKhoan *tk = timTaiKhoan(stkGoi);
    if (tk == NULL) {
        printf("Loi: Khong tim thay tai khoan [%s]!\n", stkGoi);
        return;
    }

    if (tk->soDu <= 0) {
        printf("Tai khoan [%s] co so du bang 0, khong co tien de tinh lai!\n", tk->soTK);
        return;
    }

    printf("Tai khoan: %s (%s)\n", tk->soTK, tk->hoTen);
    printf("So du hien co (Tien goc P): %.2lf VND\n", tk->soDu);
    printf("Nhap lai suat moi ky han r (vi du: 0.06 = 6%%): ");
    if (scanf("%lf", &r) != 1 || r < 0) {
        xoaBoDem();
        printf("Loi: Lai suat khong hop le!\n");
        return;
    }

    printf("Nhap so ky han gui n (so nguyen > 0): ");
    if (scanf("%d", &n) != 1 || n < 0) {
        xoaBoDem();
        printf("Loi: So ky han khong hop le!\n");
        return;
    }
    xoaBoDem();

    double tongTien = tinhLaiKep(tk->soDu, r, n);
    double tienLai = tongTien - tk->soDu;

    printf("\n=> KET QUA DU TINH LAI KEP:\n");
    printf("   + Tien goc ban dau (P) : %.2lf VND\n", tk->soDu);
    printf("   + Lai suat moi ky (r)  : %.2lf%%\n", r * 100.0);
    printf("   + So ky han gui (n)    : %d ky\n", n);
    printf("   + Tong so tien sau %d ky: %.2lf VND\n", n, tongTien);
    printf("   + Tien lai thu ve      : %.2lf VND\n", tienLai);
}

/* HAM 7: Luu va Doc tep tin nhi phan data.bin */
void luuFile(void) {
    FILE *fp = fopen(DATA_FILE, "wb");
    if (fp == NULL) {
        printf("Loi: Khong the mo tep %s de ghi du lieu!\n", DATA_FILE);
        return;
    }

    int count = 0;
    TaiKhoan *cur = dsTaiKhoan;
    while (cur != NULL) {
        fwrite(cur, sizeof(TaiKhoan), 1, fp);
        cur = cur->next;
        count++;
    }

    fclose(fp);
    printf("=> Da luu thanh cong %d tai khoan vao tep [%s]!\n", count, DATA_FILE);
}

void docFile(void) {
    FILE *fp = fopen(DATA_FILE, "rb");
    if (fp == NULL) {
        printf("(Chua co tep du lieu [%s]. He thong khoi tao danh sach rong)\n", DATA_FILE);
        return;
    }

    /* Giai phong danh sach hien tai neu co */
    while (dsTaiKhoan != NULL) {
        TaiKhoan *tmp = dsTaiKhoan;
        dsTaiKhoan = dsTaiKhoan->next;
        free(tmp);
    }

    TaiKhoan buffer;
    TaiKhoan *tail = NULL;
    int count = 0;

    while (fread(&buffer, sizeof(TaiKhoan), 1, fp) == 1) {
        TaiKhoan *node = (TaiKhoan *)malloc(sizeof(TaiKhoan));
        if (node == NULL) {
            printf("Loi: Khong du bo nho RAM khi doc tep du lieu!\n");
            break;
        }
        *node = buffer;
        node->next = NULL;

        if (dsTaiKhoan == NULL) {
            dsTaiKhoan = node;
        } else {
            tail->next = node;
        }
        tail = node;
        count++;
    }

    fclose(fp);
    printf("=> Da tai thanh cong %d tai khoan tu tep [%s]!\n", count, DATA_FILE);
}

/* ==================== BUBBLE SORT & IN DANH SACH ==================== */

/* Hoan doi noi dung data giua 2 node (giu nguyen con tro next) */
void hoanViData(TaiKhoan *a, TaiKhoan *b) {
    TaiKhoan temp = *a;
    TaiKhoan *nextA = a->next;
    TaiKhoan *nextB = b->next;

    *a = *b;
    *b = temp;

    a->next = nextA;
    b->next = nextB;
}

/* Sap xep danh sach tang dan theo So TK (Dung 2 vong for long nhau de hieu) */
void sapXepTaiKhoan(void) {
    if (dsTaiKhoan == NULL || dsTaiKhoan->next == NULL) {
        printf("Danh sach co it hon 2 tai khoan, khong can sap xep.\n");
        return;
    }

    for (TaiKhoan *p = dsTaiKhoan; p != NULL; p = p->next) {
        for (TaiKhoan *q = p->next; q != NULL; q = q->next) {
            if (strcmp(p->soTK, q->soTK) > 0) {
                hoanViData(p, q);
            }
        }
    }

    printf("=> Da sap xep danh sach tang dan theo So TK thanh cong!\n");
}

/* In toan bo danh sach tai khoan ra bang */
void inDanhSachTatCa(void) {
    if (dsTaiKhoan == NULL) {
        printf("Danh sach tai khoan hien dang rong!\n");
        return;
    }

    printf("\n========================================================================\n");
    printf("%-5s | %-15s | %-30s | %18s\n", "STT", "So TK", "Chu tai khoan", "So du (VND)");
    printf("========================================================================\n");
    int i = 1;
    for (TaiKhoan *cur = dsTaiKhoan; cur != NULL; cur = cur->next) {
        printf("%-5d | %-15s | %-30s | %18.2lf\n",
               i++, cur->soTK, cur->hoTen, cur->soDu);
    }
    printf("========================================================================\n");
}

/* ==================== MENU CONSOLE & MAIN ==================== */

void hienThiMenu(void) {
    printf("\n================ MENU QUAN LY NGAN HANG ================\n");
    printf("  1. Mo tai khoan moi (Chi nhap Ho ten, he thong tu sinh STK)\n");
    printf("  2. Xoa / Dong tai khoan theo So TK\n");
    printf("  3. Sua ho ten chu tai khoan theo So TK\n");
    printf("  4. Giao dich (Nap / Rut / Chuyen khoan)\n");
    printf("  5. In thong tin tai khoan & lich su giao dich\n");
    printf("  6. Tinh lai kep gui tiet kiem (Ham de quy)\n");
    printf("  7. Sap xep tai khoan theo So TK (Bubble Sort)\n");
    printf("  8. In danh sach tat ca tai khoan\n");
    printf("  0. Thoat chuong trinh (Tu dong luu tep data.bin)\n");
    printf("========================================================\n");
    printf("Chon chuc nang (0-8): ");
}

int main(void) {
    /* Tu dong doc du lieu cu khi khoi dong chuong trinh */
    docFile();

    int luaChon;
    do {
        hienThiMenu();
        int kq = scanf("%d", &luaChon);
        if (kq == EOF) {
            break; /* Nguoi dung nhan Ctrl+Z hoac het luong nhap */
        }
        if (kq != 1) {
            xoaBoDem();
            printf("Loi: Lua chon phai la chu so tu 0 den 8!\n");
            luaChon = -1;
            continue;
        }
        xoaBoDem();

        switch (luaChon) {
            case 1: themTaiKhoan(); break;
            case 2: xoaTaiKhoan(); break;
            case 3: suaHoTen(); break;
            case 4: giaoDich(); break;
            case 5: inThongTin(); break;
            case 6: tinhLaiTietKiemMenu(); break;
            case 7:
                sapXepTaiKhoan();
                inDanhSachTatCa();
                break;
            case 8: inDanhSachTatCa(); break;
            case 0:
                printf("\nDang luu du lieu va thoat chuong trinh...\n");
                break;
            default:
                printf("Loi: Chuc nang %d khong ton tai tren menu!\n", luaChon);
        }
    } while (luaChon != 0);

    /* Tu dong luu danh sach vao tep data.bin truoc khi ket thuc */
    luuFile();

    /* Giai phong bo nho dong cua danh sach lien ket */
    while (dsTaiKhoan != NULL) {
        TaiKhoan *tmp = dsTaiKhoan;
        dsTaiKhoan = dsTaiKhoan->next;
        free(tmp);
    }

    printf("Chuong trinh da ket thuc. Tam biet ban!\n");
    return 0;
}
