/***************************************************************************
*                                       MICA
* File: packets.h
* Workspace: micaComponents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   Binary packet specification for MICA
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.04.19 CC - Document created
********************************************************************************/
/* Header Guard */
#ifndef `$INSTANCE_NAME`_H
    #define `$INSTANCE_NAME`_H
    /***************************************
    * Included files
    ***************************************/
    #include <stdbool.h>
    #include "cytypes.h"
    /***************************************
    * Macro Definitions
    ***************************************/
    #define `$INSTANCE_NAME`_LEN_SYM_START       (1u) /**< Length of the Start of Packet Symbol */
    #define `$INSTANCE_NAME`_LEN_MODULE_ID       (1u) /**< Length of the Module ID */
    #define `$INSTANCE_NAME`_LEN_PAYLOAD_LEN     (2u) /**< Length of the Payload Length */
    #define `$INSTANCE_NAME`_LEN_CMD             (1u) /**< Length of the Command */
    #define `$INSTANCE_NAME`_LEN_CHECKSUM        (2u) /**< Length of the checksum */
    #define `$INSTANCE_NAME`_LEN_SYM_END         (1u) /**< Length of the End of Packet Symbol */
    #define `$INSTANCE_NAME`_LEN_HEADER          (`$INSTANCE_NAME`_LEN_SYM_START + `$INSTANCE_NAME`_LEN_MODULE_ID + `$INSTANCE_NAME`_LEN_PAYLOAD_LEN  + `$INSTANCE_NAME`_LEN_CMD) /**< Length of the packet overhead, for checksum validation */
    #define `$INSTANCE_NAME`_LEN_FOOTER          (`$INSTANCE_NAME`_LEN_CHECKSUM + `$INSTANCE_NAME`_LEN_SYM_END) /**< Length of the footer */
    #define `$INSTANCE_NAME`_LEN_OVERHEAD        (`$INSTANCE_NAME`_LEN_HEADER + `$INSTANCE_NAME`_LEN_FOOTER) /**< Total length of the packet overhead */
    #define `$INSTANCE_NAME`_LEN_MAX_PAYLOAD     (1000) /**< Maximum length of the payload */
    #define `$INSTANCE_NAME`_LEN_MAX_PACKET      (`$INSTANCE_NAME`_LEN_OVERHEAD + `$INSTANCE_NAME`_LEN_MAX_PAYLOAD) /**< Maximum length of the entire packet */

    #define `$INSTANCE_NAME`_INDEX_START         (0u) /**< Index of the start of packet symbol*/
    #define `$INSTANCE_NAME`_INDEX_MODULE_ID     (1u) /**< Index of the module to talk to in the packet */
    #define `$INSTANCE_NAME`_INDEX_CMD           (2u) /**< Index of the command to issue */
    #define `$INSTANCE_NAME`_INDEX_LEN_MSB       (3u) /**< Index of the Payload length MSB */
    #define `$INSTANCE_NAME`_INDEX_LEN_LSB       (4u) /**< Index of the Payload length LSB */
    #define `$INSTANCE_NAME`_INDEX_PAYLOAD       (5u) /**< Index of the packet Payload */

    #define `$INSTANCE_NAME`_SYM_START           (0x01u) /**< Start of Packet Symbol. All packets must begin with this symbol */
    #define `$INSTANCE_NAME`_SYM_END             (0xAAu) /**< End of Packet Symbol. All packets must end with this symbol */

    #define `$INSTANCE_NAME`_ID_MODULE_ENERGY    (0u)    /**< ID of the Energy Module */
    #define `$INSTANCE_NAME`_ID_MODULE_ACTUATION (1u)    /**< ID of the Actuation Module */
    #define `$INSTANCE_NAME`_ID_MODULE_POWER     (2u)    /**< ID of the Power Module */
    #define `$INSTANCE_NAME`_ID_MODULE_SENSING   (3u)    /**< ID of the Sensing Module */
    #define `$INSTANCE_NAME`_ID_MODULE_COMM      (4u)    /**< ID of the Communications Module */
    #define `$INSTANCE_NAME`_ID_MODULE_CONTROL   (5u)    /**< ID of the Contorl Module */
    #define `$INSTANCE_NAME`_ID_MODULE_MAX       (5u)    /**< Maximum value allowed */
     /* **** RESPONSES **** */
    #define `$INSTANCE_NAME`_RESP_INDEX_START    (0u) /**< Index of the start of response symbol*/
    #define `$INSTANCE_NAME`_RESP_INDEX_MODULE_ID (1u) /**< Index module that is responding*/
    #define `$INSTANCE_NAME`_RESP_INDEX_STATUS   (2u) /**< Index of the response status*/
    #define `$INSTANCE_NAME`_RESP_INDEX_LEN_MSB  (3u) /**< Index of the response payload length MSB */
    #define `$INSTANCE_NAME`_RESP_INDEX_LEN_LSB  (4u) /**< Index of the response payload length LSB*/
    #define `$INSTANCE_NAME`_RESP_INDEX_PAYLOAD  (5u) /**< Index of the response payload */

    #define `$INSTANCE_NAME`_RESP_LEN_SYM_START   (1u) /**< Length of the response Start of Packet Symbol */
    #define `$INSTANCE_NAME`_RESP_LEN_MODULE_ID   (1u) /**< Length of the module ID */        
    #define `$INSTANCE_NAME`_RESP_LEN_STATUS      (1u) /**< Length of the response Status */        
    #define `$INSTANCE_NAME`_RESP_LEN_PAYLOAD_LEN (2u) /**< Length of the response Payload Length */
    #define `$INSTANCE_NAME`_RESP_LEN_CHECKSUM    (2u) /**< Length of the response checksum */
    #define `$INSTANCE_NAME`_RESP_LEN_SYM_END     (1u) /**< Length of the response End of Packet Symbol */
    

    #define `$INSTANCE_NAME`_RESP_LEN_HEADER     (`$INSTANCE_NAME`_RESP_LEN_SYM_START + `$INSTANCE_NAME`_RESP_LEN_MODULE_ID + `$INSTANCE_NAME`_RESP_LEN_STATUS + `$INSTANCE_NAME`_RESP_LEN_PAYLOAD_LEN) /**< Length of the response packet header */
    #define `$INSTANCE_NAME`_RESP_LEN_FOOTER     (`$INSTANCE_NAME`_RESP_LEN_CHECKSUM + `$INSTANCE_NAME`_RESP_LEN_SYM_END) /**< Length of the response footer */
    #define `$INSTANCE_NAME`_RESP_LEN_OVERHEAD   (`$INSTANCE_NAME`_RESP_LEN_HEADER + `$INSTANCE_NAME`_RESP_LEN_FOOTER) /**< Length of the response overhead */   
    #define `$INSTANCE_NAME`_RESP_LEN_MAX_PAYLOAD (100) /**< Maximum length of the payload */     
    #define `$INSTANCE_NAME`_RESP_LEN_MAX_PACKET (`$INSTANCE_NAME`_RESP_LEN_OVERHEAD + `$INSTANCE_NAME`_RESP_LEN_MAX_PAYLOAD) /**< Maximum length of the entire packet */
    /* **** COMMANDS **** */
    #define `$INSTANCE_NAME`_RESP_SUCCESS        (0x00) /**< Successfully executed the previous command */
    #define `$INSTANCE_NAME`_RESP_ASYNC          (0x80) /**< All response code that are greater than or equal to this are not responses but rather async data */

    /***************************************
    * Enumerated Types
    ***************************************/
    
    #define `$INSTANCE_NAME`_ERR_SUCCESS        (0x00u)     /**< Returned Success */
    #define `$INSTANCE_NAME`_ERR_START_SYM      (0x01u)     /**< Incorrect start symbol was received */
    #define `$INSTANCE_NAME`_ERR_END_SYM        (0x02u)     /**< Incorrect end symbol was received */
    #define `$INSTANCE_NAME`_ERR_LENGTH         (0x03u)     /**< The amount of data available is outside the expected range. */
    #define `$INSTANCE_NAME`_ERR_FORMAT         (0x04u)     /**< The packet is not in the correct format */
    #define `$INSTANCE_NAME`_ERR_INCOMPLETE     (0x05u)     /**< The packet cannot be processed as it is incomplete */
    #define `$INSTANCE_NAME`_ERR_MODULE         (0x06u)     /**< An invalid module was specified */
    #define `$INSTANCE_NAME`_ERR_DATA           (0x07u)     /**< The data is not of the proper form  */
    #define `$INSTANCE_NAME`_ERR_CMD            (0x08u)     /**< The command is not recognized */
    #define `$INSTANCE_NAME`_ERR_CHECKSUM       (0x09u)     /**< The packet checksum does not match the expected value */
    #define `$INSTANCE_NAME`_ERR_STATE          (0x0Au)     /**< Device was in the incorrect state to execute the command */
    #define `$INSTANCE_NAME`_ERR_DEVICE         (0x0Bu)     /**< An Unknown device was addressed */
    #define `$INSTANCE_NAME`_ERR_UNKNOWN        (0x7Fu)     /**< An unknown error occurred - End of error space */
    /* Async data */
    #define `$INSTANCE_NAME`_ASYNC_REPORT_ADV   (0x80u)     /**< Report an advertisement packet - Start of async space */
    #define `$INSTANCE_NAME`_ASYNC_REPORT_CONN  (0x81u)     /**< Report a connection success  */
    #define `$INSTANCE_NAME`_ASYNC_REPORT_DCON  (0x82u)     /**< Report a disconnection  */

//    typedef enum {
//        `$INSTANCE_NAME`_ERR_SUCCESS = 0x00u, /**< Returned Success */
//        `$INSTANCE_NAME`_ERR_FORMAT,      /**< The packet is not in the correct format */
//        `$INSTANCE_NAME`_ERR_MODULE,      /**< An invalid module was specified */
//        `$INSTANCE_NAME`_ERR_LENGTH,      /**< The amount of data available is outside the expected range. */
//        `$INSTANCE_NAME`_ERR_DATA,        /**< The data is not of the proper form  */
//        `$INSTANCE_NAME`_ERR_CMD,         /**< The command is not recognized */
//        `$INSTANCE_NAME`_ERR_CHECKSUM,    /**< The packet checksum does not match the expected value */
//        `$INSTANCE_NAME`_ERR_STATE,        /**< Device was in the incorrect state to execute the command */
//        `$INSTANCE_NAME`_ERR_DEVICE,      /**< An Unknown device was addressed */
//        `$INSTANCE_NAME`_ERR_UNKNOWN = 0x7F,      /**< An unknown error occurred */
//        /* Async data */
//        `$INSTANCE_NAME`_ASYNC_REPORT_ADV = `$INSTANCE_NAME`_RESP_ASYNC,       /**< Report an advertisement packet */
//        `$INSTANCE_NAME`_ASYNC_REPORT_CONN,    /**< Report a connection success  */
//        `$INSTANCE_NAME`_ASYNC_REPORT_DCON    /**< Report a disconnection  */
//    } `$INSTANCE_NAME`_ERROR_T;  

    typedef enum {
        `$INSTANCE_NAME`_STATE_WAIT_FOR_START,   /**< Waiting for the start byte to be received */
        `$INSTANCE_NAME`_STATE_RECEIVE_HEADER,   /**< Receiving the header Module ID, command, Payload length */
        `$INSTANCE_NAME`_STATE_RECEIVE_PAYLOAD,  /**< Receiving N bytes of payload data */
        `$INSTANCE_NAME`_STATE_RECEIVE_FOOTER    /**< Receiving Checksum and end of packet */
    } `$INSTANCE_NAME`_STATE_T;
    
    /***************************************
    * Structures
    ***************************************/
    typedef struct {
        uint8_t moduleId;       /**< ID of the module commanded */
        uint8_t cmd;            /**< Command issued */
        uint8_t* payload;       /**< Pointer to the data */
        uint16_t payloadLen;    /**< Length of the payload in the buffer*/
        `$INSTANCE_NAME`_STATE_T state; /**< State of the packet */
        uint8_t buffer[`$INSTANCE_NAME`_LEN_MAX_PACKET];  /**< Packet buffer*/
        uint16_t bufferCount;   /**< Length of the data in the buffer*/
        bool complete;          /**< Has all of the packet been received ? */
    } `$INSTANCE_NAME`_PACKET_T;
            
    typedef struct {
        uint8_t moduleId;       /**< ID of the module commanded */
//        `$INSTANCE_NAME`_ERROR_T status; /**< Status Code of the response packet */
        uint16_t length;            /**< Length of the response payload */
        uint8_t* payload;           /**< Pointer to the payload */
    } `$INSTANCE_NAME`_RESPONSE_T;
    
    /***************************************
    * Function declarations 
    ***************************************/
    uint32_t `$INSTANCE_NAME`_initializePacket(`$INSTANCE_NAME`_PACKET_T* packet);
    uint32_t `$INSTANCE_NAME`_processPacketByte(uint8_t dataByte, `$INSTANCE_NAME`_PACKET_T* packet);
    uint32_t `$INSTANCE_NAME`_parsePacket(`$INSTANCE_NAME`_PACKET_T* packet);
    uint32_t `$INSTANCE_NAME`_createPacket(`$INSTANCE_NAME`_PACKET_T* packet);
    
    uint16_t `$INSTANCE_NAME`_computeChecksum16(uint8_t* data, uint16_t length);
//    bool `$INSTANCE_NAME`_sendResponsePacket(`$INSTANCE_NAME`_RESPONSE_T* response);
//    `$INSTANCE_NAME`_ERROR_T `$INSTANCE_NAME`_parsePacket(uint8_t* dataBuffer, `$INSTANCE_NAME`_PACKET_T* packet);
//    bool `$INSTANCE_NAME`_processPacketByte(uint8_t dataByte, uint8_t* packetBuffer);
//    uint32_t `$INSTANCE_NAME`_processPacketByte(uint8_t dataByte, `$INSTANCE_NAME`_PACKET_T* packet);

#endif /* `$INSTANCE_NAME`_H */
/* [] END OF FILE */

