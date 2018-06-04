/***************************************************************************
*                                       MICA
* File: BMX055_Gyr.c
* Workspace: micaComponents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   API for interacting with the Bosch BMX055 Gyroscope
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.06.04 CC - Document created
********************************************************************************/
#include "`$INSTANCE_NAME`_Gyr.h"
#include "`$INSTANCE_NAME`_Common.h"


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Gyr_Reset()
****************************************************************************//**
*
* \brief
*  Initializes the gyroscope. Meant to be a one time initialization / reset. 
* Use `$INSTANCE_NAME`_Gyr_Wakeup if the sensor needs to be woken up from sleep
*
* \param gyrState
* Pointer to the state variable of the gyroscope 
*
* \return  
* uint32: An error code with the result of the Start procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On successful Start
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Gyr_Reset(`$INSTANCE_NAME`_GYR_STATE_T* gyrState) {
    /* Initiate a Gyroscope software reset */
    uint32 readError = `$i2cWriteFunction`(`$INSTANCE_NAME`_GYR_ADDR, `$INSTANCE_NAME`_GYR_BGW_SOFTRESET_REG, `$INSTANCE_NAME`_GYR_BGW_SOFTRESET_VAL);
    if(readError != `$INSTANCE_NAME`_ERR_OK){ return readError; }
    /* Wait necessary boot time */
    MICA_delayMs(`$INSTANCE_NAME`_GYR_BGW_SOFTRESET_MS);
    /* Set state values to the default */
    gyrState->powerState = `$INSTANCE_NAME`_GYR_PM_NORMAL;
    gyrState->scale = `$INSTANCE_NAME`_GYR_RANGE_2000_GAIN;
    gyrState->channels.X = true;
    gyrState->channels.Y = true;
    gyrState->channels.Z = true;
    /* Return Success  */
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Gyr_Stop()
****************************************************************************//**
*
* \brief
*  Shuts down the Acc completely. Disables are interrupts. Use `$INSTANCE_NAME`_Gyr_Sleep
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
uint32 `$INSTANCE_NAME`_Gyr_Stop(void) {
    /* @TODO: Implement function */
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Gyr_Sleep()
****************************************************************************//**
*
* \brief
*  Puts the gyroscope into the low power mode specified.
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
uint32 `$INSTANCE_NAME`_Gyr_Sleep(uint8 powerMode) {
    switch(powerMode) {
        case `$INSTANCE_NAME`_GYR_PM_FAST_POWERUP:
        case `$INSTANCE_NAME`_GYR_PM_SUSPEND:
        case `$INSTANCE_NAME`_GYR_PM_DEEP_SUSPEND:
            break;
        /* Invalid Power states */
        case `$INSTANCE_NAME`_GYR_PM_NORMAL:
            return `$INSTANCE_NAME`_ERR_MODE_INVALID;
        default:
            return `$INSTANCE_NAME`_ERR_MODE_UNKNOWN; 

    }
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Gyr_Wakeup()
****************************************************************************//**
*
* \brief
*  Wakes the gyroscope up from sleep
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
uint32 `$INSTANCE_NAME`_Gyr_Wakeup(void) {
    /* @TODO: Implement function */
    return `$INSTANCE_NAME`_ERR_OK;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Gyr_Read()
****************************************************************************//**
*
* \brief
*  Reads the specified channels of the gyroscope. Places result into the dataArray.
*   values are scaled and converted to radians.
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
//uint32 `$INSTANCE_NAME`_Gyr_Read(int16* dataArray, uint8 sensorChannels){
uint32 `$INSTANCE_NAME`_Gyr_Read(GYRO_DATA_T* gyroData){
    /* Read in the gyroscope data */
    uint8 msb = ZERO;
    uint8 lsb = ZERO;
    uint32 readError;
    // TODO: scale based off settings
    float scale = 0.061f; /* Default settings 61 m°/s/lsb */
    /************** X Channel **************/
    /* Read the LSB first to lock MSB */
    readError = `$i2cReadFunction`(`$INSTANCE_NAME`_GYR_ADDR, `$INSTANCE_NAME`_GYR_X_LSB, &lsb);
    if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
    /* Read the MSB */
    readError = `$i2cReadFunction`(`$INSTANCE_NAME`_GYR_ADDR, `$INSTANCE_NAME`_GYR_X_MSB, &msb);
    int16 x = (msb << SHIFT_BYTE_ONE) | lsb;
    /* Write X value */
    gyroData->Wx = to_radians(scale * (float) x);
    /************** Y Channel **************/
    /* Read the LSB first to lock MSB */
    readError = `$i2cReadFunction`(`$INSTANCE_NAME`_GYR_ADDR, `$INSTANCE_NAME`_GYR_Y_LSB, &lsb);
    if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
    /* Read the MSB */
    readError = `$i2cReadFunction`(`$INSTANCE_NAME`_GYR_ADDR, `$INSTANCE_NAME`_GYR_Y_MSB, &msb);
    int16 y = (msb << SHIFT_BYTE_ONE) | lsb;
    /* Write Y value */
    gyroData->Wy = to_radians(scale * (float) y);
    /************** Z Channel **************/
    /* Read the LSB first to lock MSB */
    readError = `$i2cReadFunction`(`$INSTANCE_NAME`_GYR_ADDR, `$INSTANCE_NAME`_GYR_Z_LSB, &lsb);
    if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
    /* Read the MSB */
    readError = `$i2cReadFunction`(`$INSTANCE_NAME`_GYR_ADDR, `$INSTANCE_NAME`_GYR_Z_MSB, &msb);
    int16 z = (msb << SHIFT_BYTE_ONE) | lsb;
    /* Write Z value */
    gyroData->Wz = to_radians(scale * (float) z);
    
    /* Indicate success */
    return `$INSTANCE_NAME`_ERR_OK;

}
/* [] END OF FILE */
