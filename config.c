#ifndef CONFIG_C
#define CONFIG_C

#define MAX_TAIKHOAN 100
#define MAX_GIAODICH 100
#define TEN_FILE "data.bin"

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

typedef enum {
    NAP_TIEN = 1,
    RUT_TIEN = 2,
    CHUYEN_KHOAN = 3
} LoaiGiaoDich;


/* Xoa phan con sot lai tren dong nhap (vd: dau Enter '\n' ma scanf de lai) */
void xoaBoDem() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Mang 1 chieu luu danh sach tai khoan va bien dem so luong */
TaiKhoan dsTaiKhoan[MAX_TAIKHOAN];
int soLuongTK = 0;

#endif

