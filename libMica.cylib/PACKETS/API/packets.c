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

/* Store the state variable */
volatile `$INSTANCE_NAME`_STATE_T packetBufferState = `$INSTANCE_NAME`_STATE_WAIT_FOR_START;
volatile uint16_t bufferCount = ZERO;
volatile uint16_t payloadLen = ZERO;

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_processPacketByte()
****************************************************************************//**
* \brief
*  Stores a byte of data received in a buffer to be processed once the packet
*  is complete 
*
* \param dataByte
* The data byte to be processed 
*
* \param packetBuffer
* The data array to store the buffer in. Must be of at least size `$INSTANCE_NAME`_LEN_MAX_PACKET 
*
* \return
*  A boolean indicating if the packet is complete
*
*******************************************************************************/
bool `$INSTANCE_NAME`_processPacketByte(uint8_t dataByte, uint8_t* packetBuffer) {
    /* Return Value */
    bool packetComplete = false; 
    /* Act according to the state of the packet buffer */
    switch (packetBufferState) {
        /* Waiting for start, ensure that the data byte is valid */
        case `$INSTANCE_NAME`_STATE_WAIT_FOR_START: {
            /* Ensure start byte is valid */
            if (dataByte == `$INSTANCE_NAME`_SYM_START) {
                /* Reset the count */
                bufferCount = ZERO;
                /* Store the byte */
                packetBuffer[bufferCount++] = dataByte;
                /* Advance to the next state */
                packetBufferState = `$INSTANCE_NAME`_STATE_RECEIVE_HEADER;
            }
            break;
        }
        /* Waiting for the header */
        case `$INSTANCE_NAME`_STATE_RECEIVE_HEADER: {
            /* Store the data */
            packetBuffer[bufferCount++] = dataByte;
            /* Check to see if more data is required */
            if (bufferCount == `$INSTANCE_NAME`_LEN_HEADER) {
                /* Get the payload length */
                payloadLen = (packetBuffer[`$INSTANCE_NAME`_INDEX_LEN_MSB] << BITS_ONE_BYTE) | packetBuffer[`$INSTANCE_NAME`_INDEX_LEN_LSB];
                /* Ensure payload len is valid */
                if (payloadLen > `$INSTANCE_NAME`_LEN_MAX_PAYLOAD) {
                    /* Error - Move back to start state */
                    packetBufferState = `$INSTANCE_NAME`_STATE_WAIT_FOR_START;
                } else if (payloadLen == ZERO) {
                    /* Skip payload collection */
                    packetBufferState = `$INSTANCE_NAME`_STATE_RECEIVE_FOOTER;
                } else {
                    /* Advance to the next state */
                    packetBufferState = `$INSTANCE_NAME`_STATE_RECEIVE_PAYLOAD;
                }
            }
            break;
        }
        /* Receiving Payload info */
        case `$INSTANCE_NAME`_STATE_RECEIVE_PAYLOAD: {
            /* Store the data  */
            packetBuffer[bufferCount++] = dataByte;
            /* See if all data has been captured */
            if (bufferCount == (`$INSTANCE_NAME`_LEN_HEADER +  payloadLen)){
                packetBufferState = `$INSTANCE_NAME`_STATE_RECEIVE_FOOTER;   
            }
            break;
        }
        /* Wait for the footer */
        case `$INSTANCE_NAME`_STATE_RECEIVE_FOOTER: {
            /* Store the data */
            packetBuffer[bufferCount++] = dataByte;
            /*If all data has been captured */
            if (bufferCount == (`$INSTANCE_NAME`_LEN_HEADER + payloadLen + `$INSTANCE_NAME`_LEN_FOOTER)) {
                /*  Ensure stop symbol is valid */
                if (dataByte == `$INSTANCE_NAME`_SYM_END) {
                    /* Packet is complete */   
                    packetComplete = true;
                }
                /* Advance to original state */
                packetBufferState = `$INSTANCE_NAME`_STATE_WAIT_FOR_START;
            }
            break;
        }
    }
    /* Return the packet state */
    return packetComplete;
}

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
`$INSTANCE_NAME`_ERROR_T mica_parsePacket(uint8_t* dataBuffer, `$INSTANCE_NAME`_PACKET_T* packet) {
    /* Ensure start of packet symbol */
    if (dataBuffer[`$INSTANCE_NAME`_INDEX_START] != `$INSTANCE_NAME`_LEN_SYM_START) {
        return `$INSTANCE_NAME`_ERR_FORMAT;
    }
    /* Get the Module */
    packet->moduleId = dataBuffer[`$INSTANCE_NAME`_INDEX_MODULE_ID];
    if (packet->moduleId > `$INSTANCE_NAME`_ID_MODULE_MAX) {
     return `$INSTANCE_NAME`_ERR_MODULE;
    }
    /* Get the Command - Cannot tell if valid at this point */
    packet->cmd = dataBuffer[`$INSTANCE_NAME`_INDEX_CMD];
    /* Get the payload length */
    packet->length = (dataBuffer[`$INSTANCE_NAME`_INDEX_LEN_MSB] << BITS_ONE_BYTE) | dataBuffer[`$INSTANCE_NAME`_INDEX_LEN_LSB];
    if (packet->length > `$INSTANCE_NAME`_LEN_MAX_PAYLOAD) {
        return `$INSTANCE_NAME`_ERR_LENGTH;  
    }
    /* Set the payload pointer */
    packet->payload = &dataBuffer[`$INSTANCE_NAME`_INDEX_PAYLOAD];
    /* Validate checksum */
    uint16_t calculatedChecksum = `$INSTANCE_NAME`_computeChecksum16(dataBuffer, `$INSTANCE_NAME`_LEN_HEADER + packet->length);
    uint8_t* packetEndPtr = &dataBuffer[`$INSTANCE_NAME`_LEN_HEADER + packet->length];
    uint8 checkSumMsb = *packetEndPtr++;
    uint8 checkSumLsb = *packetEndPtr++;
    uint16_t reportedChecksum = (checkSumMsb << BITS_ONE_BYTE) | checkSumLsb;
    if( calculatedChecksum != reportedChecksum) {
        return `$INSTANCE_NAME`_ERR_CHECKSUM;
    }
    /* Check end of packet symbol */
    uint8 endSymbol = *packetEndPtr;
    if (endSymbol != `$INSTANCE_NAME`_SYM_END) {
        return `$INSTANCE_NAME`_ERR_FORMAT;
    }
    /* Successful packet */
    return `$INSTANCE_NAME`_ERR_SUCCESS;
} 

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_sendResponsePacket()
****************************************************************************//**
* \brief
*  Processes a command sent to the control module
*
* \param response
* Pointer to the response packet to 
*
* \return
* A boolean on whether the command was sent or not
*
*******************************************************************************/
bool `$INSTANCE_NAME`_sendResponsePacket(`$INSTANCE_NAME`_RESPONSE_T* response) {
    uint8_t respPacket[`$INSTANCE_NAME`_RESP_LEN_MAX_PACKET];
    uint16_t i = ZERO;
    
    /* Header */
    respPacket[i++] = `$INSTANCE_NAME`_SYM_START;
    respPacket[i++] = response->moduleId;
    respPacket[i++] = response->status;
    respPacket[i++] = (response->length >> BITS_ONE_BYTE) & MASK_BYTE_ONE;
    respPacket[i++] = (response->length) & MASK_BYTE_ONE;
    /* Payload */
    uint16_t j;
    for(j = ZERO; j < response->length; j++) {
        respPacket[i++] = response->payload[j];
    }
    /* Footer */
    uint16_t checksum = `$INSTANCE_NAME`_computeChecksum16(respPacket, `$INSTANCE_NAME`_RESP_LEN_HEADER + response->length);
    respPacket[i++] = (checksum >> BITS_ONE_BYTE) & MASK_BYTE_ONE;
    respPacket[i++] = (checksum) & MASK_BYTE_ONE;
    respPacket[i++] = `$INSTANCE_NAME`_SYM_END;
    /* Send out */
    for(i = ZERO; i < (`$INSTANCE_NAME`_RESP_LEN_OVERHEAD + response->length); i++){
        `$txFunction`(respPacket[i]);
    }
    return true;
}

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
