/***************************************************************************
*                                       MICA
* File: LED_RGB_pins.c
* Workspace: micaCompnents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   Block API for controlling an RGB LED
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.02.28 CC - Document created
********************************************************************************/
#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_Control_reg.h"
#include "CyLib.h"
#include "micaCommon.h"

/* Set bit at position 'bitShift' to 'val' */
#define SET_BIT_STATE(reg, bitShift, val) (reg &= ~(1u << bitShift) | (!!val << bitShift))

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Write()
********************************************************************************
* Summary:
*   Sets the state of the LED control register
*
* Parameters:
*   uint8 State - The new state mask to write to the control register.
*
* Return:
*   uint8: Value of the control register after it was written. 
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_Write(uint8 state) {
    /* Set the State accounting for active mod */
    `$INSTANCE_NAME`_Control_reg_Write( (`$activeLow` ? ~state : state) & `$INSTANCE_NAME`_CTRL_MASK );
    /* Return the value */
    return `$INSTANCE_NAME`_Control_reg_Read();
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Read()
********************************************************************************
* Summary:
*   Returns the current value of the LED control register
*
* Parameters:
*   None
*
* Return:
*   uint8: Value held in the LED control register
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_Read(void){
    return `$INSTANCE_NAME`_Control_reg_Read() & `$INSTANCE_NAME`_CTRL_MASK;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep()
********************************************************************************
* Summary:
*   Prepares the component for sleep. Sleeps the control Register.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Sleep(void) {
    /* Sleep Control reg */
    `$INSTANCE_NAME`_Control_reg_Sleep();
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup()
********************************************************************************
* Summary:
*   Wakes up the component from sleep. Wakes the control Register.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Wakeup(void) {
    /* Wakeup Control reg */
    `$INSTANCE_NAME`_Control_reg_Wakeup();
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_R_Write()
********************************************************************************
* Summary:
*   Sets the state of the Red LED. 
*
* Parameters:
*   uint8 State - The new state to write
*
* Return:
*   None
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_R_Write(bool state) {
    /* Read the Current state */
    uint8 reg = `$INSTANCE_NAME`_Control_reg_Read();
    /* Set the bit to the new state */
    SET_BIT_STATE(reg, `$INSTANCE_NAME`_R_PIN_SHIFT, state);
    /* Write the bits */
    `$INSTANCE_NAME`_Control_reg_Write(reg);
    /* Return the current state */
    return reg;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_G_Write()
********************************************************************************
* Summary:
*   Sets the state of the Red LED 
*
* Parameters:
*   uint8 State - The new state to write
*
* Return:
*   None
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_G_Write(bool state) {
    /* Read the Current state */
    uint8 reg = `$INSTANCE_NAME`_Control_reg_Read();
    /* Set the bit to the new state */
    SET_BIT_STATE(reg, `$INSTANCE_NAME`_G_PIN_SHIFT, state);
    /* Write the bits */
    `$INSTANCE_NAME`_Control_reg_Write(reg);
    /* Return the current state */
    return reg;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_B_Write()
********************************************************************************
* Summary:
*   Sets the state of the Red LED 
*
* Parameters:
*   uint8 State - The new state to write
*
* Return:
*   None
*
*******************************************************************************/
uint8 `$INSTANCE_NAME`_B_Write(bool state) {
    /* Read the Current state */
    uint8 reg = `$INSTANCE_NAME`_Control_reg_Read();
    /* Set the bit to the new state */
    SET_BIT_STATE(reg, `$INSTANCE_NAME`_B_PIN_SHIFT, state);
    /* Write the bits */
    `$INSTANCE_NAME`_Control_reg_Write(reg);
    /* Return the current state */
    return reg;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Test()
********************************************************************************
* Summary:
*   Runs through the board level testing routine for the LEDs.
*
* Parameters:
*   uint8: The number of times to iterate through the test. 0 means infinite. 
*
* Expected Outcome: 
*   0. All LEDs off
*   1. Red LED on
*   2. Green LED on
*   3. Blue LED on
*   4. Yellow (RB)
*   5. Cyan (BG)
*   6. Magenta (RG)
*   7. White (RGB) LEDs on
*
* Return:
*   None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Test(uint8 runs){
    /* Iteration variable */
    uint8 i = ZERO;     
    do{
        /* 0 - All LEDs off */
        `$INSTANCE_NAME`_Write(`$INSTANCE_NAME`_ON_NONE);
        CyDelay(`$INSTANCE_NAME`_DELAY_TEST);
        /* 1 - Red LED on */
        `$INSTANCE_NAME`_Write(`$INSTANCE_NAME`_ON_RED);
        CyDelay(`$INSTANCE_NAME`_DELAY_TEST);
        /* 2 - Green LED on */
        `$INSTANCE_NAME`_Write(`$INSTANCE_NAME`_ON_GREEN);
        CyDelay(`$INSTANCE_NAME`_DELAY_TEST);
        /* 3 - Blue LED on */
        `$INSTANCE_NAME`_Write(`$INSTANCE_NAME`_ON_BLUE);
        CyDelay(`$INSTANCE_NAME`_DELAY_TEST);
        /* 4 - Yellow on */
        `$INSTANCE_NAME`_Write(`$INSTANCE_NAME`_ON_YELLOW);
        CyDelay(`$INSTANCE_NAME`_DELAY_TEST);
        /* 5 - Cyan on */
        `$INSTANCE_NAME`_Write(`$INSTANCE_NAME`_ON_CYAN);
        CyDelay(`$INSTANCE_NAME`_DELAY_TEST);
        /* 6 - Magneta on */
        `$INSTANCE_NAME`_Write(`$INSTANCE_NAME`_ON_MAGENTA);
        CyDelay(`$INSTANCE_NAME`_DELAY_TEST);
        /* 7 -White on*/
        `$INSTANCE_NAME`_Write(`$INSTANCE_NAME`_ON_WHITE);
        CyDelay(`$INSTANCE_NAME`_DELAY_TEST);
        /* Increment the iteration */
        i++;
    } while(runs == ZERO || (i < runs));
    
}


/* [] END OF FILE */
