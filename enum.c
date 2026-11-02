struct TaiKhoan{
    char ten[50];
    int soDu;
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