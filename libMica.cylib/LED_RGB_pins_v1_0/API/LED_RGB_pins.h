/***************************************************************************
*                                       MICA
* File: LED_RGB_pins.c
* Workspace: micaCompnents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   Block Header for controlling an RGB LED
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.02.28 CC - Document created
********************************************************************************/
/* Header Guard */
#ifndef `$INSTANCE_NAME`_H
    #define `$INSTANCE_NAME`_H
    /***************************************
    * Included files
    ***************************************/
    #include "cytypes.h"
    #include <stdbool.h>
    /***************************************
    * Function declarations 
    ***************************************/
    uint8   `$INSTANCE_NAME`_R_Write(bool state);
    uint8   `$INSTANCE_NAME`_G_Write(bool state);
    uint8   `$INSTANCE_NAME`_B_Write(bool state);
    
    uint8   `$INSTANCE_NAME`_Write(uint8 state);
    uint8   `$INSTANCE_NAME`_Read(void);
    void    `$INSTANCE_NAME`_Test(uint8 runs);
    
    void    `$INSTANCE_NAME`_Sleep(void);
    void    `$INSTANCE_NAME`_Wakeup(void);
    /***************************************
    * Macro Definitions
    ***************************************/
    #define `$INSTANCE_NAME`_ON                 (!`$activeLow`)
    #define `$INSTANCE_NAME`_OFF                (`$activeLow`)
       
    #define `$INSTANCE_NAME`_R_PIN_SHIFT        (0u)
    #define `$INSTANCE_NAME`_G_PIN_SHIFT        (1u)
    #define `$INSTANCE_NAME`_B_PIN_SHIFT        (2u)
    
    #define `$INSTANCE_NAME`_ON_NONE            (0u)
    #define `$INSTANCE_NAME`_ON_RED             (1u << `$INSTANCE_NAME`_R_PIN_SHIFT)
    #define `$INSTANCE_NAME`_ON_GREEN           (1u << `$INSTANCE_NAME`_G_PIN_SHIFT)
    #define `$INSTANCE_NAME`_ON_BLUE            (1u << `$INSTANCE_NAME`_B_PIN_SHIFT)
    #define `$INSTANCE_NAME`_ON_YELLOW          (`$INSTANCE_NAME`_ON_RED  | `$INSTANCE_NAME`_ON_GREEN)
    #define `$INSTANCE_NAME`_ON_MAGENTA         (`$INSTANCE_NAME`_ON_RED  | `$INSTANCE_NAME`_ON_BLUE)
    #define `$INSTANCE_NAME`_ON_CYAN            (`$INSTANCE_NAME`_ON_BLUE | `$INSTANCE_NAME`_ON_GREEN)
    #define `$INSTANCE_NAME`_ON_WHITE           (`$INSTANCE_NAME`_ON_RED  | `$INSTANCE_NAME`_ON_GREEN | `$INSTANCE_NAME`_ON_BLUE)
    
    #define `$INSTANCE_NAME`_CTRL_MASK          (0x07u)
    #define `$INSTANCE_NAME`_DELAY_TEST         (500)
   
#endif /* `$INSTANCE_NAME`_H */
/* [] END OF FILE */
