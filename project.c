// Quản lý tài khoản & giao dịch ngân hàng đơn giản (Tài chính)	
// Quản lý tài khoản khách hàng, gửi/rút/chuyển khoản, lưu lịch sử giao dịch.	
///Mở tài khoản; gửi/rút/chuyển khoản; ghi lịch sử giao dịch; tính lãi tiết kiệm theo kỳ hạn; tra cứu số dư; lưu/đọc file.	
///struct TaiKhoan liên kết danh sách GiaoDich; 
///đệ quy: tính lãi kép qua các kỳ hạn.
#include "account_management.c"


int main() {
    struct TaiKhoan tk_list[MAX];
    // file_input(&tk_list[0]);
    infor_list_tk(&tk_list[0]);
    return 1;
}