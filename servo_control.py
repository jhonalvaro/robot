import time
from machine import Pin, PWM

# Constants
PWM_MAX = 7920
PWM_MIN = 1520

# Global variables for angles
theta0 = 90.0
theta1 = 90.0
theta2 = 90.0
theta3 = 0.0

modo_funcionamiento = 'a'

# Initialize PWM
pwm0 = PWM(Pin(0))
pwm1 = PWM(Pin(1))
pwm2 = PWM(Pin(2))
pwm3 = PWM(Pin(3))
pwm4 = PWM(Pin(4))
pwm5 = PWM(Pin(5))

# Function to stop movement
detener = False

def detenerMovimiento():
    global detener
    detener = True

def setServoAngle(servo, angle):
    pwm_value = int((angle / 180.0) * (PWM_MAX - PWM_MIN) + PWM_MIN)
    if servo == 0:
        pwm0.duty_u16(pwm_value)
    elif servo == 1:
        pwm1.duty_u16(pwm_value)
    elif servo == 2:
        pwm2.duty_u16(pwm_value)
    elif servo == 3:
        pwm3.duty_u16(pwm_value)
    elif servo == 4:
        pwm4.duty_u16(pwm_value)
    elif servo == 5:
        pwm5.duty_u16(pwm_value)

def set0(theta0_desired):
    global theta0, detener
    if theta0_desired < 0.0:
        theta0_desired = 0.0
    elif theta0_desired > 180.0:
        theta0_desired = 180.0
    while abs(theta0 - theta0_desired) > 0.1 and not detener:
        if theta0 < theta0_desired:
            theta0 += 1.0
        elif theta0 > theta0_desired:
            theta0 -= 1.0
        setServoAngle(0, theta0)
        print(f"{modo_funcionamiento}:{theta0:.1f},{theta1:.1f},{theta2:.1f}")
        time.sleep(0.02)
    detener = False

def set1(theta1_desired):
    global theta1, detener
    if theta1_desired < 0.0:
        theta1_desired = 0.0
    elif theta1_desired > 180.0:
        theta1_desired = 180.0
    while abs(theta1 - theta1_desired) > 0.1 and not detener:
        if theta1 < theta1_desired:
            theta1 += 1.0
        elif theta1 > theta1_desired:
            theta1 -= 1.0
        setServoAngle(1, theta1)
        print(f"{modo_funcionamiento}:{theta0:.1f},{theta1:.1f},{theta2:.1f}")
        time.sleep(0.02)
    detener = False

def set2(theta2_desired):
    global theta2, detener
    if theta2_desired < 0.0:
        theta2_desired = 0.0
    elif theta2_desired > 180.0:
        theta2_desired = 180.0
    while abs(theta2 - theta2_desired) > 0.1 and not detener:
        if theta2 < theta2_desired:
            theta2 += 1.0
        elif theta2 > theta2_desired:
            theta2 -= 1.0
        setServoAngle(2, theta2)
        print(f"{modo_funcionamiento}:{theta0:.1f},{theta1:.1f},{theta2:.1f}")
        time.sleep(0.02)
    detener = False

def set3(theta3_desired):
    global theta3, detener
    if theta3_desired < 0.0:
        theta3_desired = 0.0
    elif theta3_desired > 90.0:
        theta3_desired = 90.0
    while abs(theta3 - theta3_desired) > 0.1 and not detener:
        if theta3 < theta3_desired:
            theta3 += 1.0
        elif theta3 > theta3_desired:
            theta3 -= 1.0
        setServoAngle(3, theta3)
        time.sleep(0.02)
    detener = False

def goto_servo(theta0_desired, theta1_desired, theta2_desired):
    set0(theta0_desired)
    set1(theta1_desired)
    set2(theta2_desired)

def openHand():
    if not detener:
        set3(40.0)

def closeHand():
    if not detener:
        set3(10.0)

def openGate():
    if not detener:
        setServoAngle(4, 0.0)
        time.sleep(0.5)

def closeGate():
    if not detener:
        setServoAngle(4, 90.0)
