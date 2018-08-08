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
* Function Name: `$INSTANCE_NAME`_initialize()
****************************************************************************//**
* \brief
*  Initializes the packet structure to default values
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
uint32_t `$INSTANCE_NAME`_initialize(`$INSTANCE_NAME`_BUFFER_FULL_S *packetBuffer) {
    uint32_t error = `$INSTANCE_NAME`_ERR_SUCCESS;
    /* Set send process buffer to zero */
    packetBuffer->send.processBuffer.buffer = NULL;
    packetBuffer->send.processBuffer.bufferLen = ZERO;
    packetBuffer->send.processBuffer.timeCount = ZERO;
    packetBuffer->send.processBuffer.bufferIndex = ZERO;
    packetBuffer->send.bufferState = `$INSTANCE_NAME`_BUFFER_SEND_WAIT;
    packetBuffer->send.packet.payload = NULL;
    packetBuffer->send.packet.payloadLen = ZERO;
    packetBuffer->send.packet.payloadMax = ZERO;
    /* Set receive process buffer to zero */
    packetBuffer->receive.processBuffer.buffer = NULL;
    packetBuffer->receive.processBuffer.bufferLen = ZERO;
    packetBuffer->receive.processBuffer.timeCount = ZERO;
    packetBuffer->receive.processBuffer.bufferIndex = ZERO;
    packetBuffer->receive.bufferState = `$INSTANCE_NAME`_BUFFER_RECEIVE_WAIT_FOR_START;
    packetBuffer->receive.packet.payload = NULL;
    packetBuffer->receive.packet.payloadLen = ZERO;
    packetBuffer->receive.packet.payloadMax = ZERO;
    return error;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_generateBuffers()
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
uint32_t `$INSTANCE_NAME`_generateBuffers(`$INSTANCE_NAME`_BUFFER_FULL_S *packetBuffer, uint16_t bufferSize) {
    uint32_t error = `$INSTANCE_NAME`_ERR_SUCCESS;
    /* Local References */
    packets_BUFFER_PROCESS_S* rxBuffer = &(packetBuffer->receive.processBuffer);
    packets_BUFFER_PROCESS_S* txBuffer = &(packetBuffer->send.processBuffer);
    
    /* Make sure that buffers have not already been allocated */
    if(rxBuffer->buffer != NULL || txBuffer->buffer != NULL){
        error |= `$INSTANCE_NAME`_ERR_STATE;
    }

    if(!error) {
        /* Create receive process buffer */
        uint8* processRxBufferAdr = (uint8 *) malloc(bufferSize);
        if(processRxBufferAdr == NULL){
            error |= `$INSTANCE_NAME`_ERR_MEMORY; 
            /* Do not try to allocate again */
            goto `$INSTANCE_NAME`_clean1;
        }
        packetBuffer->receive.processBuffer.buffer = processRxBufferAdr;
        packetBuffer->receive.processBuffer.bufferLen = bufferSize;
        memset(processRxBufferAdr, ZERO, bufferSize);

        /* Create Send process buffer */
        uint8* processTxBufferAdr = (uint8 *) malloc(bufferSize);
        if(processTxBufferAdr == NULL){
            error |= `$INSTANCE_NAME`_ERR_MEMORY; 
            goto `$INSTANCE_NAME`_clean2;
        }
        packetBuffer->send.processBuffer.buffer = processTxBufferAdr;
        packetBuffer->send.processBuffer.bufferLen = bufferSize;
        memset(processTxBufferAdr, ZERO, bufferSize);

        /* Set initial values to zero */
        packetBuffer->receive.bufferState = `$INSTANCE_NAME`_BUFFER_RECEIVE_WAIT_FOR_START;
        packetBuffer->send.bufferState = `$INSTANCE_NAME`_BUFFER_SEND_WAIT;
        packetBuffer->receive.packet.payloadMax = ZERO;
        packetBuffer->send.packet.payloadMax = ZERO;

        /* Clean up on error */
        if(error) {  
`$INSTANCE_NAME`_clean2:
            free(processTxBufferAdr);
`$INSTANCE_NAME`_clean1:
            free(processRxBufferAdr);
        }
    }
    /* return error flags */
    return error;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_destoryBuffers()
****************************************************************************//**
* \brief
*  Deallocates memory from a packet
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
uint32_t `$INSTANCE_NAME`_destoryBuffers(`$INSTANCE_NAME`_BUFFER_FULL_S *buffer) {
    uint32_t error = `$INSTANCE_NAME`_ERR_SUCCESS;
    /* Free the Send process buffer is it exists */
    if( (buffer->send.processBuffer.bufferLen != ZERO) && (buffer->send.processBuffer.buffer != NULL) ) { 
        free(buffer->send.processBuffer.buffer);   
        buffer->send.processBuffer.buffer = NULL;
        buffer->send.processBuffer.bufferLen = ZERO;
        buffer->send.processBuffer.bufferIndex = ZERO;
        buffer->send.processBuffer.timeCount = ZERO;
    } else {
        error |= `$INSTANCE_NAME`_ERR_MEMORY;
    }
    /* Free the receive process buffer is it exists */
    if( (buffer->receive.processBuffer.bufferLen != ZERO) && (buffer->receive.processBuffer.buffer != NULL) ) { 
        free(buffer->receive.processBuffer.buffer);   
        buffer->receive.processBuffer.buffer = NULL;
        buffer->receive.processBuffer.bufferLen = ZERO;
        buffer->receive.processBuffer.bufferIndex = ZERO;
        buffer->receive.processBuffer.timeCount = ZERO;
    } else {
        error |= `$INSTANCE_NAME`_ERR_MEMORY;
    }
    /* Return error */
    return error;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_processRxByte()
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
uint32_t `$INSTANCE_NAME`_processRxByte(`$INSTANCE_NAME`_BUFFER_FULL_S* buffer, uint8_t byte) {
     uint32_t error = `$INSTANCE_NAME`_ERR_SUCCESS;
    /* Create local references */
    `$INSTANCE_NAME`_BUFFER_PROCESS_S* rxBuffer = &(buffer->receive.processBuffer);
    `$INSTANCE_NAME`_BUFFER_STATE_RECEIVE_T* bufferState = &(buffer->receive.bufferState);
    uint16_t* payloadLen = &(buffer->receive.packet.payloadLen);

    /* Ensure that buffers are valid and there is room */
    if( 
        (rxBuffer->bufferLen == ZERO) ||
        (rxBuffer->buffer == NULL) ||
        (rxBuffer->bufferIndex >= rxBuffer->bufferLen) 
    ) {
        error |= `$INSTANCE_NAME`_ERR_MEMORY;
    }

    if(!error) {
        /* Act according to the state of the packet buffer */
        switch (buffer->receive.bufferState) {
            /* Waiting for start, ensure that the data byte is valid */
            case `$INSTANCE_NAME`_BUFFER_RECEIVE_WAIT_FOR_START: {
                if(byte != `$INSTANCE_NAME`_SYM_START ){
                    error |= `$INSTANCE_NAME`_ERR_START_SYM;
                    break;
                }
                /* Reset the count */
                rxBuffer->bufferIndex = ZERO;
                /* Store the byte */
                rxBuffer->buffer[(rxBuffer->bufferIndex)++] = byte;
                /* Advance to the next state */
                *bufferState = `$INSTANCE_NAME`_BUFFER_RECEIVE_HEADER;
                break;
            }
            /* Waiting for the header */
            case `$INSTANCE_NAME`_BUFFER_RECEIVE_HEADER: {
                /* Store the byte */
                rxBuffer->buffer[(rxBuffer->bufferIndex)++] = byte;
                /* Check to see if more data is required */
                if (rxBuffer->bufferIndex == `$INSTANCE_NAME`_LEN_HEADER) {
                    /* Store the payload length */
                    *payloadLen = (rxBuffer->buffer[`$INSTANCE_NAME`_INDEX_LEN_MSB] << BITS_ONE_BYTE) | rxBuffer->buffer[`$INSTANCE_NAME`_INDEX_LEN_LSB];
                    if (*payloadLen == ZERO) {
                        /* Skip payload collection */
                        *bufferState = `$INSTANCE_NAME`_BUFFER_RECEIVE_FOOTER;
                    } else {
                        /* Advance to the next state */
                        *bufferState = `$INSTANCE_NAME`_BUFFER_RECEIVE_PAYLOAD;
                    }
                }
                break;
            }
            /* Receiving Payload info */
            case `$INSTANCE_NAME`_BUFFER_RECEIVE_PAYLOAD: {
                /* Store the data  */
                rxBuffer->buffer[(rxBuffer->bufferIndex)++] = byte;
                /* See if all data has been captured */
                if (rxBuffer->bufferIndex == (`$INSTANCE_NAME`_LEN_HEADER +  *payloadLen)){
                    /* Advance to next state */
                    *bufferState = `$INSTANCE_NAME`_BUFFER_RECEIVE_FOOTER;   
                /* Data out of range */
                } else if (rxBuffer->bufferIndex > (`$INSTANCE_NAME`_LEN_HEADER +  *payloadLen)){
                    /* Reset count */
                    *bufferState = `$INSTANCE_NAME`_BUFFER_RECEIVE_WAIT_FOR_START;
                    error |= `$INSTANCE_NAME`_ERR_LENGTH;
                }
                break;
            }
            /* Wait for the footer */
            case `$INSTANCE_NAME`_BUFFER_RECEIVE_FOOTER: {
                /* Store the data */
                rxBuffer->buffer[(rxBuffer->bufferIndex)++] = byte;
                /*If all data has been captured */
                uint16_t fullPacketLength = `$INSTANCE_NAME`_LEN_HEADER + *payloadLen + `$INSTANCE_NAME`_LEN_FOOTER;
                if (rxBuffer->bufferIndex == fullPacketLength) {
                    /* Packet is complete */   
                    *bufferState = `$INSTANCE_NAME`_BUFFER_RECEIVE_COMPLETE;
                }
                break;
            }
            /* Packet is complete, but has not been handled, throw error */
            case `$INSTANCE_NAME`_BUFFER_RECEIVE_COMPLETE: {
                    error |= `$INSTANCE_NAME`_ERR_STATE;
                break;
            }
        }
    } 
     /* Return the packet state */
     return error;
}

/*******************************************************************************
* Function Name:`$INSTANCE_NAME`_parsePacket()
****************************************************************************//**
* \brief
*  Parses a data packet from the received data.
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
uint32_t `$INSTANCE_NAME`_parsePacket(`$INSTANCE_NAME`_BUFFER_FULL_S* buffer) {
    uint32_t error = `$INSTANCE_NAME`_ERR_SUCCESS;
    /* Create local references */
    `$INSTANCE_NAME`_BUFFER_PROCESS_S* rxBuffer = &(buffer->receive.processBuffer);
    `$INSTANCE_NAME`_BUFFER_STATE_RECEIVE_T* bufferState = &(buffer->receive.bufferState);
    `$INSTANCE_NAME`_PACKET_S* packet = &(buffer->receive.packet);
    
    /* Ensure packet is complete */
    if (*bufferState != `$INSTANCE_NAME`_BUFFER_RECEIVE_COMPLETE){
        return `$INSTANCE_NAME`_ERR_INCOMPLETE;    
    }
    /* Ensure start of packet symbol */
    uint8 startByte = rxBuffer->buffer[`$INSTANCE_NAME`_INDEX_START];
    if (startByte != `$INSTANCE_NAME`_SYM_START) {
        error |= `$INSTANCE_NAME`_ERR_START_SYM;
    }
    /* Get the Module */
    packet->moduleId = rxBuffer->buffer[`$INSTANCE_NAME`_INDEX_MODULE_ID];
    if (packet->moduleId > `$INSTANCE_NAME`_ID_MODULE_MAX) {
        error |= `$INSTANCE_NAME`_ERR_MODULE;
    }
    /* Get the Command - Cannot tell if valid at this point */
    packet->cmd = rxBuffer->buffer[`$INSTANCE_NAME`_INDEX_CMD];
    /* Get the payload length */
    packet->payloadLen = (rxBuffer->buffer[`$INSTANCE_NAME`_INDEX_LEN_MSB] << BITS_ONE_BYTE) | rxBuffer->buffer[`$INSTANCE_NAME`_INDEX_LEN_LSB];
    if (packet->payloadLen > `$INSTANCE_NAME`_LEN_MAX_PAYLOAD) {
        error |= `$INSTANCE_NAME`_ERR_LENGTH;  
    }
    /* Transfer the payload to the new buffer */
    memmove(packet->payload, &(rxBuffer->buffer[`$INSTANCE_NAME`_INDEX_PAYLOAD]), packet->payloadLen); 

    /* Validate checksum */
    uint16_t calculatedChecksum = `$INSTANCE_NAME`_computeChecksum16(rxBuffer->buffer, `$INSTANCE_NAME`_LEN_HEADER + packet->payloadLen);
    uint8_t* packetEndPtr = &(rxBuffer->buffer[`$INSTANCE_NAME`_LEN_HEADER + packet->payloadLen]);
    uint8 checkSumMsb = *packetEndPtr++;
    uint8 checkSumLsb = *packetEndPtr++;
    uint16_t reportedChecksum = (checkSumMsb << BITS_ONE_BYTE) | checkSumLsb;
    if( calculatedChecksum != reportedChecksum) {
        error |= `$INSTANCE_NAME`_ERR_CHECKSUM;
    }
    /* Check end of packet symbol */
    uint8 endSymbol = *packetEndPtr;
    if (endSymbol != `$INSTANCE_NAME`_SYM_END) {
        error|= `$INSTANCE_NAME`_ERR_END_SYM;
    }
    /* Advance the rxBuffer to original state */
    *bufferState = `$INSTANCE_NAME`_BUFFER_RECEIVE_WAIT_FOR_START;
    /* Return the error code */
    return error;
} 

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_createPacket()
****************************************************************************//**
* \brief
*  Pack the data in the TX packet to the TX processBuffer
*
* \param packet
*  Pointer to the packet to pack
*
*
* \return
* A error code with the result of packing
*
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_createPacket(`$INSTANCE_NAME`_BUFFER_FULL_S* buffer) {
    uint32_t error = `$INSTANCE_NAME`_ERR_SUCCESS;
    /* Create local references */
    `$INSTANCE_NAME`_BUFFER_PROCESS_S* txBuffer = &(buffer->send.processBuffer);
    `$INSTANCE_NAME`_BUFFER_STATE_SEND_T* bufferState = &(buffer->send.bufferState);
    `$INSTANCE_NAME`_PACKET_S* packet = &(buffer->send.packet);
    
    /* Validate packet */
    /* Module ID */
    if(packet->moduleId > `$INSTANCE_NAME`_ID_MODULE_MAX) {
        error |= `$INSTANCE_NAME`_ERR_MODULE;
    }
    /* LEN less than max */
    if (packet->payloadLen > `$INSTANCE_NAME`_LEN_MAX_PAYLOAD ) {
        error |= `$INSTANCE_NAME`_ERR_LENGTH;
    }
    /* LEN less than process buffer max */
    if (packet->payloadLen > txBuffer->bufferLen) {
        error |= `$INSTANCE_NAME`_ERR_MEMORY;
    }
    /* Send buffer must not be busy */
    if(*bufferState != `$INSTANCE_NAME`_BUFFER_SEND_WAIT) {
       error |= `$INSTANCE_NAME`_ERR_STATE;
    }
    /* Assemble the packet if no error */
    if(!error) {
        /* Reset the buffer count */
        txBuffer->bufferIndex = ZERO;
        /* Header */
        txBuffer->buffer[(txBuffer->bufferIndex)++] = `$INSTANCE_NAME`_SYM_START;
        txBuffer->buffer[(txBuffer->bufferIndex)++] = packet->moduleId;
        txBuffer->buffer[(txBuffer->bufferIndex)++] = packet->cmd;
        /* Payload length MSB */
        txBuffer->buffer[(txBuffer->bufferIndex)++] = (packet->payloadLen >> BITS_ONE_BYTE) & MASK_BYTE_ONE;
        /* Payload length MSB */
        txBuffer->buffer[(txBuffer->bufferIndex)++] = (packet->payloadLen) & MASK_BYTE_ONE;
        /* Payload */
        uint16_t j;
        // @TODO: ensure data will fit in buffer
        for(j = ZERO; j < packet->payloadLen; j++) {
            txBuffer->buffer[(txBuffer->bufferIndex)++] = packet->payload[j];
        }
        /* Footer */
        uint16_t checksum = `$INSTANCE_NAME`_computeChecksum16(txBuffer->buffer, `$INSTANCE_NAME`_LEN_HEADER + packet->payloadLen);
        txBuffer->buffer[(txBuffer->bufferIndex)++] = (checksum >> BITS_ONE_BYTE) & MASK_BYTE_ONE;
        txBuffer->buffer[(txBuffer->bufferIndex)++] = (checksum) & MASK_BYTE_ONE;
        txBuffer->buffer[(txBuffer->bufferIndex)++] = `$INSTANCE_NAME`_SYM_END;
    }
    /* Return error code */
    return error;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_flushBuffers()
****************************************************************************//**
* \brief
*  Flush the RX and TX process buffer
*
* \param buffer
*  Pointer to the full buffers
*
* \return
* A error code with the result of packing
*
*******************************************************************************/
void `$INSTANCE_NAME`_flushBuffers(`$INSTANCE_NAME`_BUFFER_FULL_S* buffer){
     /* Reset TX buffers */
    buffer->send.processBuffer.bufferIndex = ZERO;
    buffer->send.bufferState = `$INSTANCE_NAME`_BUFFER_SEND_WAIT;
    /* Reset RX buffers */
    buffer->receive.processBuffer.bufferIndex = ZERO;
    buffer->receive.bufferState = `$INSTANCE_NAME`_BUFFER_RECEIVE_WAIT_FOR_START;   
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
