/***************************************************************************
*                                       MICA
* File: BMX055_Mag.h
* Workspace: micaComponents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   Header for interacting with the Bosch BMX055 Magnetometer
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.06.04 CC - Document created
********************************************************************************/
/* Header Guard */
#ifndef `$INSTANCE_NAME`_MAG_H
    #define `$INSTANCE_NAME`_MAG_H
    /***************************************
    * Included Files
    ***************************************/
    #include "cytypes.h"
    #include "micaCommon.h"
    /***************************************
    * Enumerated Types
    ***************************************/
    /* Possible Magnetometer power states */
    typedef enum  {
        `$INSTANCE_NAME`_MAG_PM_SUSPEND = (0u),      /**< Mag Suspend power mode */
        `$INSTANCE_NAME`_MAG_PM_SLEEP,               /**< Mag Sleep power mode */
        `$INSTANCE_NAME`_MAG_PM_NORMAL,              /**< Mag Normal power mode */
        `$INSTANCE_NAME`_MAG_PM_FORCED,              /**< Mag Forced power mode */
    } `$INSTANCE_NAME`_MAG_POWER_T;
    /***************************************
    * Structs
    ***************************************/
    /* Magnetometer settings */
    typedef struct {
        float scale;                             /**< Scale for the magnetometer */
        CHANNELS_XYZ_T channels;                      /**< Channels that are enabled */
        `$INSTANCE_NAME`_MAG_POWER_T powerState; /**< Power State of the magnetometer */
    } `$INSTANCE_NAME`_MAG_STATE_T;
    
    /***************************************
    * Macro Definitions
    ***************************************/
    /* Magnetometer definitions used across the entire device */
    #define `$INSTANCE_NAME`_MAG_ADDR            (0x10u)     /**< I2C Address of the Magnetometer */
    #define `$INSTANCE_NAME`_MAG_CHIPID_REG      (0x40u)     /**< Address of the Magnetometer chip id register */
    #define `$INSTANCE_NAME`_MAG_CHIPID_VAL      (0x32u)     /**< Value of the Magnetometer chip id */
    #define `$INSTANCE_NAME`_MAG_X_MSB           (0x43u)     /**< Magnetometer register address of the X-axis Most Significant Byte */
    #define `$INSTANCE_NAME`_MAG_X_LSB           (0x42u)     /**< Magnetometer register address of the X-axis Least Significant Byte */
    #define `$INSTANCE_NAME`_MAG_Y_MSB           (0x45u)     /**< Magnetometer register address of the Y-axis Most Significant Byte */
    #define `$INSTANCE_NAME`_MAG_Y_LSB           (0x44u)     /**< Magnetometer register address of the Y-axis Least Significant Byte */
    #define `$INSTANCE_NAME`_MAG_Z_MSB           (0x47u)     /**< Magnetometer register address of the Z-axis Most Significant Byte */
    #define `$INSTANCE_NAME`_MAG_Z_LSB           (0x46u)     /**< Magnetometer register address of the Z-axis Least Significant Byte */
    
    /***********************************************
    * magnetometer definitions used setting the digital filters,
    * Ordinary Data Rate (ODR), and power management on the device
    * *********************************************/

    /* Sets the power mode of the Magnetometer */
    #define `$INSTANCE_NAME`_MAG_CONTROLBITS_REG                 (0x4Bu)     /**< Address of the Magnetometer Power Control register */
    #define `$INSTANCE_NAME`_MAG_CONTROLBITS_SHIFT_PWR_CTRL    (0x00u)     /**< Position of the Power control bit */
    #define `$INSTANCE_NAME`_MAG_CONTROLBITS_PWR_CTRL          (0x01u << `$INSTANCE_NAME`_MAG_CONTROLBITS_SHIFT_PWR_CTRL )    /**< Mask of the Power control bit */
    /***************************************
    *        Function Prototypes
    ***************************************/
    /* Magnetometer specific functions */
    uint32 `$INSTANCE_NAME`_Mag_Reset(`$INSTANCE_NAME`_MAG_STATE_T* magState);    /**< Start the Magnetometer*/
    uint32 `$INSTANCE_NAME`_Mag_Stop(void);     /**< Stop the Magnetometer*/
    uint32 `$INSTANCE_NAME`_Mag_Sleep(uint8 powerMode);    /**< Put the Magnetometer into the specified sleep mode */
    uint32 `$INSTANCE_NAME`_Mag_Wakeup(void);   /**< Wakeup the Magnetometer*/
    uint32 `$INSTANCE_NAME`_Mag_Read(uint16* dataArray, uint8 sensorChannels);      /**< Read the value of Magnetometer*/
    
#endif /* `$INSTANCE_NAME`_MAG_H */
/* [] END OF FILE */
