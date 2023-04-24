#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "amcom_unit_test.h"
#include "amcom.h"

static uint8_t minPacket[] = {0xa1, 0x37, 0x00, 0x12, 0x0b}; 
static uint8_t typPacket[] = {0xa1, 0x0d, 0x14, 0x3d, 0xd6, 0x54, 0x68, 0x69, 0x73, 0x20, 0x69, 0x73, 0x20, 0x74, 0x65, 0x73, 0x74, 0x20, 0x70, 0x61, 0x79, 0x6c, 0x6f, 0x61, 0x64};
static uint8_t maxPacket[] = {0xa1, 0x2c, 0xc8, 0x62, 0xb9, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};


static bool test_serialize_min(void) {
    printf("Test 0: Checking serialization of a packet with minimum length...");
  
    uint8_t buf[AMCOM_MAX_PACKET_SIZE];
    size_t s = AMCOM_Serialize(55, NULL, 0, buf);
    if (s != sizeof(minPacket)) {
        printf("  Invalid result of AMCOM_Serialize\n");
        return false;
    }
    if (memcmp(buf, minPacket, s)) {
        printf("  Invalid output of AMCOM Serialize\n");
        printf("  expecting: ");
        for (size_t i = 0; i < s; i++) {
            printf("0x%.2x ", minPacket[i]);
        }
        printf("\n     actual: ");
        for (size_t i = 0; i < s; i++) {
            printf("0x%.2x ", buf[i]);
        }
        printf("\n             ");
        for (size_t i = 0; i < s; i++) {
            if (buf[i] != minPacket[i]) {
                printf("^^^^ ");
            } else {
                printf("     ");
            }
        }
        printf("\n");
        return false;
    }
    printf("OK\n");
    return true;
}

static bool test_serialize_typical(void) {
    printf("Test 1: Checking serialization of a typical packet...");
  
    uint8_t buf[AMCOM_MAX_PACKET_SIZE];
    size_t s = AMCOM_Serialize(13, "This is test payload", 20, buf);

    if (s != sizeof(typPacket)) {
        printf("  Invalid result of AMCOM_Serialize\n");
        return false;
    }
    if (memcmp(buf, typPacket, s)) {
        printf("  Invalid output of AMCOM Serialize\n");
        printf("  expecting: ");
        for (size_t i = 0; i < s; i++) {
            printf("0x%.2x ", typPacket[i]);
        }
        printf("\n     actual: ");
        for (size_t i = 0; i < s; i++) {
            printf("0x%.2x ", buf[i]);
        }
        printf("\n             ");
        for (size_t i = 0; i < s; i++) {
            if (buf[i] != typPacket[i]) {
                printf("^^^^ ");
            } else {
                printf("     ");
            }
        }
        printf("\n");
        return false;
    }
    printf("OK\n");
    return true;
}

static bool test_serialize_max(void) {
    printf("Test 2: Checking serialization of a packet with maximum length...");
  
    uint8_t buf[AMCOM_MAX_PACKET_SIZE];
    size_t s = AMCOM_Serialize(44, "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789", 200, buf);
    if (s != sizeof(maxPacket)) {
        printf("  Invalid result of AMCOM_Serialize");
        return false;
    }
    if (memcmp(buf, maxPacket, s)) {
        printf("  Invalid output of AMCOM Serialize\n");
        printf("  expecting: ");
        for (size_t i = 0; i < s; i++) {
            printf("0x%.2x ", maxPacket[i]);
        }
        printf("\n     actual: ");
        for (size_t i = 0; i < s; i++) {
            printf("0x%.2x ", buf[i]);
        }
        printf("\n");
        return false;
    }
    printf("OK\n");
    return true;
}

static AMCOM_Receiver amReceiver;
static AMCOM_Packet receivedPacket;
static void* receivedContext;
static void packet_handler(const AMCOM_Packet* packet, void* userContext) {
    printf("got packet...");
    memcpy(&receivedPacket, packet, sizeof(receivedPacket));
    receivedContext = userContext;
}

static bool test_deserialize_min(void) {
    printf("Test 3: Checking deserialization of a packet with minimum length...");
    
    memset(&receivedPacket, 0x00, sizeof(receivedPacket));
    AMCOM_Deserialize(&amReceiver, minPacket, sizeof(minPacket));
    
    printf("check...");
    if (receivedPacket.header.type != 55) {
        printf("bad type\n");
        return false;
    }
    if (receivedPacket.header.length != 0) {
        printf("bad length\n");
        return false;
    }
    printf("OK\n");
    return true;
}

static bool test_deserialize_typ(void) {
    printf("Test 4: Checking deserialization of a typical packet...");
    
    memset(&receivedPacket, 0x00, sizeof(receivedPacket));
    AMCOM_Deserialize(&amReceiver, typPacket, sizeof(typPacket));
    
    printf("check...");
    if (receivedPacket.header.type != 13) {
        printf("bad type\n");
        return false;
    }
    if (receivedPacket.header.length != 20) {
        printf("bad length\n");
        return false;
    }
    if (0 != memcmp(receivedPacket.payload, "This is test payload", 20)) {
        printf("bad payload\n");
        return false;
    }
    printf("OK\n");
    return true;
}

static bool test_deserialize_max(void) {
    printf("Test 5: Checking deserialization of a packet with maximum length...");
    
    memset(&receivedPacket, 0x00, sizeof(receivedPacket));
    AMCOM_Deserialize(&amReceiver, maxPacket, sizeof(maxPacket));
    
    printf("check...");
    if (receivedPacket.header.type != 44) {
        printf("bad type\n");
        return false;
    }
    if (receivedPacket.header.length != 200) {
        printf("bad length\n");
        return false;
    }
    if (0 != memcmp(receivedPacket.payload, "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789", 200)) {
        printf("bad payload\n");
        return false;
    }
    printf("OK\n");
    return true;
}

static bool test_deserialize_max_fragm(void) {
    printf("Test 6: Checking fragmented deserialization of a packet with maximum length...");
    
    memset(&receivedPacket, 0x00, sizeof(receivedPacket));
    AMCOM_Deserialize(&amReceiver, maxPacket, 20);
    if (receivedPacket.header.type != 0) {
        printf("output touched too early\n");
        return false;
    }
    AMCOM_Deserialize(&amReceiver, maxPacket+20, 30);
    if (receivedPacket.header.type != 0) {
        printf("output touched too early\n");
        return false;
    }
    AMCOM_Deserialize(&amReceiver, maxPacket+50, 50);
    if (receivedPacket.header.type != 0) {
        printf("output touched too early\n");
        return false;
    }
    AMCOM_Deserialize(&amReceiver, maxPacket+100, 105);
    
    printf("check...");
    if (receivedPacket.header.type != 44) {
        printf("bad type\n");
        return false;
    }
    if (receivedPacket.header.length != 200) {
        printf("bad length\n");
        return false;
    }
    if (0 != memcmp(receivedPacket.payload, "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789", 200)) {
        printf("bad payload\n");
        return false;
    }
    printf("OK\n");
    return true;
}

static bool test_user_context(void) {
    printf("Test 7: Checking user context forwarding...");
    
    memset(&receivedPacket, 0x00, sizeof(receivedPacket));
    AMCOM_InitReceiver(&amReceiver, packet_handler, (void*)&test_user_context);
    AMCOM_Deserialize(&amReceiver, minPacket, sizeof(minPacket));
    
    printf("check...");
    if (receivedContext != test_user_context) {
        printf("bad user context\n");
        return false;
    }
    printf("OK\n");
    return true;
}

static bool gotPacket = false;
static void packet_handler_rand(const AMCOM_Packet* packet, void* userContext) {
    printf("got packet...");
    gotPacket = true;
}
static bool test_random_input(void) {
    printf("Test 8: Checking against random input...");
    
    AMCOM_InitReceiver(&amReceiver, packet_handler_rand, NULL);
    for (size_t i = 0; i < 1000000; i++) {
        uint8_t byte = (uint8_t)rand();
        AMCOM_Deserialize(&amReceiver, &byte, 1);
    }    
    if (gotPacket) {
        printf("should not receive packet\n");
        return false;
    }
    printf("OK\n");
    return true;
}


bool AMCOM_UnitTest(void) {
    /* Intializes random number generator */
    time_t t;
    srand((unsigned) time(&t));
   
    if (!test_serialize_min()) {
        return false;
    }
    if (!test_serialize_typical()) {
        return false;
    }
    if (!test_serialize_max()) {
        return false;
    }
    AMCOM_InitReceiver(&amReceiver, packet_handler, NULL);
    if (!test_deserialize_min()) {
        return false;
    }
    if (!test_deserialize_typ()) {
        return false;
    }
    if (!test_deserialize_max()) {
        return false;
    }
    if (!test_deserialize_max_fragm()) {
        return false;
    }
    if (!test_user_context()) {
        return false;
    }
    if (!test_random_input()) {
        return false;
    }
    return true;
}