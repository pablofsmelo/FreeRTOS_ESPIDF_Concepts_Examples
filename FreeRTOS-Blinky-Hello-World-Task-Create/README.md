# _Task Create - Blinky a Led and Hello World_


In this example, two tasks with different priorities are created, the highest priority being responsible for making the ESP-32 LED blink every 100ms and the lowest priority task being responsible for writing the message “Hello World” to the serial port. Next, there is a list of the main concepts related to a task, along with the basic structure of a task within an application and the respective functions of FreeRTOS for creating tasks. In addition, this description brings other functions for creating a task and blocking a task.

## What is a Task ?

According to [1], each task task is a small program by itself. It has an entry point, it will normally run forever inside an infinite loop and not exit. Tasks are implemented as C functions. The only thing special about them is their prototype, which must return void and take a void pointer parameter. If a task ends, it is the developer's responsibility to remove it from the kernel's task list. 


```c
void MyTaskFunction( void *pvParameters ) {
  for (;;)
  {
    /*task code block*/
  }
}
```
* Within an application, several tasks can be created, each of which is executed within its own context without direct dependence on another task or a scheduler action;
* The scheduler is responsible for deciding which task should be performed within the application;
* It is also the responsibility of the scheduler to ensure that the processor context has been switched, as the task has no knowledge about the respective activities of the scheduler. To be able to carry out such an activity, each task is provided with its respective stack.

## How to create a task?
Therefore, to actually create a task, it is necessary to schedule the function for the task scheduler of the respective RTOS used. In the case of this document, we will use the xTaskCreate function.

```c
portBASE_TYPE xTaskCreate
( 
  pdTASK_CODE pvTaskCode,               /* Function that implements the task. */
  const signed portCHAR * const pcName, /* Text name for the task. */
  unsigned portSHORT usStackDepth,      /* Stack size in words, not bytes. */
  void *pvParameters,                   /* Parameter passed into the task. */
  unsigned portBASE_TYPE uxPriority,    /* Priority at which the task is created. */
  xTaskHandle *pxCreatedTask            /* Used to pass out the created task's handle. */
);
```
For more details related to each of the parameters, [click here](https://www.freertos.org/a00125.html)

Even though it is not applied in this example, it is worth noting that for the ESP-32 Dual Core, we have the xTaskCreatePinnedToCore function that allows selecting which CPU the respective task will be executed on. Below, there is a list of the respective parameters with their descriptions.

```c
BaseType_t xTaskCreatePinnedToCore
(
  TaskFunction_t pxTaskCode, 
  const char *const pcName, 
  const configSTACK_DEPTH_TYPE usStackDepth, 
  void *const pvParameters, 
  UBaseType_t uxPriority, 
  TaskHandle_t *const pvCreatedTask, 
  const BaseType_t xCoreID
)
```
For more details related to each of the parameters, [click here](https://www.google.com/url?q=https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos.html&sa=D&source=docs&ust=1674153988661893&usg=AOvVaw1IWeZmHwC6ieyAOhsJNMO6)


##  Using delay to pause a task
To pause the task in this example, the vTaskDelay function was used. This function is responsible for pausing the execution of the task for a certain time. The actual time the task remains blocked depends on the tick rate. The constant “portTICK_PERIOD_MS” can be used to calculate real time. The following is the function prototype of vTaskDelay:

```c
void vTaskDelay( const TickType_t xTicksToDelay )
```

vTaskDelay() specifies a time at which the task wishes to unblock relative to the time at which vTaskDelay() is called. For example, specifying a block period of 100 ticks will cause the task to unblock 100 ticks after vTaskDelay() is called. vTaskDelay() does not therefore provide a good method of controlling the frequency of a periodic task as the path taken through the code, as well as other task and interrupt activity, will effect the frequency at which vTaskDelay() gets called and therefore the time at which the task next executes.

## References


[1] - https://freertos.org/Documentation/161204_Mastering_the_FreeRTOS_Real_Time_Kernel-A_Hands-On_Tutorial_Guide.pdf

[2] - https://www.freertos.org/RTOS-task-states.html

[3] - https://www.freertos.org/a00125.html

[4] - https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos.htm[5] - https://www.freertos.org/a00127.html
