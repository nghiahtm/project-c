#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "enum.c";

#define MAX 100
#define account_file "data/accounts.txt"

// Thêm vào file dữ liệu tài khoản khách hàng
void add_tk(struct TaiKhoan *tk);
// Xoá tài khoản
void remove_tk(struct TaiKhoan *tk,int index);
// Xuất file dữ liệu tài khoản khách hàng
void infor_list_tk(struct TaiKhoan *tk);
/// Xoá ký tự xuống dòng trong chuỗi
void xoa_underline(char *str);
/// Lấy thông tin tài khoản từ file dữ liệu
void infor_tk(struct TaiKhoan *tk,char soTk[50]);


void xoa_underline(char *str) {
    int indexUnderLine = strcspn(str, "\n");
    str[indexUnderLine] = '\0';
}


void add_tk(struct TaiKhoan *tk) {
    /// Mở file để ghi nối tiếp vào cuối a+
    FILE *file = fopen(account_file, "a+");
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

void infor_tk(struct TaiKhoan *tk,char soTk[50]){}

void infor_list_tk(struct TaiKhoan *tk) {
    FILE *file = fopen(account_file, "r");
    if(file == NULL){
        printf("Khong the mo file de doc!\n");
        return;
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
        printf("Họ tên chủ thẻ: %s\n, Số tài khoản: %s\n, Số dư: %d\n", tk[n].ten, tk[n].soTk, tk[n].soDu);
        printf("--------------------------------------------------\n");
        n++;
    }
    
    fclose(file);
}