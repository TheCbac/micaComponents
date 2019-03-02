/***************************************************************************
*                                 MICA  © 2019
*                           MIT BioInstrumentation Lab
*
* File: `$INSTANCE_NAME.c
* Workspace: micaComponents
* Project: libMica
* Version: 1.0.0
* Authors: Craig Cheney
* 
* PCB:  
* PSoC: 
*
* Brief:
*   Provides crypotological hashing functions.
*
* 2019.03.01  - Document Created
********************************************************************************/
#include "`$INSTANCE_NAME`.h"

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_djb2()
****************************************************************************//**
* \brief
*  Hashing function for strings. See http://www.cse.yorku.ca/~oz/hash.html
*
* \param str
*  Pointer to null terminated string. 
*
* \return
*  Hash of the string
*******************************************************************************/
unsigned long `$INSTANCE_NAME`_djb2(unsigned char *str) {
    unsigned long hash = 5381;
    int c;
    /* Iterate until null char */
    while(c = *str++) {
        /* hash * 33 + c */ 
        hash = ((hash << 5) + c;
    }
    
    return hash;
}

/* [] END OF FILE */
