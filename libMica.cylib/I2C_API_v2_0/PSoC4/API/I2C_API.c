/***************************************************************************
*                                       MICA
* File: I2C_API.c
* Workspace: micaComponents
* Project Name: libMica
* Version: v2.0
* Author: Craig Cheney
*
* Brief:
*   Extension for the MICA I2C API
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.05.03 CC - Transitioned to I2C component v4 (timeout)
*   2018.03.14 CC - Document created
********************************************************************************/
#include "`$INSTANCE_NAME`.h"
#include "`$i2cInclude`.h"

/*******************************************************************************
* Function Name:  `$INSTANCE_NAME`_Write()
****************************************************************************//**
* \brief
*  Writes a byte to data to a given register of the target I2C slave 
*
* \param deviceAddr
*  Address of the I2C slave device
*
* \param regAddr
*  Address of register to write to for the slave device  
*       
* \param val
*  Byte of data to be written the slave's register
*
* \return
* An error code with the result of the Write procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On successful operation
*   Error from I2C Component, `$i2cInstanceName`
*
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_Write(uint8_t deviceAddr, uint8_t regAddr, uint8_t val) {
    /* Start, Slave Address & Write bit */
    uint32_t result = `$i2cInstanceName`_I2CMasterSendStart(deviceAddr, `$i2cInstanceName`_I2C_WRITE_XFER_MODE, `$i2cInstanceName`_TIMEOUT_WRITE );
    if (result != `$INSTANCE_NAME`_ERR_OK) { return result;}
    /* SUB Address */
    result = `$i2cInstanceName`_I2CMasterWriteByte(regAddr, `$i2cInstanceName`_TIMEOUT_WRITE);
    if (result != `$INSTANCE_NAME`_ERR_OK) { return result;}
    /* DATA */
    `$i2cInstanceName`_I2CMasterWriteByte(val, `$i2cInstanceName`_TIMEOUT_WRITE);
    if (result != `$INSTANCE_NAME`_ERR_OK) { return result;}
    /* STOP Bit */
    `$i2cInstanceName`_I2CMasterSendStop(`$i2cInstanceName`_TIMEOUT_WRITE);
    if (result != `$INSTANCE_NAME`_ERR_OK) { return result;}
    /* Indicate successs */
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name:  `$INSTANCE_NAME`_WriteCmd()
****************************************************************************//**
* \brief
*  Sends a command to the target device, with no corresponding data
*
* \param deviceAddr
*  Address of the I2C slave device
*
* \param cmd
*  Command to write
*       
* \return
* An error code with the result of the Write procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On successful operation
*   Error from I2C Component, `$i2cInstanceName`
*
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_WriteCmd(uint8_t deviceAddr, uint8_t cmd){
    /* Start, Slave Address & Write bit */
    uint32_t result = `$i2cInstanceName`_I2CMasterSendStart(deviceAddr, `$i2cInstanceName`_I2C_WRITE_XFER_MODE, `$i2cInstanceName`_TIMEOUT_WRITE );
    if (result != `$INSTANCE_NAME`_ERR_OK) { return result;}
    /* Command */
    result = `$i2cInstanceName`_I2CMasterWriteByte(cmd, `$i2cInstanceName`_TIMEOUT_WRITE);
    if (result != `$INSTANCE_NAME`_ERR_OK) { return result;}
    /* STOP Bit */
    `$i2cInstanceName`_I2CMasterSendStop(`$i2cInstanceName`_TIMEOUT_WRITE);
    if (result != `$INSTANCE_NAME`_ERR_OK) { return result;}
    /* Indicate successs */
    return `$INSTANCE_NAME`_ERR_OK;
    
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME_read()
****************************************************************************//**
* \brief
*  Reads a given register of the target I2C device and places that value into the pointer passed in. *** In 
*  current implementation, this is a blocking function ***
*
* \param deviceAddr
*  Address of the I2C slave devices
*
* \param regAddr 
*  Address of register to read from.
*
* \param readVal
* Pointer to place the results into
*   
* \return
* An error code with the result of the Read procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On successful operation
*   `$INSTANCE_NAME`_ERR_READ               | An error occured during reading
*   Error from I2C Component, `$i2cInstanceName`
*
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_Read(uint8_t deviceAddr, uint8_t regAddr, uint8_t * readVal) {
    /* Start, Slave Address & Write bit */
    uint32_t opResult = `$i2cInstanceName`_I2CMasterSendStart(deviceAddr, `$i2cInstanceName`_I2C_WRITE_XFER_MODE, `$i2cInstanceName`_TIMEOUT_WRITE);
    /* Return error and error code if operation failed */
    if (opResult != `$i2cInstanceName`_I2C_MSTR_NO_ERROR ) { goto displayError; } 
    
    /* SUB Address */
    opResult = `$i2cInstanceName`_I2CMasterWriteByte(regAddr, `$i2cInstanceName`_TIMEOUT_WRITE);
    /* Return error and error code if operation failed */
    if (opResult != `$i2cInstanceName`_I2C_MSTR_NO_ERROR ) { goto displayError; } 
    /* Restart, Slave address & read bit */
    opResult = `$i2cInstanceName`_I2CMasterSendRestart(deviceAddr, `$i2cInstanceName`_I2C_READ_XFER_MODE, `$i2cInstanceName`_TIMEOUT_WRITE);
    /* Return error and error code if operation failed */
    if (opResult != `$i2cInstanceName`_I2C_MSTR_NO_ERROR ) { goto displayError; } 
    
    /* Place to return data */
    uint8_t rdByte;
    /* Read the data */
    opResult = `$i2cInstanceName`_I2CMasterReadByte(`$i2cInstanceName`_I2C_NAK_DATA, &rdByte, `$i2cInstanceName`_TIMEOUT_WRITE);
    /* Return error and error code if operation failed */
    if (opResult != `$i2cInstanceName`_I2C_MSTR_NO_ERROR ) { goto displayError; } 
    /* Place the opResult into the pointer */
    *readVal = (uint8_t) rdByte;
    
    /* Send the stop bit */
    opResult = `$i2cInstanceName`_I2CMasterSendStop(`$i2cInstanceName`_TIMEOUT_WRITE);
    /* Return error and error code if operation failed */
    if (opResult != `$i2cInstanceName`_I2C_MSTR_NO_ERROR ) { goto displayError; } 
    
    
    /* Indicate successs */
    return `$INSTANCE_NAME`_ERR_OK;
    
/* Put the error code in readVal & return failed */
displayError:
    /* Place hardware specific value into the readVal */
    *readVal = opResult;
    /* return write failed */
    return `$INSTANCE_NAME`_ERR_READ;
//    
//    
//    /* SUB Address */
//    result = `$i2cInstanceName`_I2CMasterWriteByte(regAddr, `$i2cInstanceName`_TIMEOUT_WRITE);
//    if (result != `$INSTANCE_NAME`I2C_MSTR_NO_ERROR ) { return result;}
//    /* Restart, Slave address & read bit */
//    result = `$i2cInstanceName`_I2CMasterSendRestart(deviceAddr, `$i2cInstanceName`_I2C_READ_XFER_MODE, `$i2cInstanceName`_TIMEOUT_WRITE);
//    if (result != `$INSTANCE_NAME`I2C_MSTR_NO_ERROR ) { return result;}
//    
//    /* Read the data */
//    uint8_t rdByte; // TODO: implement the read byte functionality
//    uint32_t readErr = `$i2cInstanceName`_I2CMasterReadByte(`$i2cInstanceName`_I2C_NAK_DATA, &rdByte, `$i2cInstanceName`_TIMEOUT_WRITE);
//    if (readErr & `$INSTANCE_NAME`_MASK_READ_ERR) {return `$INSTANCE_NAME`_ERR_READ;}
//    /* Place the result into the pointer */
//    *readVal = (uint8_t) rdByte;
//    
//    /* Send the stop bit */
//    result = `$i2cInstanceName`_I2CMasterSendStop(`$i2cInstanceName`_TIMEOUT_WRITE);
//    if (result != `$INSTANCE_NAME`_ERR_OK) { return result;}
//    /* Indicate successs */
//    return `$INSTANCE_NAME`_ERR_OK;
}


/* [] END OF FILE */
