#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define STACK_DEPTH_512 512
#define STACK_DEPTH_2048 2048

#define LED_PIN 2

#define TIME_1_SEC 1000
#define TIME_100_MSEC 100

#define LOW 0
#define HIGH 1

void taskBlinkLed (void *pvParams);
void taskHelloWorld(void *pvParameter);

void app_main(void)
{   
    xTaskCreate(taskHelloWorld, "hello_task", STACK_DEPTH_2048, NULL, 3, NULL);
    xTaskCreate(taskBlinkLed, "taskBlinkLed", STACK_DEPTH_512, NULL, 5, NULL);
}

void taskBlinkLed (void *pvParams)
{
    gpio_pad_select_gpio(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    for (;;)
    {
        gpio_set_level(LED_PIN, LOW);
        vTaskDelay(TIME_1_SEC/portTICK_RATE_MS);  
        gpio_set_level(LED_PIN, HIGH);
        vTaskDelay(TIME_1_SEC/portTICK_RATE_MS);
    }
}

void taskHelloWorld(void *pvParameter)
{
	for(;;)
	{
	    printf("Hello world!\n");
	    vTaskDelay(TIME_100_MSEC / portTICK_RATE_MS);
	}
}