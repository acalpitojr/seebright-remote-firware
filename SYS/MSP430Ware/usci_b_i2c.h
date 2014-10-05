/* --COPYRIGHT--,BSD
 * Copyright (c) 2014, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
//*****************************************************************************
//
// usci_b_i2c.h - Driver for the USCI_B_I2C Module.
//
//*****************************************************************************

#ifndef __MSP430WARE_USCI_B_I2C_H__
#define __MSP430WARE_USCI_B_I2C_H__

#include "inc/hw_memmap.h"

//#ifdef __MSP430_HAS_USCI_Bx__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif
#define OFS_UCBxCTLW0__SPI     (0x0000)
#define OFS_UCBxCTLW0__SPI_L   OFS_UCBxCTLW0__SPI
#define OFS_UCBxCTLW0__SPI_H   OFS_UCBxCTLW0__SPI+1
#define OFS_UCBxCTL0__SPI      (0x0001)
#define OFS_UCBxCTL1__SPI      (0x0000)
#define OFS_UCBxBRW__SPI       (0x0006)
#define OFS_UCBxBRW__SPI_L     OFS_UCBxBRW__SPI
#define OFS_UCBxBRW__SPI_H     OFS_UCBxBRW__SPI+1
#define OFS_UCBxBR0__SPI       (0x0006)
#define OFS_UCBxBR1__SPI       (0x0007)
#define OFS_UCBxSTAT__SPI      (0x000A)
#define OFS_UCBxRXBUF__SPI     (0x000C)
#define OFS_UCBxTXBUF__SPI     (0x000E)
#define OFS_UCBxICTL__SPI      (0x001C)
#define OFS_UCBxICTL__SPI_L    OFS_UCBxICTL__SPI
#define OFS_UCBxICTL__SPI_H    OFS_UCBxICTL__SPI+1
#define OFS_UCBxIE__SPI        (0x001C)
#define OFS_UCBxIFG__SPI       (0x001D)
#define OFS_UCBxIV__SPI        (0x001E)

#define OFS_UCBxCTLW0          (0x0000)       /* USCI Bx Control Word Register 0 */
#define OFS_UCBxCTLW0_L        OFS_UCBxCTLW0
#define OFS_UCBxCTLW0_H        OFS_UCBxCTLW0+1
#define OFS_UCBxCTL0           (0x0001)
#define OFS_UCBxCTL1           (0x0000)
#define UCBxCTL1               UCBxCTLW0_L    /* USCI Bx Control Register 1 */
#define UCBxCTL0               UCBxCTLW0_H    /* USCI Bx Control Register 0 */
#define OFS_UCBxBRW            (0x0006)       /* USCI Bx Baud Word Rate 0 */
#define OFS_UCBxBRW_L          OFS_UCBxBRW
#define OFS_UCBxBRW_H          OFS_UCBxBRW+1
#define OFS_UCBxBR0            (0x0006)
#define OFS_UCBxBR1            (0x0007)
#define UCBxBR0                UCBxBRW_L      /* USCI Bx Baud Rate 0 */
#define UCBxBR1                UCBxBRW_H      /* USCI Bx Baud Rate 1 */
#define OFS_UCBxSTAT           (0x000A)       /* USCI Bx Status Register */
#define OFS_UCBxRXBUF          (0x000C)       /* USCI Bx Receive Buffer */
#define OFS_UCBxTXBUF          (0x000E)       /* USCI Bx Transmit Buffer */
#define OFS_UCBxI2COA          (0x0010)       /* USCI Bx I2C Own Address */
#define OFS_UCBxI2COA_L        OFS_UCBxI2COA
#define OFS_UCBxI2COA_H        OFS_UCBxI2COA+1
#define OFS_UCBxI2CSA          (0x0012)       /* USCI Bx I2C Slave Address */
#define OFS_UCBxI2CSA_L        OFS_UCBxI2CSA
#define OFS_UCBxI2CSA_H        OFS_UCBxI2CSA+1
#define OFS_UCBxICTL           (0x001C)       /* USCI Bx Interrupt Enable Register */
#define OFS_UCBxICTL_L         OFS_UCBxICTL
#define OFS_UCBxICTL_H         OFS_UCBxICTL+1
#define OFS_UCBxIE             (0x001C)
#define OFS_UCBxIFG            (0x001D)
#define UCBxIE                 UCBxICTL_L     /* USCI Bx Interrupt Enable Register */
#define UCBxIFG                UCBxICTL_H     /* USCI Bx Interrupt Flags Register */
#define OFS_UCBxIV             (0x001E)       /* USCI Bx Interrupt Vector Register */
//******************************************************************************
//
// The following is a struct that is passed to USCI_B_I2C_initMaster()
//
//******************************************************************************
typedef struct USCI_B_I2C_initMasterParam {
        uint8_t selectClockSource;
        uint32_t i2cClk;
        uint32_t dataRate;
} USCI_B_I2C_initMasterParam;

//*****************************************************************************
//
// The following are values that can be passed to the selectClockSource
// parameter for functions: USCI_B_I2C_masterInit().
//
//*****************************************************************************
#define USCI_B_I2C_CLOCKSOURCE_ACLK                                UCSSEL__ACLK
#define USCI_B_I2C_CLOCKSOURCE_SMCLK                              UCSSEL__SMCLK

//*****************************************************************************
//
// The following are values that can be passed to the dataRate parameter for
// functions: USCI_B_I2C_masterInit().
//
//*****************************************************************************
#define USCI_B_I2C_SET_DATA_RATE_400KBPS                                 400000
#define USCI_B_I2C_SET_DATA_RATE_100KBPS                                 100000

//*****************************************************************************
//
// The following are values that can be passed to the mode parameter for
// functions: USCI_B_I2C_setMode().
//
//*****************************************************************************
#define USCI_B_I2C_TRANSMIT_MODE                                           UCTR
#define USCI_B_I2C_RECEIVE_MODE                                            0x00

//*****************************************************************************
//
// The following are values that can be passed to the mask parameter for
// functions: USCI_B_I2C_enableInterrupt(), USCI_B_I2C_disableInterrupt(),
// USCI_B_I2C_clearInterruptFlag(), and USCI_B_I2C_getInterruptStatus() as well
// as returned by the USCI_B_I2C_getInterruptStatus() function.
//
//*****************************************************************************
#define USCI_B_I2C_STOP_INTERRUPT                                       UCSTPIE
#define USCI_B_I2C_START_INTERRUPT                                      UCSTTIE
#define USCI_B_I2C_RECEIVE_INTERRUPT                                     UCRXIE
#define USCI_B_I2C_TRANSMIT_INTERRUPT                                    UCTXIE
#define USCI_B_I2C_NAK_INTERRUPT                                       UCNACKIE
#define USCI_B_I2C_ARBITRATIONLOST_INTERRUPT                             UCALIE

//*****************************************************************************
//
// The following are values that can be passed toThe following are values that
// can be returned by the USCI_B_I2C_isBusy() function and the
// USCI_B_I2C_isBusBusy() function.
//
//*****************************************************************************
#define USCI_B_I2C_BUS_BUSY                                             UCBBUSY
#define USCI_B_I2C_BUS_NOT_BUSY                                            0x00

//*****************************************************************************
//
// The following are values that can be passed toThe following are values that
// can be returned by the USCI_B_I2C_masterIsStartSent() function.
//
//*****************************************************************************
#define USCI_B_I2C_SENDING_START                                        UCTXSTT
#define USCI_B_I2C_START_SEND_COMPLETE                                     0x00

//*****************************************************************************
//
// The following are values that can be passed toThe following are values that
// can be returned by the USCI_B_I2C_masterIsStopSent() function.
//
//*****************************************************************************
#define USCI_B_I2C_SENDING_STOP                                         UCTXSTP
#define USCI_B_I2C_STOP_SEND_COMPLETE                                      0x00

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
extern void USCI_B_I2C_initMaster(uint16_t baseAddress,
                                  USCI_B_I2C_initMasterParam *param);

extern void USCI_B_I2C_slaveInit(uint16_t baseAddress,
                                 uint8_t slaveAddress);

 void USCI_B_I2C_enable(uint16_t baseAddress);

extern void USCI_B_I2C_disable(uint16_t baseAddress);

extern void USCI_B_I2C_setSlaveAddress(uint16_t baseAddress,
                                       uint8_t slaveAddress);

extern void USCI_B_I2C_setMode(uint16_t baseAddress,
                               uint8_t mode);

extern void USCI_B_I2C_slaveDataPut(uint16_t baseAddress,
                                    uint8_t transmitData);

extern uint8_t USCI_B_I2C_slaveDataGet(uint16_t baseAddress);

extern uint8_t USCI_B_I2C_isBusBusy(uint16_t baseAddress);

extern uint8_t USCI_B_I2C_isBusy(uint16_t baseAddress);

extern uint8_t USCI_B_I2C_masterIsStopSent(uint16_t baseAddress);

extern uint8_t USCI_B_I2C_masterIsStartSent(uint16_t baseAddress);

extern void USCI_B_I2C_masterSendStart(uint16_t baseAddress);

extern void USCI_B_I2C_enableInterrupt(uint16_t baseAddress,
                                       uint8_t mask);

extern void USCI_B_I2C_disableInterrupt(uint16_t baseAddress,
                                        uint8_t mask);

extern void USCI_B_I2C_clearInterruptFlag(uint16_t baseAddress,
                                          uint8_t mask);

extern uint8_t USCI_B_I2C_getInterruptStatus(uint16_t baseAddress,
                                             uint8_t mask);

extern void USCI_B_I2C_masterSendSingleByte(uint16_t baseAddress,
                                            uint8_t txData);

extern uint8_t USCI_B_I2C_masterSendSingleByteWithTimeout(uint16_t baseAddress,
                                                       uint8_t txData,
                                                       uint32_t timeout);

extern void USCI_B_I2C_masterMultiByteSendStart(uint16_t baseAddress,
                                                uint8_t txData);

extern uint8_t USCI_B_I2C_masterMultiByteSendStartWithTimeout(uint16_t baseAddress,
                                                           uint8_t txData,
                                                           uint32_t timeout);

extern void USCI_B_I2C_masterMultiByteSendNext(uint16_t baseAddress,
                                               uint8_t txData);

extern uint8_t USCI_B_I2C_masterMultiByteSendNextWithTimeout(uint16_t baseAddress,
                                                          uint8_t txData,
                                                          uint32_t timeout);

extern void USCI_B_I2C_masterMultiByteSendFinish(uint16_t baseAddress,
                                                 uint8_t txData);

extern uint8_t USCI_B_I2C_masterMultiByteSendFinishWithTimeout(uint16_t baseAddress,
                                                            uint8_t txData,
                                                            uint32_t timeout);

extern void USCI_B_I2C_masterMultiByteSendStop(uint16_t baseAddress);

extern uint8_t USCI_B_I2C_masterMultiByteSendStopWithTimeout(uint16_t baseAddress,
                                                          uint32_t timeout);

extern void USCI_B_I2C_masterMultiByteReceiveStart(uint16_t baseAddress);

extern uint8_t USCI_B_I2C_masterMultiByteReceiveNext(uint16_t baseAddress);

extern uint8_t USCI_B_I2C_masterMultiByteReceiveFinish(uint16_t baseAddress);

extern uint8_t USCI_B_I2C_masterMultiByteReceiveFinishWithTimeout(uint16_t baseAddress,
                                                               uint8_t *rxData,
                                                               uint32_t timeout);

extern void USCI_B_I2C_masterMultiByteReceiveStop(uint16_t baseAddress);

extern void USCI_B_I2C_masterSingleReceiveStart(uint16_t baseAddress);

extern uint8_t USCI_B_I2C_masterSingleReceiveStartWithTimeout(uint16_t baseAddress,
                                                           uint32_t timeout);

extern uint8_t USCI_B_I2C_masterSingleReceive(uint16_t baseAddress);

extern uint32_t USCI_B_I2C_getReceiveBufferAddressForDMA(uint16_t baseAddress);

extern uint32_t USCI_B_I2C_getTransmitBufferAddressForDMA(uint16_t baseAddress);

uint8_t i2c_start( uint16_t baseAddress);
void i2c_set_slave_address( uint16_t baseAddress, uint8_t slave_address);
void i2c_send_byte(uint16_t baseAddress,uint8_t data);
uint8_t i2c_send_stop(uint16_t baseAddress);
uint8_t wait_for_txempty(uint16_t baseAddress);
uint8_t i2c_wait_for_byte(uint16_t baseAddres);
uint8_t i2c_get_byte(uint16_t baseAddress);
uint8_t i2c_receive_mode(uint16_t baseAddress);
uint8_t wait_for_stop(uint16_t baseAddresss);
uint8_t i2c_transmit_mode(uint16_t baseAddress);

//*****************************************************************************
//
// DEPRECATED APIS.
//
//*****************************************************************************
#define USCI_B_I2C_masterIsSTOPSent                 USCI_B_I2C_masterIsStopSent

//*****************************************************************************
//
// The following are deprecated APIs.
//
//*****************************************************************************
extern void USCI_B_I2C_masterInit(uint16_t baseAddress,
                                  uint8_t selectClockSource,
                                  uint32_t i2cClk,
                                  uint32_t dataRate);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

//#endif
#endif // __MSP430WARE_USCI_B_I2C_H__
