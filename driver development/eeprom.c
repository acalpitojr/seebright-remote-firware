
#include "driverlib.h"

#include "eeprom.h"




#if 0
void main(void)
{


#if 0
       init_eeprom();
       uint8_t read_data[4] = {0x00};
       uint8_t write_data[4] = {1,2,3,4};

        while(1)
        {

            eeprom_write(0x00, (uint8_t*)&write_data, 4 );  /*write to eeprom address 0x00, 4 bytes of data*/
            __delay_cycles(0xffff);

             memset( read_data,  0x00, sizeof(read_data)) ;  /*clear data before we fill it with what is stored in eeprom*/

            eeprom_read(0x00, (uint8_t*)&read_data,4  );  /*read from eeprom address 0x00, 4 bytes of data*/
           __delay_cycles(0xffff);

        }
#endif
eeprom_test();


}

#endif


uint8_t init_eeprom(void)
{
    uint8_t result = 1;
    CYC_SYS_I2CB1_Enable();

    return result;
}


uint8_t eeprom_write(uint8_t address, uint8_t data[], uint8_t data_length)
{
    enum{ VALIDATE_PARAMETERS,
          START_CONDITION_AND_SLAVE_ADDRESS,
          SEND_ADDRESS_TO_WRITE_TO,
          SEND_BYTE,
          SEND_STOP,
          DONE,
    }state = VALIDATE_PARAMETERS;

    uint8_t index = 0;
    uint8_t last_index = 0;
    uint8_t result = 0;

    while(state!=DONE)
    {
        switch(state)
        {/*----------------------------------------------------------*/
            case VALIDATE_PARAMETERS:
         /*----------------------------------------------------------*/
                if( (address <= EEPROM_LAST_ADDRESS) && (data_length > 0) && ((address+data_length)<=EEPROM_SIZE) )
                {
                    last_index = (data_length-1);
                    state = START_CONDITION_AND_SLAVE_ADDRESS;
                }
                else
                {
                    result = 0;
                    state = DONE;
                }
            break;
         /*----------------------------------------------------------*/
            case START_CONDITION_AND_SLAVE_ADDRESS:
         /*----------------------------------------------------------*/
                // send the start with the slave address, wait for start to complete
                USCI_B_I2C_setSlaveAddress(EEPROM_I2C,EEPROM_SLAVE_ADDRESS);
                i2c_transmit_mode(EEPROM_I2C);

                uint8_t tries = 0;
                const uint8_t max_tries = 5;

                while(state == START_CONDITION_AND_SLAVE_ADDRESS)
                {
                    if(tries<max_tries)
                    {
                        i2c_start(EEPROM_I2C);  /*SEND START AND SLAVE ADDRESS*/

                        if( wait_for_txempty(EEPROM_I2C) == 1)
                        {   state = SEND_ADDRESS_TO_WRITE_TO;  /*SLAVE ACKED, NOW SEND ADDRESS*/
                        }
                        else  /*ACK from eeprom timed out, or we got a NACK.  We need to send a stop, and try again*/
                        {   i2c_send_stop(EEPROM_I2C);   /*eeprom is busy, do some retries*/
                            tries++;
                            state = START_CONDITION_AND_SLAVE_ADDRESS;
                        }
                    }
                    else  /*MAX RETIRES REACHED, EEPROM IS NOT RESPONDING*/
                    {   result = 0;
                        state = SEND_STOP;
                    }
                }
             break;
        /*----------------------------------------------------------*/
            case SEND_ADDRESS_TO_WRITE_TO:
        /*----------------------------------------------------------*/
                i2c_send_byte(EEPROM_I2C, address);

                if( wait_for_txempty( EEPROM_I2C) )
                {   state = SEND_BYTE;
                }
                else
                {   result = 0;
                    state = SEND_STOP;
                }
            break;
            /*----------------------------------------------------------*/
            case SEND_BYTE:
            /*----------------------------------------------------------*/
                while(state == SEND_BYTE)
                {
                    if(index<=last_index)  /*STILL DATA TO SEND*/
                    {
                        i2c_send_byte(EEPROM_I2C, data[index]);  /* send the data byte you want to write*/
                        if( wait_for_txempty( EEPROM_I2C) == 1)
                        {  index++;
                           state = SEND_BYTE;
                        }
                        else
                        {  result = 0;
                           state = SEND_STOP;
                        }
                    }
                  else
                  {  result = 1;  /*completed sending*/
                     state = SEND_STOP;
                  }
             }
              break;
              /*----------------------------------------------------------*/
            case SEND_STOP:
                /*----------------------------------------------------------*/
                i2c_send_stop(EEPROM_I2C);   /*eeprom is busy, do some retries*/
                state = DONE;
            break;

            /*----------------------------------------------------------*/
            default:
            /*----------------------------------------------------------*/
                i2c_send_stop(EEPROM_I2C);   /*to be safe*/
                result = 0;
                state = DONE;
            break;
        }/*switch*/
    }/*while*/

    return result;

}


uint8_t eeprom_read(uint8_t address, uint8_t data[], uint8_t data_length)
{
    enum{  VALIDATE_PARAMETERS,
          START_CONDITION_AND_SLAVE_ADDRESS,
          SEND_ADDRESS_TO_READ_FROM,
          SWITCH_TO_RECEIVE_MODE,
          RECEIVE_BYTES,
          SEND_STOP,
          DONE,
    }state = VALIDATE_PARAMETERS;



    uint8_t index = 0;
    uint8_t last_index = 0;
    uint8_t result = 0;
    uint8_t bytes_to_receive;



    while(state!=DONE)
    {
    switch(state)
    {/*----------------------------------------------------------*/
        case VALIDATE_PARAMETERS:
     /*----------------------------------------------------------*/
            if( (address <= EEPROM_LAST_ADDRESS) && (data_length > 0) && ((address+data_length)<=EEPROM_SIZE) )
            {
                last_index = (data_length-1);
                bytes_to_receive = (data_length-1);
                state = START_CONDITION_AND_SLAVE_ADDRESS;
            }
            else
            {
                result = 0;
                state = DONE;
            }
        break;
        /*----------------------------------------------------------*/
        case START_CONDITION_AND_SLAVE_ADDRESS:
            /*----------------------------------------------------------*/
            // send the start with the slave address, wait for start to complete
            USCI_B_I2C_setSlaveAddress(EEPROM_I2C,EEPROM_SLAVE_ADDRESS);
            i2c_transmit_mode(EEPROM_I2C);

            uint8_t tries = 0;
            const uint8_t max_tries = 5;

            while(state == START_CONDITION_AND_SLAVE_ADDRESS)
            {
                if(tries<max_tries)
                {
                    i2c_start(EEPROM_I2C);  /*SEND START AND SLAVE ADDRESS*/

                    if( wait_for_txempty(EEPROM_I2C) == 1)  /*looks for nack also*/
                    {   state = SEND_ADDRESS_TO_READ_FROM;  /*SLAVE ACKED, NOW SEND ADDRESS WE WANT TO READ FROM*/
                    }
                    else  /*ACK from eeprom timed out, or we got a NACK.  We need to send a stop, and try again*/
                    {   i2c_send_stop(EEPROM_I2C);   /*eeprom is busy, do some retries*/
                        tries++;
                        state = START_CONDITION_AND_SLAVE_ADDRESS;
                    }
                }
                else  /*MAX RETIRES REACHED, EEPROM IS NOT RESPONDING*/
                {   result = 0;
                    state = SEND_STOP;
                }
            }
         break;
         /*----------------------------------------------------------*/
             case SEND_ADDRESS_TO_READ_FROM:
         /*----------------------------------------------------------*/
                 i2c_send_byte(EEPROM_I2C, address);

                 if( wait_for_txempty( EEPROM_I2C) )
                 {   state = SWITCH_TO_RECEIVE_MODE;
                 }
                 else
                 {   result = 0;
                     state = SEND_STOP;
                 }
             break;
             /*----------------------------------------------------------*/
                 case SWITCH_TO_RECEIVE_MODE:
             /*----------------------------------------------------------*/
                     i2c_receive_mode(EEPROM_I2C);
                     i2c_start(EEPROM_I2C);
                     if( wait_for_txempty( EEPROM_I2C) )
                     {   state = RECEIVE_BYTES;
                     }
                     else
                     {   result = 0;
                         state = SEND_STOP;
                     }

                 break;
                 /*----------------------------------------------------------*/
                     case RECEIVE_BYTES:
                 /*----------------------------------------------------------*/

                         for(index = 0; index<last_index; index++)
                         {
                              i2c_wait_for_byte(EEPROM_I2C);
                              data[index] =  i2c_get_byte(EEPROM_I2C);  /*once this data is read, the eeprom will start sending the next*/
                         }
                         i2c_send_stop( EEPROM_I2C);
                         i2c_wait_for_byte(EEPROM_I2C);
                          data[index] = i2c_get_byte(EEPROM_I2C);  /*after reading this byte, we will not give the slave an ack, so the communication will end*/
                          wait_for_stop(EEPROM_I2C);
                          i2c_get_byte(EEPROM_I2C);  /*just in case*/
                          state = DONE;

                         break;
                /*----------------------------------------------------------*/
                case SEND_STOP:
                /*----------------------------------------------------------*/
                     i2c_send_stop(EEPROM_I2C);   /*eeprom is busy, do some retries*/
                     state = DONE;
             break;
             /*----------------------------------------------------------*/
             default:
             /*----------------------------------------------------------*/
                 i2c_send_stop(EEPROM_I2C);   /*to be safe*/
                 result = 0;
                 state = DONE;
             break;
        }/*switch*/
    }/*while*/


  return result;
}


void eeprom_test(void)
{
   init_eeprom();



   uint8_t read_data[4] = {0x00};
   uint8_t write_data[4] = {1,2,3,4};



    eeprom_write(0x00, (uint8_t*)&write_data, 4 );  /*write to eeprom address 0x00, 4 bytes of data*/
    __delay_cycles(0xffff);

     memset( read_data,  0x00, sizeof(read_data)) ;  /*clear data before we fill it with what is stored in eeprom*/

    eeprom_read(0x00, (uint8_t*)&read_data,4  );  /*read from eeprom address 0x00, 4 bytes of data*/
   __delay_cycles(0xffff);


}

