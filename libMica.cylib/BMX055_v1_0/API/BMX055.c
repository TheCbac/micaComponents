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
//uint8 `$INSTANCE_NAME`_Acc_powerState = `$INSTANCE_NAME`_ACC_PM_NORMAL;
//uint8 `$INSTANCE_NAME`_Gyr_powerState = `$INSTANCE_NAME`_GYR_PM_NORMAL;
//uint8 `$INSTANCE_NAME`_Mag_powerState = `$INSTANCE_NAME`_MAG_PM_SUSPEND ;



/* -------------------------- Device Wide Functions -------------------------- */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start()
********************************************************************************
*
* \brief Starts all three devices (Acc, GYR, and MAG)
*
* \param deviceState
*  Pointer to struct to place the device settings into
*
* \return
*  An error code with the result of the start procedure. 
*  The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On Successful stop
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Start(`$INSTANCE_NAME`_STATE_T* deviceState) {
    /* Initialize Accelerometer */
    uint32 initError;
    initError = `$INSTANCE_NAME`_Acc_Start(&deviceState->acc);
    if(initError != `$INSTANCE_NAME`_ERR_OK){return initError;}
    /* Initialize Gyroscope */
    initError = `$INSTANCE_NAME`_Gyr_Start(&deviceState->gyr);
    if(initError != `$INSTANCE_NAME`_ERR_OK){return initError;}
    /* Initialize Magnetomter */
    initError = `$INSTANCE_NAME`_Mag_Start(&deviceState->mag);
    if(initError != `$INSTANCE_NAME`_ERR_OK){return initError;}
    /* Return success */
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop(`$INSTANCE_NAME`_STATE_T* deviceState)
********************************************************************************
*
* \brief Stop all three devices (Acc, GYR, and MAG)
*
* \param deviceState
*  Pointer to struct to place the device settings into
*
* \return
* uint8: An error code with the result of the Stop procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On Successful stop
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Stop(`$INSTANCE_NAME`_STATE_T* deviceState) {
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
* \param deviceState
*  Pointer to struct to place the device settings into
*
* \return
* uint8: An error code with the result of the sleep procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On Successful Sleep
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Sleep(`$INSTANCE_NAME`_STATE_T* deviceState) {
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
* \param deviceState
*  Pointer to struct to place the device settings into
*
* \return
* uint8: An error code with the result of the Wakeup procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On Successful Wakeup
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Wakeup(`$INSTANCE_NAME`_STATE_T* deviceState) {
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
* Function Name: `$INSTANCE_NAME`_testConnection()
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
uint32 `$INSTANCE_NAME`_testConnection(uint32* i2cError){
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
* \param accState
* Pointer to the state of the accelerometer
*
* \return  
* uint32: An error code with the result of the Start procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On successful Start
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Acc_Start(`$INSTANCE_NAME`_ACC_STATE_T* accState) {
    /* Initiate Accelerometer software reset */
    `$i2cWriteFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_BGW_SOFTRESET_REG, `$INSTANCE_NAME`_ACC_BGW_SOFTRESET_VAL);
    /* Wait necessary boot time */
    MICA_delayMs(`$INSTANCE_NAME`_ACC_BGW_SOFTRESET_MS);
    /* Set state values to the default */
    accState->powerState = `$INSTANCE_NAME`_ACC_PM_NORMAL;
    accState->scale = `$INSTANCE_NAME`_ACC_RANGE_2G_GAIN;
    accState->channels.X = true;
    accState->channels.Y = true;
    accState->channels.Z = true;
    /* Return Success */
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
* Function Name: `$INSTANCE_NAME`_Acc_SetPowerMode()
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
uint32 `$INSTANCE_NAME`_Acc_SetPowerMode(`$INSTANCE_NAME`_ACC_STATE_T* accState, `$INSTANCE_NAME`_ACC_POWER_T powerMode){
    uint8 powerRegVal;
    /* Current state */
    switch(accState->powerState){
        case `$INSTANCE_NAME`_ACC_PM_NORMAL:{
            /* Normal to Next state */
            switch(powerMode){
                /* Place device in standby mode (SUSPEND + LowPower Bit) */
                case `$INSTANCE_NAME`_ACC_PM_STANDBY: {
                    /* Set the lowpower bit in the LP register */
                    `$i2cWriteFunction`(`$INSTANCE_NAME`_ACC_ADDR,\
                                        `$INSTANCE_NAME`_ACC_PMU_LOW_POWER_REG,\
                                        `$INSTANCE_NAME`_ACC_PMU_LOW_POWER_LOWPOWER_MODE);
                    /* Prepare to place in Suspend mode */
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_SUSPEND;
                    break;   
                }
                /* Place device in Low Power 1 mode (LOW_POWER + !LowPower Bit) */
                case `$INSTANCE_NAME`_ACC_PM_LP1:{
                    /* Clear the lowpower bit in the LP register (@TODO: Should read and then clear) */
                    `$i2cWriteFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_PMU_LOW_POWER_REG, ZERO);
                    /* Prepare for low power mode */
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_LOWPOWER_EN;
                    break;
                }
                /* Place device in Low Power 2 mode (LOW_POWER + LowPower Bit) */
                case `$INSTANCE_NAME`_ACC_PM_LP2:{
                    /* Set the lowpower bit in the LP register (@TODO: Should read and then Set) */
                    `$i2cWriteFunction`(`$INSTANCE_NAME`_ACC_ADDR,\
                                        `$INSTANCE_NAME`_ACC_PMU_LOW_POWER_REG,\
                                        `$INSTANCE_NAME`_ACC_PMU_LOW_POWER_LOWPOWER_MODE);
                    /* Prepare for low power mode */
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_LOWPOWER_EN;
                    break;
                }
                /* Place device in Suspend mode (SUSPEND + !LowPower Bit) */
                case `$INSTANCE_NAME`_ACC_PM_SUSPEND:{
                    /* Clear the lowpower bit in the LP register (@TODO: Should read and then clear) */
                    `$i2cWriteFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_PMU_LOW_POWER_REG, ZERO);
                    /* Prepare for suspend */
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_SUSPEND;
                    break;
                }
                /* Place device in Deep Suspend mode (DEEP_SUSPEND) */
                case `$INSTANCE_NAME`_ACC_PM_DEEP_SUSPEND:{
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_DEEP_SUSPEND; 
                    break;
                }
                /* Invalid Power state */
                default:{
                    return `$INSTANCE_NAME`_ERR_MODE_INVALID;
                }
            }
            break;
        } /* End `$INSTANCE_NAME`_ACC_PM_NORMAL */
        case `$INSTANCE_NAME`_ACC_PM_STANDBY:{
            /* Standby to Next state */
            switch(powerMode){
                /* Exit Standby (NORMAL) */
                case `$INSTANCE_NAME`_ACC_PM_NORMAL:{
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_NORMAL;
                    break;
                }
                /* Place device in Low Power 2 mode (LOW_POWER + LowPower Bit) */
                case `$INSTANCE_NAME`_ACC_PM_LP2:{
                    /* Prepare for low power mode (Low Power bit is already set in standby) */
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_LOWPOWER_EN;
                    break;
                }
                /* Place device in Deep Suspend mode (DEEP_SUSPEND) */
                case `$INSTANCE_NAME`_ACC_PM_DEEP_SUSPEND:{
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_DEEP_SUSPEND; 
                    break;
                }
                /* Invalid Power state */
                default:{
                    return `$INSTANCE_NAME`_ERR_MODE_INVALID;
                }
            }
            break;
        } /* End `$INSTANCE_NAME`_ACC_PM_STANDBY */
        case `$INSTANCE_NAME`_ACC_PM_LP1:{
            /* Low Power 1 to Next state */
            switch(powerMode){
                /* Exit LP1 to NORMAL */
                case `$INSTANCE_NAME`_ACC_PM_NORMAL:{
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_NORMAL;
                    break;
                }
                /* Place device in SUSPEND mode (SUSPEND + !LowPower Bit) */
                case `$INSTANCE_NAME`_ACC_PM_SUSPEND:{
                    /* Prepare for low power mode (Low Power bit is already cleared in LP1) */
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_SUSPEND;
                    break;
                }
                /* Place device in Deep Suspend mode (DEEP_SUSPEND) */
                case `$INSTANCE_NAME`_ACC_PM_DEEP_SUSPEND:{
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_DEEP_SUSPEND; 
                    break;
                }
                /* Invalid Power state */
                default:{
                    return `$INSTANCE_NAME`_ERR_MODE_INVALID;
                }
            }
            break;
        } /*End `$INSTANCE_NAME`_ACC_PM_LP1 */
        case `$INSTANCE_NAME`_ACC_PM_LP2:{
            /* Low Power 2 to Next state */
            switch(powerMode){
                /* Exit LP2 to NORMAL */
                case `$INSTANCE_NAME`_ACC_PM_NORMAL:{
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_NORMAL;
                    break;
                }
                /* Place device in STANDBY mode (LowPower_En + LowPower Bit) */
                case `$INSTANCE_NAME`_ACC_PM_SUSPEND:{
                    /* Prepare for low power mode (Low Power bit is already set in LP2) */
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_SUSPEND;
                    break;
                }
                /* Place device in Deep Suspend mode (DEEP_SUSPEND) */
                case `$INSTANCE_NAME`_ACC_PM_DEEP_SUSPEND:{
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_DEEP_SUSPEND; 
                    break;
                }
                /* Invalid Power state */
                default:{
                    return `$INSTANCE_NAME`_ERR_MODE_INVALID;
                }
            }
            break;
        } /*End `$INSTANCE_NAME`_ACC_PM_LP2 */
        case `$INSTANCE_NAME`_ACC_PM_SUSPEND:{
            /* Suspend to Next state */
            switch(powerMode){
                /* Exit LP2 to NORMAL */
                case `$INSTANCE_NAME`_ACC_PM_NORMAL:{
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_NORMAL;
                    break;
                }
                /* Place device in LP1 mode (LowPower_En + !LowPower Bit) */
                case `$INSTANCE_NAME`_ACC_PM_SUSPEND:{
                    /* Prepare for low power mode (Low Power bit is already cleared in LP1) */
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_LOWPOWER_EN;
                    break;
                }
                /* Place device in Deep Suspend mode (DEEP_SUSPEND) */
                case `$INSTANCE_NAME`_ACC_PM_DEEP_SUSPEND:{
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_DEEP_SUSPEND; 
                    break;
                }
                /* Invalid Power state */
                default:{
                    return `$INSTANCE_NAME`_ERR_MODE_INVALID;
                }
            }
            break;
        } /*End `$INSTANCE_NAME`_ACC_PM_SUSPEND */
        case `$INSTANCE_NAME`_ACC_PM_DEEP_SUSPEND:{
            /* Deep Suspend to Next state */
            switch(powerMode){
                /* Exit Deep Suspend to NORMAL */
                case `$INSTANCE_NAME`_ACC_PM_NORMAL:{
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_NORMAL;
                    break;
                }
                /* Invalid Power state */
                default:{
                    return `$INSTANCE_NAME`_ERR_MODE_INVALID;
                }
            }
            break;
        } /*End `$INSTANCE_NAME`_ACC_PM_DEEP_SUSPEND */
    }
    /* Write to the low power register value selected from above */
    `$i2cWriteFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_PMU_LPW_REG, powerRegVal);
    /* Update the state (valid if reached this point) */
    accState->powerState = powerMode;
    /* Return Success */
    return `$INSTANCE_NAME`_ERR_OK;
}

///*******************************************************************************
//* Function Name: `$INSTANCE_NAME`_Acc_Sleep()
//****************************************************************************//**
//*
//* \brief
//*  Puts the Accelerometer into the low power mode specified.
//*
//* \param powerMode
//*  Power mode to place the device into 
//*
//* \return  
//* uint32: An error code with the result of the Sleep procedure. 
//* The possible error codes are:
//*
//*  Errors codes                             | Description
//*   ------------                            | -----------
//*   `$INSTANCE_NAME`_ERR_OK                 | On successful Sleep
//*   `$INSTANCE_NAME`_ERR_MODE_INVALID       | An invalid power mode was specified
//*   `$INSTANCE_NAME`_ERR_MODE_UNKNOWN       | An unknown power mode was specified
//*******************************************************************************/
//uint32 `$INSTANCE_NAME`_Acc_Sleep(uint8 powerMode) {
//    switch(powerMode) {
//        case `$INSTANCE_NAME`_ACC_PM_STANDBY:
//        case `$INSTANCE_NAME`_ACC_PM_LP1:
//        case `$INSTANCE_NAME`_ACC_PM_LP2:
//        case `$INSTANCE_NAME`_ACC_PM_SUSPEND:
//        case `$INSTANCE_NAME`_ACC_PM_DEEP_SUSPEND:
//            break;
//        /* Cannot sleep to Normal */
//        case `$INSTANCE_NAME`_ACC_PM_NORMAL:
//            return `$INSTANCE_NAME`_ERR_MODE_INVALID;
//        /* Unknown power mode */
//        default:
//            return `$INSTANCE_NAME`_ERR_MODE_UNKNOWN; 
//
//    }
//    return `$INSTANCE_NAME`_ERR_OK;
//}

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
* Function Name: `$INSTANCE_NAME`_Acc_Int2Float
****************************************************************************//**
*
* \brief
*  Converts an accelerometer data sample from int16 to float type. 
*
* \param State
*  Pointer to the Struct containing the settings of the device in order to scale correctly
*
* \param intData
*  Pointer to the int16 data to be converted
*       
* \param floatData 
*   Pointer to the output data in float format 
*
* \return 
* uint32: An error code with the result of the conversion procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On successful operation
*   `$INSTANCE_NAME`_ERR_CHANNELS_NONE      | No channels indicated for conversion
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Acc_Int2Float(`$INSTANCE_NAME`_ACC_STATE_T* state, ACC_DATA_T* intData, ACC_DATA_F* floatData){
    /* Extract channels */
    CHANNELS_T chans = state->channels;
    if( (!chans.X) && (!chans.Y) && (!chans.Z) ){
        return `$INSTANCE_NAME`_ERR_CHANNELS_NONE;
    }
    /* Gain of the accelerometer */
    float gain = state->scale;
    /* Convert to float */
    if(chans.X){ floatData->Ax = gain * (float) intData->Ax; }
    if(chans.Y){ floatData->Ay = gain * (float) intData->Ay; }
    if(chans.Z){ floatData->Az = gain * (float) intData->Az; }
    /* Return success */
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_Acc_Float2Int(); 
****************************************************************************//**
*
* \brief
*  Converts an accelerometer data sample from float to int16 type. 
*
* \param State
*  Pointer to the Struct containing the settings of the device in order to scale correctly
*
* \param floatData
*  Pointer to the float data to be converted
*       
* \param intData 
*   Pointer to the output data in int16 format 
*
* \return 
* uint32: An error code with the result of the conversion procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On successful operation
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Acc_Float2Int(`$INSTANCE_NAME`_ACC_STATE_T* state, ACC_DATA_F* floatData, ACC_DATA_T* intData) {
    /* Extract channels */
    CHANNELS_T chans = state->channels;
    /* Ensure at least one channel is enabled  */
    if( (!chans.X) && (!chans.Y) && (!chans.Z) ){
        return `$INSTANCE_NAME`_ERR_CHANNELS_NONE;
    }
    /* Gain of the accelerometer */
    float gain = state->scale;
    /* Convert to int */
    if(chans.X){ intData->Ax = (int16) (floatData->Ax / gain); }
    if(chans.Y){ intData->Ay = (int16) (floatData->Ay / gain); }
    if(chans.Z){ intData->Az = (int16) (floatData->Az / gain); }
    /* Return success */
    return `$INSTANCE_NAME`_ERR_OK;
}

///*******************************************************************************
//* Function Name: `$INSTANCE_NAME`_Acc_Read()
//****************************************************************************//**
//*
//* \brief
//*  Reads the specified channels of the Accelerometer. Places result into the dataArray
//*
//* \param state
//*  Pointer to the state of the accelerometer
//*
//* \param accData
//*  Pointer to struct to place the data into
//*
//* \return 
//* uint32: An error code with the result of the read procedure. 
//* The possible error codes are:
//*
//*  Errors codes                             | Description
//*   ------------                            | -----------
//*   `$INSTANCE_NAME`_ERR_OK                 | On successful operation
//*   `$INSTANCE_NAME`_ERR_CHANNELS_NONE      | Data was not requested from any channels
//*
//*******************************************************************************/
//uint32 `$INSTANCE_NAME`_Acc_Read(`$INSTANCE_NAME`_ACC_STATE_T* state, ACC_DATA_T* accData){
//        /* Extract channels */
//    CHANNELS_T chans = state->channnels;
//    /* Ensure at least one channel is enabled  */
//    if( (!chans.X) && (!chans.Y) && (!chans.Z) ){
//        return `$INSTANCE_NAME`_ERR_CHANNELS_NONE;
//    }
//    /* Read in the accelerometer data */
//    uint8 msb = ZERO;
//    uint8 lsb = ZERO;
//    uint32 readError;
//    // TODO: Scale correctly based on settings
//    float scale = 0.0096f;
//    /************** X Channel **************/
//    /* Read the LSB first to lock MSB */
//    readError = `$i2cReadFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_X_LSB, &lsb);
//    if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
//    /* Read the MSB */
//    readError = `$i2cReadFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_X_MSB, &msb);
//    /* Write X value */
//    accData->Ax = scale * (float) `$INSTANCE_NAME`_twosComp_12To16( (msb << SHIFT_BYTE_HALF) | ((lsb >> SHIFT_BYTE_HALF) & MASK_NIBBLE_LOW) );
//    /************** Y Channel **************/
//    /* Read the LSB first to lock MSB */
//    readError = `$i2cReadFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_Y_LSB, &lsb);
//    if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
//    /* Read the MSB */
//    readError = `$i2cReadFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_Y_MSB, &msb);
//    /* Write Y value */
//    accData->Ay = scale *  (float) `$INSTANCE_NAME`_twosComp_12To16( (msb << SHIFT_BYTE_HALF) | ((lsb >> SHIFT_BYTE_HALF) & MASK_NIBBLE_LOW) );
//    /************** Z Channel **************/
//    /* Read the LSB first to lock MSB */
//    readError = `$i2cReadFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_Z_LSB, &lsb);
//    if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
//    /* Read the MSB */
//    readError = `$i2cReadFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_Z_MSB, &msb);
//    /* Write Z value */
//    accData->Az = scale * (float) `$INSTANCE_NAME`_twosComp_12To16( (msb << SHIFT_BYTE_HALF) | ((lsb >> SHIFT_BYTE_HALF) & MASK_NIBBLE_LOW) );
//    
//    /* Indicate success */
//    return `$INSTANCE_NAME`_ERR_OK;
//}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Acc_Read()
****************************************************************************//**
*
* \brief
*  Reads the specified channels of the Accelerometer. Places result into the dataArray
*
* \param state
*  Pointer to the state of the accelerometer
*
* \param accData
*  Pointer to struct to place the data into
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
uint32 `$INSTANCE_NAME`_Acc_Read(`$INSTANCE_NAME`_ACC_STATE_T* state, ACC_DATA_T* accData){
    /* Extract channels */
    CHANNELS_T chans = state->channels;
    /* Ensure at least one channel is enabled  */
    if( (!chans.X) && (!chans.Y) && (!chans.Z) ){
        return `$INSTANCE_NAME`_ERR_CHANNELS_NONE;
    }
    /* Read in the accelerometer data */
    uint8 msb = ZERO;
    uint8 lsb = ZERO;
    uint32 readError;
    /************** X Channel **************/
    if(chans.X){
        /* Read the LSB first to lock MSB */
        readError = `$i2cReadFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_X_LSB, &lsb);
        if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
        /* Read the MSB */
        readError = `$i2cReadFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_X_MSB, &msb);
        if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
        /* Write X value */
        accData->Ax = `$INSTANCE_NAME`_twosComp_12To16( (msb << SHIFT_BYTE_HALF) | ((lsb >> SHIFT_BYTE_HALF) & MASK_NIBBLE_LOW) );
    }
    /************** Y Channel **************/
    if(chans.Y){
        /* Read the LSB first to lock MSB */
        readError = `$i2cReadFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_Y_LSB, &lsb);
        if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
        /* Read the MSB */
        readError = `$i2cReadFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_Y_MSB, &msb);
        if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
        /* Write Y value */
        accData->Ay = `$INSTANCE_NAME`_twosComp_12To16( (msb << SHIFT_BYTE_HALF) | ((lsb >> SHIFT_BYTE_HALF) & MASK_NIBBLE_LOW) );
    }
    /************** Z Channel **************/
    if(chans.Z){
        /* Read the LSB first to lock MSB */
        readError = `$i2cReadFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_Z_LSB, &lsb);
        if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
        /* Read the MSB */
        readError = `$i2cReadFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_Z_MSB, &msb);
        if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
        /* Write Z value */
        accData->Az = `$INSTANCE_NAME`_twosComp_12To16( (msb << SHIFT_BYTE_HALF) | ((lsb >> SHIFT_BYTE_HALF) & MASK_NIBBLE_LOW) );
    }
    /***************************************/
    /* Indicate success */
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Acc_Readf()
****************************************************************************//**
*
* \brief
*  Reads the specified channels of the Accelerometer and converts to a floating
*  point number.
*
* \param state
*  Pointer to the state of the Accelerometer\
*
* \param accData
*  Pointer to struct to place the data into
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
uint32 `$INSTANCE_NAME`_Acc_Readf(`$INSTANCE_NAME`_ACC_STATE_T* state, ACC_DATA_F* accData){
    /* Read from the device */
    ACC_DATA_T accIntData;
    uint32 readError = `$INSTANCE_NAME`_Acc_Read(state, &accIntData);
    if(readError != `$INSTANCE_NAME`_ERR_OK) {return readError;}
    /* Convert to a float */
    readError = `$INSTANCE_NAME`_Acc_Int2Float(state, &accIntData, accData); 
    return readError;
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
