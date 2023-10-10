//
// Created by 36348 on 2023/10/9.
//
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "led.h"

void led_init(){
    gpio_config_t io_conf;
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO15/16
    io_conf.pin_bit_mask = 1ULL << GPIO_OUTPUT_IO_2;
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);
}


void Led_Task_Run(){
    while (1)
    {
        gpio_set_level(GPIO_OUTPUT_IO_2, 0);
        vTaskDelay(100);
        gpio_set_level(GPIO_OUTPUT_IO_2, 1);
        vTaskDelay(100);
    }
}
