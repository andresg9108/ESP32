#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// Macros
#define LED 4
#define BLINK_TIME 500

void app_main(void){
    int led_state = 0;

    // Definiendo salidas
    gpio_reset_pin(LED);
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);

    while (1){
        // Establecer nivel lógico 0 ó 1
        gpio_set_level(LED, led_state);

        led_state = !led_state;

        // Los TICK les permiten al sistema operativo contar cuántas iteraciones lleva
        // Nos permite calcular usando periodo en milisegundos (MS)
        vTaskDelay(BLINK_TIME / portTICK_PERIOD_MS);
    }
}