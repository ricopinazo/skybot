/*
 * config.h
 *
 *  Created on: Oct 25, 2018
 *      Author: pedro
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include "driverlib/pwm.h"

#define MOTORS_FREQUENCY        50          // Frequency (Hz) of the servomotors
//#define SERVOM_DUTYCYCLE        0.076       // Duty cycle of the servomotors

#define MAX_FORWARD_SPEED       1000
#define MAX_BACKWARD_SPEED      -1000

#define MAX_MOTORS_DUTYCYCLE        0.1f
#define NEUTRAL_MOTORS_DUTYCYCLE    0.076f
#define MIN_MOTORS_DUTYCYCLE        0.052f

#define PWM_OUT_RIGHT_MOTOR         PWM_OUT_6
#define PWM_OUT_LEFT_MOTOR          PWM_OUT_7

#endif /* CONFIG_H_ */
