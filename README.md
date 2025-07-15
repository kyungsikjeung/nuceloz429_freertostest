# Nucleo-F429ZI FreeRTOS Task Example
 STMicroelectronics Nucleo-F429ZI Free Rtos 테스트


## 구조
```
프로젝트/
├── Core/
│   ├── Inc/                # 헤더 파일
│   │   ├── FreeRTOSConfig.h  # FreeRTOS 설정
│   │   ├── main.h
│   │   └── ...
│   └── Src/                # 소스 파일
│       ├── freertos.c        # FreeRTOS 초기화 및 관련 설정
│       ├── main.c            # 메인 프로그램 (Test Rtos - 각 폴더별 이곳 확인)
│       ├── stm32f4xx_it.c    # 인터럽트 핸들러
│       └── ...
├── Drivers/                # HAL 드라이버 및 CMSIS
│   ├── STM32F4xx_HAL_Driver/
│   └── CMSIS/
├── Middlewares/
│   └── Third_Party/
│       └── FreeRTOS/         # FreeRTOS 소스 코드
├── 프로젝트.ioc                # STM32CubeMX 설정 파일
└── README.md               # 프로젝트 설명 파일
```

## 디버깅 정보(pritnf 삽입)
```
Uart 115200 baudrate
```

## Main.c 추가할것
```
#include <stdio.h>
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}
```




# Test 

