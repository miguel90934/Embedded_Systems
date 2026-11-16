/**
 * @file    lab_07.h
 * @brief   Lab 07: persistent data in FLASH sector 29.
 */
#ifndef LAB_07_H_
#define LAB_07_H_

/**
 * @brief  Lab 07 test program (never returns).
 *
 * On boot, shows the data stored in FLASH sector 29 (if valid).
 * Button A erases the sector, button B writes and verifies the data.
 *
 * @return Never returns; declared int for consistency with the other labs.
 */
int LAB_07(void);

#endif /* LAB_07_H_ */
