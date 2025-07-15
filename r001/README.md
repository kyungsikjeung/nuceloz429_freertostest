# STM32F429ZI FreeRTOS Project (CMSIS-OS v1)

이 문서는 STM32F429ZI 보드에서 FreeRTOS를 사용하는 본 프로젝트에 대한 상세 설명을 제공합니다. STM32CubeMX를 이용한 초기 설정부터 FreeRTOS 태스크 관리 방법까지 다룹니다.

## 1. 프로젝트 개요

본 프로젝트는 STM32F429ZI 마이크로컨트롤러에서 FreeRTOS를 활용하여 여러 작업을 동시에 처리하는 예제입니다. STM32CubeMX를 통해 기본적인 하드웨어 설정 및 FreeRTOS 설정이 이루어졌으며, CMSIS-OS v1 API를 사용하여 운영체제 기능을 제어합니다.

## 2. STM32CubeMX 설정 가이드

STM32CubeMX (`r001.ioc` 파일)를 통해 다음과 같은 주요 설정이 구성되었습니다.

### 2.1. 시스템 및 하드웨어 설정

- **MCU:** STM32F429ZITx
- **System Core > SYS:**
    - **Debug:** Serial Wire
- **System Core > RCC:**
    - **High Speed Clock (HSE):** BYPASS Clock Source
- **Connectivity > USART3:**
    - **Mode:** Asynchronous
    - **Baud Rate:** 115200 Bits/s
    - **Word Length:** 8 Bits (Parity included)
    - **Parity:** None
    - **Stop Bits:** 1
- **GPIO:**
    - `PB0`, `PB7`, `PB14` 핀을 `GPIO_Output`으로 설정하여 보드의 LED(LD1, LD2, LD3)를 제어합니다.
    - `PC13` 핀을 `GPIO_Input`으로 설정하여 사용자 버튼(USER_Btn) 입력을 받습니다.

### 2.2. FreeRTOS (CMSIS-OS v1) 설정

- **Middleware > FREERTOS:**
    - **Interface:** CMSIS_V1
    - **Tasks and Queues:**
        - **task01:**
            - **Entry Function:** `Task01_init`
            - **Priority:** `osPriorityNormal`
            - **Stack Size (Words):** 128
        - **task02:**
            - **Entry Function:** `Task02_init`
            - **Priority:** `osPriorityNormal`
            - **Stack Size (Words):** 128
        - **task03:**
            - **Entry Function:** `Task03_init`
            - **Priority:** `osPriorityNormal`
            - **Stack Size (Words):** 128
    - **Kernel Settings:**
        - **System Timer:** TIM1 (다른 타이머와 충돌을 피하기 위해 선택)

이 설정들은 `main.c` 파일 내의 `MX_` 함수들 (`MX_GPIO_Init`, `MX_USART3_UART_Init` 등)과 `freertos.c` 파일에 자동으로 코드를 생성합니다.

## 3. 프로젝트 파일 구조

```
r001/
├── Core/
│   ├── Inc/                # 헤더 파일
│   │   ├── FreeRTOSConfig.h  # FreeRTOS 설정
│   │   ├── main.h
│   │   └── ...
│   └── Src/                # 소스 파일
│       ├── freertos.c        # FreeRTOS 초기화 및 관련 설정
│       ├── main.c            # 메인 프로그램
│       ├── stm32f4xx_it.c    # 인터럽트 핸들러
│       └── ...
├── Drivers/                # HAL 드라이버 및 CMSIS
│   ├── STM32F4xx_HAL_Driver/
│   └── CMSIS/
├── Middlewares/
│   └── Third_Party/
│       └── FreeRTOS/         # FreeRTOS 소스 코드
├── r001.ioc                # STM32CubeMX 설정 파일
└── README.md               # 프로젝트 설명 파일
```

## 4. FreeRTOS 태스크 관리

본 프로젝트는 CMSIS-OS v1 API를 사용하여 FreeRTOS 태스크를 관리합니다.

### 4.1. 태스크 핸들러 (`osThreadId`)

`osThreadId` 타입은 생성된 태스크를 식별하고 제어하는 데 사용되는 핸들입니다. `main.c` 파일에 각 태스크의 핸들이 다음과 같이 선언되어 있습니다.

```c
osThreadId task01Handle;
osThreadId task02Handle;
osThreadId task03Handle;
```

이 핸들러는 `osThreadCreate` 함수에 의해 반환되며, 특정 태스크를 제어(예: 중단, 재개, 우선순위 변경)할 때 사용됩니다.

### 4.2. 태스크 정의 (`osThreadDef`)

`osThreadDef` 매크로는 태스크의 속성을 정의합니다. 이 매크로는 여러 인자를 받아 태스크의 동작 방식을 설정합니다.

- **구문:** `osThreadDef(name, thread, priority, instances, stacksize)`
    - `name`: 태스크의 이름 (예: `task01`)
    - `thread`: 태스크 진입점 함수 (예: `Task01_init`)
    - `priority`: 태스크 우선순위 (예: `osPriorityNormal`)
    - `instances`: 생성할 태스크 인스턴스 수 (일반적으로 1, 여기서는 0으로 설정되어 `osThreadCreate`에서 처리)
    - `stacksize`: 태스크 스택 크기 (단위: Words)

`main.c`에서는 다음과 같이 태스크를 정의합니다.

```c
osThreadDef(task01, Task01_init, osPriorityNormal, 0, 128);
```

### 4.3. 태스크 생성 및 실행

1.  **태스크 함수 구현:** `main.c` 하단에 각 태스크가 실행할 코드를 담은 함수를 작성합니다. 각 함수는 무한 루프(`for(;;)`) 안에서 특정 동작을 주기적으로 수행합니다.

    ```c
    void Task01_init(void const * argument)
    {
      for(;;)
      {
        print_uart("Task 01 is running\r\n"); // USART3로 메시지 출력
        osDelay(1000); // 1초 대기
      }
    }
    ```

2.  **태스크 생성:** `main()` 함수 내에서 `osThreadDef`로 태스크를 정의한 후, `osThreadCreate`를 호출하여 태스크를 생성하고 커널에 등록합니다.

    ```c
    osThreadId task01Handle;
    osThreadId task02Handle;
    osThreadId task03Handle;

    task01Handle = osThreadCreate(osThread(task01), NULL);
    ```

3.  **스케줄러 시작:** 모든 태스크 생성이 완료되면 `osKernelStart()`를 호출하여 FreeRTOS 스케줄러를 시작합니다. 이 시점부터 스케줄러가 태스크들을 관리하며, 정의된 우선순위에 따라 CPU 시간을 할당합니다.

## 5. 새로운 태스크 추가 방법

1.  **STM32CubeMX에서 추가 (권장):**
    - `r001.ioc` 파일을 열고 `Middleware > FREERTOS` 설정으로 이동합니다.
    - `Tasks and Queues` 탭에서 `Add` 버튼을 눌러 새로운 태스크를 추가하고 속성을 설정합니다.
    - 코드를 다시 생성하면 `main.c`와 `freertos.c`에 관련 코드가 자동으로 추가됩니다.

2.  **수동으로 추가:**
    - `main.c`에 새로운 태스크 핸들(`osThreadId myNewTaskHandle;`)을 선언합니다.
    - 태스크 진입점 함수(`void MyNewTask_init(void const * argument)`)를 구현합니다.
    - `main()` 함수에서 `osThreadDef`와 `osThreadCreate`를 사용하여 태스크를 정의하고 생성합니다.

## 6. 예상 출력

프로젝트가 성공적으로 빌드되고 실행되면, 디버그 콘솔 또는 UART 터미널을 통해 다음과 유사한 출력을 주기적으로 확인할 수 있습니다. 이는 FreeRTOS 태스크들이 정상적으로 스케줄링되어 실행되고 있음을 나타냅니다.

```
Task 01 is running
Task 02 is running
Task 03 is running
Task 01 is running
Task 02 is running
Task 03 is running
...
```

