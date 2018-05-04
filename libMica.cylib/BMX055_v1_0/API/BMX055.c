/***************************************************************************
*                                       MICA
* File: BMX055.c
* Workspace: micaComponents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   API for interacting with the Bosch BMX055 IMU
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.03.13 CC - Document created
********************************************************************************/
#include "`$INSTANCE_NAME`.h"
#include "`$i2cIncludeFile`.h"


/* Store the power state of the device */
uint8 `$INSTANCE_NAME`_Acc_powerState = `$INSTANCE_NAME`_ACC_PM_NORMAL;
uint8 `$INSTANCE_NAME`_Gyr_powerState = `$INSTANCE_NAME`_GYR_PM_NORMAL;
uint8 `$INSTANCE_NAME`_Mag_powerState = `$INSTANCE_NAME`_MAG_PM_SUSPEND ;


/* -------------------------- Device Wide Functions -------------------------- */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start()
********************************************************************************
*
* \brief Starts all three devices (Acc, GYR, and MAG)
*
* \return
* uint8: An error code with the result of the start procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On Successful stop
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Start(void) {
    // @TODO: implement
    // StartAcc();
    // StartGyr();
    // StartMag();
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop()
********************************************************************************
*
* \brief Stop all three devices (Acc, GYR, and MAG)
*
* \return
* uint8: An error code with the result of the Stop procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On Successful stop
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Stop(void) {
    // @TODO: implement
    // StopAcc();
    // StopGyr();
    // StopMag();
    return `$INSTANCE_NAME`_ERR_OK;    
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep()
********************************************************************************
*
* \brief Sleep all three devices (Acc, GYR, and MAG)
*
* \return
* uint8: An error code with the result of the sleep procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On Successful Sleep
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Sleep(void) {
    // @TODO: implement
    // SleepAcc();
    // SleepGyr();
    // SleepMag();
    return `$INSTANCE_NAME`_ERR_OK;    
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup()
********************************************************************************
*
* \brief Wakeup all three devices (Acc, GYR, and MAG)
*
* \return
* uint8: An error code with the result of the Wakeup procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On Successful Wakeup
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Wakeup(void) {
    // @TODO: implement
    // WakeupAcc();
    // WakeupGyr();
    // WakeupMag();
    return `$INSTANCE_NAME`_ERR_OK;    
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetParameters()
********************************************************************************
*
* \brief Writes the parameters out to the device specified
*
* \param deviceAddr
*  Address of the device
*
* \param numParams
* Number of parameters to be written to the device. The array sensor params
* should be double this length as each parameter is in the formate (address, value)
* 
* \param sensorParams
* An array containing the parameters. (address, value) 
*
* \return
* uint8: An error code with the result of the start procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On successful operation
*   `$INSTANCE_NAME`_ERR_DEVICE_UNKNOWN;    | An unknown device address used
*   Error from I2C Write function, `$i2cWriteFunction`
*******************************************************************************/
uint32 `$INSTANCE_NAME`_SetParameters(uint8 deviceAddr, uint8 numParams, uint8* sensorParams) {
    /* Declare local variables */
    uint8 index;
    /* Ensure the correct device was written to */
    switch(deviceAddr){
        /* Accelerometer, gyroscope or magnetometer */
        case `$INSTANCE_NAME`_ACC_ADDR:        
        case `$INSTANCE_NAME`_GYR_ADDR:
        case `$INSTANCE_NAME`_MAG_ADDR:
            break;
        /* Unknown device */
        default:
            return `$INSTANCE_NAME`_ERR_DEVICE_UNKNOWN;
    }
   /* Iterate through each command */
   for (index = ZERO; index < (numParams * `$INSTANCE_NAME`_PARAM_BYTE_LEN ); index += `$INSTANCE_NAME`_PARAM_BYTE_LEN ){
    //    micaI2C_writeReg(BMX_ACC_ADDR, sensorParams[index], sensorParams[index+ONE]);
        uint32 result = `$i2cWriteFunction`(deviceAddr, sensorParams[index], sensorParams[index+ONE]);
        /* Ensure it was valid */
        if (result != `$INSTANCE_NAME`_ERR_OK) {
            return result;
        }
   }
    /* Return Success*/
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_GetDeviceState()
********************************************************************************
*
* \brief Allows the user to get the power state for any of the three devices
* 
* \param deviceAddr
*   Address of the device to 
*
* \return
* uint8: An error code with the result of the Wakeup procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On Successful Wakeup
*   `$INSTANCE_NAME`_ERR_DEVICE_UNKNOWN;    | An unknown device address used
*******************************************************************************/
uint32 `$INSTANCE_NAME`_GetDeviceState(uint8 deviceAddr, uint8 * returnState){
    /* Ensure the correct device was written to */
    switch(deviceAddr){
        /* Accelerometer, gyroscope or magnetometer */
        case `$INSTANCE_NAME`_ACC_ADDR:     
            *returnState = `$INSTANCE_NAME`_Acc_powerState;   
            break; 
        case `$INSTANCE_NAME`_GYR_ADDR:
            *returnState = `$INSTANCE_NAME`_Gyr_powerState;    
            break;         
        case `$INSTANCE_NAME`_MAG_ADDR:
            *returnState = `$INSTANCE_NAME`_Mag_powerState;    
            break;
        /* Unknown device */
        default:
            return `$INSTANCE_NAME`_ERR_DEVICE_UNKNOWN;
    }
    return `$INSTANCE_NAME`_ERR_OK;    
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Test()
********************************************************************************
*
* \brief Test I2C Connectivity
* 

*
* \return
* uint8: An error code with the result of the Wakeup procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On Successful Wakeup
*   `$INSTANCE_NAME`_ERR_WHOAMI             | Who am I value return did not match expected
*   `$INSTANCE_NAME`_ERR_I2C                | I2C Error occured
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Test(uint32* i2cError){
    uint8 whoAmI = ZERO;
    /* Read the LSB first to lock MSB */
    uint32 readError = `$i2cReadFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_CHIPID_REG, &whoAmI);
    /* Compare against known who am I */
    if (readError == `$INSTANCE_NAME`_ERR_OK) {
        /* Check the value received */
        if(  whoAmI == `$INSTANCE_NAME`_ACC_CHIPID_VAL) {
            return `$INSTANCE_NAME`_ERR_OK;
        }
        /* Bad Whoam i */
        return `$INSTANCE_NAME`_ERR_WHOAMI;
    }
    /* I2C Error */
    /* Pass the read error out */
    *i2cError = readError;
    return `$INSTANCE_NAME`_ERR_I2C;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_twosComp_12To16()
********************************************************************************
*
* \brief Convert from base 12 two'sComp to base 16
* 
* \param baseTwelve: Twelve bit two's comp number
*
* \return
* int16: 16 bit two's comp number
*
*******************************************************************************/
int16 `$INSTANCE_NAME`_twosComp_12To16(uint16 baseTwelve) {
    /* See if the negative bit is set */
    if(baseTwelve & (ONE << ELEVEN) ){
        /* Prepend with 1's */
        return baseTwelve | (MASK_NIBBLE_LOW << TWELVE);
    }
    /* Positive number, return original */
    return baseTwelve;
}

/* -------------------------- Accelerometer Functions -------------------------- */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Acc_Start()
****************************************************************************//**
*
* \brief
*  Initializes the Accelerometer. Meant to be a one time initialization / reset. 
* Use `$INSTANCE_NAME`_Acc_Wakeup if the sensor needs to be woken up from sleep
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
uint32 `$INSTANCE_NAME`_Acc_Start(void) {
    /* @TODO: Implement function */
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Acc_Stop()
****************************************************************************//**
*
* \brief
*  Shuts down the Acc completely. Disables are interrupts. Use `$INSTANCE_NAME`_Acc_Sleep
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
uint32 `$INSTANCE_NAME`_Acc_Stop(void) {
    /* @TODO: Implement function */
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Acc_Sleep()
****************************************************************************//**
*
* \brief
*  Puts the Accelerometer into the low power mode specified.
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
uint32 `$INSTANCE_NAME`_Acc_Sleep(uint8 powerMode) {
    switch(powerMode) {
        case `$INSTANCE_NAME`_ACC_PM_STANDBY:
        case `$INSTANCE_NAME`_ACC_PM_LP1:
        case `$INSTANCE_NAME`_ACC_PM_LP2:
        case `$INSTANCE_NAME`_ACC_PM_SUSPEND:
        case `$INSTANCE_NAME`_ACC_PM_DEEP_SUSPEND:
            break;
        /* Cannot sleep to Normal */
        case `$INSTANCE_NAME`_ACC_PM_NORMAL:
            return `$INSTANCE_NAME`_ERR_MODE_INVALID;
        /* Unknown power mode */
        default:
            return `$INSTANCE_NAME`_ERR_MODE_UNKNOWN; 

    }
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Acc_Wakeup()
****************************************************************************//**
*
* \brief
*  Wakes the Accelerometer up from sleep
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
uint32 `$INSTANCE_NAME`_Acc_Wakeup(void) {
    /* @TODO: Implement function */
    return `$INSTANCE_NAME`_ERR_OK;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Acc_Read()
****************************************************************************//**
*
* \brief
*  Reads the specified channels of the Accelerometer. Places result into the dataArray
*
* \param dataArray
*  Pointer to array to place the data into
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
//uint32 `$INSTANCE_NAME`_Acc_Read(uint16* dataArray, uint8 sensorChannels){
uint32 `$INSTANCE_NAME`_Acc_Read(ACC_DATA_T* accData){
    /* Read in the accelerometer data */
    uint8 msb = ZERO;
    uint8 lsb = ZERO;
    uint32 readError;
    // TODO: Scale correctly based on settings
    float scale = 0.0096f;
    /************** X Channel **************/
    /* Read the LSB first to lock MSB */
    readError = `$i2cReadFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_X_LSB, &lsb);
    if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
    /* Read the MSB */
    readError = `$i2cReadFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_X_MSB, &msb);
    /* Write X value */
    accData->Ax = scale * (float) `$INSTANCE_NAME`_twosComp_12To16( (msb << SHIFT_BYTE_HALF) | ((lsb >> SHIFT_BYTE_HALF) & MASK_NIBBLE_LOW) );
    /************** Y Channel **************/
    /* Read the LSB first to lock MSB */
    readError = `$i2cReadFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_Y_LSB, &lsb);
    if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
    /* Read the MSB */
    readError = `$i2cReadFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_Y_MSB, &msb);
    /* Write Y value */
    accData->Ay = scale *  (float) `$INSTANCE_NAME`_twosComp_12To16( (msb << SHIFT_BYTE_HALF) | ((lsb >> SHIFT_BYTE_HALF) & MASK_NIBBLE_LOW) );
    /************** Z Channel **************/
    /* Read the LSB first to lock MSB */
    readError = `$i2cReadFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_Z_LSB, &lsb);
    if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
    /* Read the MSB */
    readError = `$i2cReadFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_Z_MSB, &msb);
    /* Write Z value */
    accData->Az = scale * (float) `$INSTANCE_NAME`_twosComp_12To16( (msb << SHIFT_BYTE_HALF) | ((lsb >> SHIFT_BYTE_HALF) & MASK_NIBBLE_LOW) );
    
    /* Indicate success */
    return `$INSTANCE_NAME`_ERR_OK;
}

/* -------------------------- Gyroscope Functions -------------------------- */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Gyr_Start()
****************************************************************************//**
*
* \brief
*  Initializes the gyroscope. Meant to be a one time initialization / reset. 
* Use `$INSTANCE_NAME`_Gyr_Wakeup if the sensor needs to be woken up from sleep
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
uint32 `$INSTANCE_NAME`_Gyr_Start(void) {
    /* @TODO: Implement function */
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


/* -------------------------- Magnetometer Functions -------------------------- */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Mag_Start()
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
uint32 `$INSTANCE_NAME`_Mag_Start(void) {
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
