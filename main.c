 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
� [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include "ssd1306.h"

/*
    Main application
*/

 

#define PWM_MAX 7920
#define PWM_MIN 1520

// Variables globales para los �ngulos
float theta0 = 90.0;
float theta1 = 90.0;
float theta2 = 90.0;
float theta3 = 0.0;

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
    while (abs(theta0 - theta0_desired) > 0.1) {
        if (theta0 < theta0_desired) theta0 += 1.0;
        else if (theta0 > theta0_desired) theta0 -= 1.0;
        setServoAngle(0, theta0);
        printf("%.1f,%.1f,%.1f\n", theta0, theta1, theta2);
        __delay_ms(20);
    }
}

void set1(float theta1_desired) {
    if (theta1_desired < 0.0) {
    theta1_desired = 0.0;
    } else if (theta1_desired > 180.0) {
        theta1_desired = 180.0;
    }
    while (abs(theta1 - theta1_desired) > 0.1) {
        if (theta1 < theta1_desired) theta1 += 1.0;
        else if (theta1 > theta1_desired) theta1 -= 1.0;
        setServoAngle(1, theta1);
        printf("%.1f,%.1f,%.1f\n", theta0, theta1, theta2);
        __delay_ms(20);
    }
}

void set2(float theta2_desired) {
    if (theta2_desired < 0.0) {
    theta2_desired = 0.0;
    } else if (theta2_desired > 180.0) {
        theta2_desired = 180.0;
    }
    while (abs(theta2 - theta2_desired) > 0.1) {
        if (theta2 < theta2_desired) theta2 += 1.0;
        else if (theta2 > theta2_desired) theta2 -= 1.0;
        setServoAngle(2, theta2);
        printf("%.1f,%.1f,%.1f\n", theta0, theta1, theta2);
        __delay_ms(20);
    }
}

void set3(float theta3_desired) {
    if (theta3_desired < 0.0) {
    theta3_desired = 0.0;
    } else if (theta3_desired > 90.0) {
        theta3_desired = 90.0;
    }
    while (abs(theta3 - theta3_desired) > 0.1) {
        if (theta3 < theta3_desired) theta3 += 1.0;
        else if (theta3 > theta3_desired) theta3 -= 1.0;
        setServoAngle(3, theta3);
        __delay_ms(20);
    }
}

void goto_servo(float theta0_desired, float theta1_desired, float theta2_desired) {
    set0(theta0_desired);
    set1(theta1_desired);
    set2(theta2_desired);
    __delay_ms(200); // Pausa para permitir que los movimientos se estabilicen
}

void openHand(void) {
    set3(40.0);
}

void closeHand(void) {
    set3(10.0);
}

void openGate(void) {
    setServoAngle(4, 0.0);
    __delay_ms(500); // Pausa para asegurar que el servo complete el movimiento
}

void closeGate(void) {
    setServoAngle(4, 90.0);
}

void uartrecive(void){
    char data;
    data=UART1_Read();
    if(data=='a'){
        openHand();
    }
    if(data=='b'){
        closeHand();
    }
    if(data=='c'){
        openGate();
    }
    if(data=='d'){
        closeGate();
    }
    if(data=='e'){
        goto_servo(90.0,90.0,90.0);
    }
    if(data=='f'){
        goto_servo(117.0,130.0,39.0);
    }
    if(data=='g'){
        goto_servo(117.0,130.0,50.0);
    }
    if(data=='h'){
        goto_servo(73.0,90.0,130.0);
    }
    if(data=='i'){
        goto_servo(73.0,135.0,130.0);
    }
}
void main(void)
{
    SYSTEM_Initialize();
    
    PWM1_16BIT_Initialize();
    PWM2_16BIT_Initialize();
    PWM3_16BIT_Initialize();
    //ADCC_Initialize();
    UART1_Initialize();
    
    char theta0_str[5], theta1_str[5], theta2_str[5];

    while(1)
    {
        //int valor=ADCC_GetSingleConversion(POT);
        //int angulo=(float)valor*180.0/4095.0;
        //controlServoMotor(angulo);
        goto_servo(90.0,90.0,90.0);
        openHand();
        
        openGate();
        closeGate();        
             
        goto_servo(117.0,120.0,30.0); 
        goto_servo(117.0,130.0,30.0);
        goto_servo(117.0,131.0,37.0);
        goto_servo(117.0,132.0,37.0);
        closeHand();        
        
        goto_servo(117.0,130.0,39.0);
        goto_servo(117.0,130.0,50.0);
        goto_servo(73.0,90.0,130.0);
        goto_servo(73.0,135.0,130.0);
        openHand();
        
        sprintf(theta0_str, "%.1f", theta0);
        sprintf(theta1_str, "%.1f", theta1);
        sprintf(theta2_str, "%.1f", theta2);
        
        CLK_Toggle();
        DIO_Toggle();
        
        
    }
}
