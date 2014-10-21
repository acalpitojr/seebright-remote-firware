/****************************************************************************
*   COPYRIGHT 2006-2009 All rights reserved
*   Toshiba Electronics Europe GmbH
*   European LSI Design and Engineering Center (ELDEC)
*****************************************************************************
*   File Name   : $RCSfile: booting.h,v $
*   Description : Contains global booting definitions
*****************************************************************************
*   PROJECT     : Bluetooth BLE
*   MODULE      : Heart Rate BLE Profile
*               : $Name:  $
*   LIBRARIES   : None
*   AUTHOR      : $Author: arelic $
*****************************************************************************
*   VERSION     : $$
*   RELEASE     : Preliminary & Confidential
*   DATE        : $Date: 2012-08-03 13:26:26 $
*   SOURCE MOD. : $Source: /teenet/mpumcu/Capricorn/Capricorn_Bt/ipl/inc/booting.h,v $
*   LOG:        : please have a look at the end of the file ddd
****************************************************************************/

/**********************************************
*                Include files                *
**********************************************/
#include "app_bt.h"
#include "le_gatt_command.h"
#include "bt_uart_transport.h"
#include "ble_api.h"
#include "bt_OS.h"
#include "HeartRate.h"
#include <stdio.h>

/**********************************************
*               Defs                          *
**********************************************/

/**********************************************
*               Globals                          *
**********************************************/
/* GAP Device Name Service definition structure */
le_srv_service_def_st stGAPService;

/* GATT Heart Rate Service definition structure */
le_srv_service_def_st stHRService;

/* GATT Device Identification Service definition structure */
le_srv_service_def_st stDevIdService;

/* Heart Rate Measurement Characteristic */
le_srv_char_st stHRMChar;

uint8_t fHR_1HZ_tick = 0U;
uint8_t HR_ready=0U;



/******************************************************************************
*
*                       GAP/GATT SERVICE REGISTRATION
*
******************************************************************************/

/******************************************************************************/
le_api_result_e eHRAddGAPDevName_Appearance_Service(void* qHandle,
                                                   uint16_t* pu16SvcHandle,
                                                   uint16_t u16DevNameLen,
                                                   uint8_t* pu8DevName)
{
    le_api_result_e eResTemp;
    le_srv_char_st astChar[2];
    uint16_t au16ElementHandles_dev_name[1];
    uint16_t au16ElementHandles_appear[1];
    uint8_t  au8AppearData[2] = {0x00,0x00};


    /********************************************
    *********************************************
              Add Primary (GAP) service
    *********************************************
    ********************************************/
    stGAPService.u16SvcUUID = GAP_SERVICE;                                              /* GAP Service UUID */
    stGAPService.u8InclDefCount =0;                                                     /* No included services */
    stGAPService.u8CharDefCount =2;                                                     /* Two characteristics belong to this service */
    stGAPService.pstIncludes = NULL;                                                    /* No included services */
    stGAPService.pstChars = astChar;                                                    /* Pointer to Array that describes characteristics. */

    /*****************************************
           Characteristic DEVICE_NAME
     *****************************************/
    stGAPService.pstChars[0].u16CharUUID      = (uint16_t)GAP_DEV_NAME;                 /* Characteristic UUID */
    stGAPService.pstChars[0].u8CharProperties = (uint8_t)(LE_READ);                     /* Characteristic is Readable */
    stGAPService.pstChars[0].u8CharDescCnt = 0;                                         /* Only Char. Value Declaration is present and no descriptors */
    stGAPService.pstChars[0].pstCharDesc = NULL;                                        /* No descriptors are available */
    stGAPService.pstChars[0].pu16RetCharDescHandles = au16ElementHandles_dev_name;      /* Pointer to the array where handles of returned char elements shall be stored */

    /* Characteristic VALUE Declaration  */
    stGAPService.pstChars[0].stCharValDecl.u16AttValLen = u16DevNameLen;                /* Length of the actual value (device name) */
    stGAPService.pstChars[0].stCharValDecl.pu8AttVal = pu8DevName;                      /* Pointer to array containing actual value (device name) */
    stGAPService.pstChars[0].stCharValDecl.u16AttPermission = (uint16_t)LE_GATT_READ;   /* Attribute Permission set to readable */


    /*****************************************
           Characteristic APPEARANCE
     *****************************************/
    stGAPService.pstChars[1].u16CharUUID      = (uint16_t)APPEARANCE;
    stGAPService.pstChars[1].u8CharProperties = (uint8_t)(LE_READ);
    stGAPService.pstChars[1].u8CharDescCnt = 0;
    stGAPService.pstChars[1].pstCharDesc = NULL;
    stGAPService.pstChars[1].pu16RetCharDescHandles = au16ElementHandles_appear;

    /* Characteristic VALUE Declaration */
    stGAPService.pstChars[1].stCharValDecl.u16AttValLen = 2;
    stGAPService.pstChars[1].stCharValDecl.pu8AttVal = au8AppearData;
    stGAPService.pstChars[1].stCharValDecl.u16AttPermission = (uint16_t)LE_GATT_READ;

    /* Register as Primary Service */
    eResTemp = eBleSrv_RegisterPrimaryService(qHandle, &stGAPService);

    return eResTemp;
}

/******************************************************************************/
le_api_result_e eHRAddDevIdentService(void* qHandle,
                                       uint8_t* pu8ManufName,
                                       uint8_t pu8ManufNameLen,
                                       uint16_t* pu16SvcHandle,
                                       uint16_t* pu16RetHandleCharDecl,
                                       uint16_t* pu16RetHandleCharValDecl)
{
  le_api_result_e eResTemp;
  le_srv_char_st stChar;
  uint16_t au16ElementHandles[1];


  /********************************************
   ********************************************
           Add Device Information service
   ********************************************
   ********************************************/
   stDevIdService.u16SvcUUID = GATT_DEV_INFO;                                        /* GATT Device information service UUID */
   stDevIdService.u8InclDefCount =0;                                                 /* No included services */
   stDevIdService.u8CharDefCount =1;                                                 /* One characteristic belong to this service */
   stDevIdService.pstIncludes = NULL;                                                /* No included services */
   stDevIdService.pstChars = &stChar;                                                /* Pointer to structure that describes characteristics. */

  /********************************************
       Register Manuf. String characteristic
   *********************************************/

  /* Characteristic Declaration */
  stDevIdService.pstChars->u16CharUUID      = (uint16_t)GATT_CHAR_MANUF_NAME_STRING; /* Characteristic UUID */
  stDevIdService.pstChars->u8CharProperties = (uint8_t)(LE_READ);                    /* Read flag is set */
  stDevIdService.pstChars->u8CharDescCnt = 0;                                        /* Number of descriptors */
  stDevIdService.pstChars->pstCharDesc = NULL;                                       /* No character descriptors */
  stDevIdService.pstChars->pu16RetCharDescHandles = au16ElementHandles;              /* Pointer to the array where handles of returned char elements shall be stored */

  /* Characteristic VALUE Declaration */
  stDevIdService.pstChars->stCharValDecl.u16AttValLen = pu8ManufNameLen;             /* Length of the manufacturer name (in bytes) */
  stDevIdService.pstChars->stCharValDecl.pu8AttVal = pu8ManufName;                   /* Manufacturer name - string array */
  stDevIdService.pstChars->stCharValDecl.u16AttPermission = (uint16_t)LE_GATT_READ;  /* Attribute permissions */

   /* Register as Primary Service */
  eResTemp = eBleSrv_RegisterPrimaryService(qHandle, &stDevIdService);


  return eResTemp;
}

/******************************************************************************/
le_api_result_e eHRAddHeartRateService(void* qHandle, uint16_t* pu16SvcHandle,
                                     uint16_t* pu16RetHandleCharDecl,
                                     uint16_t* pu16RetHandleCharValDecl)
{
  le_api_result_e eResTemp;
  char_el_req_st astCharElement[2];
  uint16_t au16ElementHandles[2];
  uint8_t au8HRValue[2] = {0x00,0x00}; /* Default Heart Rate Value */
  uint8_t auCliProperties[2] = {0x00,0x00}; /* Heart Rate Value */


  /*******************************************
  ********************************************
           Add  Heart Rate Service
  ********************************************
  *******************************************/
  stHRService.u16SvcUUID = GATT_HEART_RATE;                                             /* GATT Heart Rate Service UUID */
  stHRService.u8InclDefCount =0;                                                        /* No included services */
  stHRService.pstIncludes = NULL;                                                       /* No included services */
  stHRService.u8CharDefCount =1;                                                        /* One characteristic belong to this service */
  stHRService.pstChars = &stHRMChar;                                                    /* Pointer to structure that describes characteristics. */

  /********************************************
       Register Heart Rate Meas. Characteristic
  ********************************************/

  /* Characteristic Declaration */
  stHRMChar.u16CharUUID      = (uint16_t)GATT_HEART_RATE_MEASUREMENT;                   /* Service Characteristic UUID */
  stHRMChar.u8CharProperties = (uint8_t)(LE_NOTIFY);                                    /* Character can be notified */
  stHRMChar.u8CharDescCnt = 1;                                                          /* Number of character descriptors */
  stHRMChar.pstCharDesc = astCharElement;                                               /* Pointer to the array containing char descriptors */
  stHRMChar.pu16RetCharDescHandles = au16ElementHandles;                                /* Pointer to the array where handles
                                                                                          of returned char descriptors shall be stored */
  /* Characteristic VALUE Declaration */
  stHRService.pstChars->stCharValDecl.u16AttValLen = sizeof(au8HRValue);
  stHRService.pstChars->stCharValDecl.pu8AttVal = au8HRValue;
  stHRService.pstChars->stCharValDecl.u16AttPermission = (uint16_t)LE_GATT_READ;

  /* Characteristic DESCRIPTOR Declaration (Client Characteristic Configuration) */
  stHRService.pstChars->pstCharDesc->au8AttType[0] = GET_BYTE_LSB((uint16_t)GATT_CLI_CHARACT_CONFIGURATION);
  stHRService.pstChars->pstCharDesc->au8AttType[1] = GET_BYTE_MSB((uint16_t)GATT_CLI_CHARACT_CONFIGURATION);
  stHRService.pstChars->pstCharDesc->eAttrLen = LE_SHORT_UUID;
  stHRService.pstChars->pstCharDesc->u16AttPermission = (uint16_t)(LE_GATT_READ | LE_GATT_WRITE);
  stHRService.pstChars->pstCharDesc->u16AttValLen = sizeof(auCliProperties);
  stHRService.pstChars->pstCharDesc->pu8AttVal = auCliProperties;

  /* Register as Primary Service */
  eResTemp = eBleSrv_RegisterPrimaryService(qHandle, &stHRService);

  /* Return Characteristic declaration handle */
  *pu16RetHandleCharValDecl = stHRMChar.u16RetCharValDeclHandle;

  return eResTemp;

}

/******************************************************************************
*
*                               ADVERTIZING
*
******************************************************************************/
le_api_result_e eHRStartAdvertising(void* qHandle)
{
  le_api_result_e eResult;
  le_adv_req_st stConfig;

  /* Advertizing configuration */
  stConfig.u16AdvIntervalMin = 0x0040;
  stConfig.u16AdvIntervalMax = 0x0040;
  stConfig.eAdvType = LE_ADV_IND;
  stConfig.eOwnAddrType    =LE_ADDR_PUBLIC;
  stConfig.eDirectAddrType =LE_ADDR_PUBLIC;
  stConfig.au8DirectAddr[0] = 0;
  stConfig.au8DirectAddr[1] = 0;
  stConfig.au8DirectAddr[2] = 0;
  stConfig.au8DirectAddr[3] = 0;
  stConfig.au8DirectAddr[4] = 0;
  stConfig.au8DirectAddr[5] = 0;
  stConfig.u8AdvChannelMap =0x07;
  stConfig.eAdvFilterPolicy = LE_SCAN_ANY_CONN_ANY;
  stConfig.u8AdvDataLen = 0x1f;
  stConfig.au8AdvData[0] = 0x07;                                                        /* Length in bytes */
  stConfig.au8AdvData[1] = GET_BYTE_LSB(LE_ADV_16_BIT_MORE);                            /* AD Type: More 16-bit Service UUIDs */
  stConfig.au8AdvData[2] = GET_BYTE_LSB(GATT_HEART_RATE);                               /* Heart-rate Service UUID */
  stConfig.au8AdvData[3] = GET_BYTE_MSB(GATT_HEART_RATE);
  stConfig.au8AdvData[4] = GET_BYTE_LSB(GAP_SERVICE);                                   /* GAP Service UUID */
  stConfig.au8AdvData[5] = GET_BYTE_MSB(GAP_SERVICE);
  stConfig.au8AdvData[6] = GET_BYTE_LSB(GATT_DEV_INFO);                                 /* GATT Device Identification Service UUID */
  stConfig.au8AdvData[7] = GET_BYTE_MSB(GATT_DEV_INFO);
  stConfig.au8AdvData[8] = 0x08;                                                        /* Length in bytes */
  stConfig.au8AdvData[9] = GET_BYTE_LSB(LE_ADV_COMPLETE_NAME);                          /* AD Type: Complete device name */
  stConfig.au8AdvData[10] = 0x54;                                                       /* Device Name Data -Char0 */
  stConfig.au8AdvData[11] = 0x4f;                                                       /* Device Name Data -Char1 */
  stConfig.au8AdvData[12] = 0x53;                                                       /* Device Name Data -Char2 */
  stConfig.au8AdvData[13] = 0x48;
  stConfig.au8AdvData[14] = 0x49;
  stConfig.au8AdvData[15] = 0x42;
  stConfig.au8AdvData[16] = 'x';
  //stConfig.au8AdvData[16] = 0x41;
  stConfig.au8AdvData[17] = 0x00;
  stConfig.au8AdvData[18] = 0x00;
  stConfig.au8AdvData[19] = 0x00;
  stConfig.au8AdvData[20] = 0x00;
  stConfig.au8AdvData[21] = 0x00;
  stConfig.au8AdvData[22] = 0x00;
  stConfig.au8AdvData[23] = 0x00;
  stConfig.au8AdvData[24] = 0x00;
  stConfig.au8AdvData[25] = 0x00;
  stConfig.au8AdvData[26] = 0x00;
  stConfig.au8AdvData[27] = 0x00;
  stConfig.au8AdvData[28] = 0x00;
  stConfig.au8AdvData[29] = 0x00;
  stConfig.au8AdvData[30] = 0x00;

  stConfig.u8ScanRespDataLen = 0x1f;

  stConfig.au8ScanRespData[0]= 0x02;
  stConfig.au8ScanRespData[1]= 0x01;
  stConfig.au8ScanRespData[2] = 0x00;
  stConfig.au8ScanRespData[3] = 0x00;
  stConfig.au8ScanRespData[4] = 0x00;
  stConfig.au8ScanRespData[5] = 0x00;
  stConfig.au8ScanRespData[6] = 0x00;
  stConfig.au8ScanRespData[7] = 0x00;
  stConfig.au8ScanRespData[8] = 0x00;
  stConfig.au8ScanRespData[9] = 0x00;
  stConfig.au8ScanRespData[10] = 0x00;
  stConfig.au8ScanRespData[11] = 0x00;
  stConfig.au8ScanRespData[12] = 0x00;
  stConfig.au8ScanRespData[13] = 0x00;
  stConfig.au8ScanRespData[14] = 0x00;
  stConfig.au8ScanRespData[15] = 0x00;
  stConfig.au8ScanRespData[16] = 0x00;
  stConfig.au8ScanRespData[17] = 0x00;
  stConfig.au8ScanRespData[18] = 0x00;
  stConfig.au8ScanRespData[19] = 0x00;
  stConfig.au8ScanRespData[20] = 0x00;
  stConfig.au8ScanRespData[21] = 0x00;
  stConfig.au8ScanRespData[22] = 0x00;
  stConfig.au8ScanRespData[23] = 0x00;
  stConfig.au8ScanRespData[24] = 0x00;
  stConfig.au8ScanRespData[25] = 0x00;
  stConfig.au8ScanRespData[26] = 0x00;
  stConfig.au8ScanRespData[27] = 0x00;
  stConfig.au8ScanRespData[28] = 0x00;
  stConfig.au8ScanRespData[29] = 0x00;
  stConfig.au8ScanRespData[30] = 0x00;

  eResult = eBlePerif_StartAdv(qHandle, stConfig);

  return eResult;

}


/******************************************************************************
*
*                           CALLBACK FUNCTIONS
*
******************************************************************************/
/******************************************************************************/
void vPrintUnexpectedCMD(uint8_t u8ServiceID,
                         uint8_t u8CmdCode,
                         uint16_t u16paramLen,
                         uint8_t* pu8ParamData)
{
  printf(" ---------- HR PROFILE UNEXPECTED COMMAND RECEIVED - START -------------\n");
  printf("| ServiceID: 0x%.2x \n", u8ServiceID);
  printf("| u8CmdCode: 0x%.2x \n", u8CmdCode);
  printf("| ParamLen: 0x%.2x \n", u16paramLen);
  printf(" ---------- HR PROFILE UNEXPECTED COMMAND RECEIVED - END -------------\n");

}

/******************************************************************************/
le_api_result_e eUpdateCharValue(void* qHandle,
                                      uint16_t u16ConnHandle,
                                      uint16_t u16CharValHandle)
{
  printf("Characteristic VALUE Update Callback Function!\n");

  return LE_API_SUCCCESS;
}

/******************************************************************************/
le_api_result_e eUpdateCharDescriptor(void* qHandle,
                                      uint16_t u16ConnHandle,
                                      uint16_t u16CharValHandle)
{
  printf("Characteristic Descriptor Callback Function!\n");

  return LE_API_SUCCCESS;
}
/******************************************************************************/
le_api_result_e eUpdateMulti(void* qHandle,
                               uint16_t u16ConnHandle,
                               uint16_t u16HandleCnt,  uint8_t* pu8Handles)
{
  printf("Character Update Multi - Update Count: %d\n", u16HandleCnt);

  return LE_API_SUCCCESS;
}



/******************************************************************************
*
*                        INIT./ MAIN EVENT HANDLER
*
******************************************************************************/
/******************************************************************************/
le_api_result_e eHRInitialise(void* qHandle, hr_init_st* stInit)
{
  le_api_result_e eResult;
  uint8_t auMyBd_Addr[6];

  /* Initialise SMART API LAYER & register callback functions */
  eBleApiInit(btQueueEVENT,
                vPrintUnexpectedCMD,
                eUpdateCharValue,
                eUpdateCharDescriptor,
                eUpdateMulti);

  /* Initialise Device as GATT Server */
  eResult = eBleDeviceSrv_Init(btQueueEVENT,
                                 stInit->pu8DevName,
                                 stInit->u8DevNameLen,
                                 auMyBd_Addr);

  if(eResult == LE_API_SUCCCESS)
  {
    /* Add GAP Device Name Service */
    eResult =  eHRAddGAPDevName_Appearance_Service(qHandle,
                                                   stInit->pu16RetDevNameSvcHndl,
                                                   stInit->u8DevNameLen,
                                                   stInit->pu8DevName);

    if(eResult == LE_API_SUCCCESS)
    {
        /* Add GATT Device Identification Service */
        eResult = eHRAddDevIdentService(qHandle,
                                        stInit->pu8ManufName,
                                        stInit->pu8ManufNameLen,
                                        stInit->pu16RetDISvcHndl,
                                        stInit->pu16RetDICharDeclHndl,
                                        stInit->pu16RetDICharValDeclHndl);

        if(eResult == LE_API_SUCCCESS)
      {
        /* Add GATT Heart Rate Service */
        eResult = eHRAddHeartRateService(qHandle,
                                         stInit->pu16RetHRSvcHndl,
                                         stInit->pu16RetHRCharDeclHndl,
                                         stInit->pu16RetHRCharValDeclHndl);
      }
    }
  }
  return eResult;
}

/****************************************************************************/
void HRMainRoutine(void* qHandle, hr_init_st* stInit)
{
  uint16_t u16Command;
  le_api_result_e eResult;
  uint16_t u16RetConnHandle;
  uint8_t au8HRValue[2] = {0x00,0x30};


  enum serviceID_opcodes{   TCU_MNG_LE_CONNECTION_COMPLETE_EVENT_SID_OC = 0xD14C,  /*taken from le_gatt_command.h*/
                                                     TCU_LE_GATT_SER_EXG_MTU_EVENT_SID_OC = 0xD3C1,
                                                     TCU_LE_GATT_SER_READ_MULTIPLE_EVENT_SID_OC = 0xD3CA,
                                                     TCU_LE_GATT_SER_READ_CHAR_VAL_EVENT_SID_OC = 0xD3C2,
                                                     TCU_LE_GATT_SER_READ_CHAR_DESP_EVENT_SID_OC = 0xD3C8,
                                                     TCU_LE_GATT_SER_WRITE_CHAR_DESP_EVENT_SID_OC = 0xD3C4,



  };

  /* Main HR-Profile Event Handler */
  while(1)
  {
    /* At this stage initialization is done and we are waiting on events
    *  Comming from a client. */

    /* Wait for a message to be received (with time-out) */
    eResult = vSmartWaitForAnyEvent(qHandle, &u16Command);
    if (LE_API_SUCCCESS == eResult)
    {
      /*   Message Handler.
       *
       *  Based on message type, the handler calls an appropriate routine
       *  implementing adequate handling.
       */
      switch(u16Command)
      {
        //case GET_CMD_MESSAGE(TCU_MNG_LE_CONNECTION_COMPLETE_EVENT):  /*omg who wrote this*/
          case TCU_MNG_LE_CONNECTION_COMPLETE_EVENT_SID_OC:
          {
            /* Client has sent a Connection Request to the Server,
               therefore a connection handler will be called */
             eResult = eBleSrv_ClientConnRequestHndlr(stInit->pstConnectInfo);
          }
        break;
       // case GET_CMD_MESSAGE(TCU_LE_GATT_SER_EXG_MTU_EVENT):
          case TCU_LE_GATT_SER_EXG_MTU_EVENT_SID_OC:
          {
            /*  MTU size negotiation started, so start an MTU Exchange
             *  handler.
             */
             eResult = eBleSrv_ClientMtuExchangeHndlr(qHandle,
                                              stInit->pstConnectInfo->u16ConnHandle,
                                              stInit->pstMtuEvtData,
                                              stInit->pstMtuAccResp);
          }
        break;
        //case GET_CMD_MESSAGE(TCU_LE_GATT_SER_READ_MULTIPLE_EVENT):
          case TCU_LE_GATT_SER_READ_MULTIPLE_EVENT_SID_OC:
          {
            /* Update of multiple values in data-base requested, before
            *  sending those data to client side  */
            eResult = eBleSrv_ReadMultiEventHndlr(qHandle,
                                                    CONN_HANDLE_ANY,
                                                    &(stInit->u16ConnHandle));
          }
        break;
        //case GET_CMD_MESSAGE(TCU_LE_GATT_SER_READ_CHAR_VAL_EVENT):
          case TCU_LE_GATT_SER_READ_CHAR_VAL_EVENT_SID_OC:
          {
            /* Read characteristic VALUE request received */
            eResult = eBleSrv_ReadCharValHndlr(qHandle,
                                                 /*stInit->u16ConnHandle,*/
                                                 stInit->pstConnectInfo->u16ConnHandle,
                                                 &u16RetConnHandle);
          }
        break;
        //case GET_CMD_MESSAGE(TCU_LE_GATT_SER_READ_CHAR_DESP_EVENT):
          case TCU_LE_GATT_SER_READ_CHAR_DESP_EVENT_SID_OC:
          {
            /* Read characteristic DESCRIPTOR request received */
            eResult = eBleSrv_ReadCharDescriptorHndlr(qHandle,
                                                          /* stInit->u16ConnHandle,*/
                                                          stInit->pstConnectInfo->u16ConnHandle,
                                                          &u16RetConnHandle);
          }
        break;


        //case GET_CMD_MESSAGE(TCU_LE_GATT_SER_WRITE_CHAR_DESP_EVENT):
          case TCU_LE_GATT_SER_WRITE_CHAR_DESP_EVENT_SID_OC:
          {
              /* Write characteristic DESCRIPTOR request received */
              eResult = eBleSrv_WriteCharDescriptorHndlr(qHandle,
                                                          /* stInit->u16ConnHandle, */
                                                          stInit->pstConnectInfo->u16ConnHandle,
                                                          &stInit->stCharDespEvt);

              if(eResult==LE_API_SUCCCESS)
              {
                 HR_ready=1;
              }
          }
        break;

      default:
        {
#ifdef DEBUG_OUT
          printf("HR Profile: Unhandled Message received() \n");
#endif
        }
      }
  }else if (LE_API_ERR_TIMEOUT == eResult)
    if(HR_ready == 1)
    {
        /* Send notification with incremented Heart-Rate Value
         * in regular time intervals
         */
        au8HRValue[1] += 0x01;
        eBleSrv_SendNotification(qHandle,
                              stInit->pstConnectInfo->u16ConnHandle,
                              stHRService.pstChars,
                              au8HRValue);
    }
  }

}




/***********************  BEGIN of DISCLAIMER   *****************************

- TOSHIBA is continually working to improve the quality and reliability of
  its products.
  Nevertheless, semiconductor devices in general can malfunction or fail
  due to their inherent electrical sensitivity and vulnerability to physical
  stress. It is the responsibility of the buyer, when utilizing TOSHIBA
  products, to comply with the standards of safety in making a safe design
  for the entire system, and to avoid situations in which a malfunction or
  failure of such TOSHIBA products could cause loss of human life,
  bodily injury or damage to property.

  In developing your designs, please ensure that TOSHIBA products are used
  within specified operating ranges as set forth in the most recent TOSHIBA
  products specifications. Also, please keep in mind the precautions and
  conditions set forth in the “Handling Guide for Semiconductor Devices, or
  TOSHIBA Semiconductor Reliability Handbook etc..

- The Toshiba products listed in this document are intended for usage in
  general electronics applications (computer, personal equipment,
  office equipment, measuring equipment,industrial robotics, domestic
  appliances, etc.). These Toshiba products are neither intended nor
  warranted for usage in equipment that requires extraordinarily high quality
  and/or reliability or a malfunction or failure of which may cause loss
  of human life or bodily injury (“Unintended Usage).
  Unintended Usage include atomic energy control instruments, airplane or
  spaceship instruments, transportation instruments, traffic signal
  instruments, combustion control instruments, medical instruments,
  all types of safety devices, etc..
  Unintended Usage of Toshiba products listed in this document shall be made
  at the customer’s own risk.

- Toshiba assumes no liability for any damage or losses (including but not
  limited to, loss of business profit,business interruption, loss of business
  information,and other pecuniary losses) occurring from the use of,
  or inability to use, this product.

- The products described in this document are subject to the foreign exchange
  and foreign trade laws.

- The products described in this document contain components made in the
  United States and subject to export control of the U.S. authorities.
  Diversion contrary to the U.S. law is prohibited.

- The information contained herein is presented only as a guide for the
  applications of our products.
  No responsibility is assumed by TOSHIBA CORPORATION for any infringements
  of intellectual property or other rights of the third parties which may
  result from its use.
  No license is granted by implication or otherwise under any intellectual
  property or other rights of TOSHIBA CORPORATION or others.

- The information contained herein is subject to change without notice.

****************************  END of DISCLAIMER ****************************/
