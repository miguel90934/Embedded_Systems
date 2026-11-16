/**
 * @file flash.h
 * @brief Flash Driver API for LPC1769.
 *
 * This module probvides functions to Read/and write on the FLASH memory.
 * It has functions for Erasing sectors, writing and comparing memory data.
 *
 * @version 1
 * @date 10 Nov 2026
 * @author Mike
 *
 * @note This is for the second project of SE
 * @warning To Write on the flash you need to write in multiples of 256.
 */

#ifndef FLASH_H_
#define FLASH_H_

#include <stdint.h>
#include <string.h>

/**
 * @page quick_api Quick API Reference
 *
 * ### Flash Driver (`flash.h`)
 * | Function | Description | Example |
 * | :--- | :--- | :--- |
 * | @ref FLASH_EraseSector | Erases an entire Sector in the Flash memory. | `FLASH_EraseSector(29);` |
 * | @ref FLASH_WriteData | Writes in the flash, from the provided address and size. | `FLASH_WriteData((void *)SECTOR_POS, &data, sizeof(data));` |
 * | @ref FLASH_VerifyData | Compares given data to the already written data in the Flash. | `FLASH_VerifyData((void *)SECTOR_POS, &data, sizeof(data));` |
 */

/**
 * @addtogroup DRIVERS
 * @{
 */

/**
 * @defgroup Flash - Flash management Driver
 * @brief Driver to Erase, write and copy from the flash.
 * @{
 */


/**
 * @defgroup Flash_Macros - IAP andd flash Macros.
 * @brief IAP commands and Location.
 * @{
 */

#define IAP_LOCATION    0x1FFF1FF1UL  /*!< The location to call the IAP commands/                   */

/*
 * Sector to store Data.
 * LPC1769 sector 29 starts at 0x00078000 and has 32 KB.
 */
#define SECTOR_POS      0x00078000UL /*!< Sector 29 memory location/                  */
#define SECTOR          29U
#define SECTOR_SIZE     0x8000U
//
#define IAP_ERASE       52U	/*!< IAP Erase command/                  */
#define IAP_COPY        51U /*!< IAP Copy command/                  */
#define IAP_PREP        50U /*!< IAP Prepare command/                  */
#define IAP_COMP        56U /*!< IAP Compare command/                  */
#define IAP_CHECK_BLANK 53U /*!< IAP Compare command/                  */
/** @} */ // FLASH_MACROS

/**
 * @brief Typedef Struct for the possible IAP Response status codes.
 */
typedef enum
{
    CMD_SUCCESS = 0,                /**<Command executed successfully. */
    INVALID_COMMAND,                /**<Invalid command. */
    SRC_ADDR_ERROR,                 /**<Source address not on word boundary. */
    DST_ADDR_ERROR,                 /**<Destination address not on correct boundary. */
    SRC_ADDR_NOT_MAPPED,            /**<Source address not mapped in memory map. */
    DST_ADDR_NOT_MAPPED,            /**<Destination address not mapped in memory map. */
    COUNT_ERROR,                    /**<Byte count invalid.*/
    INVALID_SECTOR,                 /**<Invalid sector number. */
    SECTOR_NOT_BLANK,               /**<Sector not blank. */
    SECTOR_NOT_PREPARED_FOR_WRITE,  /**<Sector not prepared for write operation. */
    COMPARE_ERROR,                  /**<Source and destination data not equal. */
    BUSY                            /**<Flash programming hardware is busy. */
}  IAP_Status_Codes;

IAP_Status_Codes FLASH_VerifyBlankData();
/**
 * @brief Erases one Flash sector.
 * @param sector - sector number.
 * @return IAP result code.
 */
IAP_Status_Codes FLASH_EraseSector(unsigned int sector);

/**
 * @brief Writes data block referenced by srcAddr into Flash at dstAddr.
 *
 * @note LPC17xx IAP copy command only supports sizes 256, 512, 1024 or 4096 bytes. This function Prepares the sector first then erases, as stated in the LPC manual.
 *
 * @param dstAddr - destination Flash address.
 * @param srcAddr - source RAM address.
 * @param size - number of bytes to write.
 * @return IAP result code.
 */
IAP_Status_Codes FLASH_WriteData(void *dstAddr, void *srcAddr, unsigned int size);

/**
 * @brief Compares data block referenced by srcAddr with Flash at dstAddr.
 * @param dstAddr - destination Flash address.
 * @param srcAddr - source address.
 * @param size - number of bytes to compare.
 * @return IAP result code.
 */
IAP_Status_Codes FLASH_VerifyData(void *dstAddr, void *srcAddr, unsigned int size);

/** @} */  // FLASH
/** @} */  // DRIVERS

#endif /* FLASH_H_ */
