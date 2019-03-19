/***************************************************************************
*                                 MICA  © 2019
*                           MIT BioInstrumentation Lab
*
* File: `$INSTANCE_NAME`.h
* Workspace: micaComponents
* Project: libMica
* Version: 1.0.0
* Authors: Craig Cheney
* 
*
* Brief:
*   Header for hash.c
*
* 2019.03.01  - Document Created
********************************************************************************/

/* Header Guard */
#ifndef `$INSTANCE_NAME`_H
    #define `$INSTANCE_NAME`_H
    /***************************************
    * Included files
    ***************************************/
    #include <stdint.h>
    /***************************************
    * Macro Definitions
    ***************************************/
//    #define  `$INSTANCE_NAME`_DEFINE_NAME             (0x00)  /**< DEFINE NAME Description */
    
    /***************************************
    * Enumerated Types
    ***************************************/
//    typedef enum {
//        typeVal1,                 /**< val1 Description */
//        typeVal2                  /**< val2 Description */
//    }  `$INSTANCE_NAME`_ENUM_NAME_T;
    
    /***************************************
    * Structures
    ***************************************/
//    typedef struct {
//        uint8_t param;            /**< param Description */
//    }  `$INSTANCE_NAME`_structName_S;
    
    /***************************************
    * Function declarations 
    ***************************************/
    uint32_t `$INSTANCE_NAME`_hash_djb2(char *str);
    uint32_t `$INSTANCE_NAME`_rand_xorshift32(uint32_t seed);
    
    
    void `$INSTANCE_NAME`_printHash(char* hashString, uint32_t hashValue, void (*printFn)(char *pszFmt, ...));
    

#endif /* `$INSTANCE_NAME`_H */
/* [] END OF FILE */
