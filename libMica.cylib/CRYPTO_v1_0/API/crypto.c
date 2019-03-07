/***************************************************************************
*                                 MICA  © 2019
*                           MIT BioInstrumentation Lab
*
* File: `$INSTANCE_NAME`.c
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
* Function Name: `$INSTANCE_NAME`_hash_djb2()
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
uint32_t `$INSTANCE_NAME`_hash_djb2(char *str) {
    uint32_t hash = 5381;
    int c;
    /* Iterate until null char */
    while( (c = *str++) ) {
        /* hash * 33 + c */ 
        hash = ((hash << 5) + c);
    }
    
    return hash;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_printHash()
****************************************************************************//**
* \brief
*  Prints a hash
*
* \param hashString [in]
*  Packet to string that was hashed
*
* \param hashVaule [in]
* Value that was hashed 
* 
* \param fn [in]
*   Print function to use to display results
* 
* \return
*  None
*******************************************************************************/
  void `$INSTANCE_NAME`_printHash(char* hashString, uint32_t hashValue, void (*printFn)(char *pszFmt, ...)){
    printFn("\r\n");
    printFn(hashString);
    printFn(" hashed to %d", hashValue);
}


/* [] END OF FILE */
