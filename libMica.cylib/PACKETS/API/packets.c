/***************************************************************************
*                                       MICA
* File: packets.c
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
#include "`$INSTANCE_NAME`.h"
#include "micaCommon.h"
#include "`$uartIncludeFile`.h"
#include <stdlib.h>

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Buffer_Gen()
****************************************************************************//**
* \brief
*  Allocates memory for a new packet buffer
*
* \param buffer
*   Pointer to the packet to be initialized. 
*
* \return
*  A number indicating the error code
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_SUCCESS            | On Successful init
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_Buffer_Gen(`$INSTANCE_NAME`_BUFFER_FULL_S **packetBuffer) {
    uint32_t result = ZERO;
    /* Create the packetBuffer */
    *packetBuffer = (`$INSTANCE_NAME`_BUFFER_FULL_S *) malloc(sizeof(`$INSTANCE_NAME`_BUFFER_FULL_S));
    /* See if failed */
    if(*packetBuffer == NULL){
        result |= `$INSTANCE_NAME`_ERR_MEMORY; 
        goto `$INSTANCE_NAME`_clean1;
    }
    /* Create receive process buffer */
    uint8* processRxBufferAdr = (uint8 *) malloc(`$INSTANCE_NAME`_LEN_BLOCK_PACKET);
    if(processRxBufferAdr == NULL){
        result |= packets_ERR_MEMORY; 
        goto `$INSTANCE_NAME`_clean2;
    }
    (**packetBuffer).receive.processBuffer.buffer = processRxBufferAdr;
    memset(processRxBufferAdr, ZERO, `$INSTANCE_NAME`_LEN_BLOCK_PACKET);

    /* Create Send process buffer */
    uint8* processTxBufferAdr = (uint8 *) malloc(`$INSTANCE_NAME`_LEN_BLOCK_PACKET);
    if(processTxBufferAdr == NULL){
        result |= packets_ERR_MEMORY; 
        goto `$INSTANCE_NAME`_clean3;
    }
    (**packetBuffer).send.processBuffer.buffer = processTxBufferAdr;
    memset(processTxBufferAdr, ZERO, `$INSTANCE_NAME`_LEN_BLOCK_PACKET);

    /* Create receive payload */
    uint8* packetReceiveBuffer = (uint8 *) malloc(`$INSTANCE_NAME`_LEN_BLOCK_PACKET);
    if(packetReceiveBuffer == NULL){
        result |= `$INSTANCE_NAME`_ERR_MEMORY; 
        goto `$INSTANCE_NAME`_clean4;
    }
    (**packetBuffer).receive.packet.payload = packetReceiveBuffer;
    memset(packetReceiveBuffer, ZERO, `$INSTANCE_NAME`_LEN_BLOCK_PACKET);

    /* Create send payload */
    uint8* packetSendBuffer = (uint8 *) malloc(`$INSTANCE_NAME`_LEN_BLOCK_PACKET);
    if(packetSendBuffer == NULL){
        result |= `$INSTANCE_NAME`_ERR_MEMORY; 
        goto `$INSTANCE_NAME`_clean5;
    }
    (**packetBuffer).send.packet.payload = packetSendBuffer;
    memset(packetSendBuffer, ZERO, `$INSTANCE_NAME`_LEN_BLOCK_PACKET);

/* Clean up failed memory */
`$INSTANCE_NAME`_clean5:
    free(packetSendBuffer);   
`$INSTANCE_NAME`_clean4:
    free(packetReceiveBuffer);    
`$INSTANCE_NAME`_clean3:
    free(processTxBufferAdr);
`$INSTANCE_NAME`_clean2:
    free(processRxBufferAdr);
`$INSTANCE_NAME`_clean1:
    free(*packetBuffer);


    /* return error flags */
    return result;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Buffer_processRxByte()
****************************************************************************//**
* \brief
*  Processes the lastest received byt . 
*
* \return
*  A number indicating the error code
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_SUCCESS            | On Successful init
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_Buffer_processRxByte(`$INSTANCE_NAME`_BUFFER_FULL_S* buffer, uint8_t byte) {
    return `$INSTANCE_NAME`_ERR_SUCCESS;
}

// /*******************************************************************************
// * Function Name: `$INSTANCE_NAME`_initializePacket()
// ****************************************************************************//**
// * \brief
// *  Initializes and resets the packet structure
// *
// * \param packetBuffer
// *   Pointer to the packet to be initialized. 
// *
// * \return
// *  A number indicating the error code
// *  Errors codes                             | Description
// *   ------------                            | -----------
// *   `$INSTANCE_NAME`_ERR_SUCCESS            | On Successful init
// *******************************************************************************/
// uint32_t `$INSTANCE_NAME`_initializePacket(`$INSTANCE_NAME`_PACKET_T* packet) {
//     /* Set all values to zero */
//     packet->moduleId = ZERO;
//     packet->cmd = ZERO;
//     packet->payloadLen = ZERO;
//     packet->payload = ZERO;
//     packet->state = `$INSTANCE_NAME`_STATE_WAIT_FOR_START;
//     memset(packet->buffer, ZERO, `$INSTANCE_NAME`_LEN_MAX_PACKET);
//     packet->bufferCount = ZERO;
//     packet->payloadLen = ZERO;
//     packet->complete = false;
//     /* Indicate success */
//     return `$INSTANCE_NAME`_ERR_SUCCESS;
// }
// /*******************************************************************************
// * Function Name: `$INSTANCE_NAME`_processPacketByte()
// ****************************************************************************//**
// * \brief
// *  Stores a byte of data received in a buffer to be processed once the packet
// *  is complete 
// *
// * \param dataByte
// * The data byte to be processed 
// *
// * \param packetBuffer
// *   Pointer to the packet to be added to. 
// *
// * \return
// *  A number indicating the error code
// *
// *******************************************************************************/
// uint32_t `$INSTANCE_NAME`_processPacketByte(uint8_t dataByte, `$INSTANCE_NAME`_PACKET_T* packet) {
//     uint32_t error = `$INSTANCE_NAME`_ERR_SUCCESS;
//     /* Act according to the state of the packet buffer */
//     switch (packet->state) {
//         /* Waiting for start, ensure that the data byte is valid */
//         case `$INSTANCE_NAME`_STATE_WAIT_FOR_START: {
//             /* Ensure start byte is valid */
//             if (dataByte == `$INSTANCE_NAME`_SYM_START) {
//                 /* Reset the count */
//                packet->bufferCount = ZERO;
//                 /* Store the byte */
//                 packet->buffer[(packet->bufferCount)++] = dataByte;
//                 /* Advance to the next state */
//                 packet->state = `$INSTANCE_NAME`_STATE_RECEIVE_HEADER;
//             /* Invalid start symbol */
//             } else {
//                 error = `$INSTANCE_NAME`_ERR_START_SYM;
//             }
//             break;
//         }
//         /* Waiting for the header */
//         case `$INSTANCE_NAME`_STATE_RECEIVE_HEADER: {
//             /* Store the byte */
//             packet->buffer[(packet->bufferCount)++] = dataByte;
//             /* Check to see if more data is required */
//             if (packet->bufferCount == `$INSTANCE_NAME`_LEN_HEADER) {
//                 /* Get the payload length */
//                 packet->payloadLen = (packet->buffer[`$INSTANCE_NAME`_INDEX_LEN_MSB] << BITS_ONE_BYTE) | packet->buffer[`$INSTANCE_NAME`_INDEX_LEN_LSB];
//                 /* Ensure payload len is valid */
//                 if (packet->payloadLen > `$INSTANCE_NAME`_LEN_MAX_PAYLOAD) {
//                     /* Error - Move back to start state */
//                     packet->state = `$INSTANCE_NAME`_STATE_WAIT_FOR_START;
//                     error = `$INSTANCE_NAME`_ERR_LENGTH;
//                 } else if (packet->payloadLen == ZERO) {
//                     /* Skip payload collection */
//                     packet->state = `$INSTANCE_NAME`_STATE_RECEIVE_FOOTER;
//                 } else {
//                     /* Advance to the next state */
//                     packet->state = `$INSTANCE_NAME`_STATE_RECEIVE_PAYLOAD;
//                 }
//             }
//             break;
//         }
//         /* Receiving Payload info */
//         case `$INSTANCE_NAME`_STATE_RECEIVE_PAYLOAD: {
//             /* Store the data  */
//             packet->buffer[(packet->bufferCount)++] = dataByte;
//             /* See if all data has been captured */
//             if (packet->bufferCount == (`$INSTANCE_NAME`_LEN_HEADER +  packet->payloadLen)){
//                 /* Advance to next state */
//                 packet->state = `$INSTANCE_NAME`_STATE_RECEIVE_FOOTER;   
//             /* Data out of range */
//             } else if (packet->bufferCount > (`$INSTANCE_NAME`_LEN_HEADER +  packet->payloadLen)){
//                 /* Reset count */
//                 packet->state = `$INSTANCE_NAME`_STATE_WAIT_FOR_START;
//                 error = `$INSTANCE_NAME`_ERR_LENGTH;
//             }
//             break;
//         }
//         /* Wait for the footer */
//         case `$INSTANCE_NAME`_STATE_RECEIVE_FOOTER: {
//             /* Store the data */
//             packet->buffer[(packet->bufferCount)++] = dataByte;
//             /*If all data has been captured */
//             uint16_t fullPacketLength = `$INSTANCE_NAME`_LEN_HEADER + packet->payloadLen + `$INSTANCE_NAME`_LEN_FOOTER;
//             if (packet->bufferCount == fullPacketLength) {
//                 /*  Ensure stop symbol is valid */
//                 if (dataByte == `$INSTANCE_NAME`_SYM_END) {
//                     /* Packet is complete */   
//                     packet->complete = true;
//                     /* Process the packet */
//                     `$INSTANCE_NAME`_parsePacket(packet);
//                 } else {
//                     error = `$INSTANCE_NAME`_ERR_END_SYM;    
//                 }
//                 /* Advance to original state */
//                  packet->state = `$INSTANCE_NAME`_STATE_WAIT_FOR_START;
//             } else if (packet->bufferCount > fullPacketLength){
//                 error = `$INSTANCE_NAME`_ERR_LENGTH;
//             }
//             break;
//         }
//     }
//     /* Return the packet state */
//     return error;
// }


// /*******************************************************************************
// * Function Name:`$INSTANCE_NAME`_parsePacket()
// ****************************************************************************//**
// * \brief
// *  Parses a data packet from the received data.
// *
// * \param packet
// * Pointer to a packet structure to place the infomation in
// *
// * \return
// * The error code of the result packet parsing
// * The possible error codes are:
// *
// *  Errors codes                         | Description
// *   ------------                        | -----------
// *   `$INSTANCE_NAME`_ERR_SUCCESS        | The packet was successfully parsed.
// *   `$INSTANCE_NAME`_ERR_FORMAT         | The packet was in the incorrect format.
// *   `$INSTANCE_NAME`_ERR_MODULE         | An unknown module was requested.
// *   `$INSTANCE_NAME`_ERR_LENGTH         | The packet payload length was outside the allowed value.
// *   `$INSTANCE_NAME`_ERR_CHECKSUM       | The calculated checksum did not match the reported checksum.
// *******************************************************************************/
// uint32_t `$INSTANCE_NAME`_parsePacket(`$INSTANCE_NAME`_PACKET_T* packet) {
//     /* Ensure packet is complete */
//     if (packet->complete == false){
//         return `$INSTANCE_NAME`_ERR_INCOMPLETE;    
//     }
//     /* Ensure start of packet symbol */
//     if (packet->buffer[`$INSTANCE_NAME`_INDEX_START] != `$INSTANCE_NAME`_LEN_SYM_START) {
//         return `$INSTANCE_NAME`_ERR_START_SYM;
//     }
//     /* Get the Module */
//     packet->moduleId = packet->buffer[`$INSTANCE_NAME`_INDEX_MODULE_ID];
//     if (packet->moduleId > `$INSTANCE_NAME`_ID_MODULE_MAX) {
//         return `$INSTANCE_NAME`_ERR_MODULE;
//     }
//     /* Get the Command - Cannot tell if valid at this point */
//     packet->cmd = packet->buffer[`$INSTANCE_NAME`_INDEX_CMD];
//     /* Get the payload length */
//     packet->payloadLen = (packet->buffer[`$INSTANCE_NAME`_INDEX_LEN_MSB] << BITS_ONE_BYTE) | packet->buffer[`$INSTANCE_NAME`_INDEX_LEN_LSB];
//     if (packet->payloadLen > `$INSTANCE_NAME`_LEN_MAX_PAYLOAD) {
//         return `$INSTANCE_NAME`_ERR_LENGTH;  
//     }
//     /* Set the payload pointer */
//     packet->payload = &(packet->buffer[`$INSTANCE_NAME`_INDEX_PAYLOAD]);
//     /* Validate checksum */
//     uint16_t calculatedChecksum = `$INSTANCE_NAME`_computeChecksum16(packet->buffer, `$INSTANCE_NAME`_LEN_HEADER + packet->payloadLen);
//     uint8_t* packetEndPtr = &(packet->buffer[`$INSTANCE_NAME`_LEN_HEADER + packet->payloadLen]);
//     uint8 checkSumMsb = *packetEndPtr++;
//     uint8 checkSumLsb = *packetEndPtr++;
//     uint16_t reportedChecksum = (checkSumMsb << BITS_ONE_BYTE) | checkSumLsb;
//     if( calculatedChecksum != reportedChecksum) {
//         return `$INSTANCE_NAME`_ERR_CHECKSUM;
//     }
//     /* Check end of packet symbol */
//     uint8 endSymbol = *packetEndPtr;
//     if (endSymbol != `$INSTANCE_NAME`_SYM_END) {
//         return `$INSTANCE_NAME`_ERR_END_SYM;
//     }
//     /* Successful packet */
//     return `$INSTANCE_NAME`_ERR_SUCCESS;
// } 


// /*******************************************************************************
// * Function Name: `$INSTANCE_NAME`_createPacket()
// ****************************************************************************//**
// * \brief
// *  Package a packet object into a packet to send
// *
// * \param packet
// *  Pointer to the packet to pack
// *
// *
// * \return
// * A error code with the result of packing
// *
// *******************************************************************************/
// uint32_t `$INSTANCE_NAME`_createPacket(`$INSTANCE_NAME`_PACKET_T* packet) {
//     /* Reset the buffer count */
//     packet->bufferCount = ZERO;
//     /* Header */
//     packet->buffer[(packet->bufferCount)++] = `$INSTANCE_NAME`_SYM_START;
//     packet->buffer[(packet->bufferCount)++] = packet->moduleId;
//     packet->buffer[(packet->bufferCount)++] = packet->cmd;
//     /* Payload length MSB */
//     packet->buffer[(packet->bufferCount)++] = (packet->payloadLen >> BITS_ONE_BYTE) & MASK_BYTE_ONE;
//     /* Payload length MSB */
//     packet->buffer[(packet->bufferCount)++] = (packet->payloadLen) & MASK_BYTE_ONE;
//     /* Payload */
//     uint16_t j;
//     for(j = ZERO; j < packet->payloadLen; j++) {
//         packet->buffer[(packet->bufferCount)++] = packet->payload[j];
//     }
//     /* Footer */
//     uint16_t checksum = `$INSTANCE_NAME`_computeChecksum16(packet->buffer, `$INSTANCE_NAME`_LEN_HEADER + packet->payloadLen);
//     packet->buffer[(packet->bufferCount)++] = (checksum >> BITS_ONE_BYTE) & MASK_BYTE_ONE;
//     packet->buffer[(packet->bufferCount)++] = (checksum) & MASK_BYTE_ONE;
//     packet->buffer[(packet->bufferCount)++] = `$INSTANCE_NAME`_SYM_END;
//     /* Return Success */
//     return `$INSTANCE_NAME`_ERR_SUCCESS;
// }

// /*******************************************************************************
// * Function Name: `$INSTANCE_NAME`_flushBuffer()
// ****************************************************************************//**
// * \brief
// *  Flushes the buffer if an error occured
// *
// * \param packet
// *  Pointer to the packet to pack
// *
// *
// * \return
// * A error code with the result of packing
// *
// *******************************************************************************/
// uint32_t `$INSTANCE_NAME`(`$INSTANCE_NAME`_PACKET_T* packet) {
    
// }

///*******************************************************************************
//* Function Name: `$INSTANCE_NAME`_sendResponsePacket()
//****************************************************************************//**
//* \brief
//*  Processes a command sent to the control module
//*
//* \param response
//* Pointer to the response packet to pack
//*
//* \param buffer
//* Pointer to write the packet contents into
//*
//* \return
//* A boolean on whether the command was sent or not
//*
//*******************************************************************************/
//bool `$INSTANCE_NAME`_createResponsePacket(`$INSTANCE_NAME`_RESPONSE_T* response) {
//    uint8_t respPacket[`$INSTANCE_NAME`_RESP_LEN_MAX_PACKET];
//    uint16_t i = ZERO;
//    
//    /* Header */
//    respPacket[i++] = `$INSTANCE_NAME`_SYM_START;
//    respPacket[i++] = response->moduleId;
//    respPacket[i++] = response->status;
//    respPacket[i++] = (response->payloadLen >> BITS_ONE_BYTE) & MASK_BYTE_ONE;
//    respPacket[i++] = (response->payloadLen) & MASK_BYTE_ONE;
//    /* Payload */
//    uint16_t j;
//    for(j = ZERO; j < response->payloadLen; j++) {
//        respPacket[i++] = response->payload[j];
//    }
//    /* Footer */
//    uint16_t checksum = `$INSTANCE_NAME`_computeChecksum16(respPacket, `$INSTANCE_NAME`_RESP_LEN_HEADER + response->payloadLen);
//    respPacket[i++] = (checksum >> BITS_ONE_BYTE) & MASK_BYTE_ONE;
//    respPacket[i++] = (checksum) & MASK_BYTE_ONE;
//    respPacket[i++] = `$INSTANCE_NAME`_SYM_END;
//    /* Send out */
//    for(i = ZERO; i < (`$INSTANCE_NAME`_RESP_LEN_OVERHEAD + response->payloadLen); i++){
//        `$txFunction`(respPacket[i]);
//    }
//    return true;
//}

//bool `$INSTANCE_NAME`_processPacketByte(uint8_t dataByte, uint8_t* packetBuffer) {
//    /* Return Value */
//    bool packetComplete = false; 
//    /* Act according to the state of the packet buffer */
//    switch (packetBufferState) {
//        /* Waiting for start, ensure that the data byte is valid */
//        case `$INSTANCE_NAME`_STATE_WAIT_FOR_START: {
//            /* Ensure start byte is valid */
//            if (dataByte == `$INSTANCE_NAME`_SYM_START) {
//                /* Reset the count */
//                bufferCount = ZERO;
//                /* Store the byte */
//                packetBuffer[bufferCount++] = dataByte;
//                /* Advance to the next state */
//                packetBufferState = `$INSTANCE_NAME`_STATE_RECEIVE_HEADER;
//            }
//            break;
//        }
//        /* Waiting for the header */
//        case `$INSTANCE_NAME`_STATE_RECEIVE_HEADER: {
//            /* Store the data */
//            packetBuffer[bufferCount++] = dataByte;
//            /* Check to see if more data is required */
//            if (bufferCount == `$INSTANCE_NAME`_LEN_HEADER) {
//                /* Get the payload length */
//                payloadLen = (packetBuffer[`$INSTANCE_NAME`_INDEX_LEN_MSB] << BITS_ONE_BYTE) | packetBuffer[`$INSTANCE_NAME`_INDEX_LEN_LSB];
//                /* Ensure payload len is valid */
//                if (payloadLen > `$INSTANCE_NAME`_LEN_MAX_PAYLOAD) {
//                    /* Error - Move back to start state */
//                    packetBufferState = `$INSTANCE_NAME`_STATE_WAIT_FOR_START;
//                } else if (payloadLen == ZERO) {
//                    /* Skip payload collection */
//                    packetBufferState = `$INSTANCE_NAME`_STATE_RECEIVE_FOOTER;
//                } else {
//                    /* Advance to the next state */
//                    packetBufferState = `$INSTANCE_NAME`_STATE_RECEIVE_PAYLOAD;
//                }
//            }
//            break;
//        }
//        /* Receiving Payload info */
//        case `$INSTANCE_NAME`_STATE_RECEIVE_PAYLOAD: {
//            /* Store the data  */
//            packetBuffer[bufferCount++] = dataByte;
//            /* See if all data has been captured */
//            if (bufferCount == (`$INSTANCE_NAME`_LEN_HEADER +  payloadLen)){
//                packetBufferState = `$INSTANCE_NAME`_STATE_RECEIVE_FOOTER;   
//            }
//            break;
//        }
//        /* Wait for the footer */
//        case `$INSTANCE_NAME`_STATE_RECEIVE_FOOTER: {
//            /* Store the data */
//            packetBuffer[bufferCount++] = dataByte;
//            /*If all data has been captured */
//            if (bufferCount == (`$INSTANCE_NAME`_LEN_HEADER + payloadLen + `$INSTANCE_NAME`_LEN_FOOTER)) {
//                /*  Ensure stop symbol is valid */
//                if (dataByte == `$INSTANCE_NAME`_SYM_END) {
//                    /* Packet is complete */   
//                    packetComplete = true;
//                }
//                /* Advance to original state */
//                packetBufferState = `$INSTANCE_NAME`_STATE_WAIT_FOR_START;
//            }
//            break;
//        }
//    }
//    /* Return the packet state */
//    return packetComplete;
//}

/*******************************************************************************
* Function Name:`$INSTANCE_NAME`_parsePacket()
****************************************************************************//**
* \brief
*  Parses a data packet from the received data.
*
* \param dataBuffer
* Pointer to the received data
*
* \param packet
* Pointer to a packet structure to place the infomation in
*
* \return
* The error code of the result packet parsing
* The possible error codes are:
*
*  Errors codes                         | Description
*   ------------                        | -----------
*   `$INSTANCE_NAME`_ERR_SUCCESS        | The packet was successfully parsed.
*   `$INSTANCE_NAME`_ERR_FORMAT         | The packet was in the incorrect format.
*   `$INSTANCE_NAME`_ERR_MODULE         | An unknown module was requested.
*   `$INSTANCE_NAME`_ERR_LENGTH         | The packet payload length was outside the allowed value.
*   `$INSTANCE_NAME`_ERR_CHECKSUM       | The calculated checksum did not match the reported checksum.
*******************************************************************************/
//`$INSTANCE_NAME`_ERROR_T `$INSTANCE_NAME`_parsePacket(uint8_t* dataBuffer, `$INSTANCE_NAME`_PACKET_T* packet) {
//    /* Ensure start of packet symbol */
//    if (dataBuffer[`$INSTANCE_NAME`_INDEX_START] != `$INSTANCE_NAME`_LEN_SYM_START) {
//        return `$INSTANCE_NAME`_ERR_FORMAT;
//    }
//    /* Get the Module */
//    packet->moduleId = dataBuffer[`$INSTANCE_NAME`_INDEX_MODULE_ID];
//    if (packet->moduleId > `$INSTANCE_NAME`_ID_MODULE_MAX) {
//     return `$INSTANCE_NAME`_ERR_MODULE;
//    }
//    /* Get the Command - Cannot tell if valid at this point */
//    packet->cmd = dataBuffer[`$INSTANCE_NAME`_INDEX_CMD];
//    /* Get the payload length */
//    packet->payloadLen = (dataBuffer[`$INSTANCE_NAME`_INDEX_LEN_MSB] << BITS_ONE_BYTE) | dataBuffer[`$INSTANCE_NAME`_INDEX_LEN_LSB];
//    if (packet->payloadLen > `$INSTANCE_NAME`_LEN_MAX_PAYLOAD) {
//        return `$INSTANCE_NAME`_ERR_LENGTH;  
//    }
//    /* Set the payload pointer */
//    packet->payload = &dataBuffer[`$INSTANCE_NAME`_INDEX_PAYLOAD];
//    /* Validate checksum */
//    uint16_t calculatedChecksum = `$INSTANCE_NAME`_computeChecksum16(dataBuffer, `$INSTANCE_NAME`_LEN_HEADER + packet->payloadLen);
//    uint8_t* packetEndPtr = &dataBuffer[`$INSTANCE_NAME`_LEN_HEADER + packet->payloadLen];
//    uint8 checkSumMsb = *packetEndPtr++;
//    uint8 checkSumLsb = *packetEndPtr++;
//    uint16_t reportedChecksum = (checkSumMsb << BITS_ONE_BYTE) | checkSumLsb;
//    if( calculatedChecksum != reportedChecksum) {
//        return `$INSTANCE_NAME`_ERR_CHECKSUM;
//    }
//    /* Check end of packet symbol */
//    uint8 endSymbol = *packetEndPtr;
//    if (endSymbol != `$INSTANCE_NAME`_SYM_END) {
//        return `$INSTANCE_NAME`_ERR_FORMAT;
//    }
//    /* Successful packet */
//    return `$INSTANCE_NAME`_ERR_SUCCESS;
//} 



/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_computeChecksum16()
****************************************************************************//**
* \brief
*  Calculates the 16 bit, two's complement, checksum from an array of data
*
* \param data
* Array which contains the data
*
* \param length
* The length of the data to interate over
*
* \return
* The value of the checksum in two's complement form
*
*******************************************************************************/
uint16_t `$INSTANCE_NAME`_computeChecksum16(uint8_t* data, uint16_t length){
    /* Local variables */
    uint8_t idx;
    uint16_t sum = ZERO;
    /* Iterate over the values */
    for( idx = ZERO; idx < length; idx++ ){
        sum += data[idx];
    }
    /* Return the sum in two's complement */
    return (1 + ~sum);
}

/* [] END OF FILE */
