// Quản lý tài khoản & giao dịch ngân hàng đơn giản (Tài chính)	
// Quản lý tài khoản khách hàng, gửi/rút/chuyển khoản, lưu lịch sử giao dịch.	
///Mở tài khoản; gửi/rút/chuyển khoản; ghi lịch sử giao dịch; tính lãi tiết kiệm theo kỳ hạn; tra cứu số dư; lưu/đọc file.	
///struct TaiKhoan liên kết danh sách GiaoDich; 
///đệ quy: tính lãi kép qua các kỳ hạn.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100
struct TaiKhoan{
    char ten[50];
    long soDu;
    char soTk[20];
};

enum MethodPayment {
    /// Gửi tiền
    PAYMENT_SEND,
    /// Nhận tiền
    PAYMENT_RECEIVE,
    /// Chuyển khoản
    PAYMENT_TRANSFER,
};
// Thêm vào file dữ liệu tài khoản khách hàng
void add_tk(struct TaiKhoan *tk);
// Xoá tài khoản
void remove_tk(struct TaiKhoan *tk,int index);
// Xuất file dữ liệu tài khoản khách hàng
void infor_list_tk(void);
/// Xoá ký tự xuống dòng trong chuỗi
void xoa_underline(char *str);
/// Hiển thị thông tin tài khoản
void infor_tk(struct TaiKhoan *tk,char soTk[50]);
/// Lấy thông tin tài khoản từ file
struct TaiKhoan *tk_list(void);

void xoa_underline(char *str) {
    int indexUnderLine = strcspn(str, "\n");
    str[indexUnderLine] = '\0';
}


void add_tk(struct TaiKhoan *tk) {
    /// Mở file để ghi nối tiếp vào cuối a+
    FILE *file = fopen("data.txt", "a+");
    if(file == NULL){
        printf("Khong the mo file de ghi!\n");
        return;
    }
    printf("Nhap ten: ");
    fgets(tk->ten, sizeof(tk->ten), stdin);
    xoa_underline(tk->ten);
    printf("Nhap so tai khoan: ");
    fgets(tk->soTk, sizeof(tk->soTk), stdin);
    xoa_underline(tk->soTk);
    tk->soDu = 50000;
    fprintf(file, "%s,%s,%d\n", tk->ten, tk->soTk, tk->soDu);
    fclose(file);
}
///TODO remove
void remove_tk(struct TaiKhoan *tk,int index){

}

void infor_tk(struct TaiKhoan *tk,char soTk[50]){
    for(int i = 0; i < MAX; i++){
        if(strcmp(tk[i].soTk, soTk) == 0){
            printf("Họ tên chủ thẻ: %s\n, Số tài khoản: %s\n, Số dư: %d\n", tk[i].ten, tk[i].soTk, tk[i].soDu);
            return;
        }
    }
    printf("Không tìm thấy tài khoản!\n");
}

struct TaiKhoan *tk_list(void){
    struct TaiKhoan *tk = (struct TaiKhoan *)malloc(MAX * sizeof(struct TaiKhoan));
    FILE *file = fopen("data.txt", "r");
    if(file == NULL){
        printf("Khong the mo file de doc!\n");
        return NULL;
    }
    char line[256];
    int n = 0;

    while ( n < MAX && fgets(line, sizeof(line), file) != NULL) {
        char *ten = strtok(line, ",");
        char *soTk = strtok(NULL, ",");
        char *soDu = strtok(NULL, ",\n");

        tk[n].soDu = atoi(soDu);
        strcpy(tk[n].ten, ten);
        strcpy(tk[n].soTk, soTk);
        n++;
    }
    
    fclose(file);
    return  tk;
}

void infor_list_tk(void) {
    struct TaiKhoan *tk = tk_list();
    if(tk == NULL){
        return;
    }
    for(int i = 0; i < sizeof(*tk); i++){
        printf("Họ tên chủ thẻ: %s\n, Số tài khoản: %s\n, Số dư: %d\n", tk[i].ten,tk[i].soTk,tk[i].soDu);
        printf("----------------------------------\n");
    }
    
}


int main(void) {
    struct TaiKhoan *allTks = tk_list();
    // file_input(&tk_list[0]);
    infor_list_tk();
    infor_tk(&allTks[0], "09238123123");
    return 1;
}