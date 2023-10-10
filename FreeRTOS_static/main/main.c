#include <stdio.h>
#include <esp_system.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "led.h"

#define APP_TASK_PRIO   3
#define APP_STK_SIZE    5*1024
#define LED0_TASK_PRIO  4
#define LED0_STK_SIZE   4*1024

//任务句柄
static TaskHandle_t AppTaskCreate_Handle;
static TaskHandle_t LED0_Task_Handle;

//任务堆栈
static StackType_t Idle_Task_Stack[configMINIMAL_STACK_SIZE];
static StackType_t Timer_Task_Stack[configTIMER_TASK_STACK_DEPTH];
static StackType_t AppTaskCreate_Stack[APP_STK_SIZE];
static StackType_t LED0_Task_Stack[128];

//任务控制块
static StaticTask_t Idle_Task_TCB;
static StaticTask_t Timer_Task_TCB;
static StaticTask_t AppTaskCreate_TCB;
static StaticTask_t LED0_Task_TCB;

//开始任务
void AppTaskCreate(void *pvParameters)
{
    //创建任务1
    LED0_Task_Handle = xTaskCreateStatic((TaskFunction_t )Led_Task_Run,
                                         (const char*    )"led0_task",
                                         (uint32_t       )LED0_STK_SIZE,
                                         (void*          )NULL,
                                         (UBaseType_t    )LED0_TASK_PRIO,
                                         (StackType_t*   ) LED0_Task_Stack,
                                         (StaticTask_t*  ) &LED0_Task_TCB);
    if (LED0_Task_Handle != NULL)
        vTaskDelete(AppTaskCreate_Handle);
}

void app_main()
{
    printf("Hello world!\n");
    led_init();
    //创建任务1
    LED0_Task_Handle = xTaskCreateStatic((TaskFunction_t )Led_Task_Run,
                                         (const char*    )"led0_task",
                                         (uint32_t       )LED0_STK_SIZE,
                                         (void*          )NULL,
                                         (UBaseType_t    )LED0_TASK_PRIO,
                                         (StackType_t*   ) LED0_Task_Stack,
                                         (StaticTask_t*  ) &LED0_Task_TCB);
    //创建开始任务
//    AppTaskCreate_Handle = xTaskCreateStatic((TaskFunction_t ) AppTaskCreate,
//                                             (const char*    ) "AppTaskCreate",
//                                             (uint32_t       ) APP_STK_SIZE,
//                                             (void*          ) NULL,
//                                             (UBaseType_t    ) APP_TASK_PRIO,
//                                             (StackType_t*   ) AppTaskCreate_Stack,
//                                             (StaticTask_t*  ) &AppTaskCreate_TCB);

    //开始任务调度
//    vTaskStartScheduler();
    printf("ERROR!!!\r\n");
    esp_restart();
}

//空闲任务所需内存
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize )
{
    *ppxIdleTaskTCBBuffer=&Idle_Task_TCB;
    *ppxIdleTaskStackBuffer=Idle_Task_Stack;
    *pulIdleTaskStackSize=configMINIMAL_STACK_SIZE;
}

//定时器任务所需内存
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
                                    StackType_t **ppxTimerTaskStackBuffer,
                                    uint32_t *pulTimerTaskStackSize )
{
    *ppxTimerTaskTCBBuffer=&Timer_Task_TCB;
    *ppxTimerTaskStackBuffer=Timer_Task_Stack;
    *pulTimerTaskStackSize=configTIMER_TASK_STACK_DEPTH;
}