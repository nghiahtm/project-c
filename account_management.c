#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "enum.c"
#include "data_file.c"
#define MAX 100
#define account_file "data/accounts.txt"

FILE *file;
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
    printf("Nhap ten: ");
    fgets(tk->ten, sizeof(tk->ten), stdin);
    xoa_underline(tk->ten);
    printf("Nhap so tai khoan: ");
    fgets(tk->soTk, sizeof(tk->soTk), stdin);
    xoa_underline(tk->soTk);
    tk->soDu = 50000;
    
    char data[512];
    sprintf(data, "%s,%s,%d\n", tk->ten, tk->soTk, tk->soDu);
    addData(file, account_file, data);
}
///TODO remove
void remove_tk(struct TaiKhoan *tk,int index){

}

void infor_tk(struct TaiKhoan *tk,char soTk[50]){}

void infor_list_tk(struct TaiKhoan *tk) {
    
    char *data = getData(file, account_file);
    if(data == NULL) return;
    int n = 0;

    // Tách từng dòng, mỗi dòng có dạng: ten,soTk,soDu
    char *line = strtok(data, "\n");
    while (n < MAX && line != NULL) {
        if(sscanf(line, "%49[^,],%19[^,],%d", tk[n].ten, tk[n].soTk, &tk[n].soDu) == 3) {
            printf("Ho ten chu the: %s, So tai khoan: %s, So du: %d\n", tk[n].ten, tk[n].soTk, tk[n].soDu);
            printf("--------------------------------------------------\n");
            n++;
        }
        line = strtok(NULL, "\n");
    }

    free(data);
}