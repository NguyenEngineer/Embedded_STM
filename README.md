# Embedded STM32

</details>
<details><summary> LESSION 1 : GPIO </summary>

1 Giới thiệu GPIO.

Ở bài này, chúng ta sẽ thực hành cấu hình GPIO trên bộ thư viện SPL (Standard Peripherals Firmware Library ). Các hàm phục vụ cho việc cấu hình GPIO, cấp xung ngoại vi được định nghĩa trong file "stm32f10x_rcc.h", và "stm32f10x_gpio.h"

Ở trong thư viện này, các cấu hình được chia thành các trường và định nghĩa bằng các cấu trúc như struct và enum.

Một số định nghĩa đã được cung cấp trong thư viện có thể kể ra như: 

- Các GPIO: các thanh ghi phục vụ chức năng GPIO đã được tổ chức dưới dạng 1 struct. Các thanh ghi cấu hình cho các GPIO được tổ chức trong struct GPIO_Typedef.
```c
typedef struct
{
  __IO uint32_t CRL;
  __IO uint32_t CRH;
  __IO uint32_t IDR;
  __IO uint32_t ODR;
  __IO uint32_t BSRR;
  __IO uint32_t BRR;
  __IO uint32_t LCKR;
} GPIO_TypeDef;
```
- Trong thư viện SPL, các thuộc tính của GPIO được tổ chức thành 1 struct GPIO_InitTypeDef chứa các trường GPIO_Mode, GPIO_Pin và GPIO_Speed.
```c
typedef struct
{
  uint16_t GPIO_Pin;             /*!< Specifies the GPIO pins to be configured.
                                      This parameter can be any value of @ref GPIO_pins_define */

  GPIOSpeed_TypeDef GPIO_Speed;  /*!< Specifies the speed for the selected pins.
                                      This parameter can be a value of @ref GPIOSpeed_TypeDef */

  GPIOMode_TypeDef GPIO_Mode;    /*!< Specifies the operating mode for the selected pins.
                                      This parameter can be a value of @ref GPIOMode_TypeDef */
}GPIO_InitTypeDef;
```
- GPIO_InitStructure.GPIO_Mode là một trường dùng để xác định chế độ hoạt động của chân GPIO trong thư viện của STM32.
```c
typedef enum
{ GPIO_Mode_AIN = 0x0,
  GPIO_Mode_IN_FLOATING = 0x04,
  GPIO_Mode_IPD = 0x28,
  GPIO_Mode_IPU = 0x48,
  GPIO_Mode_Out_OD = 0x14,
  GPIO_Mode_Out_PP = 0x10,
  GPIO_Mode_AF_OD = 0x1C,
  GPIO_Mode_AF_PP = 0x18
}GPIOMode_TypeDef;
```
*Dưới đây là các giá trị mà trường GPIO_Mode có thể nhận và giải thích chi tiết về từng chế độ:

 GPIO_Mode_AIN:
 
● Mô tả: Analog Input.

● Giải thích: Chân GPIO được cấu hình làm đầu vào analog. Thường được sử dụng cho các chức năng như ADC (Analog to Digital Converter).

 GPIO_Mode_IN_FLOATING:
 
● Mô tả: Floating Input.

● Giải thích: Chân GPIO được cấu hình làm đầu vào và ở trạng thái nổi (không pull-up hay pull-down). Điều này có nghĩa là chân không được kết nối cố định với mức cao (VDD) hoặc mức thấp (GND) thông qua điện trở.

 GPIO_Mode_IPD:
 
● Mô tả: Input with Pull-down.

● Giải thích: Chân GPIO được cấu hình làm đầu vào với một điện trở pull-down nội bộ kích hoạt. Khi không có tín hiệu nào được áp dụng lên chân này, nó sẽ được kéo về mức thấp (GND).

 GPIO_Mode_IPU:
 
● Mô tả: Input with Pull-up.

● Giải thích: Chân GPIO được cấu hình làm đầu vào với một điện trở pull-up nội bộ kích hoạt. Khi không có tín hiệu nào được áp dụng lên chân này, nó sẽ được kéo về mức cao (VDD).

 GPIO_Mode_Out_OD:
 
● Mô tả: Open-drain Output.

● Giải thích: Chân GPIO được cấu hình làm đầu ra với chế độ open-drain. Trong chế độ này, chân có thể được kéo xuống mức thấp, nhưng để đạt được mức cao, cần một điện trở pull-up ngoài hoặc từ một nguồn khác.

 GPIO_Mode_Out_PP:
 
● Mô tả: Push-pull Output.

● Giải thích: Chân GPIO được cấu hình làm đầu ra với chế độ push-pull. Trong chế độ này, chân có thể đạt được cả mức cao và mức thấp mà không cần bất kỳ phần cứng bổ sung nào.

 GPIO_Mode_AF_OD:
 
● Mô tả: Alternate Function Open-drain.

● Giải thích: Chân GPIO được cấu hình để hoạt động trong một chức năng thay thế (như USART, I2C, etc.) và sử dụng chế độ open-drain.

 GPIO_Mode_AF_PP:
 
● Mô tả: Alternate Function Push-pull.

● Giải thích: Chân GPIO được cấu hình để hoạt động trong một chức năng thay thế và sử dụng chế độ push-pull.

GPIO_Pin là trường xác định chân trong GPIOx tương ứng. các giá trị được khai báo trong file header, có dạng GPIO_Pin_x với x là chân từ 0-15.

![image](https://github.com/phatminhswe/stm32/assets/162662273/fe0fc39d-e3fc-4f1b-a1d0-0cde7d2c2bf5)


GPIO_Speed là trường xác định tốc độ đáp ứng của chân. Thường được cấu hình đi kèm với chế độ Output, các giá trị cũng được khai báo trong file header trong GPIO_SpeedTypeDef:
```c
typedef enum
{ 
  GPIO_Speed_10MHz = 1,
  GPIO_Speed_2MHz, 
  GPIO_Speed_50MHz
}GPIOSpeed_TypeDef;

```

**Cấu hình RCC cấp clock cho ngoại vi**

Trong tài liệu của bộ thư viện : “STM32F10x Standard Peripherals Firmware Library”, xung clock cho ngoại vi được cấu hình bởi các hàm trong modules RCC. 

Các hàm :có chức năng cấp xung hoặc ngưng cấp xung cho ngoại vi tương ứng. Các hàm này được định nghĩa trong file "stm32f10x_rcc.h". 
Các hàm này nhận tham số vào là Macro của các ngoại vi được định nghĩa sẵn trong file header, tham số thứ 2 quy định việc cấp hay ngưng xung clock cho ngoại vi tương ứng.

- RCC_APB1PeriphClockCmd

Enables or disables the Low Speed APB (APB1) peripheral clock. 

Parameters:
```
RCC_APB1Periph,:specifies the APB1 peripheral to gates its clock. This parameter can be any combination of the following values:

RCC_APB1Periph_TIM2, 
RCC_APB1Periph_TIM3, 
RCC_APB1Periph_TIM4, 
RCC_APB1Periph_TIM5, 
RCC_APB1Periph_TIM6, 
RCC_APB1Periph_TIM7, 
RCC_APB1Periph_WWDG, 
RCC_APB1Periph_SPI2, 
RCC_APB1Periph_SPI3, 
RCC_APB1Periph_USART2, 
RCC_APB1Periph_USART3, 
RCC_APB1Periph_USART4, 
RCC_APB1Periph_USART5, 
RCC_APB1Periph_I2C1, 
RCC_APB1Periph_I2C2, 
RCC_APB1Periph_USB, 
RCC_APB1Periph_CAN1, 
RCC_APB1Periph_BKP, 
RCC_APB1Periph_PWR, 
RCC_APB1Periph_DAC, 
RCC_APB1Periph_CEC, 
RCC_APB1Periph_TIM12, 
RCC_APB1Periph_TIM13, 
RCC_APB1Periph_TIM14

NewState,:
new state of the specified peripheral clock. This parameter can be: ENABLE or DISABLE.

Return values:
None

```

- RCC_APB2PeriphClockCmd

Enables or disables the High Speed APB (APB2) peripheral clock.
Parameters:
```
RCC_APB2Periph,:specifies the APB2 peripheral to gates its clock. This parameter can be any combination of the following values:

RCC_APB2Periph_AFIO, 
RCC_APB2Periph_GPIOA, 
RCC_APB2Periph_GPIOB, 
RCC_APB2Periph_GPIOC, 
RCC_APB2Periph_GPIOD, 
RCC_APB2Periph_GPIOE, 
RCC_APB2Periph_GPIOF, 
RCC_APB2Periph_GPIOG, 
RCC_APB2Periph_ADC1, 
RCC_APB2Periph_ADC2, 
RCC_APB2Periph_TIM1, 
RCC_APB2Periph_SPI1, 
RCC_APB2Periph_TIM8, 
RCC_APB2Periph_USART1, 
RCC_APB2Periph_ADC3, 
RCC_APB2Periph_TIM15, 
RCC_APB2Periph_TIM16, 
RCC_APB2Periph_TIM17, 
RCC_APB2Periph_TIM9, 
RCC_APB2Periph_TIM10, 
RCC_APB2Periph_TIM11
NewState,:
new state of the specified peripheral clock. This parameter can be: ENABLE or DISABLE.

Return values:
None
```



GPIOC được cấp xung bởi APB2 nên sử dụng hàm :

RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOC, ENABLE); để cấu hình clock.

Cấu hình Pin GPIO

Như đã đề cập ở trên, các thuộc tính của 1 chân trong GPIO có thể được cấu hình thông qua struct GPIO_InitTypeDef, chúng ta sẽ tạo 1 biến struct kiểu này, sau đó gán các giá trị cần cấu hình thông qua biến đó.

Khởi tạo GPIO
Hàm GPIO_Init(); khởi tạo GPIOx với các tham số đã được thiết lập trong GPIO_InitStruct. Hàm nhận 2 tham số là 1 GPIOx cần khởi tạo và 1 con trỏ trỏ tới struct GPIO_InitTypedDef chứa các thông tin đã thiết lập cho GPIO. 

Vì vậy, để khởi tạo 1 GPIO để sử dụng, trước tiên cần cấu hình clock, sau đó tạo 1 struct GPIO_InitTypedDef  cấu hình tham số cho GPIO, sau đó gọi hàm GPIO_Init() với GPIOx cần cấu hình và struct vừa tạo.
```
GPIO_InitTypeDef GPIO_InitStruct;
RCC_APB2PeriphClockCmd(RCC_APBxPeriph_GPIOx, ENABLE);

GPIO_InitStruct.GPIO_Pin = GPIO_Pin_x;
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_xx;
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_xx;
GPIO_Init(GPIOx, &GPIO_InitStruct);
```

2 Các hàm cơ bản trên GPIO.

Thư viện SPL hỗ trợ sẵn các hàm để thực thi trên các GPIO.
```
GPIO_SetBits(GPIO_TypeDef GPIOx, uint16_t GPIO_Pin)*
```
● Mô tả: Đặt một hoặc nhiều chân GPIO ở mức cao (logic 1).

● Tham số:

● GPIOx: là cổng GPIO muốn điều khiển (ví dụ: GPIOA, GPIOB,...).

● GPIO_Pin: chọn chân hoặc chân cần đặt ở mức cao (ví dụ: GPIO_Pin_0, GPIO_Pin_1 hoặc kết hợp như GPIO_Pin_0 | GPIO_Pin_1).
```
 GPIO_ResetBits(GPIO_TypeDef GPIOx, uint16_t GPIO_Pin)*
``` 
● Mô tả: Đặt một hoặc nhiều chân GPIO ở mức thấp (logic 0).

● Tham số: Tương tự như hàm GPIO_SetBits.
```
GPIO_ReadInputDataBit(GPIO_TypeDef GPIOx, uint16_t GPIO_Pin)*
```
● Mô tả: Đọc trạng thái của một chân GPIO đã được cấu hình là input.

● Tham số: Tương tự như hàm GPIO_SetBits.

● Giá trị trả về: Trả về Bit_SET nếu chân đang ở mức cao hoặc Bit_RESET nếu chân đang ở mức thấp.
```
GPIO_ReadOutputDataBit(GPIO_TypeDef GPIOx, uint16_t GPIO_Pin)*
```
● Mô tả: Đọc trạng thái của một chân GPIO đã được cấu hình là output.

● Tham số: Tương tự như hàm GPIO_SetBits.

● Giá trị trả về: Trả về Bit_SET nếu chân đang ở mức cao hoặc Bit_RESET nếu chân đang ở mức thấp.
```
GPIO_WriteBit(GPIO_TypeDef GPIOx, uint16_t GPIO_Pin, BitAction BitVal)*
```
● Mô tả: Đặt trạng thái của một chân GPIO dựa trên giá trị của BitVal.

● Tham số:

● GPIOx và GPIO_Pin tương tự như hàm GPIO_SetBits.

● BitVal: là giá trị mà bạn muốn đặt cho chân GPIO, có thể là Bit_SET hoặc Bit_RESET.
```
 GPIO_ReadInputData(GPIO_TypeDef GPIOx)*
``` 
● Mô tả: Đọc giá trị của tất cả các chân GPIO đã được cấu hình là đầu vào trên cổng GPIO chỉ định.

● Tham số:

● GPIOx: cổng GPIO mà bạn muốn đọc (ví dụ: GPIOA, GPIOB,...).

● Giá trị trả về: Một giá trị 16-bit biểu diễn trạng thái của tất cả các chân trên cổng GPIO.
```
 GPIO_ReadOutputData(GPIO_TypeDef GPIOx)*
``` 
● Mô tả: Đọc giá trị của tất cả các chân GPIO đã được cấu hình là đầu ra trên cổng GPIO chỉ định.

● Tham số:

● GPIOx: cổng GPIO mà bạn muốn đọc.

● Giá trị trả về: Một giá trị 16-bit biểu diễn trạng thái của tất cả các chân trên cổng GPIO.
```
 GPIO_Write(GPIO_TypeDef GPIOx, uint16_t PortVal)*
``` 
● Mô tả: Ghi giá trị cho toàn bộ cổng GPIO.

● Tham số:

● GPIOx: cổng GPIO bạn muốn ghi.

● PortVal: giá trị 16-bit mà bạn muốn đặt cho cổng GPIO.
```
 GPIO_PinLockConfig(GPIO_TypeDef GPIOx, uint16_t GPIO_Pin)*
 ```
● Mô tả: Khóa cấu hình của chân GPIO. Sau khi chân đã bị khóa, bạn sẽ không thể thay đổi cấu hình của nó cho đến khi hệ thống được reset.

● Tham số:

● GPIOx: cổng GPIO mà bạn muốn khóa chân.

● GPIO_Pin: chọn chân cần khóa (ví dụ: GPIO_Pin_0, GPIO_Pin_1 hoặc kết hợp như GPIO_Pin_0 | GPIO_Pin_1).
```
GPIO_EventOutputConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource)
```
● Mô tả: Cấu hình chân sự kiện đầu ra.

● Tham số:

● GPIO_PortSource: xác định cổng GPIO.

● GPIO_PinSource: xác định chân GPIO.
```
 GPIO_EventOutputCmd(FunctionalState NewState)
``` 
● Mô tả: Cho phép hoặc vô hiệu hóa chân sự kiện đầu ra.

● Tham số:

● NewState: trạng thái mới của chân. Có thể là ENABLE hoặc DISABLE.
```
 GPIO_AFIODeInit()
``` 
● Mô tả: Đặt lại tất cả các thanh ghi của AFIO (Alternate Function IO) về giá trị mặc định.

  
</details>
<details><summary> LESSION 2 : Ngắt và Timer </summary>

# 1.Ngắt

Ngắt là 1 sự kiện khẩn cấp xảy ra trong hay ngoài vi điều khiển. Nó yêu MCU phải dừng chương trình chính và thực thi chương trình ngắt.

**Các loại ngắt thông dụng**

Mỗi ngắt có 1 trình phục vụ ngắt, sẽ yêu cầu MCU thực thi lệnh tại trình phục vụ ngắt khi có ngắt xảy ra.
Các ngắt có các địa chỉ cố định trong bộ nhớ để giữ các trình phục vụ. Các địa chỉ này gọi là vector ngắt.

![image](https://github.com/phatminhswe/stm32/assets/162662273/3f0b8c5f-deab-4e8d-b7f1-24f1b228fc53)


Quá trình ngắt:

![image](https://github.com/phatminhswe/stm32/assets/162662273/031f2525-dfff-424c-a313-efa6726625d5)



**Ngắt ngoài: **

Xảy ra khi có thay đổi điện áp trên các chân GPIO được cấu hình làm ngõ vào ngắt.

LOW: kích hoạt ngắt liên tục khi chân ở mức thấp.

HIGH: Kích hoạt liên tục khi chân ở mức cao.

Rising: Kích hoạt khi trạng thái trên chân chuyển từ thấp lên cao.

Falling: Kích hoạt khi trạng thái trên chân chuyển từ cao xuống thấp.

**Ngắt timer:**

Ngắt Timer xảy ra khi giá trị trong thanh ghi đếm của timer tràn. Giá trị tràn được xác định bởi giá trị cụ thể trong thanh ghi đếm của timer.
Vì đây là ngắt nội trong MCU, nên phải reset giá trị thanh ghi timer để có thể tạo được ngắt tiếp theo.


**Ngắt truyền nhận:**

Ngắt truyền nhận xảy ra khi có sự kiện truyền/nhận dữ liệu giữ MCU với các thiết bị bên ngoài hay với MCU. Ngắt này sử dụng cho nhiều phương thức như Uart, SPI, I2C…v.v nhằm đảm bảo việc truyền nhận chính xác.

**Độ ưu tiên ngắt**

Độ ưu tiên ngắt là khác nhau ở các ngắt. Nó xác định ngắt nào được quyền thực thi khi nhiều ngắt xảy ra đồng thời.

STM32 quy định ngắt nào có số thứ tự ưu tiên càng thấp thì có quyền càng cao. Các ưu tiên ngắt có thể lập trình được.

# 2.TIMER

Giới thiệu về Timer:

Có thể hiểu 1 cách đơn giản: timer là 1 mạch digital logic có vai trò đếm mỗi chu kỳ clock (đếm lên hoặc đếm xuống).

Timer còn có thể hoạt động ở chế độ counter, nó sẽ nhận xung clock từ các tín hiệu ngoài. Có thể là từ 1 nút nhấn, bộ đếm sẽ được tăng sau mỗi lần bấm nút (sườn lên hoặc sườn xuống tùy vào cấu hình).

Ngoài ra còn các chế độ khác (ở đây mình chỉ liệt kê, sau này sẽ có bài viết riêng về các chế độ này):

·        PWM Mode
·        Advanced PWM Mode
·        Output Compare Mode
·        One-Pulse Mode
·        Input Capture Mode
·        Encoder Mode
·        Timer Gate Mode
·        Timer DMA Burst Mode
·        IRTIM Infrared Mode

STM32f103C8 có tất cả 7 timer nhưng trong đó đã bao gồm 1 systick timer, 2 watchdog timer. Vậy chỉ còn lại 4 timer dùng cho các chức năng như ngắt, timer base, PWM, Encoder, Input capture…. Trong đó TIM1 là Timer đặc biệt, chuyên dụng cho việc xuất xung với các mode xuất xung, các mode bảo vệ đầy đủ hơn so với các timer khác. TIM1 thuộc khối clock APB2, còn các TIM2,TIM3,TIM4 thuộc nhóm APB1.


**Timer clock**

Khi không có cấu hình gì liên quan đến clock và đã gắn đúng thạch anh ngoài trên chân PD0(5) và PD1(6) thì clock tương ứng của TIM1,TIM2,TIM3,TIM4 đã là 72Mhz. Cần ghi nhớ là sử dụng timer nào thì cấp clock cho timer đó theo đúng nhánh clock.

**Prescaler**

Prescaler là bộ chia tần số của timer. Bộ chia này có giá trị tối đa là 16 bit tương ứng với giá trị là 65535. Các giá trị này có thể được thay đổi và điều chỉnh bằng lập trình. Tần số sau bộ chia này sẽ được tính là:
```
FCK_CNT = fCK_PSC/(PSC+1).
```

FCK_CNT: tần số sau bộ chia.

fCK_PSC: tần số clock đầu vào cấp cho timer.

PSC: chính là giá trị truyền vào được lập trình bằng phần mềm


**Auto Reload Value**

Auto Reload value là giá trị bộ đếm tối đa có thể được điều chỉnh để nạp vào cho timer. Giá trị bộ đếm này được cài đặt tối đa là 16bit tương ứng với giá trị là 65535.Từ các thông số trên ta rút ra công thức cần tính cuối cùng đó là:

```
FTIMER= fSYSTEM/[(PSC+1)(Period+1)]
```

FTIMER : là giá trị cuối cùng của bài toán, đơn vị là hz.
FSYSTEM : tần số clock hệ thống được chia cho timer sử dụng, đơn vị là hz.
PSC : giá trị nạp vào cho bộ chia tần số của timer. Tối đa là 65535.
Period : giá trị bộ đếm nạp vào cho timer. Tối đa là 65535.

**Cấu hình Timer**

Tương tự các ngoại vi khác, cần xác định clock cấp cho timer, các tham số cho timer được cấu hình trong struct TIM_TimBaseInitTypeDef, cuối cùng gọi hàm TIM_TimBaseInit() để khởi tạo timer.

![image](https://github.com/phatminhswe/stm32/assets/162662273/17a29070-22d2-42b0-9e14-1145ee346b01)



7199 tương ứng với giá trị PSC, 9999 tương ứng với Period. Clock cung cấp cho TIM4 là 72Mhz. Tính theo công thức ta sẽ được thời gian ngắt tràn là 1s. 


  
</details>
<details><summary> LESSION 3 : Các chuẩn giao tiếp </summary>

Các MCU truyền nhận dữ liệu với nhau hoặc với các thiết bị  thông qua tín hiệu điện áp. MCU có thể truyền nhận song song, nối tiếp các tín hiệu điện áp này thông quá các chân được cấu hình riêng biệt.

Để việc truyền nhận được dễ dàng với nhiều dòng MCU và phần cứng, các chuẩn giao tiếp được tạo ra.  Vi điều khiển sẽ sử dụng các chuẩn giao tiếp khác nhau để liên lạc với nhau hoặc liên lạc với các thiết bị khác hay các phần tử  khác trên mạch. Có thể kể đến như I2C, SPI, UART, ….

# 1 SPI.

SPI – Serial Peripheral Interface – hay còn gọi là giao diện ngoại vi nối tiếp, được phát triển bởi hãng Motorola. 
Chuẩn đồng bộ nối truyền dữ liệu ở chế độ full - duplex (hay gọi là "song công toàn phần". Nghĩa là tại 1 thời điểm có thể xảy ra đồng thời quá trình truyền và nhận. Là giao tiếp đồng bộ, bất cứ quá trình nào cũng đều được đồng bộ với xung clock sinh ra bởi thiết bị Master  
Tốc độ truyền thông cao: SPI cho phép truyền dữ liệu với tốc độ rất nhanh, thường đạt được tốc độ Mbps hoặc thậm chí hàng chục Mbps. Điều này rất hữu ích khi cần truyền dữ liệu nhanh và đáng tin cậy trong các ứng dụng như truyền thông không dây, điều khiển từ xa và truyền dữ liệu đa phương tiện.

**SPI sử dụng 4 đường giao tiếp nên đôi khi được gọi là chuẩn truyền thông “ 4 dây”:**

- SCK (Serial Clock): Thiết bị Master tạo xung tín hiệu SCK và cung cấp cho Slave. Xung này có chức năng giữ nhịp cho giao tiếp SPI. Mỗi nhịp trên chân SCK báo 1 bit dữ liệu đến hoặc đi → Quá trình ít bị lỗi và tốc độ truyền cao.

- MISO (Master Input Slave Output): Tín hiệu tạo bởi thiết bị Slave và nhận bởi thiết bị Master. Đường MISO phải được kết nối giữa thiết bị Master và Slave.

- MOSI (Master Output Slave Input): Tín hiệu tạo bởi thiết bị Master và nhận bởi thiết bị Slave. Đường MOSI phải được kết nối giữa thiết bị Master và Slave.

- SS (Slave Select): Chọn thiết bị Slave cụ thể để giao tiếp. Để chọn Slave giao tiếp thiết bị Master chủ động kéo đường SS tương ứng xuống mức 0 (Low). Chân này đôi khi còn được gọi là 
CS (Chip Select). Chân SS của vi điều khiển (Master) có thể được người dùng tạo bằng cách cấu hình 1 chân GPIO bất kỳ chế độ Output.

SPI cho phép 1 MCU chủ giao tiếp với nhiều thiết bị tớ thông qua tín hiệu chọn thiết bị SS. Các thiết bị tớ chỉ có thể có 1 chân CS để nhận tín hiệu chọn này, tuy nhiên thiết bị chủ có thể có nhiều hơn 1 chân SS để chọn từng thiết bị muốn giao tiếp.

![image](https://github.com/phatminhswe/stm32/assets/162662273/ec91e5f9-9a16-4460-af67-f3dcd8bf1a1a)



Khung truyền SPI:

Mỗi chip Master hay Slave đều có một thanh ghi dữ liệu 8 bits. Quá trình truyền nhận giữa Master và Slave xảy ra đồng thời theo chu kỳ clock ở chân CLK, một byte dữ liệu được truyền theo cả 2 hướng.

Quá trình trao đổi dữ liệu bắt đầu khi Master tạo 1 xung clock từ bộ tạo xung nhịp (Clock Generator) và kéo đường SS của Slave mà nó truyền dữ liệu xuống mức Low. Mỗi xung clock, Master sẽ gửi đi 1 bit từ thanh ghi dịch (Shift Register) của nó đến thanh ghi dịch của Slave thông qua đường MOSI. Đồng thời Slave cũng gửi lại 1 bit đến cho Master qua đường MISO.Như vậy sau 8 chu kỳ clock thì hoàn tất việc truyền và nhận 1 byte dữ liệu.

Trong giao tiếp SPI, chỉ có thể có 1 Master nhưng có thể 1 hoặc nhiều Slave cùng lúc. Ở trạng thái nghỉ, chân SS của các Slave ở mức 1, muốn giao tiếp với Slave nào thì ta chỉ việc kéo chân SS của Slave đó xuống mức 0.

![image](https://github.com/phatminhswe/stm32/assets/162662273/4fa05a4f-9ab5-4a95-a0d0-391945c33bff)



Chế độ hoạt động: 
SPI có 4 chế độ hoạt động phụ thuộc vào cực của xung giữ (Clock Polarity – CPOL) và pha (Phase - CPHA). CPOL dùng để chỉ trạng thái của chân SCK ở trạng thái nghỉ. Chân SCK giữ ở mức cao khi CPOL=1 hoặc mức thấp khi CPOL=0. CPHA dùng để chỉ các mà dữ liệu được lấy mẫu theo xung. Dữ liệu sẽ được lấy ở cạnh lên của SCK khi CPHA=0 hoặc cạnh xuống khi CPHA=1.


![image](https://github.com/phatminhswe/stm32/assets/162662273/dd5737ea-4dd6-4b4c-a468-fb1ed247a7ed)



- Mode 0 (mặc định) – xung nhịp của đồng hồ ở mức thấp (CPOL = 0) và dữ liệu được lấy mẫu khi chuyển từ thấp sang cao (cạnh lên) (CPHA = 0). 
- Mode 1 - xung nhịp của đồng hồ ở mức thấp (CPOL = 0) và dữ liệu được lấy mẫu khi chuyển từ cao sang thấp (cạnh xuống) (CPHA = 1).
- Mode 2 - xung nhịp của đồng hồ ở mức cao (CPOL = 1) và dữ liệu được lấy mẫu khi chuyển từ cao sang thấp (cạnh lên) (CPHA = 0).
- Mode 3 - xung nhịp của đồng hồ ở mức cao (CPOL = 1) và dữ liệu được lấy mẫu khi chuyển từ thấp sang cao (cạnh xuông) (CPHA = 1).

# 2 UART.


UART (Universal Asynchronous Receiver-Transmitter – Bộ truyền nhận dữ liệu không đồng bộ) là một giao thức truyền thông phần cứng dùng giao tiếp nối tiếp không đồng bộ và có thể cấu hình được tốc độ.

Giao thức UART là một giao thức đơn giản và phổ biến, bao gồm hai đường truyền dữ liệu độc lập là TX (truyền) và RX (nhận). Dữ liệu được truyền và nhận qua các đường truyền này dưới dạng các khung dữ liệu (data frame) có cấu trúc chuẩn, với một bit bắt đầu (start bit), một số bit dữ liệu (data bits), một bit kiểm tra chẵn lẻ (parity bit) và một hoặc nhiều bit dừng (stop bit).

![image](https://github.com/phatminhswe/stm32/assets/162662273/c322591f-1194-4e42-bcb1-3294ef0ad27a)


Thông thường, tốc độ truyền của UART được đặt ở một số chuẩn, chẳng hạn như 9600, 19200, 38400, 57600, 115200 baud và các tốc độ khác. Tốc độ truyền này định nghĩa số lượng bit được truyền qua mỗi giây. Các tốc độ truyền khác nhau thường được sử dụng tùy thuộc vào ứng dụng và hệ thống sử dụng.

Uart truyền dữ liệu nối tiếp, theo 1 trong 3 chế độ:

- Simplex: Chỉ tiến hành giao tiếp một chiều

- Half duplex: Dữ liệu sẽ đi theo một hướng tại 1 thời điểm
  
- Full duplex: Thực hiện giao tiếp đồng thời đến và đi từ mỗi master và slave


Chân Tx (truyền) của một chip sẽ kết nối trực tiếp với chân Rx (nhận) của chip khác và ngược lại. Quá trình truyền dữ liệu thường sẽ diễn ra ở 3.3V hoặc 5V. Uart là một giao thức giao tiếp giữa một master và một slave. Trong đó 1 thiết bị được thiết lập để tiến hành giao tiếp với chỉ duy nhất 1 thiết bị khác.

Dữ liệu truyền đến và đi từ Uart song song với thiết bị điều khiển. Khi tín hiệu gửi trên chân Tx (truyền), bộ giao tiếp Uart đầu tiên sẽ dịch thông tin song song này thành dạng nối tiếp và sau đó truyền tới thiết bị nhận. Chân Rx (nhận) của Uart thứ 2 sẽ biến đổi nó trở lại thành dạng song song để giao tiếp với các thiết bị điều khiển.

Dữ liệu truyền qua Uart sẽ đóng thành các gói (packet). Mỗi gói dữ liệu chứa 1 bit bắt đầu, 5 – 9 bit dữ liệu (tùy thuộc vào bộ Uart), 1 bit chẵn lẻ tùy chọn và 1 bit hoặc 2 bit dừng.

![image](https://github.com/phatminhswe/stm32/assets/162662273/7b1b5b2d-f2a1-449d-b619-e86bd5072975)


Quá trình truyền dữ liệu Uart sẽ diễn ra dưới dạng các gói dữ liệu này, bắt đầu bằng 1 bit bắt đầu, đường mức cao được kéo dần xuống thấp. Sau bit bắt đầu là 5 – 9 bit dữ liệu truyền trong khung dữ liệu của gói, theo sau là bit chẵn lẻ tùy chọn để nhằm xác minh việc truyền dữ liệu thích hợp. Sau cùng, 1 hoặc nhiều bit dừng sẽ được truyền ở nơi đường đặt tại mức cao. Vậy là sẽ kết thúc việc truyền đi một gói dữ liệu


![image](https://github.com/phatminhswe/stm32/assets/162662273/a33a8312-f9f9-42d6-b4ce-75827c7e4bac)



# 3 I2C.
I2C kết hợp các tính năng tốt nhất của SPI và UART. Giống như giao tiếp UART, I2C chỉ sử dụng hai dây để truyền dữ liệu giữa các thiết bị:

- SDA (Serial Data) - đường truyền cho master và slave để gửi và nhận dữ liệu.

- SCL (Serial Clock) - đường mang tín hiệu xung nhịp.

I2C là một giao thức truyền thông nối tiếp, vì vậy dữ liệu được truyền từng bit dọc theo một đường duy nhất (đường SDA).

Giống như SPI, I2C là đồng bộ, do đó đầu ra của các bit được đồng bộ hóa với việc lấy mẫu các bit bởi một tín hiệu xung nhịp được chia sẻ giữa master và slave. Tín hiệu xung nhịp luôn được điều khiển bởi master.

Với I2C, dữ liệu được truyền trong các tin nhắn. Tin nhắn được chia thành các khung dữ liệu. Mỗi tin nhắn có một khung địa chỉ chứa địa chỉ nhị phân của địa chỉ slave và một hoặc nhiều khung dữ liệu chứa dữ liệu đang được truyền. Thông điệp cũng bao gồm điều kiện khởi động và điều kiện dừng, các bit đọc / ghi và các bit ACK / NACK giữa mỗi khung dữ liệu:

![image](https://github.com/phatminhswe/stm32/assets/162662273/0f8c73cc-caf2-4e3f-aa06-c618ea763aa2)




Điều kiện khởi động: Đường SDA chuyển từ mức điện áp cao xuống mức điện áp thấp trước khi đường SCL chuyển từ mức cao xuống mức thấp.

Điều kiện dừng: Đường SDA chuyển từ mức điện áp thấp sang mức điện áp cao sau khi đường SCL chuyển từ mức thấp lên mức cao.

Khung địa chỉ: Một chuỗi 7 hoặc 10 bit duy nhất cho mỗi slave để xác định slave khi master muốn giao tiếp với nó.

Bit Đọc / Ghi: Một bit duy nhất chỉ định master đang gửi dữ liệu đến slave (mức điện áp thấp) hay yêu cầu dữ liệu từ nó (mức điện áp cao).

Bit ACK / NACK: Mỗi khung trong một tin nhắn được theo sau bởi một bit xác nhận / không xác nhận. Nếu một khung địa chỉ hoặc khung dữ liệu được nhận thành công, một bit ACK sẽ được trả lại cho thiết bị gửi từ thiết bị nhận.

Địa chỉ

I2C không có các đường Slave Select như SPI, vì vậy cần một cách khác để cho slave biết rằng dữ liệu đang được gửi đến slave này chứ không phải slave khác. Nó thực hiện điều này bằng cách định địa chỉ. Khung địa chỉ luôn là khung đầu tiên sau bit khởi động.

Master gửi địa chỉ của slave mà nó muốn giao tiếp với mọi slave được kết nối với nó. Sau đó, mỗi slave sẽ so sánh địa chỉ được gửi từ master với địa chỉ của chính nó. Nếu địa chỉ phù hợp, nó sẽ gửi lại một bit ACK điện áp thấp cho master. Nếu địa chỉ không khớp, slave không làm gì cả và đường SDA vẫn ở mức cao.

Bit đọc / ghi

Khung địa chỉ bao gồm một bit duy nhất ở cuối tin nhắn cho slave biết master muốn ghi dữ liệu vào nó hay nhận dữ liệu từ nó. Nếu master muốn gửi dữ liệu đến slave, bit đọc / ghi ở mức điện áp thấp. Nếu master đang yêu cầu dữ liệu từ slave, thì bit ở mức điện áp cao.

Khung dữ liệu

Sau khi master phát hiện bit ACK từ slave, khung dữ liệu đầu tiên đã sẵn sàng được gửi.

Khung dữ liệu luôn có độ dài 8 bit và được gửi với bit quan trọng nhất trước. Mỗi khung dữ liệu ngay sau đó là một bit ACK / NACK để xác minh rằng khung đã được nhận thành công. Bit ACK phải được nhận bởi master hoặc slave (tùy thuộc vào cái nào đang gửi dữ liệu) trước khi khung dữ liệu tiếp theo có thể được gửi.
 
Sau khi tất cả các khung dữ liệu đã được gửi, master có thể gửi một điều kiện dừng cho slave để tạm dừng quá trình truyền. Điều kiện dừng là sự chuyển đổi điện áp từ thấp lên cao trên đường SDA sau khi chuyển tiếp từ thấp lên cao trên đường SCL , với đường SCL vẫn ở mức cao.
 
**Các bước truyền dữ liệu I2C**

1.Master gửi điều kiện khởi động đến mọi slave được kết nối bằng cách chuyển đường SDA từ mức điện áp cao sang mức điện áp thấp trước khi chuyển đường SCL từ mức cao xuống mức thấp.

2.Master gửi cho mỗi slave địa chỉ 7 hoặc 10 bit của slave mà nó muốn giao tiếp, cùng với bit đọc / ghi.

3.Mỗi slave sẽ so sánh địa chỉ được gửi từ master với địa chỉ của chính nó. Nếu địa chỉ trùng khớp, slave sẽ trả về một bit ACK bằng cách kéo dòng SDA xuống thấp cho một bit. Nếu địa chỉ từ master không khớp với địa chỉ của slave, slave rời khỏi đường SDA cao.

4.Master gửi hoặc nhận khung dữ liệu.

5.Sau khi mỗi khung dữ liệu được chuyển, thiết bị nhận trả về một bit ACK khác cho thiết bị gửi để xác nhận đã nhận thành công khung.

6.Để dừng truyền dữ liệu, master gửi điều kiện dừng đến slave bằng cách chuyển đổi mức cao SCL trước khi chuyển mức cao SDA.

![image](https://github.com/phatminhswe/stm32/assets/162662273/9747434b-99dc-4af1-a6e8-3ef2b688b67a)


**Một master với nhiều slave**

Vì I2C sử dụng định địa chỉ nên nhiều slave có thể được điều khiển từ một master duy nhất. Với địa chỉ 7 bit sẽ có 128 (2 mũ 7) địa chỉ duy nhất. Việc sử dụng địa chỉ 10 bit không phổ biến, nhưng nó cung cấp 1.024 (2 mũ 10) địa chỉ duy nhất.


**Nhiều master với nhiều slave**

Nhiều master có thể được kết nối với một slave hoặc nhiều slave. Sự cố với nhiều master trong cùng một hệ thống xảy ra khi hai master cố gắng gửi hoặc nhận dữ liệu cùng một lúc qua đường SDA. Để giải quyết vấn đề này, mỗi master cần phải phát hiện xem đường SDA thấp hay cao trước khi truyền tin nhắn. Nếu đường SDA thấp, điều này có nghĩa là một master khác có quyền điều khiển bus và master đó phải đợi để gửi tin nhắn. Nếu đường SDA cao thì có thể truyền tin nhắn an toàn. Để kết nối nhiều master với nhiều slave.

![image](https://github.com/phatminhswe/stm32/assets/162662273/f040dacf-b6ef-4dfb-9987-ee01cf133397)


  
</details>
<details><summary> LESSION 4 : SPI </summary>

</details>
<details><summary> LESSION 5 : I2C </summary>

</details>
<details><summary> LESSION 4 : UART </summary>

- Xác định baudrate: Vì uart ko có dây clock nên nó phải thống nhất với thiết bị truyền 1 baudrate nhất định.
- Baudrate là số đơn vị tín hiệu được truyền trên mỗi đơn vị thời gian cần thiết để biểu diễn các bit đó.
- Bitrate là số bit (tức là 0 và 1) được truyền trong mỗi đơn vị thời gian.
                  ![image](https://github.com/NguyenEngineer/Embedded_STM/assets/120030797/cc1358d3-e800-46ca-ac4d-03e3e1e6e14f)

-  Tính baudrate là trong khoảng thời gian Period đó sẽ xác định là 1 bit (0/1).
-  VD: baudrate = 9600 thì 1 bit sẽ được xác định trong khoảng 1 bit = 0.104 ms.
                 ![image](https://github.com/NguyenEngineer/Embedded_STM/assets/120030797/482e15c7-68a4-4fd7-9b82-a8e3739db75e)

- Cấu hình:
                        
                       void UART_Config(){
                            GPIO_SetBits(UART_GPIO, TX_Pin);   //Baudrate = 9600bits/s >> 0.10467 ms for 1 bit = 104,67 us //=>> time delay ~~105 us
                            delay_us(1);
                       }
- Hàm truyền:     - Tạo 1 bit start bằng cách kéo chân RX xuống mức 0, tạo 1 delay để xác nhận 1 bit.
                  - Truyền 8 bit đi và mỗi bit sẽ được truyền trong khoảng 1 period time.
                  - Dịch phải mỗi bít đã truyền.
                  - Truyền bit stop bằng cách: kéo chân RX lên mức 1 trong 1 khoảng period time.
            VD:

                      void UART_Transmit(const char DataValue)
                    {
                        	GPIO_WriteBit(UART_GPIO, TX_Pin, Bit_RESET);
                        	delay_us(BRateTime);
                        	for ( unsigned char i = 0; i < 8; i++ ){
                          		if( ((DataValue>>i)&0x1) == 0x1 ){
                          			GPIO_WriteBit(UART_GPIO, RX_Pin, Bit_SET);
                          		} else{
                          			GPIO_WriteBit(UART_GPIO, RX_Pin, Bit_RESET);
                        		}
                        	delay_us(BRateTime);
                    	}
                    	GPIO_WriteBit(UART_GPIO, TX_Pin, Bit_SET);                     	// Send Stop Bit
                    	delay_us(BRateTime);
                    }
  
- Hàm nhận:       - Chờ tín hiệu start từ thiết bị gửi ( thiết bị nhận sẽ nhận đc 1 tín hiệu mức 0 để biết bit Start ), tạo 1 delay bằng với period time.
                  - Sau khi nhận đc bit start thì phải delay thêm (1.5 x period time) để chống nhiễu ( 1 --> 0)
                  - Đọc 8 bit và mỗi bit sẽ được ghi vào biến lưu.
                  - Dịch mỗi bit đã nhận.
                  - Truyền bit stop bằng cách: kéo chân RX lên mức 1 trong 1 khoảng period time.
          ![image](https://github.com/NguyenEngineer/Embedded_STM/assets/120030797/ec85e433-4014-4def-b0d2-03b1caef44da)

            VD:

                      unsigned char UART_Receive(void){
                        	unsigned char DataValue = 0;
                        	while(GPIO_ReadInputDataBit(UART_GPIO, RX_Pin) == 1);
                        	delay_us(BRateTime);
                        	delay_us(BRateTime/2);
                        	for ( unsigned char i = 0; i < 8; i++ ){
                        		if ( GPIO_ReadInputDataBit(UART_GPIO, RX_Pin) == 1 ){
                        			DataValue += (1<<i);}                               // nếu nhận được bit 1 thì sẽ dịch bit đó sang trái theo thứ tự bit nhận đc và cộng dồn vào biến Datavalue
                                                                                  // VD:  DataValue có 8 bit 0, bit đầu nhận đc là 1:  for i = 0  dịch (1 << 0) và cộng vào DataValue  0x00 + 0x01 = 0x01 => DataValue = 0x01
                                                                                           DataValue có bit 0x01, bit thứ 2 nhận đc là 1:  for i = 1  dịch (1 << 1) và cộng vào DataValue  0x01 + 0x02 = 0x03 => DataValue = 0x03
                        		delay_us(BRateTime);
                        	}
                        		if ( GPIO_ReadInputDataBit(UART_GPIO, RX_Pin) == 1 ){
                        			delay_us(BRateTime/2);
                        			return DataValue;
                        	} 
                       }
  
- Hàm kiểm tra cờ:   Hàm USART_GetFlagStatus(USART_TypeDef* USARTx, uint16_t USART_FLAG) trả về trạng thái cờ USART_FLAG tương ứng:
                          USART_FLAG_TXE: Cờ truyền, set lên 1 nếu quá trình truyền hoàn tất.
                          USART_FLAG_RXNE: Cờ nhận, set lên 1 nếu quá trình nhận hoàn tất.
                          USART_FLAG_IDLE: Cờ báo đường truyền đang ở chế độ Idle.
                          USART_FLAG_PE: Cờ báo lỗi Parity.
  
- Cấu hình:         -Struct USART_InitTypeDef:
                 - USART_Mode: Cấu hình chế độ hoạt động cho UART:
                 - USART_Mode_Tx: Cấu hình truyền.
                 - USART_Mode_Rx: Cấu hình nhận.     // Có thể cấu hình cả 2 cùng lúc (song công).
                 - USART_BaudRate: Cấu hình tốc độ baudrate cho uart.
                 - USART_HardwareFlowControl: Cấu hình chế độ bắt tay cho uart.
                 - USART_WordLength: Cấu hình số bit mỗi lần truyền.
                 - USART_StopBits: Cấu hình số lượng stopbits.
                 - USART_Parity: cấu hình bit kiểm tra chẳn, lẻ.
        VD:
  
                    void UART_Config(){
                  		//Usart
                  	USARTInitStruct.USART_BaudRate = 9600;
                  	USARTInitStruct.USART_WordLength = USART_WordLength_8b;
                  	USARTInitStruct.USART_StopBits = USART_StopBits_1;
                  	USARTInitStruct.USART_Parity = USART_Parity_No;
                  	USARTInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
                  	USARTInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
                  	USART_Init(USART1, &USARTInitStruct);
                  	USART_Cmd(USART1,ENABLE);
                  }
  
</details>
<details><summary> LESSION  :  </summary>

</details>
<details><summary> LESSION  :  </summary>

</details>
<details><summary> LESSION  :  </summary>

</details>
<details><summary> LESSION  :  </summary>

</details>
<details><summary> LESSION 11 : Flash and Bootloader </summary>
## Flash
- Khi mất nguồn toàn bộ dữ liệu đang hoạt động của VDK sẽ mất đi. Nên ta phải lưu vào bộ nhớ Flash và Eprom
![image](https://github.com/NguyenEngineer/Embedded_STM/assets/120030797/1dce2e76-4bb9-46e8-a215-32b8c84be62d)
- Flash là bộ nhớ lưu trữ dữ liệu chương trình mà khi mất nguồn thì ko mất dữ liệu. 
- Eprom là giống flash nhưng là chip mở rộng hơn để lưu trữ.
![image](https://github.com/NguyenEngineer/Embedded_STM/assets/120030797/16dd9910-1180-40af-af1a-7f0f76ca4a0d)
- Tùy vào kiến trúc VDK mà kích thướbộ nhớ Flash có thể lưu được.               VD: STM32F103 có 128/64Kb Flash
- Flash được chia nhỏ ra thành mỗi PAGE, 1 PAGE có kích thước 1KB.              VD: STM32F103 có 128/64Kb Flash -> thì sẽ có 127 page (0 -> 127)
- 1 Bank gồm nhiều các PAGE.                                                    VD: 1 Bank gồm có 16 Page.
- Flash phải được xóa đặt về 0 trước khi lưu dữ liệu mới
![image](https://github.com/NguyenEngineer/Embedded_STM/assets/120030797/a7c40dda-df66-4b59-a9b9-3deb2d5aec0b)
- Thông thường chương trình sẽ được nạp vào vùng nhớ bắt đầu ở 0x08000000
- Vùng nhớ phía sau sẽ là trống và người dùng có thể lưu trữ dữ liệu ở vùng này.

Qui trình hoạt động của flash
![image](https://github.com/NguyenEngineer/Embedded_STM/assets/120030797/1d5c05bf-442c-4658-bbcf-dd20ef26f7dc)
- Mỗi lần ghi 2bytes hoặc 4bytes, tuy nhiên mỗi lần xóa phải xóa cả Page.
- Sơ đồ xóa FLash như hình:
       + Đầu tiên, kiểm tra cờ LOCK của Flash, nếu Cờ này đang được bật, Flash đang ở chế độ Lock và cần phải được Unlock trước khi sử dụng.
       + Sau khi FLash đã Unlock, cờ CR_PER được set lên 1.
       + Địa chỉ của Page cần xóa được ghi vào FAR.
       + Set bit CR_STRT lên 1 để bắt đầu quá trình xóa.
       + Kiểm tra cờ BSY đợi haonf tất quá trình xóa.
- Các hàm sử dụng trong flash:

        Các hàm LOCK, UNLOCK Flash:
        void FLASH_Unlock(void): Hàm này Unlock cho tất cả vùng nhớ trong Flash.
        void FLASH_UnlockBank1(void): Hàm này chỉ Unlock cho Bank đầu tiên. Vì SMT32F103C8T6 chỉ có 1 Bank duy nhất nên chức năng tương tự hàm trên.
        void FLASH_UnlockBank2(void): Unlock cho Bank thứ 2.
        void FLASH_Lock(void): Lock bộ điều khiển xóa Flash cho toàn bộ vùng nhớ Flash.
        void FLASH_LockBank1(void) và void FLASH_LockBank2(void): Lock bộ điều khiển xóa Flash cho Bank 1 hoặc 2.
  
        Các Hàm xóa Flash:
        FLASH_Status FLASH_EraseAllBank1Pages(void): Xóa tất cả các Page trong Bank 1 của Flash. 
        FLASH_Status FLASH_EraseAllBank2Pages(void): Xóa tất cả các Page trong Bank 2 của Flash. 
        FLASH_Status FLASH_EraseAllPages(void): Xóa toàn bộ Flash.
        FLASH_Status FLASH_ErasePage(uint32_t Page_Address): Xóa 1 page cụ thể trong Flash, cụ thể là Page bắt đầu bằng địa chỉ Page_Address.
  
        Các hàm Ghi Flash:
        FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data):  Ghi dữ liệu vào vùng nhớ Address với kích thước mỗi 2 byte (Halfword).
        FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data): Ghi dữ liệu vào vùng nhớ Address với kích thước mỗi 4 byte (Word).
        
        FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG): hàm này trả về trạng thái của Flag. Ở bài này ta sẽ dùng hàm này để kiểm tra cờ FLASH_FLAG_BSY. Cờ này báo hiệu rằng Flash đang bận (Xóa/Ghi) nếu được set lên 1. 

- Code mẫu các hàm:
   + Hàm xóa 1 Page flash:
     
                void Flash_Erase(uint32_t addresspage){                // truyền vào địa chỉ của 1 page flash
              	FLASH_Unlock();
              	while(FLASH_GetFlagStatus(FLASH_FLAG_BSY) == 1);
              	FLASH_ErasePage(addresspage);
              	while(FLASH_GetFlagStatus(FLASH_FLAG_BSY) == 1);
              	FLASH_Lock();}

  + Hàm viết 1 KDL int xuống flash:
                
              void Flash_WriteInt(uint32_t address, uint16_t value){
              	FLASH_Unlock();
              	while(FLASH_GetFlagStatus(FLASH_FLAG_BSY) == 1);
              	FLASH_ProgramHalfWord(address, value);
              	while(FLASH_GetFlagStatus(FLASH_FLAG_BSY) == 1);
              	FLASH_Lock();}
  + Hàm viết 2 Byte xuống flash:
 
                void Flash_WriteNumByte(uint32_t address, uint8_t *data, int num){
                	FLASH_Unlock();
                	while(FLASH_GetFlagStatus(FLASH_FLAG_BSY) == 1);
                	uint16_t *ptr = (uint16_t*)data;                   // ép kiểu cho data từ uint8_t thành uint16_t
                	for(int i=0; i<((num+1)/2); i++){
                		FLASH_ProgramHalfWord(address+2*i, *ptr);
                		while(FLASH_GetFlagStatus(FLASH_FLAG_BSY) == 1);
                		ptr++;
                	}
                	FLASH_Lock();}


