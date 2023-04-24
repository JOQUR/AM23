#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "amcom.h"

/// Start of packet character
const uint8_t  AMCOM_SOP         = 0xA1;
const uint16_t AMCOM_INITIAL_CRC = 0xFFFF;



static uint16_t AMCOM_UpdateCRC(uint8_t byte, uint16_t crc)
{
	byte ^= (uint8_t)(crc & 0x00ff);
	byte ^= (uint8_t)(byte << 4);
	return ((((uint16_t)byte << 8) | (uint8_t)(crc >> 8)) ^ (uint8_t)(byte >> 4) ^ ((uint16_t)byte << 3));
}


void AMCOM_InitReceiver(AMCOM_Receiver* receiver, AMCOM_PacketHandler packetHandlerCallback, void* userContext) {
	// TODO
}

size_t AMCOM_Serialize(uint8_t packetType, const void* payload, size_t payloadSize, uint8_t* destinationBuffer) {
	
    //starting value of crc
    uint16_t crc = AMCOM_INITIAL_CRC;

    //saving array to buffer
    const uint8_t* buff = payload;


    if(NULL == destinationBuffer)
    {
        printf("destinationBuffer is a NULL ptr!");
        return 0;
    }

    int size = 0;

    // Add SOP Field
    destinationBuffer[size] = AMCOM_SOP;
    size++;

    // Add TYPE Field
    destinationBuffer[size] = packetType;
    size++; 
    destinationBuffer[size] = payloadSize;
    size++;

    // Skipping crc fields 
    size++;
    size++;

    // calculating CRC
    crc = AMCOM_UpdateCRC(packetType, crc);
    crc = AMCOM_UpdateCRC(payloadSize, crc);

    if((payloadSize > 0) && (NULL != payload))
    {
        int i = 0;
        for(; i < payloadSize; i++)
        {
            destinationBuffer[5 + i] = buff[i];
            crc = AMCOM_UpdateCRC(buff[i], crc);
            size++;
        }
    }

    //save crc
    destinationBuffer[4] = (uint8_t)((crc & 0xff00) >> 8);
    destinationBuffer[3] = (uint8_t)(crc & 0x00ff);
    
    printf("\ncrc = 0x%.4x\n", crc);
	return size;
}

void AMCOM_Deserialize(AMCOM_Receiver* receiver, const void* data, size_t dataSize) {
    // TODO
}
