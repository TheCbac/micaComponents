/***************************************************************************
*                                 MICA  © 2019
*                           MIT BioInstrumentation Lab
*
* File: `$INSTANCE_NAME`.h
* Workspace: micaComponents
* Project: libMica
* Version: 1.0.0
* Authors: Craig Cheney
* 
*
* Brief:
*   Header for systemtTimer.c
*
* 2019.01.10  - Document Created
********************************************************************************/

/* Header Guard */
#ifndef `$INSTANCE_NAME`_H
    #define `$INSTANCE_NAME`_H
    /***************************************
    * Included files
    ***************************************/
    #include <stdint.h>
    #include <stdbool.h>
    #include "`$INSTANCE_NAME`_timer.h"
    /***************************************
    * Macro Definitions
    ***************************************/
//    #define  `$INSTANCE_NAME`_DEFINE_NAME             (0x00)  /**< DEFINE NAME Description */
    
    /***************************************
    * Enumerated Types
    ***************************************/
//    typedef enum {
//        typeVal1,                 /**< val1 Description */
//        typeVal2                  /**< val2 Description */
//    }  `$INSTANCE_NAME`_ENUM_NAME_T;
    
    /***************************************
    * Structures
    ***************************************/
    typedef struct {
        uint32_t seconds;            /**< Number of seconds the timer has been running */
        uint32_t microSecs;         /**< number of microseconds elapsed */
    }  `$INSTANCE_NAME`_time_S;
    
    /***************************************
    * Function declarations 
    ***************************************/
    void `$INSTANCE_NAME`_ResetTime(void);
    void `$INSTANCE_NAME`_Start(void);        
    void `$INSTANCE_NAME`_Stop(void);
    

#endif /* `$INSTANCE_NAME`_H */

/* [] END OF FILE */
