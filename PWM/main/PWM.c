#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "driver/ledc.h"

#define LEDC_TIMER LEDC_TIMER_0 // Definiendo el timer
#define LEDC_MODE LEDC_HIGH_SPEED_MODE // Definiendo el modo de alta velocidad (desde el hardware)
#define LEDC_OUTPUT 32 // Definiendo el pin de salida PWM
#define LEDC_CHANNEL LEDC_CHANNEL_4 // Definiendo el canal de salida PWM
#define LEDC_DUTY_RES LEDC_TIMER_12_BIT // Definiendo la resolución del timer (12 bits)
#define LEDC_FREQUENCY 5000 // Definiendo la frecuencia de salida PWM (5kHz)
#define LEDC_DUTY 0 // Definiendo valor inicial del duty cycle (0%)
#define LEDC_HPOINT 0 // Definiendo fase inicial del PWM

void app_main(void) {
    int32_t raw_value;

    // Corrigiendo el nombre de la estructura
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_MODE,
        .timer_num = LEDC_TIMER,
        .duty_resolution = LEDC_DUTY_RES,
        .freq_hz = LEDC_FREQUENCY,
        .clk_cfg = LEDC_AUTO_CLK
    };

    ledc_channel_config_t ledc_channel = {
        .speed_mode = LEDC_MODE,
        .channel = LEDC_CHANNEL,
        .timer_sel = LEDC_TIMER,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = LEDC_OUTPUT,
        .duty = LEDC_DUTY,
        .hpoint = LEDC_HPOINT
    };

    // Configurando el timer en el procesador
    ledc_timer_config(&ledc_timer);

    // Configurando el canal
    ledc_channel_config(&ledc_channel);

    // Configurando entrada analógica y atenuación (ADC)
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_0);

    while (1) {
        // Leyendo el valor puro de la entrada analógica (ADC)
        raw_value = adc1_get_raw(ADC1_CHANNEL_6);
        // printf("ADC raw: %" PRId32 "\n", raw_value);

        // Actualizando el duty cycle del PWM con el valor leído del ADC
        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, raw_value);
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);

        // vTaskDelay(pdMS_TO_TICKS(200));
    }
}