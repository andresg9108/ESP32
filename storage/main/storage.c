#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "nvs_flash.h"
#include "nvs.h"

void app_main(void){
    printf("Start");

    // Inicializar el NVS
    esp_err_t err = nvs_flash_init();
    printf("NVS init\n");
    printf((err != ESP_OK) ? "Failed\n" : "Done\n");

    // Accediendo a una partición de NVS
    nvs_handle_t my_storage;
    err = nvs_open("Storage1", NVS_READWRITE, &my_storage);
    printf("NVS open\n");
    printf((err != ESP_OK) ? "Failed\n" : "Done\n");

    // Escribir en NVS
    err = nvs_set_i32(my_storage, "ag_test_1", 10);
    printf("NVS set\n");
    printf((err != ESP_OK) ? "Failed\n" : "Done\n");

    // Guardar en NVS
    err = nvs_commit(my_storage);
    printf("NVS commit\n");
    printf((err != ESP_OK) ? "Failed\n" : "Done\n");

    // Leer NVS
    int32_t my_num_test_1;
    err = nvs_get_i32(my_storage, "ag_test_1", &my_num_test_1);
    printf("NVS get\n");
    printf((err != ESP_OK) ? "Failed\n" : "Done\n");

    printf("El valor recuperado es: %" PRId32 "\n", my_num_test_1);

    // Cerrando la conexión
    nvs_close(my_storage);

    printf("End\n");
}
