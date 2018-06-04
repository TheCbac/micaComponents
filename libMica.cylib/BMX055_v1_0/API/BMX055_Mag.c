/***************************************************************************
*                                       MICA
* File: BMX055_Mag.c
* Workspace: micaComponents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   API for interacting with the Bosch BMX055 Magnetometer
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.06.04 CC - Document created
********************************************************************************/
#include "`$INSTANCE_NAME`_Mag.h"
#include "`$INSTANCE_NAME`_Common.h"


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Mag_Reset()
****************************************************************************//**
*
* \brief
*  Initializes the magnetometer. Meant to be a one time initialization / reset. 
* Use `$INSTANCE_NAME`_Mag_Wakeup if the sensor needs to be woken up from sleep
*
*
* \return  
* uint32: An error code with the result of the Start procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On successful Start
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Mag_Reset(void) {
    /* @TODO: Implement function */
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Mag_Stop()
****************************************************************************//**
*
* \brief
*  Shuts down the Acc completely. Disables are interrupts. Use `$INSTANCE_NAME`_Mag_Sleep
*  if interrupts should be maintained
*
*
* \return  
* uint32: An error code with the result of the Stop procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On successful Stop
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Mag_Stop(void) {
    /* @TODO: Implement function */
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Mag_Sleep()
****************************************************************************//**
*
* \brief
*  Puts the magnetometer into the low power mode specified.
*
* \param powerMode
*  Power mode to place the device into 
*
* \return  
* uint32: An error code with the result of the Sleep procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On successful Sleep
*   `$INSTANCE_NAME`_ERR_MODE_INVALID       | An invalid power mode was specified
*   `$INSTANCE_NAME`_ERR_MODE_UNKNOWN       | An unknown power mode was specified
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Mag_Sleep(uint8 powerMode) {
    switch(powerMode) {
        case `$INSTANCE_NAME`_MAG_PM_FORCED:
        case `$INSTANCE_NAME`_MAG_PM_SUSPEND:
        case `$INSTANCE_NAME`_MAG_PM_SLEEP:
            break;
        /* Invalid Power states */
        case `$INSTANCE_NAME`_MAG_PM_NORMAL:
            return `$INSTANCE_NAME`_ERR_MODE_INVALID;
        default:
            return `$INSTANCE_NAME`_ERR_MODE_UNKNOWN;

    }
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Mag_Wakeup()
****************************************************************************//**
*
* \brief
*  Wakes the magnetometer up from sleep
*
* \param powerMode
*  Power mode to place the device into 
*
* \return  
* uint32: An error code with the result of the Wakeup procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On successful Stop
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Mag_Wakeup(void) {
    /* @TODO: Implement function */
    return `$INSTANCE_NAME`_ERR_OK;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Mag_Read()
****************************************************************************//**
*
* \brief
*  Reads the specified channels of the magnetometer. Places result into the dataArray
*
* \param dataArray
*  Array to place the data into
*       
* \param sensorChannels 
* A bit mask of the channels to sample 
*
* \return 
* uint32: An error code with the result of the read procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On successful operation
*   `$INSTANCE_NAME`_ERR_CHANNELS_NONE      | Data was not requested from any channels
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Mag_Read(uint16* dataArray, uint8 sensorChannels){
    /* Read in the magnetometer data */
    uint8 * msb = ZERO;
    uint8 * lsb = ZERO;
    uint16 channelCount = ZERO;
    uint32 readError;
    /* X Data */
    if (sensorChannels & `$INSTANCE_NAME`_CHANNEL_MASK_X){
            /* A channel is being read */
            channelCount++;
            /* Read the LSB first to lock MSB */
            readError = `$i2cReadFunction`(`$INSTANCE_NAME`_MAG_ADDR, `$INSTANCE_NAME`_MAG_X_LSB, lsb);
            if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
            /* Read the MSB */
            readError = `$i2cReadFunction`(`$INSTANCE_NAME`_MAG_ADDR, `$INSTANCE_NAME`_MAG_X_MSB, msb);
            if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
        /* Discard LS nibble and store the value in the output array */
        dataArray[channelCount] = (*msb << SHIFT_BYTE_HALF) | ((*lsb >> SHIFT_BYTE_HALF) & MASK_NIBBLE_LOW);
    }
    /* Y Data */
    if (sensorChannels & `$INSTANCE_NAME`_CHANNEL_MASK_Y){ 
            channelCount++;
            readError = `$i2cReadFunction`(`$INSTANCE_NAME`_MAG_ADDR, `$INSTANCE_NAME`_MAG_Y_LSB, lsb);
            if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
            readError = `$i2cReadFunction`(`$INSTANCE_NAME`_MAG_ADDR, `$INSTANCE_NAME`_MAG_Y_MSB, msb);
            if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
        dataArray[channelCount] = (*msb << SHIFT_BYTE_HALF) | ((*lsb >> SHIFT_BYTE_HALF) & MASK_NIBBLE_LOW);
    }
    /* Z Data */
    if (sensorChannels & `$INSTANCE_NAME`_CHANNEL_MASK_Z){
            channelCount++;
            readError = `$i2cReadFunction`(`$INSTANCE_NAME`_MAG_ADDR, `$INSTANCE_NAME`_MAG_Z_LSB, lsb);
            if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
            readError = `$i2cReadFunction`(`$INSTANCE_NAME`_MAG_ADDR, `$INSTANCE_NAME`_MAG_Z_MSB, msb);
            if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
        dataArray[channelCount] = (*msb << SHIFT_BYTE_HALF) | ((*lsb >> SHIFT_BYTE_HALF) & MASK_NIBBLE_LOW);
    }
    /* if no channels reported, return noData */
    if(!channelCount){return `$INSTANCE_NAME`_ERR_CHANNELS_NONE;}
    /* Pack the Channel info */
    dataArray[`$INSTANCE_NAME`_CHANNEL_INDEX_NUM_CHAN] = channelCount;
    /* Return success */
    return `$INSTANCE_NAME`_ERR_OK;
}
/* [] END OF FILE */
