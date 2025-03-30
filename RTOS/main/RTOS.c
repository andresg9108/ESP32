#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t taskHandle1 = NULL;
TaskHandle_t taskHandle2 = NULL;

void task1(void *args){
    int count = 0;
    while(1){
        count++;
        printf("Task #1; count: %d\n", count);
        if(count == 3 && taskHandle2 != NULL){
            vTaskSuspend(taskHandle2);
            printf("Task #2 suspend\n");
        }
        if(count == 10 && taskHandle2 != NULL){
            vTaskResume(taskHandle2);
            printf("Task #2 resume\n");
        }
        if(count == 12 && taskHandle2 != NULL){
            vTaskDelete(taskHandle2);
            printf("Task #2 delete\n");
        }
        if(count >= 15){
            printf("Task #1 Ok\n");
            vTaskDelete(NULL);
        }
    }
}

void task2(void *args){
    int count = 0;
    while(1){
        count++;
        printf("Task #2; count: %d\n", count);

        if(count >= 15){
            vTaskDelete(NULL);
        }
    }
}

void app_main(void){
    // Parametros: 
    //      función, 
    //      nombre de la tarea, 
    //      espacio reservado en memoria,
    //      datos iniciales de la tarea,
    //      prioridad de la tarea,
    //      Almacenar la tarea para manipularla,
    //      # de Core
    
    xTaskCreate(task1, "task1", 4096, NULL, 10, &taskHandle1); // Core 0 por defecto
    xTaskCreatePinnedToCore(task2, "task2", 4096, NULL, 10, &taskHandle2, 1);
}
