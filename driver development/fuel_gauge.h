#ifndef FUEL_GUAGE_H_
#define FUEL_GAUGE_H_

#ifndef __MSP430_HAS_USCI_Bx__
#define __MSP430_HAS_USCI_Bx__
#endif


#define FUEL_GAUGE_SLAVE_ADDRESS  (0x55u)  /*according to datasheet*/
#define FUEL_GAUGE_I2C            (USCI_B1_BASE)
#define FUEL_GAUGE_SIZE           (128u)  /*change this to last register+1*/
#define FUEL_GAUGE_LAST_ADDRESS  (FUEL_GAUGE_SIZE-1)  /* */



uint8_t init_fuel_gauge(void);
uint8_t fuel_gauge_write(uint8_t data[], uint8_t data_length);
uint8_t fuel_gauge_read(uint8_t data[], uint8_t data_length);

void fuel_gauge_test(void);

#endif