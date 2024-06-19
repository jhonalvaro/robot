/**
 * TIMEOUTDRIVER Generated Driver File
 *
 * @file timeout.c
 * 
 * @ingroup timeoutdriver
 * 
 * @brief Contains the driver code for Time-out module.
 *
 * @version Timeout Driver Version 1.1.1
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

#ifdef __XC
#include <xc.h>
#endif
#include <stdio.h>
#include "../timeout.h"
#include "../tmr0.h"


uint32_t dummyHandler(void *payload) {return 0;};
void startTimerAtHead(void);
INLINE void enqueueCallback(timerStruct_t* timer);
INLINE void setTimerDuration(uint32_t duration);
INLINE uint32_t makeAbsolute(uint32_t timeout);
INLINE uint32_t rebaseList(void);
INLINE void printList(void);

timerStruct_t *listHead = NULL;
timerStruct_t * volatile executeQueueHead = NULL;

timerStruct_t dummy;
timerStruct_t dummy_exec = {dummyHandler};
volatile uint32_t absoluteTimeofLastTimeout = 0;
volatile uint32_t lastTimerLoad = 0;
volatile bool  isRunning = false;

bool timeout_hasPendingTimeouts(void)
{
    return (listHead == NULL);
}

bool timeout_hasPendingCallbacks(void)
{
    return (executeQueueHead == NULL);
}

/**
 * @ingroup timeoutdriver
 * @brief Disables all the timers without deleting them. Timers can be restarted by calling starTimerAtHead.
 * @param None.
 * @returns None.
*/
void stopTimeouts(void)
{
    PIE3bits.TMR0IE = 0;
    absoluteTimeofLastTimeout = 0;
    lastTimerLoad = 0;
    isRunning = false;
}

/**
 * @ingroup timeoutdriver
 * @brief Sets the number of ticks the timer will run for.
 * @param Duration - Number of timer ticks
 * @returns None.
*/
inline void setTimerDuration(uint32_t duration)
{
    lastTimerLoad = 65535 - duration;

    Timer0_Write(0);

    PIR3bits.TMR0IF = 0;
    Timer0_Write(lastTimerLoad);
}

/**
 * @ingroup timeoutdriver
 * @brief Returns the total number of timer ticks since the last time-out occurred or since the module was started. 
 * @param Duration - Number of ticks of a specific timer
 * @returns Time-out - Number of timer ticks since the last time-out occurred
*/ 
inline uint32_t makeAbsolute(uint32_t timeout)
{
    timeout += absoluteTimeofLastTimeout;
    if (isRunning) {
        uint32_t timerVal = Timer0_Read();
        if (timerVal < lastTimerLoad) // Timer has wrapped while we were busy
        {
            timerVal = 65535;
        }
        timeout += timerVal - lastTimerLoad;
    }
    return timeout;
}

uint32_t timeout_getTimeRemaining(timerStruct_t *timer)
{
    return timer->absoluteTime - makeAbsolute(0);
}

/**
 * @ingroup timeoutdriver
 * @brief Adjusts the time base so that the timer can never wrap
 * @param None.
 * @returns Number of timer ticks since the last time-out occurred
*/
inline uint32_t rebaseList(void)
{
    timerStruct_t *basePoint = listHead;
    uint32_t baseTime = makeAbsolute(0);
    while(basePoint != NULL)
    {
        basePoint->absoluteTime -= baseTime;
        basePoint = basePoint->next;
    }
    absoluteTimeofLastTimeout -= baseTime;
    return baseTime;
}

/**
 * @ingroup timeoutdriver
 * @brief Prints the times for each of the timers on the queue.
 * @param None.
 * @returns None.
*/
inline void printList(void)
{
    timerStruct_t *basePoint = listHead;
    while(basePoint != NULL)
    {
        printf("%ld -> ", (uint32_t)basePoint->absoluteTime);
        basePoint = basePoint->next;
    }
    printf("NULL\n");
}

/**
 * @ingroup timeoutdriver
 * @brief Shows where the specific timer will be placed on the queue.
 * @param Timer - Instance of a timer added to the queue
 * @retval True - If inserted at the top of the queue
 * @retval False - Not inserted at the top of the queue
*/
bool sortedInsert(timerStruct_t *timer)
{    
    uint32_t timerAbsoluteTime = timer->absoluteTime;
    uint8_t  atHead = 1;    
    timerStruct_t *insertPoint = listHead;
    timerStruct_t *prevPoint = NULL;
    timer->next = NULL;

    if(timerAbsoluteTime < absoluteTimeofLastTimeout)
    {
        timerAbsoluteTime += 65535 - rebaseList() + 1;
        timer->absoluteTime = timerAbsoluteTime;
    }
    
    while(insertPoint != NULL)
    {
        if(insertPoint->absoluteTime > timerAbsoluteTime)
        {
            break; // found the spot
        }
        prevPoint = insertPoint;
        insertPoint = insertPoint->next;
        atHead = 0;
    }
    
    if(atHead == 1) // the front of the list. Checking the uint8_t saves 7 instructions
    {
        setTimerDuration(65535);
        PIR3bits.TMR0IF = 0;

        timer->next = (listHead==&dummy)?dummy.next: listHead;
        listHead = timer;
        return true;
    }
    else // middle of the list
    {
        timer->next = prevPoint->next;
    }
    
    prevPoint->next = timer;
    return false;
}

/**
 * @ingroup timeoutdriver
 * @brief Starts the timer queue from the beginning. 
 * @param None.
 * @returns None.
*/
void startTimerAtHead(void)
{
    // NOTE: listHead must NOT equal NULL at this point.

    PIE3bits.TMR0IE = 0;

    if(listHead==NULL) // no timeouts left
    {
        stopTimeouts();
        return;
    }

    uint32_t period = listHead->absoluteTime - absoluteTimeofLastTimeout;

    // Timer is too far, insert dummy and schedule timer after the dummy
    if (period > 65535)
    {
        dummy.absoluteTime = absoluteTimeofLastTimeout + 65535;
        dummy.next = listHead;
        listHead = &dummy;
        period = 65535;
    }

    setTimerDuration(period);

    PIE3bits.TMR0IE = 1;
    isRunning = true;
}

void timeout_flushAll(void)
{
    stopTimeouts();

    while (listHead != NULL)
        timeout_delete(listHead);

    while (executeQueueHead != NULL)
        timeout_delete(executeQueueHead);

}

/**
 * @ingroup timeoutdriver
 * @brief Looks for a specific timer instance and removes it from the queue. 
 * @param List - Pointer to the timer instance at the top of the queue
 * @param Timer - Timer instance to be removed 
 * @retval True - If the timer is found and successfully removed from the list
 * @retval False - The operation was not successful 
*/
bool timeout_deleteHelper(timerStruct_t * volatile *list, timerStruct_t *timer)
{
    bool retVal = false; 
    if (*list == NULL)
        return retVal;

    // Guard in case we get interrupted, we cannot safely compare/search and get interrupted
    PIE3bits.TMR0IE = 0;

    // Special case, the head is the one we are deleting
    if (timer == *list)
    {
        *list = (*list)->next;       // Delete the head
        retVal = true;
        startTimerAtHead();        // Start the new timer at the head
    } else 
    {   // More than one timer in the list, search the list.  
        timerStruct_t *findTimer = *list;
        timerStruct_t *prevTimer = NULL;
        while(findTimer != NULL)
        {
            if(findTimer == timer)
            {
                prevTimer->next = findTimer->next;
                retVal = true;
                break;
            }
            prevTimer = findTimer;
            findTimer = findTimer->next;
        } 
        PIE3bits.TMR0IE = 1;
    }

    return retVal;
}

void timeout_delete(timerStruct_t *timer)
{
    if (!timeout_deleteHelper(&listHead, timer))
    {
        timeout_deleteHelper(&executeQueueHead, timer);
    }

    timer->next = NULL;
}

/**
 * @ingroup timeoutdriver
 * @brief Queues the timers that need their callback called with callNextCallback.
 * @param Timer - Timer instance whose callback have to be called
 * @returns None.
*/
inline void enqueueCallback(timerStruct_t* timer)
{
    timerStruct_t  *tmp;
    if( timer == &dummy )
    {
        // keeping a separate copy for dummy in execution queue to avoid the modification of next from the timer list. 
        timer = &dummy_exec;
    }
    timer->next = NULL;
    
    // Special case for empty list
    if (executeQueueHead == NULL)
    {
        executeQueueHead = timer;
        return;
    }    
    
    // Find the end of the list and insert the next expired timer at the back of the queue
    tmp = executeQueueHead;
    while(tmp->next != NULL)
        tmp = tmp->next;
    
    tmp->next = timer;
}

extern inline void timeout_callNextCallback(void)
{
    if (executeQueueHead == NULL)
        return;

    bool tempIE = (PIE3bits.TMR0IE == 1?1:0);
    PIE3bits.TMR0IE = 0;

    timerStruct_t *callBackTimer = executeQueueHead;
    
    // Done, remove from list
    executeQueueHead = executeQueueHead->next;
    // Mark the timer as not in use
    callBackTimer->next = NULL;

    if(tempIE)
    {
        PIE3bits.TMR0IE = 1;
    }
    
    uint32_t reschedule = callBackTimer->callbackPtr(callBackTimer->payload);

    // Do we have to reschedule it? If yes then add delta to absolute for reschedule
    if(reschedule)
    {
        timeout_create(callBackTimer, reschedule);
    } 
}

void timeout_initialize(void)
{
    Timer0_Stop();
    Timer0_Write(0);
    Timer0_OverflowCallbackRegister(timeout_isr);
    Timer0_Start();
}

void timeout_create(timerStruct_t *timer, uint32_t timeout)
{
    // If this timer is already active, replace it
    timeout_delete(timer);

    PIE3bits.TMR0IE = 0;

    timer->absoluteTime = makeAbsolute(timeout);
    
    // We only have to start the timer at head if the insert was at the head
    if(sortedInsert(timer))
    {
        startTimerAtHead();
    } else {
        if (isRunning)
            PIE3bits.TMR0IE = 1;
    }
}

void timeout_isr(void)
{
    timerStruct_t *next = listHead->next;
    absoluteTimeofLastTimeout = listHead->absoluteTime;
    lastTimerLoad = 0;
    
    if (listHead != &dummy) {
        enqueueCallback(listHead);
    }

    listHead = next;
    
    startTimerAtHead();    
}

void timeout_startTimer(timerStruct_t *timer)
{
    uint32_t i = -1;
    timeout_create(timer, i>>1);
}

uint32_t timeout_stopTimer(timerStruct_t *timer)
{
    uint32_t  now = makeAbsolute(0); // Do this as fast as possible for accuracy
    uint32_t i = -1;
    i>>=1;
    
    timeout_delete(timer);

    uint32_t  diff = timer->absoluteTime - now;
    
    // This calculates the (max range)/2 minus (remaining time) which = elapsed time
    return (i - diff);
}
