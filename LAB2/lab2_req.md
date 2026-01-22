# Lab 2

## Mục tiêu
Thực hành với các hàm truyền nhận Serial trên Arduino

## Linh kiện cần thiết
- Mạch Arduino Uno R3
- Mạch khung
- LED
- Điện trở
- Dây nối

## Yêu cầu
Truyền thông tin từ máy tính cho mạch Arduino để điều khiển độ sáng 3 LEDs: **Red, Green, Blue**

- Nội dung thông tin truyền theo định dạng **`Rx, Gy, Bz`**  
  Ví dụ: nếu truyền `R255, G150, B50` thì:
  - Đèn Red sáng ở mức 255
  - Đèn Green sáng ở mức 150
  - Đèn Blue sáng ở mức 50

  - Nếu gửi giá trị > 255 thì đèn vẫn sáng ở mức 255
  - Nếu gửi giá trị < 0 thì đèn tắt
  - Trường hợp chỉ gửi thông tin 1 hoặc 2 đèn thì độ sáng những đèn còn lại không thay đổi

- Như yêu cầu trên với thông tin truyền theo định dạng **`RxGyBz`**

- Như yêu cầu trên với thông tin truyền theo định dạng **`RxGyBzDt`**  
  với **t** là thời gian sáng của 3 LEDs
