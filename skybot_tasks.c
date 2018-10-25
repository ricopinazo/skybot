
#include <skybot_tasks.h>
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "driverlib/pwm.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "config.h"


xQueueHandle xMotorsQueue;
struct Speed
{
    int32_t right;
    int32_t left;
};


static portTASK_FUNCTION(MotorsTask, pvParameters)
{
    struct Speed speed;
    float right_duty_cycle;
    float left_duty_cycle;

    while(1)
    {
        xQueueReceive(xMotorsQueue, &speed, portMAX_DELAY);

        right_duty_cycle = MAX_MOTORS_DUTYCYCLE - (MAX_FORWARD_SPEED - speed.right) / (MAX_FORWARD_SPEED - MAX_BACKWARD_SPEED) * (MAX_MOTORS_DUTYCYCLE - MIN_MOTORS_DUTYCYCLE);
        left_duty_cycle = MAX_MOTORS_DUTYCYCLE - (MAX_FORWARD_SPEED - speed.left) / (MAX_FORWARD_SPEED - MAX_BACKWARD_SPEED) * (MAX_MOTORS_DUTYCYCLE - MIN_MOTORS_DUTYCYCLE);
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_RIGHT_MOTOR,
                         (uint32_t)((float)PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3) * right_duty_cycle));
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_LEFT_MOTOR,
                             (uint32_t)((float)PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3) * left_duty_cycle));
        PWMGenEnable(PWM1_BASE, PWM_GEN_3);
    }
}

static portTASK_FUNCTION(BrainTask, pvParameters)
{
    struct Speed speed;

    speed.right = MAX_FORWARD_SPEED;
    speed.left = MAX_BACKWARD_SPEED;
    xQueueSend(xMotorsQueue, &speed, portMAX_DELAY);

    SysCtlSleep();
}


void init_tasks()
{
    xMotorsQueue = xQueueCreate(2, sizeof(struct Speed));

    if((xTaskCreate(BrainTask, "BrainTask", 256, NULL, tskIDLE_PRIORITY + 1, NULL)) != pdTRUE)
    {
        while(1);
    }

    if((xTaskCreate(MotorsTask, "MotorsTask", 256, NULL, tskIDLE_PRIORITY + 1, NULL)) != pdTRUE)
    {
        while(1);
    }
}