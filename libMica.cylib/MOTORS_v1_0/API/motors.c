/***************************************************************************
*                                       MICA
* File: `$INSTANCE_NAME`.c
* Workspace: micaCompnents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   API for contolling dual Hbridge motors
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.04.10 CC - Document created
********************************************************************************/
#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_PWM_M1.h"
#include "`$INSTANCE_NAME`_PWM_M2.h"
#include "`$INSTANCE_NAME`_ControlReg.h"


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start()
********************************************************************************
* Summary:
*   Initialize the H-brige - start the PWM blocks.
*
* Return:
*   None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void) {
    /* Start the PWM blocks */    
    `$INSTANCE_NAME`_PWM_M1_Start();
    `$INSTANCE_NAME`_PWM_M2_Start();
    /* Enables the motors */
    `$INSTANCE_NAME`_Enable();
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable()
********************************************************************************
* Summary:
*   Enables both motors
*
* Return:
*   None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void) {
    /* Read the current value in the control register*/    
    uint8 val = `$INSTANCE_NAME`_ControlReg_Read();
    /* Set enable bits */
    val |= (`$INSTANCE_NAME`_M1_EN | `$INSTANCE_NAME`_M2_EN);
    /* Write the value out */
    `$INSTANCE_NAME`_ControlReg_Write(val);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Disable()
********************************************************************************
* Summary:
*   Enables both motors
*
* Return:
*   None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Disable(void) {
    /* Read the current value in the control register*/    
    uint8 val = `$INSTANCE_NAME`_ControlReg_Read();
    /* Clear enable bits */
    val &= ~(`$INSTANCE_NAME`_M1_EN | `$INSTANCE_NAME`_M2_EN);
    /* Write the value out */
    `$INSTANCE_NAME`_ControlReg_Write(val);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Move()
********************************************************************************
* Summary:
*   Moves the robot in the specified direction at the specified speed.
*
* Parameter direction
*   The diretion to move
*
* Parameter speed
*   The speed to move at
*
* Return:
*   None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Move(`$INSTANCE_NAME`_DIRECTION_T direction, uint16 speed){
    
    switch(direction) {
        /* Forward */
        case  `$INSTANCE_NAME`_DIRECTION_FORWARD: {
            /* Write the control register value */
            `$INSTANCE_NAME`_ControlReg_Write( `$INSTANCE_NAME`_M1_FORWARD | `$INSTANCE_NAME`_M2_FORWARD);
            /* Write to the PWM blocks */
            `$INSTANCE_NAME`_PWM_M1_WriteCompare(speed);
            `$INSTANCE_NAME`_PWM_M2_WriteCompare(speed);
        }
        /* Pick up here */
    }
}

/* [] END OF FILE */
