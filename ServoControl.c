
#include "ServoControl.h"
#include <xc.h>
#include "mcc_generated_files/system/system.h"
#include <stdlib.h>


extern char modo_funcionamiento;

extern float theta0;
extern float theta1;
extern float theta2;
extern float theta3;

volatile bool detener = false;

void detenerMovimiento() {
    detener = true;
}

void controlServoMotor(int angulo) {
    uint16_t valorPWM;

    // Aseg�rate de que el �ngulo est� dentro del rango permitido (0-180 grados)
    if(angulo < 0) {
        angulo = 0;
    } else if(angulo > 180) {
        angulo = 180;
    }

    // Convierte el �ngulo a un valor de PWM. 
    // Esto depender� de tu servo y tu m�dulo PWM espec�ficos.
    // Aqu�, asumimos un servo de 180 grados y un m�dulo PWM de 16 bits.
    valorPWM = (uint16_t)(((float)angulo / 180.0 * (PWM_MAX - PWM_MIN)) + PWM_MIN);

    // Configura el registro de ciclo de trabajo del PWM con el valor calculado
    PWM1_16BIT_SetSlice1Output1DutyCycleRegister(valorPWM);

    // Carga los registros del buffer
    PWM1_16BIT_LoadBufferRegisters();
}

void setServoAngle(unsigned char servo, float angulo) {
    unsigned int pwmValue = (uint16_t)(((float)angulo / 180.0 * (PWM_MAX - PWM_MIN)) + PWM_MIN); // Conversi�n de �ngulo a valor PWM
    switch (servo) {
        case 0:
            // Configura el registro de ciclo de trabajo del PWM con el valor calculado
            PWM1_16BIT_SetSlice1Output1DutyCycleRegister(pwmValue);
            // Carga los registros del buffer
            PWM1_16BIT_LoadBufferRegisters();
            break;
        case 1:
            // Configura el registro de ciclo de trabajo del PWM con el valor calculado
            PWM1_16BIT_SetSlice1Output2DutyCycleRegister(pwmValue);
            // Carga los registros del buffer
            PWM1_16BIT_LoadBufferRegisters();
            break;
        case 2:
            // Configura el registro de ciclo de trabajo del PWM con el valor calculado
            PWM2_16BIT_SetSlice1Output1DutyCycleRegister(pwmValue);
            // Carga los registros del buffer
            PWM2_16BIT_LoadBufferRegisters();
            break;
        case 3:
            // Configura el registro de ciclo de trabajo del PWM con el valor calculado
            PWM2_16BIT_SetSlice1Output2DutyCycleRegister(pwmValue);
            // Carga los registros del buffer
            PWM2_16BIT_LoadBufferRegisters();
            break;
        case 4:
            // Configura el registro de ciclo de trabajo del PWM con el valor calculado
            PWM3_16BIT_SetSlice1Output1DutyCycleRegister(pwmValue);
            // Carga los registros del buffer
            PWM3_16BIT_LoadBufferRegisters();
            break;
        case 5:
            // Configura el registro de ciclo de trabajo del PWM con el valor calculado
            PWM3_16BIT_SetSlice1Output2DutyCycleRegister(pwmValue);
            // Carga los registros del buffer
            PWM3_16BIT_LoadBufferRegisters();
            break;
    }
}

void set0(float theta0_desired) {
    if (theta0_desired < 0.0) {
    theta0_desired = 0.0;
    } else if (theta0_desired > 180.0) {
        theta0_desired = 180.0;
    }
    while (abs(theta0 - theta0_desired) > 0.1 && !detener) {
        if (theta0 < theta0_desired) theta0 += 1.0;
        else if (theta0 > theta0_desired) theta0 -= 1.0;
        setServoAngle(0, theta0);
        printf("%c:%.1f,%.1f,%.1f\n", modo_funcionamiento, theta0, theta1, theta2); 
        
        //tm1637output(theta0, 3, 0, 1, 0);
        //tm1637UpdateDisplay();
        
        __delay_ms(20);
    }
    detener = false;
}


void set1(float theta1_desired) {
    if (theta1_desired < 0.0) {
    theta1_desired = 0.0;
    } else if (theta1_desired > 180.0) {
        theta1_desired = 180.0;
    }
    while (abs(theta1 - theta1_desired) > 0.1 && !detener) {
        if (theta1 < theta1_desired) theta1 += 1.0;
        else if (theta1 > theta1_desired) theta1 -= 1.0;
        setServoAngle(1, theta1);
        printf("%c:%.1f,%.1f,%.1f\n", modo_funcionamiento, theta0, theta1, theta2); 
        
        //tm1637output(theta1, 3, 0, 1, 0);
        //tm1637UpdateDisplay();
        
        __delay_ms(20);
    }
    detener = false;
    
}



void set2(float theta2_desired) {
    if (theta2_desired < 0.0) {
    theta2_desired = 0.0;
    } else if (theta2_desired > 180.0) {
        theta2_desired = 180.0;
    }
    while (abs(theta2 - theta2_desired) > 0.1 && !detener) {
        if (theta2 < theta2_desired) theta2 += 1.0;
        else if (theta2 > theta2_desired) theta2 -= 1.0;
        setServoAngle(2, theta2);
        printf("%c:%.1f,%.1f,%.1f\n", modo_funcionamiento, theta0, theta1, theta2);
               
        //tm1637output(theta2, 3, 0, 1, 0);
        //tm1637UpdateDisplay();
        
        __delay_ms(20);
    }
    detener = false;
}


void set3(float theta3_desired) {
    if (theta3_desired < 0.0) {
    theta3_desired = 0.0;
    } else if (theta3_desired > 90.0) {
        theta3_desired = 90.0;
    }
    while (abs(theta3 - theta3_desired) > 0.1 && !detener) {
        if (theta3 < theta3_desired) theta3 += 1.0;
        else if (theta3 > theta3_desired) theta3 -= 1.0;
        setServoAngle(3, theta3);
        __delay_ms(20);
    }
    detener = false;
}

void goto_servo(float theta0_desired, float theta1_desired, float theta2_desired) {
    set0(theta0_desired);
    set1(theta1_desired);
    set2(theta2_desired);
    //__delay_ms(200); // Pausa para permitir que los movimientos se estabilicen
    
}

void openHand(void) {
    if (!detener)
    {
        set3(40.0);
    }
    
}

void closeHand(void) {
    if (!detener)
    {
        set3(10.0);
    }
    
}

void openGate(void) {
    //condicion para verificar si esta en interupcion activada

    if (!detener)
    {
          setServoAngle(4, 0.0);
        __delay_ms(500); // Pausa para asegurar que el servo complete el movimiento
    }
    

    
  
}

void closeGate(void) {
    if (!detener)
    {
        setServoAngle(4, 90.0);
    }
    
}

