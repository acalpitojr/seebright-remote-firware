/*
 * eeprom.h
 *
 *  Created on: Oct 4, 2014
 *      Author: Owner
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#ifndef __MSP430_HAS_USCI_Bx__
#define __MSP430_HAS_USCI_Bx__
#endif


#define EEPROM_SLAVE_ADDRESS  (0x50u)  /*according to datasheet*/
#define EEPROM_I2C            (USCI_B1_BASE)
#define EEPROM_SIZE           (128u)
#define EEPROM_LAST_ADDRESS  (EEPROM_SIZE-1)  /*128 byte eeprom, 0-127*/



uint8_t init_eeprom(void);
uint8_t eeprom_write(uint8_t address, uint8_t data[], uint8_t data_length);
uint8_t eeprom_read(uint8_t address, uint8_t data[], uint8_t data_length);

void eeprom_test(void);


#endif /* EEPROM_H_ */
