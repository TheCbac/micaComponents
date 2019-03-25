/***************************************************************************
*                                 MICA  © 2019
*                           MIT BioInstrumentation Lab
*
* File: systemtTimer.c
* Workspace: micaComponents
* Project: libMica
* Version: 1.0.0
* Authors: Craig Cheney
* 
* PCB:  
* PSoC: 
*
* Brief:
*   Manages timing for system events
*
* 2019.01.10  - Document Created
********************************************************************************/
#include "`$INSTANCE_NAME`.h"
#include "micaCommon.h"
#include "`$INSTANCE_NAME`_timer_interrupt.h"


volatile `$INSTANCE_NAME`_time_S systemTime;
volatile bool flag_systemTime_halfSec = false;

/* ISR Function declarations */
void `$INSTANCE_NAME`_ISR_incTime(void);


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start()
****************************************************************************//**
* \brief
*  Starts the system timer
*
* \return
*   None
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void){
    `$INSTANCE_NAME`_ResetTime();
    `$INSTANCE_NAME`_timer_interrupt_StartEx(`$INSTANCE_NAME`_ISR_incTime);
    `$INSTANCE_NAME`_timer_Start();
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop()
****************************************************************************//**
* \brief
*  Stop the timer
*
* \return
*   None
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void){
    `$INSTANCE_NAME`_timer_Stop();
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ResetTime()
****************************************************************************//**
* \brief
*  Starts the system timer
*
* \return
*   None
*******************************************************************************/
void `$INSTANCE_NAME`_ResetTime(void){
    systemTime.seconds = ZERO;
    systemTime.microSecs = ZERO;
    flag_systemTime_halfSec = false;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_getSystemTime()
****************************************************************************//**
* \brief
*  Places the current system time into 
*
* \return
*   None
*******************************************************************************/
void `$INSTANCE_NAME`_getSystemTime(`$INSTANCE_NAME`_time_S *time){
    uint8_t intStatus = CyEnterCriticalSection();
    
    time->seconds = systemTime.seconds;
    uint32_t microSecs = `$INSTANCE_NAME`_timer_ReadCounter();
    if ( flag_systemTime_halfSec) {
        microSecs += MICA_DELAY_US_SEC_HALF;
    }
    time->microSecs = microSecs;
    
    CyExitCriticalSection(intStatus);
}


/*******************************************************************************
* ISR Name: `$INSTANCE_NAME`_ISR_incTime()
********************************************************************************
* Summary:
*  Triggers from the system timer component. Increments the stored time count
*
* Interrupt: 
*       timer_interupt
*
*******************************************************************************/
void `$INSTANCE_NAME`_ISR_incTime(void){
    if(flag_systemTime_halfSec) {
        flag_systemTime_halfSec = false;
        systemTime.seconds++;
    } else {
        flag_systemTime_halfSec = true;    
    }
    /* Clear the interrupt  */
    `$INSTANCE_NAME`_timer_ClearInterrupt(`$INSTANCE_NAME`_timer_INTR_MASK_TC);

}

/* [] END OF FILE */
