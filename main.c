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
#include "ServoControl.h"
//#include "TM1637PIC.h"

/*
    Main application
*/

 

#define PWM_MAX 7920
#define PWM_MIN 1520

// Definiciones de modos
#define MODO_MANUAL 0
#define MODO_AUTOMATICO 1
#define MODO_UART 2

// Variables globales para los �ngulos
float theta0 = 90.0;
float theta1 = 90.0;
float theta2 = 90.0;
float theta3 = 0.0;

char modo_funcionamiento;
int modoActual;

// Prototipos de funciones
void cambiarModo(void);
void ejecutarModoManual(void);
void ejecutarModoAutomatico(void);
void ejecutarModoUART(void);
void configurarBoton(void);
void ISR_Boton(void);
void evaluarModoActual(void);


void main(void)
{
    

    SYSTEM_Initialize();

    INT0_SetInterruptHandler(ISR_Boton);
    
    INTERRUPT_GlobalInterruptEnable();
    
    PWM1_16BIT_Initialize();
    PWM2_16BIT_Initialize();
    PWM3_16BIT_Initialize();
    //ADCC_Initialize();
    UART1_Initialize();
    
    //tm1637initialise((uint8_t*)&TRISC, (uint8_t*)&PORTC, (uint8_t*)&LATC, 2, 1, 1, 0);
    
   
    
    char theta0_str[5], theta1_str[5], theta2_str[5];
    modoActual=MODO_AUTOMATICO;
    evaluarModoActual();

    while(1)
    {
        
        
        
        
    evaluarModoActual();
        
        
    }
}

void evaluarModoActual(void) {
    // Evaluar el modo actual basado en la entrada de usuario
    // Puedes usar un botón, un sensor, un comando UART, etc.
    // Aquí, simplemente cambiamos el modo cada 5 segundos
    LED0_SetHigh();
    switch(modoActual) {
            case MODO_MANUAL:
                modo_funcionamiento='m';
                ejecutarModoManual();
                break;
            case MODO_AUTOMATICO:
                modo_funcionamiento='a';
                ejecutarModoAutomatico();
                break;
            case MODO_UART:
                modo_funcionamiento='u';
                ejecutarModoUART();
                break;
            default:
                // Modo desconocido, volver al modo manual
                modoActual = MODO_MANUAL;
                break;
        }
    LED0_SetLow();
    __delay_ms(100);
}

void cambiarModo(void) {
    modoActual = (modoActual + 1) % 3; // Cambia al siguiente modo
    evaluarModoActual();
}

void ejecutarModoManual(void) {
    printf("%c:%.1f,%.1f,%.1f\n", modo_funcionamiento, theta0, theta1, theta2); 
        
}

void ejecutarModoAutomatico(void) {
    // Código para modo automático

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
    
    /*sprintf(theta0_str, "%.1f", theta0);
    sprintf(theta1_str, "%.1f", theta1);
    sprintf(theta2_str, "%.1f", theta2);*/
}

void ejecutarModoUART(void) {
    printf("%c:%.1f,%.1f,%.1f\n", modo_funcionamiento, theta0, theta1, theta2); 
        
}

void configurarBoton(void) {
    // Configurar interrupciones y lógica para el botón swModo
    // Esta función debe asegurarse de que ISR_Boton se llame cuando se presione el botón
}

void ISR_Boton(void) {
    // Esta función se llama cuando se presiona el botón swModo
    detenerMovimiento();
    // Limpiar la bandera de interrupción del botón aquí, si es necesario
}
