/***************************************************************************
*                                       MICA
* File: pushButton.c
* Workspace: micaCompnents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   Component for interactive with a push button
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.07.03 CC - Document created
********************************************************************************/
#include "`$INSTANCE_NAME`.h"
#include "CyLib.h"
#include "`$INSTANCE_NAME`_btn_press_interrupt.h"
#include "`$INSTANCE_NAME`_btn_release_interrupt.h"

/* State Variables */
volatile uint32 `$INSTANCE_NAME`_btnPressCount = ZERO;
volatile uint32 `$INSTANCE_NAME`_btnReleaseCount = ZERO; /**< Number of times button has been released */
volatile bool `$INSTANCE_NAME`_btnPressed = false;       /**< Whether or not a button has been pressed since last check */

/* Call callback functions */
FUNCTION_T* `$INSTANCE_NAME`_btnPressCallback = NULL;    /**< Pointer to ISR callback */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_getPressCount()
********************************************************************************
* Summary: 
*  Checks to see if there has been a button press since the last check
*
* Return:
*   Number of Button presses
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_getPressCount(void) {
    return `$INSTANCE_NAME`_btnPressCount;
}

/*******************************************************************************
* Function Name:`$INSTANCE_NAME`_getReleaseCount()
********************************************************************************
* Summary: 
*  Checks to see the number of times a button has been release
*
* Return:
*   Number of Button releases
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_getReleaseCount(void){
    /* Return number of counts */
    return `$INSTANCE_NAME`_btnReleaseCount;
    
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_resetBtnCounts()
********************************************************************************
* Summary: 
*  Checks to see if there has been a button press since the last check
*
* Return:
*   Number of Button presses
*
*******************************************************************************/
void `$INSTANCE_NAME`_resetBtnCounts(void){
    /* Disable interrupts */
    uint8 ints = CyEnterCriticalSection();
    /* Reset counts */
    `$INSTANCE_NAME`_btnPressCount = ZERO;
    `$INSTANCE_NAME`_btnReleaseCount = ZERO;
    /* Enable interrupts */
    CyExitCriticalSection(ints);
}  

    
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_wasButtonPressed()
********************************************************************************
* Summary: 
*  Checks if the button pressed flag is true and resets it
*
* Return:
*   True if the button has been pressed since the last check
*
*******************************************************************************/
bool `$INSTANCE_NAME`_wasButtonPressed(void){
    /* Disable interrupts */
    uint8 ints = CyEnterCriticalSection();
    /* Check if pressed */
    bool pressed = `$INSTANCE_NAME`_btnPressed;
    /* Reset the flag */
    `$INSTANCE_NAME`_btnPressed = false;
    /* Enable interrupts */
    CyExitCriticalSection(ints);
    /* Return if the button was pressed */
    return pressed;
    
}  

/*******************************************************************************
* Function Name:`$INSTANCE_NAME`_EnableBtnInterrupts()
********************************************************************************
* Summary: 
*  Enable the button interrupts
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_EnableBtnInterrupts(void){
    /* Initialize interrupt vectors */
    `$INSTANCE_NAME`_btn_press_interrupt_StartEx(`$INSTANCE_NAME`_ISR_testButton_press); 
    `$INSTANCE_NAME`_btn_release_interrupt_StartEx(`$INSTANCE_NAME`_ISR_testButton_release); 
}  


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetBtnPressIsr()
********************************************************************************
* Summary: 
*  Passes in an ISR to call when the button in pressed
*
* \param callback
*   Function to call when the btn is pressed. Of type 'void func(void)'
*
* Return:
*   None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetBtnPressIsr(FUNCTION_T * callback){
    /* Change address of global variable */
    `$INSTANCE_NAME`_btnPressCallback = callback;   
}

/*******************************************************************************
* ISR Name: `$INSTANCE_NAME`_ISR_testButton_press()
********************************************************************************
* Summary:
*  Triggers whenever user presses the button. Toggles the red led's state,
*  turn the green led on. 
*
* Interrupt: 
*       button_interrupt_press
*
*******************************************************************************/
void `$INSTANCE_NAME`_ISR_testButton_press(void){
    /* Clear Interrupt */
//    button_pin_ClearInterrupt();
    /* Log the Press */
    `$INSTANCE_NAME`_btnPressCount++;
    /* Call the button interrupt code if present */
    if(`$INSTANCE_NAME`_btnPressCallback != NULL){
        /* Call the function */
        `$INSTANCE_NAME`_btnPressCallback();   
    }
    /* Register that a button was pressed */
    `$INSTANCE_NAME`_btnPressed = true; 
}

/*******************************************************************************
* ISR Name: `$INSTANCE_NAME`_ISR_testButton_release()
********************************************************************************
* Summary:
*  Triggers whenever user releases the button. Turns the green led off 
*
* Interrupt: 
*       button_interrupt_release
*
*******************************************************************************/
void `$INSTANCE_NAME`_ISR_testButton_release(void){
    /* Clear Interrupt */
//    button_pin_ClearInterrupt();
    /* Log the release */
    `$INSTANCE_NAME`_btnReleaseCount++;
}
/* [] END OF FILE */
