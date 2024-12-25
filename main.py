import time
from machine import Pin, PWM, UART

# Constants
PWM_MAX = 7920
PWM_MIN = 1520

# Modes
MODO_MANUAL = 0
MODO_AUTOMATICO = 1
MODO_UART = 2

# Global variables for angles
theta0 = 90.0
theta1 = 90.0
theta2 = 90.0
theta3 = 0.0

modo_funcionamiento = 'a'
modoActual = MODO_AUTOMATICO

# Initialize UART
uart = UART(0, baudrate=115200)

# Initialize PWM
pwm0 = PWM(Pin(0))
pwm1 = PWM(Pin(1))
pwm2 = PWM(Pin(2))
pwm3 = PWM(Pin(3))
pwm4 = PWM(Pin(4))
pwm5 = PWM(Pin(5))

# Function prototypes
def cambiarModo():
    global modoActual
    modoActual = (modoActual + 1) % 3
    evaluarModoActual()

def ejecutarModoManual():
    print(f"{modo_funcionamiento}:{theta0:.1f},{theta1:.1f},{theta2:.1f}")

def ejecutarModoAutomatico():
    goto_servo(90.0, 90.0, 90.0)
    openHand()
    openGate()
    closeGate()
    goto_servo(117.0, 120.0, 30.0)
    goto_servo(117.0, 130.0, 30.0)
    goto_servo(117.0, 131.0, 37.0)
    goto_servo(117.0, 132.0, 37.0)
    closeHand()
    goto_servo(117.0, 130.0, 39.0)
    goto_servo(117.0, 130.0, 50.0)
    goto_servo(73.0, 90.0, 130.0)
    goto_servo(73.0, 135.0, 130.0)
    openHand()

def ejecutarModoUART():
    print(f"{modo_funcionamiento}:{theta0:.1f},{theta1:.1f},{theta2:.1f}")

def evaluarModoActual():
    global modo_funcionamiento
    if modoActual == MODO_MANUAL:
        modo_funcionamiento = 'm'
        ejecutarModoManual()
    elif modoActual == MODO_AUTOMATICO:
        modo_funcionamiento = 'a'
        ejecutarModoAutomatico()
    elif modoActual == MODO_UART:
        modo_funcionamiento = 'u'
        ejecutarModoUART()
    else:
        modoActual = MODO_MANUAL

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
    global theta0
    if theta0_desired < 0.0:
        theta0_desired = 0.0
    elif theta0_desired > 180.0:
        theta0_desired = 180.0
    while abs(theta0 - theta0_desired) > 0.1:
        if theta0 < theta0_desired:
            theta0 += 1.0
        elif theta0 > theta0_desired:
            theta0 -= 1.0
        setServoAngle(0, theta0)
        print(f"{modo_funcionamiento}:{theta0:.1f},{theta1:.1f},{theta2:.1f}")
        time.sleep(0.02)

def set1(theta1_desired):
    global theta1
    if theta1_desired < 0.0:
        theta1_desired = 0.0
    elif theta1_desired > 180.0:
        theta1_desired = 180.0
    while abs(theta1 - theta1_desired) > 0.1:
        if theta1 < theta1_desired:
            theta1 += 1.0
        elif theta1 > theta1_desired:
            theta1 -= 1.0
        setServoAngle(1, theta1)
        print(f"{modo_funcionamiento}:{theta0:.1f},{theta1:.1f},{theta2:.1f}")
        time.sleep(0.02)

def set2(theta2_desired):
    global theta2
    if theta2_desired < 0.0:
        theta2_desired = 0.0
    elif theta2_desired > 180.0:
        theta2_desired = 180.0
    while abs(theta2 - theta2_desired) > 0.1:
        if theta2 < theta2_desired:
            theta2 += 1.0
        elif theta2 > theta2_desired:
            theta2 -= 1.0
        setServoAngle(2, theta2)
        print(f"{modo_funcionamiento}:{theta0:.1f},{theta1:.1f},{theta2:.1f}")
        time.sleep(0.02)

def set3(theta3_desired):
    global theta3
    if theta3_desired < 0.0:
        theta3_desired = 0.0
    elif theta3_desired > 90.0:
        theta3_desired = 90.0
    while abs(theta3 - theta3_desired) > 0.1:
        if theta3 < theta3_desired:
            theta3 += 1.0
        elif theta3 > theta3_desired:
            theta3 -= 1.0
        setServoAngle(3, theta3)
        time.sleep(0.02)

def goto_servo(theta0_desired, theta1_desired, theta2_desired):
    set0(theta0_desired)
    set1(theta1_desired)
    set2(theta2_desired)

def openHand():
    set3(40.0)

def closeHand():
    set3(10.0)

def openGate():
    setServoAngle(4, 0.0)
    time.sleep(0.5)

def closeGate():
    setServoAngle(4, 90.0)

# Main loop
while True:
    evaluarModoActual()
    time.sleep(0.1)
