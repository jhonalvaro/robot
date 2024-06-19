/* 
 * File:   ServoControl.h
 * Author: jhon-
 *
 * Created on June 16, 2024, 1:36 PM
 */

#ifndef SERVOCONTROL_H
#define	SERVOCONTROL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>

// Definiciones de los límites de PWM para el servo
#define PWM_MIN 0
#define PWM_MAX 65535

// Prototipos de funciones para el control de servomotores
void detenerMovimiento(void);
void controlServoMotor(int angulo);
void setServoAngle(unsigned char servo, float angulo);
void set0(float theta0_desired);
void set1(float theta1_desired);
void set2(float theta2_desired);
void set3(float theta3_desired);
void goto_servo(float theta0_desired, float theta1_desired, float theta2_desired);
void openHand(void);
void closeHand(void);
void openGate(void);
void closeGate(void);

#ifdef	__cplusplus
}
#endif

#endif	/* SERVOCONTROL_H */