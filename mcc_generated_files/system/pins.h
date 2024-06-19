/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.1.0
*/

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

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

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RB4 aliases
#define SERV0_TRIS                 TRISBbits.TRISB4
#define SERV0_LAT                  LATBbits.LATB4
#define SERV0_PORT                 PORTBbits.RB4
#define SERV0_WPU                  WPUBbits.WPUB4
#define SERV0_OD                   ODCONBbits.ODCB4
#define SERV0_ANS                  ANSELBbits.ANSELB4
#define SERV0_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define SERV0_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define SERV0_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define SERV0_GetValue()           PORTBbits.RB4
#define SERV0_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define SERV0_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define SERV0_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define SERV0_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define SERV0_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define SERV0_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define SERV0_SetAnalogMode()      do { ANSELBbits.ANSELB4 = 1; } while(0)
#define SERV0_SetDigitalMode()     do { ANSELBbits.ANSELB4 = 0; } while(0)

// get/set RB5 aliases
#define IO_RB5_TRIS                 TRISBbits.TRISB5
#define IO_RB5_LAT                  LATBbits.LATB5
#define IO_RB5_PORT                 PORTBbits.RB5
#define IO_RB5_WPU                  WPUBbits.WPUB5
#define IO_RB5_OD                   ODCONBbits.ODCB5
#define IO_RB5_ANS                  ANSELBbits.ANSELB5
#define IO_RB5_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define IO_RB5_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define IO_RB5_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define IO_RB5_GetValue()           PORTBbits.RB5
#define IO_RB5_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define IO_RB5_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define IO_RB5_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define IO_RB5_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define IO_RB5_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define IO_RB5_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define IO_RB5_SetAnalogMode()      do { ANSELBbits.ANSELB5 = 1; } while(0)
#define IO_RB5_SetDigitalMode()     do { ANSELBbits.ANSELB5 = 0; } while(0)

// get/set RB6 aliases
#define SERV1_TRIS                 TRISBbits.TRISB6
#define SERV1_LAT                  LATBbits.LATB6
#define SERV1_PORT                 PORTBbits.RB6
#define SERV1_WPU                  WPUBbits.WPUB6
#define SERV1_OD                   ODCONBbits.ODCB6
#define SERV1_ANS                  ANSELBbits.ANSELB6
#define SERV1_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define SERV1_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define SERV1_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define SERV1_GetValue()           PORTBbits.RB6
#define SERV1_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define SERV1_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define SERV1_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define SERV1_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)
#define SERV1_SetPushPull()        do { ODCONBbits.ODCB6 = 0; } while(0)
#define SERV1_SetOpenDrain()       do { ODCONBbits.ODCB6 = 1; } while(0)
#define SERV1_SetAnalogMode()      do { ANSELBbits.ANSELB6 = 1; } while(0)
#define SERV1_SetDigitalMode()     do { ANSELBbits.ANSELB6 = 0; } while(0)

// get/set RB7 aliases
#define IO_RB7_TRIS                 TRISBbits.TRISB7
#define IO_RB7_LAT                  LATBbits.LATB7
#define IO_RB7_PORT                 PORTBbits.RB7
#define IO_RB7_WPU                  WPUBbits.WPUB7
#define IO_RB7_OD                   ODCONBbits.ODCB7
#define IO_RB7_ANS                  ANSELBbits.ANSELB7
#define IO_RB7_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define IO_RB7_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define IO_RB7_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define IO_RB7_GetValue()           PORTBbits.RB7
#define IO_RB7_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define IO_RB7_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define IO_RB7_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define IO_RB7_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)
#define IO_RB7_SetPushPull()        do { ODCONBbits.ODCB7 = 0; } while(0)
#define IO_RB7_SetOpenDrain()       do { ODCONBbits.ODCB7 = 1; } while(0)
#define IO_RB7_SetAnalogMode()      do { ANSELBbits.ANSELB7 = 1; } while(0)
#define IO_RB7_SetDigitalMode()     do { ANSELBbits.ANSELB7 = 0; } while(0)

// get/set RC0 aliases
#define swModo_TRIS                 TRISCbits.TRISC0
#define swModo_LAT                  LATCbits.LATC0
#define swModo_PORT                 PORTCbits.RC0
#define swModo_WPU                  WPUCbits.WPUC0
#define swModo_OD                   ODCONCbits.ODCC0
#define swModo_ANS                  ANSELCbits.ANSELC0
#define swModo_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define swModo_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define swModo_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define swModo_GetValue()           PORTCbits.RC0
#define swModo_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define swModo_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define swModo_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define swModo_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define swModo_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define swModo_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define swModo_SetAnalogMode()      do { ANSELCbits.ANSELC0 = 1; } while(0)
#define swModo_SetDigitalMode()     do { ANSELCbits.ANSELC0 = 0; } while(0)

// get/set RC1 aliases
#define LED0_TRIS                 TRISCbits.TRISC1
#define LED0_LAT                  LATCbits.LATC1
#define LED0_PORT                 PORTCbits.RC1
#define LED0_WPU                  WPUCbits.WPUC1
#define LED0_OD                   ODCONCbits.ODCC1
#define LED0_ANS                  ANSELCbits.ANSELC1
#define LED0_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define LED0_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define LED0_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define LED0_GetValue()           PORTCbits.RC1
#define LED0_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define LED0_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define LED0_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define LED0_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define LED0_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define LED0_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define LED0_SetAnalogMode()      do { ANSELCbits.ANSELC1 = 1; } while(0)
#define LED0_SetDigitalMode()     do { ANSELCbits.ANSELC1 = 0; } while(0)

// get/set RC2 aliases
#define DIO_TRIS                 TRISCbits.TRISC2
#define DIO_LAT                  LATCbits.LATC2
#define DIO_PORT                 PORTCbits.RC2
#define DIO_WPU                  WPUCbits.WPUC2
#define DIO_OD                   ODCONCbits.ODCC2
#define DIO_ANS                  ANSELCbits.ANSELC2
#define DIO_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define DIO_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define DIO_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define DIO_GetValue()           PORTCbits.RC2
#define DIO_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define DIO_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define DIO_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define DIO_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define DIO_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define DIO_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define DIO_SetAnalogMode()      do { ANSELCbits.ANSELC2 = 1; } while(0)
#define DIO_SetDigitalMode()     do { ANSELCbits.ANSELC2 = 0; } while(0)

// get/set RC4 aliases
#define SERV3_TRIS                 TRISCbits.TRISC4
#define SERV3_LAT                  LATCbits.LATC4
#define SERV3_PORT                 PORTCbits.RC4
#define SERV3_WPU                  WPUCbits.WPUC4
#define SERV3_OD                   ODCONCbits.ODCC4
#define SERV3_ANS                  ANSELCbits.ANSELC4
#define SERV3_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define SERV3_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define SERV3_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define SERV3_GetValue()           PORTCbits.RC4
#define SERV3_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define SERV3_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define SERV3_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define SERV3_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define SERV3_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define SERV3_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define SERV3_SetAnalogMode()      do { ANSELCbits.ANSELC4 = 1; } while(0)
#define SERV3_SetDigitalMode()     do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set RC5 aliases
#define SERV2_TRIS                 TRISCbits.TRISC5
#define SERV2_LAT                  LATCbits.LATC5
#define SERV2_PORT                 PORTCbits.RC5
#define SERV2_WPU                  WPUCbits.WPUC5
#define SERV2_OD                   ODCONCbits.ODCC5
#define SERV2_ANS                  ANSELCbits.ANSELC5
#define SERV2_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define SERV2_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define SERV2_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define SERV2_GetValue()           PORTCbits.RC5
#define SERV2_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define SERV2_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define SERV2_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define SERV2_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define SERV2_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define SERV2_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define SERV2_SetAnalogMode()      do { ANSELCbits.ANSELC5 = 1; } while(0)
#define SERV2_SetDigitalMode()     do { ANSELCbits.ANSELC5 = 0; } while(0)

// get/set RC6 aliases
#define SERV4_TRIS                 TRISCbits.TRISC6
#define SERV4_LAT                  LATCbits.LATC6
#define SERV4_PORT                 PORTCbits.RC6
#define SERV4_WPU                  WPUCbits.WPUC6
#define SERV4_OD                   ODCONCbits.ODCC6
#define SERV4_ANS                  ANSELCbits.ANSELC6
#define SERV4_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define SERV4_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define SERV4_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define SERV4_GetValue()           PORTCbits.RC6
#define SERV4_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define SERV4_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define SERV4_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define SERV4_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define SERV4_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define SERV4_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define SERV4_SetAnalogMode()      do { ANSELCbits.ANSELC6 = 1; } while(0)
#define SERV4_SetDigitalMode()     do { ANSELCbits.ANSELC6 = 0; } while(0)

// get/set RC7 aliases
#define SERV5_TRIS                 TRISCbits.TRISC7
#define SERV5_LAT                  LATCbits.LATC7
#define SERV5_PORT                 PORTCbits.RC7
#define SERV5_WPU                  WPUCbits.WPUC7
#define SERV5_OD                   ODCONCbits.ODCC7
#define SERV5_ANS                  ANSELCbits.ANSELC7
#define SERV5_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define SERV5_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define SERV5_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define SERV5_GetValue()           PORTCbits.RC7
#define SERV5_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define SERV5_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define SERV5_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define SERV5_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define SERV5_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define SERV5_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define SERV5_SetAnalogMode()      do { ANSELCbits.ANSELC7 = 1; } while(0)
#define SERV5_SetDigitalMode()     do { ANSELCbits.ANSELC7 = 0; } while(0)

/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);


#endif // PINS_H
/**
 End of File
*/