# Cách sử dụng Retarget Printf cho stm32 bằng KEIL C

## Để sử dụng được hàm printf và in lên Serial COM Uart ta làm theo bước sau:

● B1: Vào KeilC tìm vào thanh công cụ tìm HELP. Tại vì mỗi trình biên dịch sẽ có cách sử dụng Retarget Printf riêng nên ta phải vào đó check xem.
● B2: Ấn và Search và tìm kiếm Retargeting Printf và nó sẽ hiện ra như hình dưới

  ![image](https://github.com/NguyenEngineer/Embedded_STM/assets/120030797/f486cd62-e65f-48c4-8714-d2dc6584d305)

● B3: Copy đoạn code từ chổ include tới hàm int fputc() và dán vào hàm main.
● B4: Xong nạp và chạy.
