#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"

void app_main(void){
    int32_t raw_value;

    // Configurando entrada analogica y hay que investigar en que consiste la atenuación (ADC)
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_0);

    while(1){
        // Leyendo el valor puro de la entrada analogica (ADC)
        raw_value = adc1_get_raw(ADC1_CHANNEL_6);

        printf("ADC raw: %" PRId32 "\n", raw_value);
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}
