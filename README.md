### 1. Tóm tắt thay đổi
Hoàn thiện chương trình **Quản lý tài khoản và giao dịch ngân hàng** (`project2.c`) bằng ngôn ngữ C trên giao diện console.

### 2. Các chức năng chính đã thực hiện
- **Quản lý tài khoản:** Mở tài khoản mới (tự động cấp số TK không trùng), sửa họ tên, xóa tài khoản theo số TK.
- **Giao dịch ngân hàng:** Nạp tiền, rút tiền, chuyển khoản (có kiểm tra số dư và tự động ghi lịch sử giao dịch cho cả 2 bên).
- **Tra cứu & Thống kê:** Xem chi tiết tài khoản kèm lịch sử giao dịch; sắp xếp danh sách tăng dần theo số TK và in bảng tổng hợp.
- **Tính lãi tiết kiệm:** Áp dụng hàm đệ quy tính lãi kép theo kỳ hạn dựa trên số dư thực tế.
- **Lưu trữ dữ liệu:** Tự động đọc và lưu dữ liệu ra file nhị phân (`data.bin`) khi khởi động và thoát chương trình.

### 3. Bảng phân chia công việc (3 thành viên)

| STT | Thành viên | Nhiệm vụ phụ trách | Các hàm trong `project2.c` | Tỷ lệ | Hoàn thành |
| :-: | :--- | :--- | :--- | :-: | :-: |
| 1 | **Thành viên 1** (Nhóm trưởng) | Thiết kế `struct`, hàm phụ trợ, tự sinh STK, chức năng Thêm / Xóa / Sửa tài khoản, quản lý Git | `nhapChuoi`, `timViTriTK`, `tuSinhSoTK`, `themTaiKhoan`, `xoaTaiKhoan`, `suaHoTen` | 34% | 100% |
| 2 | **Thành viên 2** | Nghiệp vụ Giao dịch (Nạp, Rút, Chuyển khoản), ghi lịch sử giao dịch, Tra cứu chi tiết tài khoản | `luuLichSu`, `giaoDich`, `inThongTin` | 33% | 100% |
| 3 | **Thành viên 3** | Hàm đệ quy tính lãi kép, Sắp xếp & In danh sách tài khoản, Đọc/Ghi file `data.bin`, Menu `main` | `tinhLaiKep`, `tinhLaiTietKiem`, `sapXepVaInDanhSach`, `luuFile`, `docFile`, `main` | 33% | 100% |


💡 Gợi ý ôn tập nhanh theo phân công (để đi bảo vệ):
- Thành viên 1 chỉ cần nắm chắc: Cách khai báo struct, cách xóa ký tự \n bằng strcspn, cách tự sinh STK tăng dần (10000001...), và cách xóa 1 phần tử trong mảng bằng vòng lặp dịch lùi dsTaiKhoan[i] = dsTaiKhoan[i + 1].
- Thành viên 2 chỉ cần nắm chắc: Các điều kiện kiểm tra khi Nạp/Rút/Chuyển (soTien > 0, soTien <= soDu, không chuyển cho chính mình) và cách lưu vào mảng lichSu[].
- Thành viên 3 chỉ cần nắm chắc: Công thức đệ quy lãi kép tinhLaiKep(P * (1 + r), r, n - 1) (dừng khi n == 0), 2 vòng for sắp xếp đổi chỗ tam, và cặp hàm fread / fwrite với file data.bin.
