#include <stdio.h>

FILE *openFile(FILE *file, char *fileName, char *mode);

void closeFile(FILE *file);
void addData(FILE *file, char *fileName,char *data);

void removeData(FILE *file, char *fileName,char *data);

FILE *openFile(FILE *file, char *fileName, char *mode) {
    file = fopen(fileName,mode);

    if(file == NULL){
        printf("Khong the mo file");
        return NULL;
    }
    return file;
}
 
void closeFile(FILE *file){
    fclose(file);
}

/// Đọc toàn bộ nội dung file vào một chuỗi.
/// Trả về chuỗi cấp phát bằng malloc (người gọi phải free), hoặc NULL nếu lỗi.
char *getData(FILE *file, char *fileName){
    // Mở file ở chế độ chỉ đọc
    file = openFile(file,fileName,"r");
    if(file == NULL) return NULL;

    // Lấy kích thước file: nhảy tới cuối file, đọc vị trí hiện tại (= số byte),
    // rồi quay lại đầu file để chuẩn bị đọc
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    // Cấp phát vùng nhớ đủ chứa file + 1 byte cho ký tự kết thúc '\0'.
    // Không dùng mảng cục bộ vì mảng sẽ bị huỷ khi hàm kết thúc
    char *data = malloc(size + 1);
    if(data == NULL){
        closeFile(file);
        return NULL;
    }

    // Đọc file vào data. n là số byte thực sự đọc được, có thể nhỏ hơn size
    // vì trên Windows chế độ "r" chuyển "\r\n" thành "\n"
    size_t n = fread(data, 1, size, file);
    // Thêm '\0' để data thành chuỗi C hợp lệ
    data[n] = '\0';

    closeFile(file);
    return data; // nhớ free() sau khi dùng xong
}

void addData(FILE *file, char *fileName,char *data) {
   file = openFile(file,fileName,"a");
   if(file == NULL) return;
   fprintf( file,data);
   closeFile(file);
   printf("Them du lieu thanh cong");
}