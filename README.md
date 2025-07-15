# Nucleo-F429ZI FreeRTOS Task Example
 STMicroelectronics Nucleo-F429ZI Free Rtos �׽�Ʈ


## ����
```
������Ʈ/
������ Core/
��   ������ Inc/                # ��� ����
��   ��   ������ FreeRTOSConfig.h  # FreeRTOS ����
��   ��   ������ main.h
��   ��   ������ ...
��   ������ Src/                # �ҽ� ����
��       ������ freertos.c        # FreeRTOS �ʱ�ȭ �� ���� ����
��       ������ main.c            # ���� ���α׷� (Test Rtos - �� ������ �̰� Ȯ��)
��       ������ stm32f4xx_it.c    # ���ͷ�Ʈ �ڵ鷯
��       ������ ...
������ Drivers/                # HAL ����̹� �� CMSIS
��   ������ STM32F4xx_HAL_Driver/
��   ������ CMSIS/
������ Middlewares/
��   ������ Third_Party/
��       ������ FreeRTOS/         # FreeRTOS �ҽ� �ڵ�
������ ������Ʈ.ioc                # STM32CubeMX ���� ����
������ README.md               # ������Ʈ ���� ����
```

## ����� ����(pritnf ����)
```
Uart 115200 baudrate
```

## Main.c �߰��Ұ�
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

