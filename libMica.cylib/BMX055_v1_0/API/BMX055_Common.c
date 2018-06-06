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
*   2018.06.06 CC - Document created
********************************************************************************/
#include "`$INSTANCE_NAME`_Common.h"

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


/* [] END OF FILE */
