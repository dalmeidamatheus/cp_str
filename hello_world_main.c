#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

SemaphoreHandle_t xSemaphore1;
SemaphoreHandle_t xSemaphore2;
SemaphoreHandle_t xSemaphore3;

void Task1(void *pvParameters)
{
    while (1) 
    {
        if (xSemaphoreTake(xSemaphore1, portMAX_DELAY) == pdTRUE) 
        {
            printf("[Tarefa 1] Executou - Matheus\n");
            vTaskDelay(pdMS_TO_TICKS(1000));
            xSemaphoreGive(xSemaphore2);
        }
    }
}

void Task2(void *pvParameters)
{
    while (1) 
    {
        if (xSemaphoreTake(xSemaphore2, portMAX_DELAY) == pdTRUE) 
        {
            printf("[Tarefa 2] Executou - Matheus\n");
            vTaskDelay(pdMS_TO_TICKS(1000));
            xSemaphoreGive(xSemaphore3);
        }
    }
}

void Task3(void *pvParameters)
{
    while (1) 
    {
        if (xSemaphoreTake(xSemaphore3, portMAX_DELAY) == pdTRUE) 
        {
            printf("[Tarefa 3] Executou - Matheus\n");
            vTaskDelay(pdMS_TO_TICKS(1000));
            xSemaphoreGive(xSemaphore1);
        }
    }
}

void app_main(void)
{
    xSemaphore1 = xSemaphoreCreateBinary();
    xSemaphore2 = xSemaphoreCreateBinary();
    xSemaphore3 = xSemaphoreCreateBinary();

    if (xSemaphore1 == NULL || xSemaphore2 == NULL || xSemaphore3 == NULL) 
    {
        printf("Erro ao criar semáforos\n");
        return;
    }

    xSemaphoreGive(xSemaphore1);

    xTaskCreate(Task1, "Task1", 2048, NULL, 5, NULL);
    xTaskCreate(Task2, "Task2", 2048, NULL, 5, NULL);
    xTaskCreate(Task3, "Task3", 2048, NULL, 5, NULL);
}
