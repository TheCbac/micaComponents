/***************************************************************************//**
* \file `$INSTANCE_NAME`.h
* \version 0.1.0
*
* \brief
*   Simple print functionality
*
* \date Date Created:  2017.12.19
* \date Last Modified: 2017.12.19
*
********************************************************************************
* \copyright
* Copyright 2017, MICA. All rights reserved.
*******************************************************************************/
/* Header Guard */
#ifndef `$INSTANCE_NAME`_H
    #define `$INSTANCE_NAME`_H
    /***************************************
    * Included files
    ***************************************/
    #include "cytypes.h"
    /***************************************
    * Function declarations 
    ***************************************/
    void `$INSTANCE_NAME`(char8 *pszFmt,...);
    /***************************************
    * Macro Definitions
    ***************************************/
    #define `$INSTANCE_NAME`_clearScreen()  `$INSTANCE_NAME`("\033[2J\033[1;1H")
    
    
#endif /* (`$INSTANCE_NAME`_H) */
/* [] END OF FILE */
