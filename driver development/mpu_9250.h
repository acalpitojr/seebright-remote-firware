/*
 * mpu_9259.h
 *
 *  Created on: Oct 4, 2014
 *      Author: Owner
 */

#ifndef MPU_9259_H_
#define MPU_9259_H_


#ifndef __MSP430_HAS_USCI_Bx__
#define __MSP430_HAS_USCI_Bx__
#endif


#define MPU_SLAVE_ADDRESS  (0x68u)  /*according to datasheet  0110 1000*/
#define MPU_I2C            (USCI_B0_BASE)

#define MPU_LAST_ADDRESS  (100)  /*TBD*/



uint8_t init_mpu(void);
uint8_t mpu_write(uint8_t address, uint8_t data[], uint8_t data_length);
uint8_t mpu_read(uint8_t address, uint8_t data[], uint8_t data_length);

void mpu_test(void);





#endif /* MPU_9259_H_ */
