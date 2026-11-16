/**
* @file Flash.c
* @brief Internal Flash driver using LPC17xx IAP.
* @version 2.1
* @date 09 Nov 2025
* @author Mike
*/

#include "Flash.h"

#include "LPC17xx.h"
#include "system_LPC17xx.h"

typedef void (*IAP_Function)(uint32_t command[], uint32_t result[]);
static const IAP_Function iap_entry = (IAP_Function)IAP_LOCATION;

static void IAP_Command(uint32_t command[], uint32_t result[]) {

	uint32_t primask = __get_PRIMASK();
	__disable_irq();
	iap_entry(command, result);
	__set_PRIMASK(primask);
}
IAP_Status_Codes FLASH_VerifyBlankData() {
    uint32_t command[5] = {0U};
    uint32_t result[5] = {0U};

    command[0] = IAP_CHECK_BLANK;
    command[1] = SECTOR;
    command[2] = SECTOR;
    IAP_Command(command, result);

    return (IAP_Status_Codes)result[0];
}
IAP_Status_Codes FLASH_EraseSector(unsigned int sector) {
    uint32_t command[5] = {0U};
    uint32_t result[5] = {0U};

    command[0] = IAP_PREP;
    command[1] = sector;
    command[2] = sector;
    IAP_Command(command, result);

    if (result[0] != CMD_SUCCESS) return (IAP_Status_Codes)result[0];

    command[0] = IAP_ERASE;
    command[1] = sector;
    command[2] = sector;
    command[3] = (SystemCoreClock / 1000U);
    IAP_Command(command, result);

    return (IAP_Status_Codes)result[0];
}

IAP_Status_Codes FLASH_WriteData(void *dstAddr, void *srcAddr, unsigned int size) {
    uint32_t command[5] = {0U};
    uint32_t result[5] = {0U};

    if ((dstAddr == 0) || (srcAddr == 0)) return INVALID_COMMAND;

    unsigned int newsize;
    if (size == 0U || size > 4096U) return COUNT_ERROR;
    else if (size <= 256U)  newsize = 256U;
    else if (size <= 512U)  newsize = 512U;
    else if (size <= 1024U) newsize = 1024U;
    else                    newsize = 4096U;

    uint32_t buf[newsize];
    memset(buf, 0xFF, newsize);
    memcpy(buf, srcAddr, size);

    command[0] = IAP_PREP;
    command[1] = SECTOR;
    command[2] = SECTOR;
    IAP_Command(command, result);

    if (result[0] != CMD_SUCCESS) return (IAP_Status_Codes)result[0];

    command[0] = IAP_COPY;
    command[1] = (uint32_t)dstAddr;
    command[2] = (uint32_t)buf;
    command[3] = newsize;
    command[4] = (SystemCoreClock / 1000U);
    IAP_Command(command, result);

    return (IAP_Status_Codes)result[0];
}

IAP_Status_Codes FLASH_VerifyData(void *dstAddr, void *srcAddr, unsigned int size) {
    uint32_t command[5] = {0U};
    uint32_t result[5] = {0U};

    if ((dstAddr == 0) || (srcAddr == 0) || (size == 0U)) return INVALID_COMMAND;

    command[0] = IAP_COMP;
    command[1] = (uint32_t)dstAddr;
    command[2] = (uint32_t)srcAddr;
    command[3] = size;
    IAP_Command(command, result);

    return (IAP_Status_Codes)result[0];
}
