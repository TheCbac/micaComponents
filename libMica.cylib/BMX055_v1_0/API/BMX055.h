/***************************************************************************
*                                       MICA
* File: BMX055.h
* Workspace: micaComponents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   Header for interacting with the Bosch BMX055 IMU
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.03.13 CC - Document created
********************************************************************************/
/* Header Guard */
#ifndef `$INSTANCE_NAME`_H
    #define `$INSTANCE_NAME`_H
    /***************************************
    * Included Files
    ***************************************/
    #include "cytypes.h"
    #include "micaCommon.h"
    #include "`$INSTANCE_NAME`_Acc.h"
    #include "`$INSTANCE_NAME`_Gyr.h"
    #include "`$INSTANCE_NAME`_Mag.h"
    /***************************************
    * Enumerated Types
    ***************************************/
    
    /***************************************
    * Structs
    ***************************************/

    /* Struct used for keeping track of the IMU Settings */
    typedef struct {
        `$INSTANCE_NAME`_ACC_STATE_T acc;       /**< Device settings for the Accelerometer */
        `$INSTANCE_NAME`_GYR_STATE_T gyr;       /**< Device settings for the Gyroscope */
        `$INSTANCE_NAME`_MAG_STATE_T mag;       /**< Device settings for the Magnetometer */
    }`$INSTANCE_NAME`_STATE_T;
    /***************************************
    * Macro Definitions
    ***************************************/
   
    /***************************************
    *        Function Prototypes
    ***************************************/
    /* Device wide Functions */
    uint32 `$INSTANCE_NAME`_Start(`$INSTANCE_NAME`_STATE_T* deviceState);        /**< Start the IMU (Acc, Gyr, Mag) */
    uint32 `$INSTANCE_NAME`_Stop(`$INSTANCE_NAME`_STATE_T* deviceState);         /**< Disable the IMU (Acc, Gyr, Mag)*/
    uint32 `$INSTANCE_NAME`_Sleep(`$INSTANCE_NAME`_STATE_T* deviceState);        /**< Put the IMU (Acc, Gyr, Mag) to sleep */
    uint32 `$INSTANCE_NAME`_Wakeup(`$INSTANCE_NAME`_STATE_T* deviceState);       /**< Wakeup all of the IMU (Acc, Gyr, Mag)*/
    uint32 `$INSTANCE_NAME`_SetParameters(uint8 deviceAddr, uint8 numParams, uint8* sensorParams); /**< Writes the parameters out to the device specified */
    // uint32 `$INSTANCE_NAME`_GetDeviceState(uint8 deviceAddr, uint8 * returnState); /**< Get the value of the power state for a device */
    uint32 `$INSTANCE_NAME`_testConnection(uint32* i2cError);          /**< Test basic I2C contact with device */
 

#endif /* `$INSTANCE_NAME`_H */
/* [] END OF FILE */
