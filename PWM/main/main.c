/* pwm example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "esp_log.h"
#include "esp_system.h"
#include "esp_err.h"

#include "esp8266/gpio_register.h"
#include "esp8266/pin_mux_register.h"

#include "driver/pwm.h"

#define PWM_0_OUT_IO_NUM  4

// PWM period 1000us(1Khz), same as depth
#define PWM_PERIOD    (1000)

static const char *TAG = "pwm_example";

// pwm pin number
const uint32_t pin_num[1] = {PWM_0_OUT_IO_NUM,};

// duties table, real_duty = duties[x]/PERIOD
uint32_t duties[1] = {500,};

// phase table, delay = (phase[x]/360)*PERIOD
float phase[1] = {0,};

static int set_duty = 10;
static int dir = 1;
os_timer_t os_timer;
void Task_pwm_blank(void)
{
    if (dir == true)
    {
        if (++set_duty >= 500)
        {
            dir = false;
        }
    }
    else
    {
        if (--set_duty <= 30)
        {
            dir = true;
        }
    }
    //其用法和之前的sdk一样，注意其 set_duty 的范围是：0到周期这个范围之前
    pwm_set_duty(0, set_duty);
    pwm_start();
}

static void Task_Pwm_test(void *pData)
{
    //呼吸效果
    os_timer_disarm(&os_timer);
    os_timer_setfn(&os_timer, (os_timer_func_t *)(Task_pwm_blank), NULL);
    os_timer_arm(&os_timer, 6, 1);
    for (;;)
    {
        /* code */
    }
}

void app_main()
{
    pwm_init(PWM_PERIOD, duties, 4, pin_num);
    pwm_set_phases(phase);
    pwm_start();
    int16_t count = 0;
    xTaskCreate(Task_Pwm_test, "Task_Pwm_test", 1024, NULL, 5, NULL);
}

