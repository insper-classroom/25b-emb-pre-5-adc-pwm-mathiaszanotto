#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <queue.h>

#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/pwm.h"

const int PWM_R_PIN = 4;
const int PWM_G_PIN = 6;

void led_task(void *p) {
    gpio_set_function(PWM_R_PIN, GPIO_FUNC_PWM);
    uint slice_r = pwm_gpio_to_slice_num(PWM_R_PIN);
    uint chan_r  = pwm_gpio_to_channel(PWM_R_PIN);
    pwm_set_clkdiv(slice_r, 125);
    pwm_set_wrap(slice_r, 100);
    pwm_set_chan_level(slice_r, chan_r, 80);
    pwm_set_enabled(slice_r, true);

    gpio_set_function(PWM_G_PIN, GPIO_FUNC_PWM);
    uint slice_g = pwm_gpio_to_slice_num(PWM_G_PIN);
    uint chan_g  = pwm_gpio_to_channel(PWM_G_PIN);
    pwm_set_clkdiv(slice_g, 125);
    pwm_set_wrap(slice_g, 100);
    pwm_set_chan_level(slice_g, chan_g, 20);
    pwm_set_enabled(slice_g, true);

    while (true) {
    }
}

int main() {
    stdio_init_all();
    printf("Start RTOS \n");

    xTaskCreate(led_task, "LED_Task 1", 256, NULL, 1, NULL);

    vTaskStartScheduler();

    while (true)
        ;
}
