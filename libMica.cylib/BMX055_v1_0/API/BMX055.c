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
#include "`$INSTANCE_NAME`_Common.h"


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
    initError = `$INSTANCE_NAME`_Acc_Reset(&deviceState->acc);
    if(initError != `$INSTANCE_NAME`_ERR_OK){return initError;}
    /* Initialize Gyroscope */
    initError = `$INSTANCE_NAME`_Gyr_Reset(&deviceState->gyr);
    if(initError != `$INSTANCE_NAME`_ERR_OK){return initError;}
    /* Initialize Magnetomter */
    initError = `$INSTANCE_NAME`_Mag_Reset(&deviceState->mag);
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

/* [] END OF FILE */
