/***************************************************************************
*                                       MICA
* File: BMX055_Common.h
* Workspace: micaComponents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*  Common values across all IMU devices
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.06.04 CC - Document created
********************************************************************************/
/* Header Guard */
#ifndef `$INSTANCE_NAME`_COMMON_H
    #define `$INSTANCE_NAME`_COMMON_H
    /***************************************
    * Included Files
    ***************************************/
    #include "cytypes.h"
    #include "micaCommon.h"
    /***************************************
    * Enumerated Types
    ***************************************/

    /***************************************
    * Structs
    ***************************************/
    
    /***************************************
    * Macro Definitions
    ***************************************/
    #define `$INSTANCE_NAME`_ERR_OK             (0u) /**< Operation was successful */
    #define `$INSTANCE_NAME`_ERR_DEVICE_UNKNOWN (1u) /**< An unknown device was addressed */
    #define `$INSTANCE_NAME`_ERR_CHANNELS_NONE  (2u) /**< No active channels were selected */
    #define `$INSTANCE_NAME`_ERR_MODE_INVALID   (3u) /**< An invalid power mode was specified */
    #define `$INSTANCE_NAME`_ERR_MODE_UNKNOWN   (4u) /**< An unknown power mode was specified */
    #define `$INSTANCE_NAME`_ERR_WHOAMI         (5u) /**< The WHO_AM_I value received did not match expected */
    #define `$INSTANCE_NAME`_ERR_I2C            (6u) /**< I2C Error occured */
    

    #define `$INSTANCE_NAME`_PARAM_BYTE_LEN     (2u) /**< Number of bytes contained in a dynamic param for a sensor (address & value) */
   
    #define `$INSTANCE_NAME`_CHANNEL_INDEX_X                 (0u)    /**< Index of the X Channel*/
    #define `$INSTANCE_NAME`_CHANNEL_INDEX_Y                 (1u)    /**< Index of the Y channel*/
    #define `$INSTANCE_NAME`_CHANNEL_INDEX_Z                 (2u)    /**< Index of the Z channel*/
    #define `$INSTANCE_NAME`_CHANNEL_INDEX_NUM_CHAN          (0u)    /**< Index of the number of channels that data was collected from*/      
    #define `$INSTANCE_NAME`_CHANNEL_INDEX_DATA              (1u)    /**< Index of the start of data when reported by a sensor */
    #define `$INSTANCE_NAME`_CHANNEL_MASK_X                  (1u << `$INSTANCE_NAME`_CHANNEL_INDEX_X) /**< Mask of the X channel*/
    #define `$INSTANCE_NAME`_CHANNEL_MASK_Y                  (1u << `$INSTANCE_NAME`_CHANNEL_INDEX_Y) /**< Mask of the Y channel*/
    #define `$INSTANCE_NAME`_CHANNEL_MASK_Z                  (1u << `$INSTANCE_NAME`_CHANNEL_INDEX_Z) /**< Mask of the Z channel*/
    /***************************************
    * Function Prototypes
    ***************************************/
    int16 `$INSTANCE_NAME`_twosComp_12To16(uint16 baseTwelve);  /**< Convert from base 12 two'sComp to base 16 */   
    
#endif /* `$INSTANCE_NAME`_COMMON_H */
/* [] END OF FILE */
