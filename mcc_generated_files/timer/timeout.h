/**
 * TIMEOUTDRIVER Generated Driver API Header File
 * 
 * @file timeout.h
 * 
 * @defgroup timeoutdriver Time-out Driver
 * 
 * @brief This file contains the API prototypes and other data types for the Time-out module.
 *
 * @version Timeout Driver Version 1.1.1
 * 
 *	Note: Enable interrupts for the dependent timers for this driver to work.
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

#ifndef __TIMEOUTDRIVER_H
#define __TIMEOUTDRIVER_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/*
*   Please note that the timer tick is different from the timer period. 
*   A tick occurs each time the peripheral timer increases its count
*   The timer period is when the number of ticks reaches its specified maximum and 
*      the timer overflow interrupt occurs. 
*   This library sets the timer period internally as needed
*/

#define INLINE inline


// mSec to Ticks and Ticks to mSec conversion. These values are based on the minimum period of the TMRx peripheral
// Note that these values have been rounded to the nearest power of two to make the calculations faster at runtime
#define timeout_mSecToTicks(a)     ( ((uint32_t)(a)) * 32UL )
#define timeout_ticksToMsec(a)     ( ((uint32_t)(a)) / 32UL )

typedef  uint32_t (*timercallback_ptr_t)(void *payload);

/**
 * @ingroup timeoutdriver
 * @struct tmrStruct_t
 * @brief Defines a timer instance.
*/
typedef struct tmrStruct {
    timercallback_ptr_t  callbackPtr;   /**<Pointer to the callback handler.*/
    void* payload;                      /**<The value that can be passed on to the callback.*/
    struct tmrStruct*  next;            /**<Pointer to the next timer on the queue.*/
    uint32_t absoluteTime;              /**<The number of ticks the timer will count down.*/
} timerStruct_t;

/**
 * @ingroup timeoutdriver
 * @brief Sets the time-out Interrupt Service Routine (ISR) handler as the interrupt handler for the timer.
 * @param Timer - Timer instance whose callback have to be called
 * @returns None.
*/
void timeout_initialize(void);

/**
 * @ingroup timeoutdriver
 * @brief Queues and starts the timer. The running timer is cancelled and a new timer will start. 
 * @param Timer - Timer instance to be created and added to the list
 * @param Time-out - Number of timer ticks before this timer expires
 * @returns None.
*/
void timeout_create(timerStruct_t *timer, uint32_t timeout);

/**
 * @ingroup timeoutdriver
 * @brief Cancels and removes a running timer.
 * @param Timer - Timer instance to be removed
 * @returns None.
*/
void timeout_delete(timerStruct_t *timer);

/**
 * @ingroup timeoutdriver
 * @brief Cancels and removes all the timers in the queue.
 * @param None.
 * @returns None.
*/
void timeout_flushAll(void);

/**
 * @ingroup timeoutdriver
 * @brief Checks if there are any timers running or waiting to be called.
 * @param None.
 * @retval True - There are no more events lined up
 * @retval False - Events are running or waiting to be called
*/
bool timeout_hasPendingTimeouts(void);

/**
 * @ingroup timeoutdriver
 * @brief Checks if there are events being executed or waiting to be executed.
 * @param None.
 * @retval True - There are no more events lined up
 * @retval False - Events are running or waiting to be called
*/
bool timeout_hasPendingCallbacks(void);

/**
@ingroup timeoutdriver
@brief Checks the list of expired timers and calls the first one.
 
If the callback returned a value greater than `0`, it reschedules the timer. It is recommended this is called from the main superloop
(while(1)) in the code but, by design, it can also be called from the timer ISR as the last action in timeout_isr. 

 * @param None.
 * @returns None.
*/
extern INLINE void timeout_callNextCallback(void);

/**
 * @ingroup timeoutdriver
 * @brief Handler function called whenever the timer peripheral interrupts. It counts the time
 *        elapsed and calls the next timer in the queue. It assumesthat the callback is complete before the next timer tick.
 * @param None.
 * @returns None.
*/
void timeout_isr(void);

/**
 * @ingroup timeoutdriver
 * @brief Starts a timer with maximum time-out which can be up to the maximum range of the timer divided by two only in Stopwatch/Cycle Counter mode.
 * @param Timer - timer instance that will be used in stopwatch mode.
 * @returns None.
*/
void timeout_startTimer(timerStruct_t *timer);

/**
 * @ingroup timeoutdriver
 * @brief Stops the running timer and returns the number of ticks it counted, but only in Stopwatch/Cycle Counter mode.
 * @param Timer - Timer instance used in Stopwatch mode 
 * @returns Number of ticks counted by the timer
*/
uint32_t timeout_stopTimer(timerStruct_t *timer);

/**
 * @ingroup timeoutdriver
 * @brief Gets the number of ticks remaining before a specific timer runs out.
 * @param Timer - The specific timer 
 * @returns Number of ticks remaining before a timer runs out
*/
uint32_t timeout_getTimeRemaining(timerStruct_t *timer);

#endif // __TIMEOUTDRIVER_H
