# VS Code Snippets 사용법 (Complete Guide)

## 1. 기본 스니펫 사용법

### 스니펫 트리거 방법
- **자동 완성**: 코드 입력 중 `Ctrl + Space`로 IntelliSense 열기
- **직접 입력**: 스니펫 접두사(prefix) 입력 후 `Tab` 또는 `Enter`
- **명령 팔레트**: `Ctrl + Shift + P` → "Insert Snippet" 검색

### 내장 스니펫 예시 (C/C++)
```c
// "for" 입력 후 Tab
for (int i = 0; i < count; i++) {
    // code
}

// "if" 입력 후 Tab
if (condition) {
    // code
}

// "while" 입력 후 Tab  
while (condition) {
    // code
}
```

## 2. 사용자 정의 스니펫 만들기

### 전역 스니펫 생성 (모든 워크스페이스에서 사용)
1. `Ctrl + Shift + P` → "Configure User Snippets" 선택
2. "New Global Snippets file" 선택
3. 파일명 입력 (예: `my-snippets.code-snippets`)

### 언어별 스니펫 생성
1. `Ctrl + Shift + P` → "Configure User Snippets" 선택  
2. 언어 선택 (예: `c.json`, `cpp.json`)

### 워크스페이스별 스니펫 생성
1. `Ctrl + Shift + P` → "Configure User Snippets" 선택
2. "New Snippets file for '[워크스페이스명]'" 선택

## 3. 스니펫 문법

### 기본 구조
```json
{
    "스니펫 이름": {
        "prefix": "트리거 키워드",
        "body": [
            "코드 라인 1",
            "코드 라인 2"
        ],
        "description": "스니펫 설명"
    }
}
```

### 변수 및 플레이스홀더
- `$1`, `$2`, `$3`: 탭 순서 (Tab키로 이동)
- `$0`: 최종 커서 위치
- `${1:기본값}`: 기본값이 있는 플레이스홀더
- `${1|선택1,선택2,선택3|}`: 드롭다운 선택

### 내장 변수
- `$TM_FILENAME`: 현재 파일명
- `$TM_FILENAME_BASE`: 확장자 제외 파일명
- `$TM_DIRECTORY`: 현재 디렉토리
- `$TM_FILEPATH`: 전체 파일 경로
- `$CURRENT_YEAR`: 현재 연도
- `$CURRENT_MONTH`: 현재 월
- `$CURRENT_DATE`: 현재 날짜

## 4. FreeRTOS/STM32 전용 스니펫 예시

### C 언어용 스니펫 (`c.json`)
```json
{
    "FreeRTOS Task": {
        "prefix": "freertos_task",
        "body": [
            "void ${1:TaskName}(void const * argument)",
            "{",
            "  for(;;)",
            "  {",
            "    ${2:// Task code here}",
            "    osDelay(${3:1000});",
            "  }",
            "}"
        ],
        "description": "FreeRTOS task template"
    },
    
    "HAL GPIO Write": {
        "prefix": "hal_gpio_write",
        "body": [
            "HAL_GPIO_WritePin(${1:GPIOB}, ${2:GPIO_PIN_0}, ${3|GPIO_PIN_SET,GPIO_PIN_RESET|});"
        ],
        "description": "HAL GPIO write pin"
    },
    
    "HAL GPIO Read": {
        "prefix": "hal_gpio_read",
        "body": [
            "if (HAL_GPIO_ReadPin(${1:GPIOA}, ${2:GPIO_PIN_0}) == ${3|GPIO_PIN_SET,GPIO_PIN_RESET|})",
            "{",
            "  ${4:// Code here}",
            "}"
        ],
        "description": "HAL GPIO read pin"
    },
    
    "Printf Debug": {
        "prefix": "printf_debug",
        "body": [
            "printf(\"${1:Debug}: %${2|d,s,f,x|}\\r\\n\", ${3:variable});"
        ],
        "description": "Printf debug statement"
    },
    
    "UART Transmit": {
        "prefix": "uart_tx",
        "body": [
            "HAL_UART_Transmit(&${1:huart3}, (uint8_t *)${2:data}, ${3:size}, HAL_MAX_DELAY);"
        ],
        "description": "UART transmit data"
    },
    
    "Error Handler": {
        "prefix": "error_check",
        "body": [
            "if (${1:function_call} != HAL_OK)",
            "{",
            "  Error_Handler();",
            "}"
        ],
        "description": "HAL error checking"
    }
}
```

## 5. 스니펫 관리 팁

### 스니펫 파일 위치
- **전역**: `%APPDATA%\\Code\\User\\snippets\\`
- **워크스페이스**: `.vscode\\snippets\\` (프로젝트 폴더 내)

### 스니펫 공유
1. 스니펫 파일을 Git으로 버전 관리
2. 팀원들과 `.vscode/snippets/` 폴더 공유
3. VS Code 확장으로 패키징

### 스니펫 디버깅
- `Ctrl + Shift + P` → "Developer: Reload Window" (스니펫 재로드)
- JSON 문법 오류 확인 (VS Code에서 자동 검증)

## 6. 유용한 확장 프로그램

### 스니펫 관련 확장
- **Snippet Creator**: 선택한 코드를 스니펫으로 변환
- **Code Snippets**: 다양한 언어별 스니펫 제공
- **C/C++ Snippets**: C/C++ 전용 스니펫 모음

### 설치 방법
1. `Ctrl + Shift + X` (확장 탭 열기)
2. 확장 이름 검색 후 설치

## 7. 실제 사용 예시

### 현재 프로젝트에 적용할 수 있는 스니펫
```json
{
    "Task Creation": {
        "prefix": "create_task",
        "body": [
            "osThreadDef(${1:taskName}, ${2:TaskFunction}, osPriorityNormal, 0, 128);",
            "${1:taskName}Handle = osThreadCreate(osThread(${1:taskName}), NULL);"
        ],
        "description": "Create FreeRTOS task"
    },
    
    "LED Toggle": {
        "prefix": "led_toggle",
        "body": [
            "HAL_GPIO_TogglePin(GPIOB, ${1|LD1_Pin,LD2_Pin,LD3_Pin|});"
        ],
        "description": "Toggle LED on STM32 board"
    }
}
```

## 8. 키보드 단축키

### 스니펫 관련 단축키
- `Ctrl + Space`: IntelliSense 활성화
- `Tab`: 다음 플레이스홀더로 이동
- `Shift + Tab`: 이전 플레이스홀더로 이동
- `Escape`: 스니펫 모드 종료

## 9. 주의사항

### JSON 문법 주의점
- 따옴표는 이스케이프: `\"`
- 백슬래시는 이스케이프: `\\`
- 새 줄은 `\\n` 또는 배열로 분리

### 성능 고려사항
- 너무 많은 스니펫은 자동완성 성능 저하
- 명확한 prefix 사용으로 충돌 방지
- 설명(description) 추가로 가독성 향상

이 가이드를 참고하여 VS Code에서 효율적으로 스니펫을 활용하세요!
