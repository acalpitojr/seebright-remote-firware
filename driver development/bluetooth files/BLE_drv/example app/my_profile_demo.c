


/**********************************************
*                Include files                *
**********************************************/
#include "bt_common.h"
#include "bt_spp_api.h"
#include "ble_api.h"
#include "my_profile.h"

/**********************************************
*         Variables and forward declarations  *
**********************************************/
void* qHandle;
uint32_t err;//error code

/*****************************************************************************
*   This software is copyright protected. All rights reserved
*   Toshiba Electronics Europe GmbH
*   European LSI Design and Engineering Center (ELDEC)
******************************************************************************
*   Description : Bluetooth(SPP) DEMO
******************************************************************************
*   PROJECT     : TC35661 "Bluetooth SPP"
*   MODULE      : Bluetooth SPP Driver
******************************************************************************
*   VERSION     : 1.00
*   DATE        : 1.12.2012
*****************************************************************************/


/**********************************************
*                Include files                *
**********************************************/
#include <stdint.h>
#include <stdio.h>
//#include "main.h"
#include "bt_common.h"

/**********************************************
*             Constants & Macros              *
**********************************************/



/**********************************************
*  Static variables and forward declarations  *
**********************************************/



void* btQueueEVENT = NULL;  /*this is only for freetos code i believe*/
/**************************************
**************************************/
//void vApplicationStackOverflowHook (xTaskHandle *pxTask, signed portCHAR *pcTaskName)
//{
    /* This function will get called if a task overflows its stack. */
 // (void)pxTask;
 // (void)pcTaskName;
 // while(1);
//}

/**************************************
**************************************/
void error(void){
  while(1);
}
/**************************************
**************************************/


/********************************************************************************
 Function       app_BT_SPP_DEMO(void* pvParameters)
 Argumets       :pvParameters
 Returns        :non
 Explanation    :
*********************************************************************************/
void my_profile_DEMO(void)
{
  uint32_t loop;
 // portBASE_TYPE queueRETURN;
  le_api_result_e eLeResult;
  uint16_t u16GAPSvcHandle;
  uint16_t u16DISvcHandle;
  uint16_t u16DICharDeclHndl;
  uint16_t u16DICharValDeclHndl;
  uint16_t u16MPSvcHndl;
  uint16_t u16MPCharDeclHndl;
  uint16_t au16MPCharValDeclHndl[4];
  uint16_t u16ConnHndl;
  uint16_t u16ClientRxMtuSize;
  le_conn_evt_st stConnectInfo;
  le_mtu_exchg_st stMtuEvtData;                       /* MTU Event Data */
  le_mtu_exchg_acc_resp_st stMtuAccResp;              /* MTU Accept Response */
  uint8_t au8DummyCharDescEvntData[50];               /* placeholder for characteristic desc. update evnt. */

  hr_init_st stMPInit;

  char auDevName[]="MY MPS";
  uint8_t au8ManufName[7] = {0x54,0x4F,0x53,0x48,0x49,0x42,0x41}; /* "Toshiba" string in UTF8-format */

 /*initializing the RESET PIN, AND TAKING THE DEVICE OUT OF RESET*/
#if 0
  #if defined(BOARD_TOPASM369_BT)
    /*RESET Chiron*/
    GPIO_SetOpenDrain(GPIO_PD, GPIO_BIT_7, ENABLE);//set PD7 to Open-drain
    GPIO_WriteDataBit(GPIO_PD, GPIO_BIT_7, 0);//set Reset signal to low
    GPIO_SetOutputEnableReg(GPIO_PD, GPIO_BIT_7, ENABLE);
    GPIO_SetInputEnableReg(GPIO_PD, GPIO_BIT_7, DISABLE);
    for(loop=0; loop< 40000;loop++){
    }
    GPIO_WriteDataBit(GPIO_PD, GPIO_BIT_7, 1);//set Reset signal to high
    for(loop=0; loop< 40000;loop++){
    }
    /*RESET Chiron*/
  #endif
#endif

//  /*Initiate OS resources for BT SPP driver*/
 // if(BT_os_init() != API_SUCCESS){
  //    while(1){};//endless loop
 // }

  /*Switch Chiron to TCU Compete mode*/
  //if(BT_hci_init((uint8_t *)(&BD_ADDR), (uint8_t *)&Device_Name) != API_SUCCESS){
  err = BT_hci_init((uint8_t *)(&BD_ADDR), (uint8_t *)&Device_Name);
  if(err != API_SUCCESS){
    while(1){};//endless loop
    }

  /* Prepare Heart Rate Profile Initialization Structure */
  stMPInit.pu8DevName = (uint8_t*)auDevName;                            /* Device Name of the Heart Rate Sensor */
  stMPInit.u8DevNameLen = sizeof(auDevName);                            /* Length of the Devace Name */
  stMPInit.pu16RetDevNameSvcHndl = &u16GAPSvcHandle;                    /* GAP Device Name Service Return Handle */

  stMPInit.pu8ManufName = au8ManufName;                                 /* GATT Manufacturer Name String Characteristic Value (Part of Device Identification Service) */
  stMPInit.pu8ManufNameLen = 7;                                         /* Manufacturer Name String length */

  stMPInit.pu16RetDISvcHndl = &u16DISvcHandle;                          /* GATT Device Identification Service Return Handle */
  stMPInit.pu16RetDICharDeclHndl = &u16DICharDeclHndl;                  /* GATT Device Identification Characteristic Declaration Return Handle */
  stMPInit.pu16RetDICharValDeclHndl = &u16DICharValDeclHndl;            /* GATT Device Identification Characteristic VALUE Declaration Return Handle */

  stMPInit.pu16RetMPSvcHndl = &u16MPSvcHndl;                            /* GATT Heart Rate Service Return Handle */
  stMPInit.pu16RetMPCharDeclHndl = &u16MPCharDeclHndl;                  /* GATT Heart Rate Measurement Characteristic Declaration Return Handle */
  stMPInit.pu16RetMPCharValDeclHndl = au16MPCharValDeclHndl;            /* GATT Heart Rate Measurement Characteristic VALUE Declaration Return Handle */



  stMPInit.pstConnectInfo = &stConnectInfo;                             /* Connection Info. Structure */
  stMPInit.pstMtuEvtData = &stMtuEvtData;                               /* MTU Event Data */
  stMPInit.pstMtuAccResp = &stMtuAccResp;                               /* MTU Accept Response */

  stMPInit.stCharDespEvt.pu8CharDescValue = au8DummyCharDescEvntData;   /* Write characteristic Descriptor placeholder */

  stMtuEvtData.pu16ConnHandle = &u16ConnHndl;
  stMtuEvtData.pu16ClientRxMtuSize = &u16ClientRxMtuSize;

  /* Initialize Heart Rate Profile */
  eLeResult = eMPInitialise(btQueueEVENT, &stMPInit);
  if(LE_API_SUCCCESS == eLeResult)
  {
    /* Start advertizing */
     eLeResult = eMPStartAdvertising(btQueueEVENT);
     if(eLeResult == LE_API_SUCCCESS)
     {
        // Start MP Profile Event Handler
        MPMainRoutine(btQueueEVENT, &stMPInit);
     }
  }
  while(1){};//endless loop
}
