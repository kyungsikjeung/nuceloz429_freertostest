# VS Code Snippets ���� (Complete Guide)

## 1. �⺻ ������ ����

### ������ Ʈ���� ���
- **�ڵ� �ϼ�**: �ڵ� �Է� �� `Ctrl + Space`�� IntelliSense ����
- **���� �Է�**: ������ ���λ�(prefix) �Է� �� `Tab` �Ǵ� `Enter`
- **��� �ȷ�Ʈ**: `Ctrl + Shift + P` �� "Insert Snippet" �˻�

### ���� ������ ���� (C/C++)
```c
// "for" �Է� �� Tab
for (int i = 0; i < count; i++) {
    // code
}

// "if" �Է� �� Tab
if (condition) {
    // code
}

// "while" �Է� �� Tab  
while (condition) {
    // code
}
```

## 2. ����� ���� ������ �����

### ���� ������ ���� (��� ��ũ�����̽����� ���)
1. `Ctrl + Shift + P` �� "Configure User Snippets" ����
2. "New Global Snippets file" ����
3. ���ϸ� �Է� (��: `my-snippets.code-snippets`)

### �� ������ ����
1. `Ctrl + Shift + P` �� "Configure User Snippets" ����  
2. ��� ���� (��: `c.json`, `cpp.json`)

### ��ũ�����̽��� ������ ����
1. `Ctrl + Shift + P` �� "Configure User Snippets" ����
2. "New Snippets file for '[��ũ�����̽���]'" ����

## 3. ������ ����

### �⺻ ����
```json
{
    "������ �̸�": {
        "prefix": "Ʈ���� Ű����",
        "body": [
            "�ڵ� ���� 1",
            "�ڵ� ���� 2"
        ],
        "description": "������ ����"
    }
}
```

### ���� �� �÷��̽�Ȧ��
- `$1`, `$2`, `$3`: �� ���� (TabŰ�� �̵�)
- `$0`: ���� Ŀ�� ��ġ
- `${1:�⺻��}`: �⺻���� �ִ� �÷��̽�Ȧ��
- `${1|����1,����2,����3|}`: ��Ӵٿ� ����

### ���� ����
- `$TM_FILENAME`: ���� ���ϸ�
- `$TM_FILENAME_BASE`: Ȯ���� ���� ���ϸ�
- `$TM_DIRECTORY`: ���� ���丮
- `$TM_FILEPATH`: ��ü ���� ���
- `$CURRENT_YEAR`: ���� ����
- `$CURRENT_MONTH`: ���� ��
- `$CURRENT_DATE`: ���� ��¥

## 4. FreeRTOS/STM32 ���� ������ ����

### C ���� ������ (`c.json`)
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

## 5. ������ ���� ��

### ������ ���� ��ġ
- **����**: `%APPDATA%\\Code\\User\\snippets\\`
- **��ũ�����̽�**: `.vscode\\snippets\\` (������Ʈ ���� ��)

### ������ ����
1. ������ ������ Git���� ���� ����
2. ������� `.vscode/snippets/` ���� ����
3. VS Code Ȯ������ ��Ű¡

### ������ �����
- `Ctrl + Shift + P` �� "Developer: Reload Window" (������ ��ε�)
- JSON ���� ���� Ȯ�� (VS Code���� �ڵ� ����)

## 6. ������ Ȯ�� ���α׷�

### ������ ���� Ȯ��
- **Snippet Creator**: ������ �ڵ带 ���������� ��ȯ
- **Code Snippets**: �پ��� �� ������ ����
- **C/C++ Snippets**: C/C++ ���� ������ ����

### ��ġ ���
1. `Ctrl + Shift + X` (Ȯ�� �� ����)
2. Ȯ�� �̸� �˻� �� ��ġ

## 7. ���� ��� ����

### ���� ������Ʈ�� ������ �� �ִ� ������
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

## 8. Ű���� ����Ű

### ������ ���� ����Ű
- `Ctrl + Space`: IntelliSense Ȱ��ȭ
- `Tab`: ���� �÷��̽�Ȧ���� �̵�
- `Shift + Tab`: ���� �÷��̽�Ȧ���� �̵�
- `Escape`: ������ ��� ����

## 9. ���ǻ���

### JSON ���� ������
- ����ǥ�� �̽�������: `\"`
- �齽���ô� �̽�������: `\\`
- �� ���� `\\n` �Ǵ� �迭�� �и�

### ���� �������
- �ʹ� ���� �������� �ڵ��ϼ� ���� ����
- ��Ȯ�� prefix ������� �浹 ����
- ����(description) �߰��� ������ ���

�� ���̵带 �����Ͽ� VS Code���� ȿ�������� �������� Ȱ���ϼ���!
