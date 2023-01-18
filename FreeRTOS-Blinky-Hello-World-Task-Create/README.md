# _Create tasks - Blinky a Led and Hello World_


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
