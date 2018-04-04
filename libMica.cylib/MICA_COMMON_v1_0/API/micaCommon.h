/***************************************************************************
*                                       MICA
* File: micaCommon.h
* Workspace: micaCompnents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   common Definitions used in MICA
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.03.03 CC - Document created
********************************************************************************/
/* Header Guard */
#ifndef `$INSTANCE_NAME`_H
    #define `$INSTANCE_NAME`_H
    /***************************************
    * Macro Definitions
    ***************************************/
    #define ZERO            (0u)    /**< Constant 0 */
    #define ONE             (1u)    /**< Constant 1 */
    #define TWO             (2u)    /**< Constant 2 */
    #define THREE           (3u)    /**< Constant 3 */
    #define FOUR            (4u)    /**< Constant 4 */
    #define FIVE            (5u)    /**< Constant 5 */
    #define SIX             (6u)    /**< Constant 6 */
    #define SEVEN           (7u)    /**< Constant 7 */
    #define EIGHT           (8u)    /**< Constant 8 */
    #define NINE            (9u)    /**< Constant 9 */
    #define NULL_OCTET      (0u)    /**< Null Octet */
    
    #define BITS_SINGLE_BIT         (0x01u)             /**< Single bit mask */
    #define BITS_ONE_NIBBLE         (4u)                /**< Number of bits in a nibble */
    #define BITS_ONE_BYTE           (8u)                /**< Number of bits in one byte */
    #define BITS_TWO_BYTES          (16u)               /**< Number of bits in two bytes */
    #define BITS_THREE_BYTES        (24u)               /**< Number of bits in three bytes */
    
    #define SHIFT_BYTE_HALF         (BITS_ONE_NIBBLE)   /**< Half Byte Shift*/
    #define SHIFT_BYTE_ONE          (BITS_ONE_BYTE)     /**< One Byte Shift*/
    #define SHIFT_BYTE_TWO          (BITS_TWO_BYTES)    /**< Two Byte Shift*/
    #define SHIFT_BYTE_THREE        (BITS_THREE_BYTES)  /**< Three Byte Shift*/
    
    #define MASK_NIBBLE_HIGH        (0xF0u)             /**< High nibble mask*/
    #define MASK_NIBBLE_LOW         (0x0Fu)             /**< Low nibble mask*/
    #define MASK_BYTE_ONE           (0xFFu)             /**< One byte mask*/
    #define MASK_BYTE_TWO           (0xFFFFu)           /**< Two byte mask*/
    #define MASK_BYTE_THREE         (0xFFFFFFu)         /**< Three byte mask*/
    
    #define MASK_BIT_ONE            (0x1u)              /**< One bit mask*/
    #define MASK_BIT_TWELVE         (0xFFFu)            /**< One and a half byte mask*/
    #define MASK_ODD                (MASK_BIT_ONE)      /**< Odd mask*/
    
    #define INDEX_ZERO_CORRECT      (1u)                /**< Corrects for a zero indexed array*/
    
    #define MICA_TEST_INFINITE      (0u)                /**< Run test an infinite number of times  */

#endif /* `$INSTANCE_NAME`_H */

/* [] END OF FILE */

