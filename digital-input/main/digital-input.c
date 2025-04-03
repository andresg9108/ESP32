#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"

// Macros 
#define INPUT 14
#define LED 4

void app_main(void){
    int led_state = 0;

    // Definiendo entradas
    gpio_set_direction(INPUT, GPIO_MODE_INPUT);

    // Definiendo salidas
    gpio_reset_pin(LED);
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);

    gpio_set_level(LED, led_state);

    while (1){
        // Obteniendo nivel lógico de la entrada 0 ó 1
        led_state = gpio_get_level(INPUT);

        // Establecer nivel lógico 0 ó 1
        gpio_set_level(LED, led_state);
    }
}