#include <stdio.h>
#include <esp_system.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "led.h"

#define APP_TASK_PRIO       1
#define APP_STK_SIZE        5*1024

#define LED0_TASK_PRIO       3
#define LED0_STK_SIZE        4*1024

#define LED1_TASK_PRIO       4
#define LED1_STK_SIZE        4*1024

void AppTaskCreate(void *pvParameters);

TaskHandle_t AppTaskCreate_Handler;
TaskHandle_t LED0_Task_Handler;
TaskHandle_t LED1_Task_Handler;

void app_main()
{
    printf("Hello world!\r\n");
    led_init();

    //创建开始任务
    xTaskCreate((TaskFunction_t ) AppTaskCreate,
                (const char*    ) "AppTaskCreate",
                (uint16_t       ) APP_STK_SIZE,
                (void*          ) NULL,
                (UBaseType_t    ) APP_TASK_PRIO,
                (TaskHandle_t*  ) &AppTaskCreate_Handler);
    printf("ERROR!\r\n");
    //开始任务调度
//    vTaskStartScheduler();
    printf("ERROR!\r\n");
    while (1){

    }
}

uint8_t i = 0;
void Led_Task_Run(void *pvParameters){
    while (1)
    {
        i++;
        if (i == 10){
            printf("Delete Task2!!!\r\n");
            vTaskDelete(LED1_Task_Handler);
        }
        printf("Task1 Running!!!\r\n");
        gpio_set_level(GPIO_OUTPUT_IO_2, 0);
        vTaskDelay(100);
        gpio_set_level(GPIO_OUTPUT_IO_2, 1);
        vTaskDelay(100);
    }
}

void Led1_Task_Run(void *pvParameters){
    while (1)
    {
        printf("Task2 Running!!!\r\n");
        vTaskDelay(50);
    }
}

//开始任务
void AppTaskCreate(void *pvParameters)
{
    //创建任务1
    xTaskCreate((TaskFunction_t ) Led_Task_Run,
                (const char*    ) "led0_task",
                (uint16_t       ) LED0_STK_SIZE,
                (void*          ) NULL,
                (UBaseType_t    ) LED0_TASK_PRIO,
                (TaskHandle_t*  ) &LED0_Task_Handler);

    //创建任务2
    xTaskCreate((TaskFunction_t ) Led1_Task_Run,
                (const char*    ) "led1_task",
                (uint16_t       ) LED1_STK_SIZE,
                (void*          ) NULL,
                (UBaseType_t    ) LED1_TASK_PRIO,
                (TaskHandle_t*  ) &LED1_Task_Handler);

    vTaskDelete(AppTaskCreate_Handler);
}
