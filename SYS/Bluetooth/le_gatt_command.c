/****************************************************************************
*   COPYRIGHT 2006-2009 All rights reserved
*   Toshiba Electronics Europe GmbH
*   European LSI Design and Engineering Center (ELDEC)
*****************************************************************************
*   File Name   : $RCSfile: booting.h,v $
*   Description : Contains global booting definitions
*****************************************************************************
*   PROJECT     : Bluetooth BLE
*   MODULE      : LE + GATT Commands
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
#include "le_gatt_command.h"
//#include "bt_mng_drv.h"
#include "stdio.h"

/**********************************************
*               Defs                          *
**********************************************/

//uint8_t au8SendBuff[UART_PACKET_LENGHT];
/**********************************************
*                Functions                    *
**********************************************/


/******************************************************************************/
#ifdef DEBUG_PRINT

void vPrintCmd(uint8_t u8ServId, uint8_t u8OpCode)
{
    switch(u8ServId)
    {
      case 0xD1: 
        {
              /* Process MNG Events/Responces */
              switch(u8OpCode)
              {
                case GET_CMD_OPCODE(TCU_MNG_LE_INIT_REQ):  printf("TCU_MNG_LE_INIT_REQ \n");                 
                break;
                case GET_CMD_OPCODE(TCU_MNG_LE_INIT_RESP):  printf("TCU_MNG_LE_INIT_RESP \n");                 
                break;
                case GET_CMD_OPCODE(TCU_MNG_LE_SET_SCAN_ENABLE_REQ):  printf("TCU_MNG_LE_SET_SCAN_ENABLE_REQ \n");                 
                break;
                case GET_CMD_OPCODE(TCU_MNG_LE_SET_SCAN_ENABLE_RESP):  printf("TCU_MNG_LE_SET_SCAN_ENABLE_RESP \n");                 
                break;
                case GET_CMD_OPCODE(TCU_MNG_LE_ADV_REPORT_EVENT):  printf("TCU_MNG_LE_ADV_REPORT_EVENT \n");                 
                break;
                case GET_CMD_OPCODE(TCU_MNG_LE_CREATE_CONNECTION_REQ):  printf("TCU_MNG_LE_CREATE_CONNECTION_REQ \n");                 
                break;
                case GET_CMD_OPCODE(TCU_MNG_LE_CONNECTION_COMPLETE_EVENT):  printf("TCU_MNG_LE_CONNECTION_COMPLETE_EVENT \n");                 
                break;
                case GET_CMD_OPCODE(TCU_MNG_LE_CREATE_CONNECTION_CANCEL_REQ):  printf("TCU_MNG_LE_CREATE_CONNECTION_CANCEL_REQ \n");                 
                break;
                case GET_CMD_OPCODE(TCU_MNG_LE_CREATE_CONNECTION_CANCEL_RESP):  printf("TCU_MNG_LE_CREATE_CONNECTION_CANCEL_RESP \n");                 
                break;
                case GET_CMD_OPCODE(TCU_MNG_LE_DISCONNECT_REQ):  printf("TCU_MNG_LE_DISCONNECT_REQ \n");                 
                break;
                case GET_CMD_OPCODE(TCU_MNG_LE_DISCONNECT_EVENT):  printf("TCU_MNG_LE_DISCONNECT_EVENT \n");                 
                break;
                case GET_CMD_OPCODE(TCU_MNG_LE_SET_SCAN_DISABLE_REQ):  printf("TCU_MNG_LE_SET_SCAN_DISABLE_REQ \n");                 
                break;
                case GET_CMD_OPCODE(TCU_MNG_LE_SET_SCAN_DISABLE_RESP):  printf("TCU_MNG_LE_SET_SCAN_DISABLE_RESP \n");                 
                break;
                case GET_CMD_OPCODE(TCU_MNG_LE_START_ADVERTISE_REQ):  printf("TCU_MNG_LE_START_ADVERTISE_REQ \n");                 
                break;
                case GET_CMD_OPCODE(TCU_MNG_LE_START_ADVERTISE_RESP):  printf("TCU_MNG_LE_START_ADVERTISE_RESP \n");                 
                break;
                case GET_CMD_OPCODE(TCU_LE_ACCEPT):  printf("TCU_LE_ACCEPT \n");                 
                break;
                default:
                {
                    printf("!!! UNKNOWN MNG COMMAND !!! \n");    
                }
              }       
        }
      break;
      case 0xD2:
        {
          /* Process GATT Client Events/Responces */
          switch(u8OpCode)
              {
                default:
                {
                    printf("!!! UNKNOWN GATT CLI COMMAND !!! \n");    
                }
              }                
        }  
      break;
      case 0xD3:
        {
          /* Process GATT Server Events/Responces */
              
            switch(u8OpCode)
            {
              case GET_CMD_OPCODE(TCU_LE_GATT_SDB_ADD_PRIM_SVC_REQ):  printf("TCU_LE_GATT_SDB_ADD_PRIM_SVC_REQ \n");                 
              break;
              case GET_CMD_OPCODE(TCU_LE_GATT_SDB_ADD_PRIM_SVC_RESP):  printf("TCU_LE_GATT_SDB_ADD_PRIM_SVC_RESP \n");                 
              break;
              case GET_CMD_OPCODE(TCU_LE_GATT_SDB_ADD_CHAR_DECL_REQ):  printf("TCU_LE_GATT_SDB_ADD_CHAR_DECL_REQ \n");                 
              break;
              case GET_CMD_OPCODE(TCU_LE_GATT_SDB_ADD_CHAR_DECL_RESP):  printf("TCU_LE_GATT_SDB_ADD_CHAR_DECL_RESP \n");                 
              break;
              case GET_CMD_OPCODE(TCU_LE_GATT_SDB_ADD_CHAR_ELE_REQ):  printf("TCU_LE_GATT_SDB_ADD_CHAR_ELE_REQ \n");                 
              break;
              case GET_CMD_OPCODE(TCU_LE_GATT_SDB_ADD_CHAR_ELE_RESP):  printf("TCU_LE_GATT_SDB_ADD_CHAR_ELE_RESP \n");                 
              break;
              case GET_CMD_OPCODE(TCU_LE_GATT_SDB_UPD_CHAR_ELE_REQ):  printf("TCU_LE_GATT_SDB_UPD_CHAR_ELE_REQ \n");                 
              break;
              case GET_CMD_OPCODE(TCU_LE_GATT_SDB_UPD_CHAR_ELE_RESP):  printf("TCU_LE_GATT_SDB_UPD_CHAR_ELE_RESP \n");                 
              break;
              case GET_CMD_OPCODE(TCU_LE_GATT_SDB_RET_END_GRP_HLE_REQ):  printf("TCU_LE_GATT_SDB_RET_END_GRP_HLE_REQ \n");                 
              break;
              case GET_CMD_OPCODE(TCU_LE_GATT_SDB_RET_END_GRP_HLE_RESP):  printf("TCU_LE_GATT_SDB_RET_END_GRP_HLE_RESP \n");                 
              break;
              case GET_CMD_OPCODE(TCU_LE_GATT_SER_INIT_REQ):  printf("TCU_LE_GATT_SER_INIT_REQ \n");                 
              break;
              case GET_CMD_OPCODE(TCU_LE_GATT_SER_INIT_RESP):  printf("TCU_LE_GATT_SER_INIT_RESP \n");                 
              break;
              case GET_CMD_OPCODE(TCU_LE_GATT_SER_WRITE_CHAR_DESP_EVENT):  printf("TCU_LE_GATT_SER_WRITE_CHAR_DESP_EVENT \n");                 
              break;
              case GET_CMD_OPCODE(TCU_LE_GATT_SER_WRITE_CHAR_DESP_ACCEPT_REQ):  printf("TCU_LE_GATT_SER_WRITE_CHAR_DESP_ACCEPT_REQ \n");                 
              break;
              case GET_CMD_OPCODE(TCU_LE_GATT_SER_READ_CHAR_VAL_ACCEPT_REQ):  printf("TCU_LE_GATT_SER_READ_CHAR_VAL_ACCEPT_REQ \n");                 
              break;
              case GET_CMD_OPCODE(TCU_LE_GATT_SER_READ_CHAR_VAL_ACCEPT_RESP):  printf("TCU_LE_GATT_SER_READ_CHAR_VAL_ACCEPT_RESP \n");                 
              break;
              case GET_CMD_OPCODE(TCU_LE_GATT_SER_EXG_MTU_EVENT):  printf("TCU_LE_GATT_SER_EXG_MTU_EVENT \n");                 
              break;
              case GET_CMD_OPCODE(TCU_LE_GATT_SER_EXG_MTU_ACCEPT_REQ):  printf("TCU_LE_GATT_SER_EXG_MTU_ACCEPT_REQ \n");                 
              break;
              case GET_CMD_OPCODE(TCU_LE_GATT_SER_EXG_MTU_ACCEPT_RESP):  printf("TCU_LE_GATT_SER_EXG_MTU_ACCEPT_RESP \n");                 
              break;
              case GET_CMD_OPCODE(TCU_LE_GATT_SER_READ_CHAR_VAL_EVENT):  printf("TCU_LE_GATT_SER_READ_CHAR_VAL_EVENT \n");                 
              break;
              case GET_CMD_OPCODE(TCU_LE_GATT_SER_WRITE_CHAR_VAL_EVENT):  printf("TCU_LE_GATT_SER_WRITE_CHAR_VAL_EVENT \n");                 
              break;
              case GET_CMD_OPCODE(TCU_LE_GATT_SER_WRITE_CHAR_VAL_ACCEPT_REQ):  printf("TCU_LE_GATT_SER_WRITE_CHAR_VAL_ACCEPT_REQ \n");                 
              break;
              case GET_CMD_OPCODE(TCU_LE_GATT_SER_READ_MULTIPLE_EVENT):  printf("TCU_LE_GATT_SER_READ_MULTIPLE_EVENT \n");                 
              break;
              case GET_CMD_OPCODE(TCU_LE_GATT_SER_READ_MULTIPLE_ACCEPT_REQ):  printf("TCU_LE_GATT_SER_READ_MULTIPLE_ACCEPT_REQ \n");                 
              break;
              case GET_CMD_OPCODE(TCU_LE_GATT_SER_READ_MULTIPLE_ACCEPT_RESP):  printf("TCU_LE_GATT_SER_READ_MULTIPLE_ACCEPT_RESP \n");                 
              break;
              case GET_CMD_OPCODE(TCU_LE_GATT_SER_CHAR_VAL_NOTIFICATION_REQ):  printf("TCU_LE_GATT_SER_CHAR_VAL_NOTIFICATION_REQ \n");                 
              break;
              case GET_CMD_OPCODE(TCU_LE_GATT_SER_CHAR_VAL_NOTIFICATION_EVENT):  printf("TCU_LE_GATT_SER_CHAR_VAL_NOTIFICATION_EVENT \n");                 
              break;
              case GET_CMD_OPCODE(TCU_LE_GATT_SER_WRITE_WITHOUT_RESPONSE_CMD_EVENT):  printf("TCU_LE_GATT_SER_WRITE_WITHOUT_RESPONSE_CMD_EVENT \n");                 
              break;
              case GET_CMD_OPCODE(TCU_LE_GATT_SER_WRITE_CHAR_DESP_ACCEPT_RESP):  printf("TCU_LE_GATT_SER_WRITE_CHAR_DESP_ACCEPT_RESP \n");                 
              break;
              case GET_CMD_OPCODE(TCU_LE_GATT_SER_READ_CHAR_DESP_EVENT):  printf("TCU_LE_GATT_SER_READ_CHAR_DESP_EVENT \n");                 
              
              default:
              {
                  printf("!!! UNKNOWN SRV COMMAND !!! \n");    
              }
            }               
        }    
      break;
      default: 
        {
          printf("!!! UNKNOWN SERVICE ID !!! \n");   
        }
    }


}

void vDebugRcvdCmdPrintf(uint8_t* pu8Data, uint16_t u16Count)
{
    uint8_t u8ServId = (eTCU_SERVICE_ID_)PARSE_CMD_SERVICE_ID(pu8Data);
    uint8_t u8OpCode = PARSE_CMD_OPCODE(pu8Data);
    
    /* Print command name*/
    vPrintCmd(u8ServId, u8OpCode);

    /* Print array content */
    printf("< ");
    printf("%.2x ", pu8Data[0]);
    printf("%.2x ", pu8Data[1]);
    printf("%.2x| ", pu8Data[2]);
    printf("ID: %.2x, ", pu8Data[3]);
    printf("CMD: %.2x, ", pu8Data[4]);
    printf("LEN: %.2x ", pu8Data[5]);
    printf("%.2x ", pu8Data[6]);
    printf("PARAM: ");
    
    for (int i=7; i<u16Count; i++)
    {
      printf("%.2x ", pu8Data[i]);
    }
    printf("> \n\n");
}
#endif

/******************************************************************************/
void vSetCmdLength(uint8_t* pu8Data, uint16_t u16Len)
{
    pu8Data[CMD_ARRAY_LEN_OFFS] = ((u16Len) & 0xFF);
    pu8Data[CMD_ARRAY_LEN_OFFS+1] = ((u16Len)>>8 & 0xFF);
}

/******************************************************************************/
void vWrite2Array_8(uint8_t* pu8Data, uint8_t u8Data, uint16_t* pu16Offset)
{
    pu8Data[*pu16Offset]  = u8Data;
    *pu16Offset+=1;
}
    
/******************************************************************************/
void vWrite2Array_16(uint8_t* pu8Data, uint16_t u16Data, uint16_t* pu16Offset)
{
    pu8Data[*pu16Offset]  = GET_BYTE_LSB((u16Data));
    pu8Data[*pu16Offset + 1]= GET_BYTE_MSB((u16Data));
    *pu16Offset+=2;
}

/******************************************************************************/
le_func_status_e eSendData(uint8_t* pu8Data, uint32_t u32Len)
{
    uint32_t u32TotalLen;

    /* Total UART package length:3-bytes for packet length + 4-byte BLE message header + BLE message */
    u32TotalLen = UART_PACKET_OFFSET +  (uint32_t)GET_TOTAL_LE_MESSAGE_SIZE(pu8Data);

    /* Set length of entire UART package (first 3-bytes) */
    pu8Data[0]=(0x0000ff & u32TotalLen);
    pu8Data[1]=(0x00ff00 & u32TotalLen);
    pu8Data[2]=(0xff0000 & u32TotalLen);

#ifdef DEBUG_OUT 
    
    vDebugRcvdCmdPrintf(pu8Data, u32Len);

 #endif
    
    /* Send data via UART */
    send_tx(pu8Data, u32TotalLen);

    return LE_FUNC_SUCCCESS;
};

/******************************************************************************/
le_func_status_e eIsCmdMatching(uint8_t* pu8Data, uint32_t u32Cmd)
{
    le_func_status_e eRes;

    /* Check if matches */
    if(PARSE_CMD_SERVICE_ID(pu8Data) == GET_CMD_SERVICE_ID(u32Cmd))
    {
        if(PARSE_CMD_OPCODE(pu8Data) == GET_CMD_OPCODE(u32Cmd))
        {
            /* Command check OK */
            eRes = LE_FUNC_SUCCCESS;
        }
        else
        {
            /* Op-code error */
            eRes = LE_FUNC_ERR_OPCODE;
        }
    }
    else
    {
        /* Service ID error */
        eRes = LE_FUNC_ERR_CMD_SVC_ID;
    }

    return eRes;
}

/******************************************************************************/
void vGetCmdDetails(uint8_t* pu8Data, uint8_t* pu8ServID, uint8_t* pu8OpCode, uint16_t* pu16Len)
{
    /* Extract command parameters */
    *pu8ServID = PARSE_CMD_SERVICE_ID(pu8Data);
    *pu8OpCode = PARSE_CMD_OPCODE(pu8Data);
    *pu16Len   = PARSE_CMD_PARAM_LENGTH(pu8Data);
}

/******************************************************************************/
uint16_t u16AutoSetCmdHeader(uint8_t* pu8Data, uint32_t u32Cmd,  uint16_t u16Offset)
{
    uint16_t u16DataCnt=0;

    /* Set service ID */
    SET_CMD_SVC_ID(pu8Data, u32Cmd);
    u16DataCnt++;

    /* Set Opcode */
    SET_CMD_OP_CODE(pu8Data, u32Cmd);
    u16DataCnt++;

    /* Set length */
    vSetCmdLength(pu8Data, GET_PARAM_LENGTH(u32Cmd));
    u16DataCnt+=2;

    return (u16Offset + u16DataCnt);
}

/******************************************************************************/
void vCopyArrayParams(uint8_t* pu8Src, uint8_t* pu8Dst, uint8_t u8SrcOffs, uint8_t u8DstOffs, uint16_t u16Count)
{
    uint16_t u16Iter;

    for(u16Iter=0;u16Iter < u16Count;u16Iter++)
    {
        pu8Dst[u8DstOffs + u16Iter] = pu8Src[u8SrcOffs + u16Iter];
    }
}

/******************************************************************************/
uint16_t u16SetCmdHeaderUserLen(uint8_t* pu8Data, uint32_t u32Cmd, uint16_t u16Len, uint16_t u16Offset)
{
    uint16_t u16DataCnt=0;

    /* Set service ID */
    SET_CMD_SVC_ID(pu8Data, u32Cmd);
    u16DataCnt++;

    /* Set Opcode */
    SET_CMD_OP_CODE(pu8Data, u32Cmd);
    u16DataCnt++;

    /* Set length */
    vSetCmdLength(pu8Data, u16Len);
    u16DataCnt+=2;

    return (u16DataCnt + u16Offset);
}


/******************************************************************************/
uint16_t u16SetSidOpCode(uint8_t* pu8Data,uint32_t u32Cmd)
{
     uint16_t u16DataCnt=0;

    /* Set service ID */
    SET_CMD_SVC_ID(pu8Data, u32Cmd);
    u16DataCnt++;

    /* Set Opcode */
    SET_CMD_OP_CODE(pu8Data, u32Cmd);
    u16DataCnt++;

    return u16DataCnt;
}

/******************************************************************************/
le_func_status_e eGetLeAccept_Ack(uint8_t* pu8Data, le_accept_st* pstEvntData)
{
    le_func_status_e eResult;
    uint16_t u16Offset = CMD_ARRAY_PARAM_OFFS;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data,TCU_LE_ACCEPT);

    if(LE_FUNC_SUCCCESS == eResult)
    {
      pstEvntData->eStatus = (le_accept_status_e)pu8Data[u16Offset];
      u16Offset+=1;
      pstEvntData->u16ServiceId= pu8Data[u16Offset];
      u16Offset+=2;;
      pstEvntData->u8OpCode = pu8Data[u16Offset];
    }

     return eResult;
}

/******************************************************************************/
le_func_status_e eGetLeNOTAcceptStatus_Ack(uint8_t* pu8Data, uint8_t* pu8ServID, uint8_t* pu8OpCode)
{
    le_func_status_e eResult;
    uint16_t u16ParamLen =0;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data,TCU_LE_NOT_ACCEPT);

    if(LE_FUNC_SUCCCESS == eResult)
    {
        /* Get common params */
        vGetCmdDetails(pu8Data, pu8ServID, pu8OpCode, &u16ParamLen);
    }

    return eResult;
};
/******************************************************************************/
le_func_status_e eGetLeFatalError_Notfy(uint8_t* pu8Data, uint8_t* pu8ErrorCode)
{
    le_func_status_e eResult;
    uint16_t u16ParamLen =0;
    uint8_t u8ServID;
    uint8_t u8OpCode;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data,TCU_LE_FATAL_ERROR);

    if(LE_FUNC_SUCCCESS == eResult)
    {
        /* Get common params */
        vGetCmdDetails(pu8Data, &u8ServID, &u8OpCode, &u16ParamLen);
    }

    return eResult;
};

/******************************************************************************/
le_func_status_e eSetLeMngInit_Req(uint8_t* pu8DevName, uint8_t u8NameLen)
{
    le_func_status_e eResult;

    uint16_t u16Offset = UART_PACKET_OFFSET;
    //uint8_t au8SendBuff[256];

    /* Check if name length ok */
    if((u8NameLen > 0) && (u8NameLen < 248))
    {
        /* Set command op-code service id and parameter length */
        u16Offset = u16SetCmdHeaderUserLen(au8SendBuff,TCU_MNG_LE_INIT_REQ,(uint16_t) (u8NameLen+1), u16Offset);

        /* Length of Device Name */
        au8SendBuff[u16Offset++] = u8NameLen;

        /* Copy device name in the array */
        vCopyArrayParams(pu8DevName, au8SendBuff, 0, u16Offset, (uint16_t)u8NameLen);

        /* Send command */
        eResult = eSendData(au8SendBuff, u16Offset + u8NameLen + 1);
   }
    else
    {
        /* Invalid device name length */
        eResult = LE_FUNC_ERR_DEV_NAME;
    }

    return eResult;
};

/******************************************************************************/
le_func_status_e eGetLeMngInit_Resp(uint8_t* pu8Data, le_mnginit_resp_st* pstResp)
{
    le_func_status_e eResult;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_MNG_LE_INIT_RESP);

    if(LE_FUNC_SUCCCESS == eResult)
    {
        /* Get Status */
        pstResp->eStatus = (mgn_init_resp_status_e)pu8Data[CMD_ARRAY_PARAM_OFFS];

        /* Copy BD_ADDR */
        vCopyArrayParams(pu8Data, pstResp->pu8BdAddr, CMD_ARRAY_PARAM_OFFS+1, 0, BD_ADDR_SIZE);
    }

    return eResult;
};

/******************************************************************************/
le_func_status_e eSetLeMngSetScanEnable_Req(set_scan_en_st stConfig)
{
    le_func_status_e eResult;
    uint16_t u16Offset = UART_PACKET_OFFSET;
   // uint8_t au8SendBuff[64];

    u16Offset = u16AutoSetCmdHeader(au8SendBuff, TCU_MNG_LE_SET_SCAN_ENABLE_REQ, u16Offset);

    au8SendBuff[u16Offset++] = GET_BYTE_MSB(stConfig.u16LE_Scan_Interval);
    au8SendBuff[u16Offset++] = GET_BYTE_LSB(stConfig.u16LE_Scan_Interval);

    au8SendBuff[u16Offset++] = GET_BYTE_MSB(stConfig.u16LE_Scan_Window);
    au8SendBuff[u16Offset++] = GET_BYTE_LSB(stConfig.u16LE_Scan_Window);

    au8SendBuff[u16Offset++] = (uint8_t)stConfig.eLE_Scan_Type;
    au8SendBuff[u16Offset++] = (uint8_t)stConfig.eAddrType;
    au8SendBuff[u16Offset++] = (uint8_t)stConfig.eScanPolicy;
    au8SendBuff[u16Offset++] = (uint8_t)stConfig.eScanEnable;
    au8SendBuff[u16Offset++] = (uint8_t)stConfig.eDuplFiltEnable;

    /* Send command */
    eResult = eSendData(au8SendBuff, u16Offset);

    return eResult;
};

/******************************************************************************/
le_func_status_e eGetLeMngSetScanEnable_Resp(uint8_t* pu8Data, uint8_t* pu8Status)
{
   le_func_status_e eResult;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_MNG_LE_SET_SCAN_ENABLE_RESP);

    if(LE_FUNC_SUCCCESS == eResult)
    {
        /* Get Status */
        *pu8Status = pu8Data[CMD_ARRAY_PARAM_OFFS];
    }

    return eResult;
};

/******************************************************************************/
/* ?????????????? */
le_func_status_e eGetLeAdvReport_Event(uint8_t* pu8Data, uint8_t* pu8Status, uint8_t* pu8SubEvtCode, uint8_t* pu8NumReports, le_adv_report_evnt_st* pstReports)
{
    le_func_status_e eResult;
    uint8_t u8Iter;
    uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_MNG_LE_ADV_REPORT_EVENT);

    if(LE_FUNC_SUCCCESS == eResult)
    {
        *pu8Status = pu8Data[u32Offset];
        *pu8SubEvtCode = pu8Data[u32Offset++];
        *pu8NumReports = pu8Data[u32Offset++];

        /* Copy reports */
        for(u8Iter=0; u8Iter < *pu8NumReports; u8Iter++)
        {
            pstReports[u8Iter].au8EvntType = pu8Data[u32Offset];
            pstReports[u8Iter].au8AddrType = pu8Data[u32Offset + 1];
            vCopyArrayParams(pu8Data, pstReports[u8Iter].au8Address, u32Offset + 2, 0, BD_ADDR_SIZE);
            pstReports[u8Iter].au8DataLen  = pu8Data[u32Offset + 2 + BD_ADDR_SIZE];
            vCopyArrayParams(pu8Data, pstReports[u8Iter].pu8Data, u32Offset + 2 + BD_ADDR_SIZE + 1, 0, pstReports[u8Iter].au8DataLen);
            pstReports[u8Iter].i8Rssi      = pu8Data[u32Offset + 2 + BD_ADDR_SIZE + 1 + pstReports[u8Iter].au8DataLen];
            u32Offset = pu8Data[u32Offset + 2 + BD_ADDR_SIZE + 1 + pstReports[u8Iter].au8DataLen + 1];
        }
    }

    return eResult;
};

/******************************************************************************/
 le_func_status_e eSetLeMngCreateConn_Req(le_create_conn_st stConfig)
 {
    le_func_status_e eResult;
    uint16_t u16Offset = UART_PACKET_OFFSET;
    uint8_t au8SendBuff[64];

    u16Offset = u16AutoSetCmdHeader(au8SendBuff, TCU_MNG_LE_CREATE_CONNECTION_REQ, u16Offset);

    vWrite2Array_16(au8SendBuff, stConfig.u16ScanInterval, &u16Offset);
    vWrite2Array_16(au8SendBuff, stConfig.u16ScanWindow, &u16Offset);

    vWrite2Array_8(au8SendBuff, stConfig.eInitFiltPolicy, &u16Offset);
    vWrite2Array_8(au8SendBuff, stConfig.ePeerAddrType, &u16Offset);

    vCopyArrayParams(stConfig.au8PeerAddr,au8SendBuff ,0 ,u16Offset , BD_ADDR_SIZE);
    u16Offset+=BD_ADDR_SIZE;

    vWrite2Array_8(au8SendBuff, stConfig.eOwnAddrType, &u16Offset);
    vWrite2Array_16(au8SendBuff, stConfig.u16ConnIntMin, &u16Offset);
    vWrite2Array_16(au8SendBuff, stConfig.u16ConnIntMax, &u16Offset);
    vWrite2Array_16(au8SendBuff, stConfig.u16ConnLatency, &u16Offset);
    vWrite2Array_16(au8SendBuff, stConfig.u16SupervTimeout, &u16Offset);
    vWrite2Array_16(au8SendBuff, stConfig.u16MinCeLength, &u16Offset);
    vWrite2Array_16(au8SendBuff, stConfig.u16MaxCeLength, &u16Offset);

    /* Send command */
    eResult = eSendData(au8SendBuff, u16Offset);

    return eResult;
 };

/******************************************************************************/
le_func_status_e eGetLeMngConnComplete_Event(uint8_t* pu8Data, le_conn_evt_st* pstEvent)
{

   le_func_status_e eResult;
    uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_MNG_LE_CONNECTION_COMPLETE_EVENT);

    if(LE_FUNC_SUCCCESS == eResult)
    {
        pstEvent->u8Status= pu8Data[u32Offset++];
        pstEvent->u16ConnHandle= GET_SHORT(pu8Data[u32Offset], pu8Data[u32Offset+1]);
        u32Offset+=2;
        pstEvent->eRole= (role_e)pu8Data[u32Offset++];
        pstEvent->ePeerAddrType=(own_addr_type_e)pu8Data[u32Offset++];

        vCopyArrayParams(pu8Data, pstEvent->au8PeerAddr , u32Offset, 0 , BD_ADDR_SIZE);
        u32Offset+=BD_ADDR_SIZE;

        pstEvent->u16ConnInt=GET_SHORT(pu8Data[u32Offset], pu8Data[u32Offset+1]);
        u32Offset+=2;
        pstEvent->u16ConnLatency=GET_SHORT(pu8Data[u32Offset], pu8Data[u32Offset+1]);
        u32Offset+=2;
        pstEvent->u16SupervTimeout=GET_SHORT(pu8Data[u32Offset], pu8Data[u32Offset+1]);
        u32Offset+=2;
        pstEvent->u8MstrClkAccuracy=pu8Data[u32Offset];

    }

    return eResult;

};

/******************************************************************************/
 le_func_status_e eSetLeMngCreateConnCancel_Req(void)
 {
    le_func_status_e eResult;
    uint16_t u16Offset = UART_PACKET_OFFSET;
    //uint8_t au8SendBuff[64];

    u16Offset = u16AutoSetCmdHeader(au8SendBuff, TCU_MNG_LE_CREATE_CONNECTION_CANCEL_REQ, u16Offset);

    /* Send command */
    eResult = eSendData(au8SendBuff, u16Offset);

    return  eResult;
 };

/******************************************************************************/
le_func_status_e eGetLeMngCreateConnCancel_Resp(uint8_t* pu8Data, uint8_t* puStatus)
{

   le_func_status_e eResult;
    uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_MNG_LE_CREATE_CONNECTION_CANCEL_RESP);

    if(LE_FUNC_SUCCCESS == eResult)
    {
        *puStatus=pu8Data[u32Offset];
    }

    return eResult;

};

/******************************************************************************/
le_func_status_e eSetLeDisconnect_Req(uint8_t* pu8BdAddr)
{
   le_func_status_e eResult;
    uint16_t u16Offset = UART_PACKET_OFFSET;;
    //uint8_t au8SendBuff[64];

    u16Offset = u16AutoSetCmdHeader(au8SendBuff, TCU_MNG_LE_DISCONNECT_REQ, u16Offset);

     vCopyArrayParams(pu8BdAddr,au8SendBuff ,0 ,u16Offset , BD_ADDR_SIZE);

    /* Send command */
    eResult = eSendData(au8SendBuff, u16Offset);

    return  eResult;
 };

/******************************************************************************/
le_func_status_e eGetLeDisconnect_Event(uint8_t* pu8Data, le_disconnect_st* pstEvntData)
{

    le_func_status_e eResult;
    uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_MNG_LE_DISCONNECT_EVENT);

    if(LE_FUNC_SUCCCESS == eResult)
    {
        pstEvntData->u16ConnHandle = GET_SHORT(pu8Data[u32Offset], pu8Data[u32Offset+1]);
        u32Offset+=2;
        pstEvntData->u8Status = pu8Data[u32Offset++];
        pstEvntData->u8Reason = pu8Data[u32Offset];
    }

    return eResult;

};

/******************************************************************************/
le_func_status_e eSetLeScanDisable_Req(void)
{
    le_func_status_e eResult;
    uint16_t u16Offset = UART_PACKET_OFFSET;
    //uint8_t au8SendBuff[64];

    u16Offset = u16AutoSetCmdHeader(au8SendBuff, TCU_MNG_LE_SET_SCAN_DISABLE_REQ, u16Offset);

    /* Send command */
    eResult = eSendData(au8SendBuff, u16Offset);

    return  eResult;

};

/******************************************************************************/
le_func_status_e eGetLeScanDisable_Resp(uint8_t* pu8Data, uint8_t* pu8Status)
{

    le_func_status_e eResult;
    uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_MNG_LE_SET_SCAN_DISABLE_RESP);

    if(LE_FUNC_SUCCCESS == eResult)
    {
        *pu8Status = pu8Data[u32Offset];
    }

    return eResult;

};


/******************************************************************************/
le_func_status_e eSetLeStartAdvertise_Req(le_adv_req_st stConfig)
{
    le_func_status_e eResult;
    uint16_t u16Offset = UART_PACKET_OFFSET;
    //uint8_t au8SendBuff[64];

    u16Offset = u16AutoSetCmdHeader(au8SendBuff, TCU_MNG_LE_START_ADVERTISE_REQ, u16Offset);

    vWrite2Array_16(au8SendBuff, stConfig.u16AdvIntervalMin, &u16Offset);
    vWrite2Array_16(au8SendBuff, stConfig.u16AdvIntervalMax, &u16Offset);
    vWrite2Array_8(au8SendBuff, stConfig.eAdvType, &u16Offset);
    vWrite2Array_8(au8SendBuff, stConfig.eOwnAddrType, &u16Offset);
    vWrite2Array_8(au8SendBuff, stConfig.eDirectAddrType, &u16Offset);

    vCopyArrayParams(stConfig.au8DirectAddr, au8SendBuff , 0, u16Offset , BD_ADDR_SIZE);
    u16Offset+= BD_ADDR_SIZE;

    vWrite2Array_8(au8SendBuff, stConfig.u8AdvChannelMap, &u16Offset);
    vWrite2Array_8(au8SendBuff, stConfig.eAdvFilterPolicy, &u16Offset);
    vWrite2Array_8(au8SendBuff, stConfig.u8AdvDataLen, &u16Offset);
    
    vCopyArrayParams(stConfig.au8AdvData, au8SendBuff , 0, u16Offset, 31);
    u16Offset = u16Offset + 31;
    
    vWrite2Array_8(au8SendBuff, stConfig.u8ScanRespDataLen, &u16Offset);

    vCopyArrayParams(stConfig.au8ScanRespData, au8SendBuff , 0, u16Offset, 31);
    u16Offset = u16Offset + 31;
    /* Send command */
    eResult = eSendData(au8SendBuff, u16Offset);

    return  eResult;
};

/******************************************************************************/
le_func_status_e eGetLeStartAdvertise_Resp(uint8_t* pu8Data, uint8_t* pu8Status)
{

    le_func_status_e eResult;
    uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_MNG_LE_START_ADVERTISE_RESP);

    if(LE_FUNC_SUCCCESS == eResult)
    {
         *pu8Status = pu8Data[u32Offset];
    }

    return eResult;

};

/******************************************************************************/
le_func_status_e eSetLeDisableAdvertise_Req(void)
{
    le_func_status_e eResult;
    uint16_t u16Offset = UART_PACKET_OFFSET;
    
    u16Offset = u16AutoSetCmdHeader(au8SendBuff, TCU_MNG_LE_DISABLE_ADVERTISE_REQ, u16Offset);

    /* Send command */
    eResult = eSendData(au8SendBuff, u16Offset);

    return  eResult;
};

/******************************************************************************/
le_func_status_e eGetLeDisableAdvertise_Resp(uint8_t* pu8Data, uint8_t* pu8Status)
{

    le_func_status_e eResult;
    uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_MNG_LE_DISABLE_ADVERTISE_RESP);

    if(LE_FUNC_SUCCCESS == eResult)
    {
         *pu8Status = pu8Data[u32Offset];
    }

    return eResult;

};

/******************************************************************************/
le_func_status_e eSetSdbGattAddPrimaryService_Req(uuid_type_e eUuidLen, uint8_t* pu8UUIDVal)
{
    le_func_status_e eResult;
    uint16_t u16Offset = UART_PACKET_OFFSET;
    //uint8_t au8SendBuff[64];

    u16Offset = u16SetCmdHeaderUserLen(au8SendBuff, TCU_LE_GATT_SDB_ADD_PRIM_SVC_REQ, (uint16_t)(eUuidLen) + 1, u16Offset);

    vWrite2Array_8(au8SendBuff, eUuidLen, &u16Offset);

    vCopyArrayParams(pu8UUIDVal,au8SendBuff ,0 ,u16Offset , (uint16_t)eUuidLen);

    /* Send command */
    eResult = eSendData(au8SendBuff, u16Offset);

    return  eResult;
};

/******************************************************************************/
le_func_status_e eGetSdbGattAddPrimaryService_Resp(uint8_t* pu8Data, uint8_t* pu8Status, uint16_t* pu16Handle)
{

    le_func_status_e eResult;
    uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_LE_GATT_SDB_ADD_PRIM_SVC_RESP);

    if(LE_FUNC_SUCCCESS == eResult)
    {
         *pu8Status = pu8Data[u32Offset++];
         *pu16Handle = GET_SHORT(pu8Data[u32Offset],pu8Data[u32Offset+1]);

    }

    return eResult;

};

/******************************************************************************/
le_func_status_e eSetSdbGattAddSecondaryService_Req(uuid_type_e eUuidLen, uint16_t u16ParentSvcHandle, uint8_t* pu8UUIDVal)
{
    le_func_status_e eResult;
    uint16_t u16Offset = UART_PACKET_OFFSET;
    
    u16Offset = u16SetCmdHeaderUserLen(au8SendBuff, TCU_LE_GATT_SDB_ADD_SEC_SVC_REQ, (uint16_t)(eUuidLen) + 1, u16Offset);
    
    vWrite2Array_16(au8SendBuff, u16ParentSvcHandle, &u16Offset);

    vWrite2Array_8(au8SendBuff, eUuidLen, &u16Offset);

    vCopyArrayParams(pu8UUIDVal,au8SendBuff ,0 ,u16Offset , (uint16_t)eUuidLen);

    /* Send command */
    eResult = eSendData(au8SendBuff, u16Offset);

    return  eResult;
};

/******************************************************************************/
le_func_status_e eGetSdbGattAddSecondaryService_Resp(uint8_t* pu8Data, uint8_t* pu8Status, uint16_t* pu16Handle)
{
    le_func_status_e eResult;
    uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_LE_GATT_SDB_ADD_SEC_SVC_RESP);

    if(LE_FUNC_SUCCCESS == eResult)
    {
         *pu8Status = pu8Data[u32Offset++];
         *pu16Handle = GET_SHORT(pu8Data[u32Offset],pu8Data[u32Offset+1]);

    }

    return eResult;

};
/******************************************************************************/
le_func_status_e eSetSdbGattAddCharacterDecl_Req(uint16_t u16Handle, uint8_t u8Properties, uuid_type_e eUuidLen, uint8_t* pu8UUIDVal)
{
    le_func_status_e eResult;
    uint16_t u16Offset = UART_PACKET_OFFSET;
    //uint8_t au8SendBuff[64];

    u16Offset = u16SetCmdHeaderUserLen(au8SendBuff, TCU_LE_GATT_SDB_ADD_CHAR_DECL_REQ, (uint16_t)(eUuidLen)+4, u16Offset);

    vWrite2Array_16(au8SendBuff, u16Handle, &u16Offset);
    vWrite2Array_8(au8SendBuff, u8Properties, &u16Offset);
    vWrite2Array_8(au8SendBuff, eUuidLen, &u16Offset);

    vCopyArrayParams(pu8UUIDVal,au8SendBuff ,0 ,u16Offset , (uint16_t)eUuidLen);
    u16Offset += (uint16_t)eUuidLen;

    /* Send command */
    eResult = eSendData(au8SendBuff, u16Offset);

    return  eResult;
};
/******************************************************************************/
le_func_status_e eGetSdbGattAddCharacterDecl_Resp(uint8_t* pu8Data, gatt_status_code_e* peStatus, uint16_t* pu16Handle)
{
    le_func_status_e eResult;
    uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_LE_GATT_SDB_ADD_CHAR_DECL_RESP);

    if(LE_FUNC_SUCCCESS == eResult)
    {
        *peStatus = (gatt_status_code_e)pu8Data[u32Offset++];
        *pu16Handle = GET_SHORT(pu8Data[u32Offset],pu8Data[u32Offset+1]);
    }

    return eResult;

};

/******************************************************************************/
le_func_status_e eSetSdbGattAddCharacterEle_Req(uint16_t  u16Handle, char_el_req_st stParams)
{
    le_func_status_e eResult;
    uint16_t u16Offset = UART_PACKET_OFFSET;
    
    u16Offset = u16SetCmdHeaderUserLen(au8SendBuff, TCU_LE_GATT_SDB_ADD_CHAR_ELE_REQ, stParams.eAttrLen + stParams.u16AttValLen + 7, u16Offset);

    vWrite2Array_16(au8SendBuff,u16Handle, &u16Offset);
    vWrite2Array_8(au8SendBuff, (uint8_t)(stParams.eAttrLen), &u16Offset);
    vCopyArrayParams(stParams.au8AttType, au8SendBuff , 0, u16Offset , (uint16_t)stParams.eAttrLen);
    u16Offset += (uint16_t)stParams.eAttrLen;
    vWrite2Array_16(au8SendBuff, stParams.u16AttValLen, &u16Offset);
    vCopyArrayParams(stParams.pu8AttVal, au8SendBuff , 0, u16Offset , (uint16_t)stParams.u16AttValLen);
    u16Offset += (uint16_t)stParams.u16AttValLen;

    vWrite2Array_16(au8SendBuff, stParams.u16AttPermission, &u16Offset);

    /* Send command */
    eResult = eSendData(au8SendBuff, u16Offset);

    return  eResult;
};
/******************************************************************************/
le_func_status_e eGetSdbGattAddCharacterEle_Resp(uint8_t* pu8Data, gatt_status_code_e* peStatus, uint16_t* pu16Handle)
{

    le_func_status_e eResult;
    uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_LE_GATT_SDB_ADD_CHAR_ELE_RESP);

    if(LE_FUNC_SUCCCESS == eResult)
    {
       *peStatus = (gatt_status_code_e)pu8Data[u32Offset++];
       *pu16Handle = GET_SHORT(pu8Data[u32Offset],pu8Data[u32Offset+1]);

    }

    return eResult;

};

/******************************************************************************/
le_func_status_e eSetSdbGattUpdateCharacterEle_Req(uint16_t u16Handle, uint16_t u16AttValLen, uint8_t* pu8AttVal)
{
    le_func_status_e eResult;
    uint16_t u16Offset = UART_PACKET_OFFSET;
    //uint8_t au8SendBuff[64];

    u16Offset = u16SetCmdHeaderUserLen(au8SendBuff, TCU_LE_GATT_SDB_UPD_CHAR_ELE_REQ,  u16AttValLen + 4, u16Offset);

    vWrite2Array_16(au8SendBuff, u16Handle, &u16Offset);
    vWrite2Array_16(au8SendBuff, u16AttValLen, &u16Offset);

    vCopyArrayParams(pu8AttVal, au8SendBuff , 0, u16Offset , u16AttValLen);
    u16Offset += u16AttValLen;

    /* Send command */
    eResult = eSendData(au8SendBuff, u16Offset);

    return  eResult;
};
/******************************************************************************/
le_func_status_e eGetSdbGattUpdateCharacterEle_Resp(uint8_t* pu8Data, gatt_status_code_e* peStatus)
{

    le_func_status_e eResult;
    uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_LE_GATT_SDB_UPD_CHAR_ELE_RESP);

    if(LE_FUNC_SUCCCESS == eResult)
    {
        *peStatus = (gatt_status_code_e)pu8Data[u32Offset];
    }

    return eResult;
};

/******************************************************************************/
le_func_status_e eSetSdbGattAddInclSvc_Req(uint16_t u16SvcHandle, uuid_type_e eAttValLen, uint8_t* pu8AttVal)
{
    le_func_status_e eResult;
    uint16_t u16Offset = UART_PACKET_OFFSET;

    u16Offset = u16SetCmdHeaderUserLen(au8SendBuff, TCU_LE_GATT_SDB_ADD_INC_SVC_REQ,  eAttValLen + 4, u16Offset);

    vWrite2Array_16(au8SendBuff, u16SvcHandle, &u16Offset);
    vWrite2Array_8(au8SendBuff, eAttValLen, &u16Offset);

    vCopyArrayParams(pu8AttVal, au8SendBuff , 0, u16Offset , eAttValLen);
    u16Offset += eAttValLen;

    /* Send command */
    eResult = eSendData(au8SendBuff, u16Offset);

    return  eResult;
};

/******************************************************************************/
le_func_status_e eGetSdbGattAddInclSvc_Resp(uint8_t* pu8Data, le_resp_st* pstRespData)
{
    le_func_status_e eResult;
    uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_LE_GATT_SDB_ADD_INC_SVC_RESP);

    if(LE_FUNC_SUCCCESS == eResult)
    {
      pstRespData->eStatus = (gatt_status_code_e)pu8Data[u32Offset++];
      pstRespData->u16Handle = GET_SHORT(pu8Data[u32Offset],pu8Data[u32Offset+1]);
    }

    return eResult;
};

/******************************************************************************/
le_func_status_e eSetSdbGattReturnEndGroupHandle_Req(uint16_t u16Handle)
{
    le_func_status_e eResult;
    uint16_t u16Offset= UART_PACKET_OFFSET;
    //uint8_t au8SendBuff[64];

    u16Offset = u16AutoSetCmdHeader(au8SendBuff, TCU_LE_GATT_SDB_RET_END_GRP_HLE_REQ, u16Offset);

    vWrite2Array_16(au8SendBuff, u16Handle, &u16Offset);

    /* Send command */
    eResult = eSendData(au8SendBuff, u16Offset);

    return  eResult;
};
/******************************************************************************/
le_func_status_e eGetSdbGattReturnEndGroupHandle_Resp(uint8_t* pu8Data, le_resp_st* pstRespData)
{
    le_func_status_e eResult;
    uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_LE_GATT_SDB_RET_END_GRP_HLE_RESP);

    if(LE_FUNC_SUCCCESS == eResult)
    {
        pstRespData->eStatus = (gatt_status_code_e)pu8Data[u32Offset++];
        pstRespData->u16Handle = GET_SHORT(pu8Data[u32Offset],pu8Data[u32Offset+1]);
    }

    return eResult;

};

/******************************************************************************/
le_func_status_e eSetServerGattInit_Req(void)
{
    le_func_status_e eResult;
    uint16_t u16Offset = UART_PACKET_OFFSET;

    u16Offset = u16AutoSetCmdHeader(au8SendBuff, TCU_LE_GATT_SER_INIT_REQ, u16Offset);

    /* Send command */
    eResult = eSendData(au8SendBuff, u16Offset);

    return  eResult;
};

/******************************************************************************/
le_func_status_e eGetServerGattInit_Resp(uint8_t* pu8Data, gatt_status_code_e* peStatus)
{
    le_func_status_e eResult;
    uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_LE_GATT_SER_INIT_RESP);

    if(LE_FUNC_SUCCCESS == eResult)
    {
        *peStatus = (gatt_status_code_e)pu8Data[u32Offset];
    }

    return eResult;
}

/******************************************************************************/

le_func_status_e eGetServerGattWriteCharDesc_Event(uint8_t* pu8Data, le_srv_write_char_desp_event_st* pstEvntData)
{
    le_func_status_e eResult;
    uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;
    uint16_t u16paramLen = PARSE_CMD_PARAM_LENGTH(pu8Data) - 4;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_LE_GATT_SER_WRITE_CHAR_DESP_EVENT);

    if(LE_FUNC_SUCCCESS == eResult)
    {
      pstEvntData->u16ConnHandle = GET_SHORT(pu8Data[u32Offset], pu8Data[u32Offset+1]);
      u32Offset+=2;
      pstEvntData->u16CharDescHandle = GET_SHORT(pu8Data[u32Offset], pu8Data[u32Offset+1]);
      u32Offset+=2;
      
      pstEvntData->u16CharValueLen = u16paramLen;
            
      vCopyArrayParams(pu8Data, pstEvntData->pu8CharDescValue, u32Offset, 0 , pstEvntData->u16CharValueLen);
    
    }

    return eResult;
}

/******************************************************************************/
le_func_status_e eSetServerGattWriteCharDescAccept_Req(uint16_t u16ConnHandle,gatt_status_code_e eStatus, uint16_t u16DescHle)
{
    le_func_status_e eResult;
    uint16_t u16Offset = UART_PACKET_OFFSET;
    //uint8_t au8SendBuff[64];

    u16Offset = u16AutoSetCmdHeader(au8SendBuff, TCU_LE_GATT_SER_WRITE_CHAR_DESP_ACCEPT_REQ, u16Offset);

    vWrite2Array_16(au8SendBuff, u16ConnHandle, &u16Offset);
    vWrite2Array_8(au8SendBuff, eStatus, &u16Offset);
    vWrite2Array_16(au8SendBuff, u16DescHle, &u16Offset);

    /* Send command */
    eResult = eSendData(au8SendBuff, u16Offset);

    return  eResult;
};

/******************************************************************************/
le_func_status_e eGetServerGattReadCharVal_Event(uint8_t* pu8Data, le_srv_read_char_val_event_st* pstEvntData)
{
    le_func_status_e eResult;
    uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_LE_GATT_SER_READ_CHAR_VAL_EVENT);

    if(LE_FUNC_SUCCCESS == eResult)
    {
        pstEvntData->u16ConnHandle     = GET_SHORT(pu8Data[u32Offset],pu8Data[u32Offset+1]);
        u32Offset+=2;
        pstEvntData->u16CharDescHandle = GET_SHORT(pu8Data[u32Offset],pu8Data[u32Offset+1]);
    }

    return eResult;
}

/******************************************************************************/
le_func_status_e eGetServerGattWriteCharDespAccept_Resp(uint8_t* pu8Data, le_srv_multi_acc_event_st* pstEvntData)
{
    le_func_status_e eResult;
    uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_LE_GATT_SER_WRITE_CHAR_DESP_ACCEPT_RESP);

    if(LE_FUNC_SUCCCESS == eResult)
    {
      pstEvntData->u16ConnHandle = GET_SHORT(pu8Data[u32Offset], pu8Data[u32Offset+1]);
      u32Offset+=2;
      pstEvntData->eStatus = (gatt_status_code_e) pu8Data[u32Offset];
    }

    return eResult;
}


/******************************************************************************/
le_func_status_e eSetServerGattReadCharValAccept_Req(uint16_t u16ConnHandle, gatt_status_code_e eStatus, uint16_t u16ReadCharHle)
{
    le_func_status_e eResult;
    uint16_t u16Offset = UART_PACKET_OFFSET;
    //uint8_t au8SendBuff[64];

    u16Offset = u16AutoSetCmdHeader(au8SendBuff, TCU_LE_GATT_SER_READ_CHAR_VAL_ACCEPT_REQ, u16Offset);

    vWrite2Array_16(au8SendBuff, u16ConnHandle, &u16Offset);
    vWrite2Array_8(au8SendBuff, eStatus, &u16Offset);
    vWrite2Array_16(au8SendBuff, u16ReadCharHle, &u16Offset);

    /* Send command */
    eResult = eSendData(au8SendBuff, u16Offset);

    return  eResult;
};

/******************************************************************************/
le_func_status_e eSetServerGattReadCharValAccept_Resp(uint8_t* pu8Data, le_srv_read_char_acc_event_st* pstEvntData)
{
    le_func_status_e eResult;
    uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_LE_GATT_SER_READ_CHAR_VAL_ACCEPT_RESP);

    if(LE_FUNC_SUCCCESS == eResult)
    {
        pstEvntData->u16ConnHandle = GET_SHORT(pu8Data[u32Offset],pu8Data[u32Offset+1]);
        u32Offset+=2;
        pstEvntData->eStatus       =(gatt_status_code_e)(GET_SHORT(pu8Data[u32Offset],pu8Data[u32Offset+1]));
    }

    return eResult;  
};

/******************************************************************************/
le_func_status_e eGetServerGattExgMtu_Event(uint8_t* pu8Data, le_mtu_exchg_st* pstMtuData)
{
    le_func_status_e eResult;
    uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_LE_GATT_SER_EXG_MTU_EVENT);

    if(LE_FUNC_SUCCCESS == eResult)
    {
        *(pstMtuData->pu16ConnHandle) = GET_SHORT(pu8Data[u32Offset],pu8Data[u32Offset+1]);
        u32Offset+=2;
        *(pstMtuData->pu16ClientRxMtuSize) = GET_SHORT(pu8Data[u32Offset],pu8Data[u32Offset+1]);
    }

    return eResult;
}

/******************************************************************************/
le_func_status_e eGetServerGattExgMtuAccept_Req(uint16_t u16ConnHandle, uint8_t  u8Status, uint16_t u16ServerRxMtuSize)
{
  le_func_status_e eResult;
  uint16_t u16Offset = UART_PACKET_OFFSET;


  u16Offset = u16AutoSetCmdHeader(au8SendBuff, TCU_LE_GATT_SER_EXG_MTU_ACCEPT_REQ, u16Offset);
    
  vWrite2Array_16(au8SendBuff, u16ConnHandle, &u16Offset);
  vWrite2Array_8(au8SendBuff, u8Status, &u16Offset);
  vWrite2Array_16(au8SendBuff, u16ServerRxMtuSize, &u16Offset);
  
  /* Send command */
  eResult = eSendData(au8SendBuff, u16Offset);
    
  return  eResult;
}

/******************************************************************************/
le_func_status_e eGetServerGattExgMtuAccept_Resp(uint8_t* pu8Data, le_mtu_exchg_acc_resp_st* stResp)
{
    le_func_status_e eResult;
    uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_LE_GATT_SER_EXG_MTU_ACCEPT_RESP);

    if(LE_FUNC_SUCCCESS == eResult)
    {
      stResp->u16ConnHandle = GET_SHORT(pu8Data[u32Offset],pu8Data[u32Offset+1]);
      u32Offset+=2;
      stResp->u8Status = pu8Data[u32Offset++];
      stResp->u16ServerRxMtuSize = GET_SHORT(pu8Data[u32Offset],pu8Data[u32Offset+1]);
    }

    return eResult;
}

/******************************************************************************/
le_func_status_e eGetServerGattWriteCharVal_Event(uint8_t* pu8Data,le_srv_write_char_desp_event_st* pstEvntData)
{
    le_func_status_e eResult;
    uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;
    uint16_t u16paramLen = PARSE_CMD_PARAM_LENGTH(pu8Data) - 4;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_LE_GATT_SER_WRITE_CHAR_VAL_EVENT);

    if(LE_FUNC_SUCCCESS == eResult)
    {
      pstEvntData->u16ConnHandle = GET_SHORT(pu8Data[u32Offset], pu8Data[u32Offset+1]);
      u32Offset+=2;
      pstEvntData->u16CharDescHandle = GET_SHORT(pu8Data[u32Offset], pu8Data[u32Offset+1]);
      u32Offset+=2;
      
      pstEvntData->u16CharValueLen = u16paramLen;
            
      vCopyArrayParams(pu8Data, pstEvntData->pu8CharDescValue, u32Offset, 0 , pstEvntData->u16CharValueLen);
    
    }

    return eResult;
}

/******************************************************************************/
le_func_status_e eSetServerGattWriteCharValAccept_Req(uint16_t u16ConnHandle, gatt_status_code_e eStatus, uint16_t u16ValHle)
{
    le_func_status_e eResult;
    uint16_t u16Offset = UART_PACKET_OFFSET;
    //uint8_t au8SendBuff[64];

    u16Offset = u16AutoSetCmdHeader(au8SendBuff, TCU_LE_GATT_SER_WRITE_CHAR_VAL_ACCEPT_REQ, u16Offset);

    vWrite2Array_16(au8SendBuff, u16ConnHandle, &u16Offset);
    vWrite2Array_8(au8SendBuff, eStatus, &u16Offset);
    vWrite2Array_16(au8SendBuff, u16ValHle, &u16Offset);

    /* Send command */
    eResult = eSendData(au8SendBuff, u16Offset);

    return  eResult;
};

/******************************************************************************/
le_func_status_e eGetServerGattWriteCharValAccept_Resp(uint8_t* pu8Data, le_srv_multi_acc_event_st* pstEvntData)
{
    le_func_status_e eResult;
    uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_LE_GATT_SER_WRITE_CHAR_VAL_ACCEPT_RESP);

    if(LE_FUNC_SUCCCESS == eResult)
    {
      pstEvntData->u16ConnHandle = GET_SHORT(pu8Data[u32Offset], pu8Data[u32Offset+1]);
      u32Offset+=2;
      pstEvntData->eStatus = (gatt_status_code_e) pu8Data[u32Offset];
    }

    return eResult;
}

/******************************************************************************/
le_func_status_e eGetServerGattReadMulti_Event(uint8_t* pu8Data, le_srv_multi_event_st* pstEvntData)
{
    le_func_status_e eResult;
   // uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;
     uint32_t u32Offset = CMD_ARRAY_LEN_OFFS;
     uint16_t u16ParamCnt;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_LE_GATT_SER_READ_MULTIPLE_EVENT);

    if(LE_FUNC_SUCCCESS == eResult)
    {
        u16ParamCnt  = GET_SHORT(pu8Data[u32Offset], pu8Data[u32Offset+1]);  
        pstEvntData->u16HndlCnt = u16ParamCnt - 2;
        u32Offset += 2;
        
        pstEvntData->u16ConnHandle = GET_SHORT(pu8Data[u32Offset], pu8Data[u32Offset+1]); 
        u32Offset += 2;
        
        vCopyArrayParams(&pu8Data[u32Offset], pstEvntData->pu8HndlList, 0, 0,  pstEvntData->u16HndlCnt);
    }

    return eResult;
}

/******************************************************************************/
le_func_status_e eSetServerGattReadMultiAccept_Req(uint16_t u16ConnHandle, gatt_status_code_e eStatus, uint8_t *pu8ReadMulHle)
{
    le_func_status_e eResult;
    uint16_t u16Offset = UART_PACKET_OFFSET;
    
    u16Offset = u16AutoSetCmdHeader(au8SendBuff, TCU_LE_GATT_SER_READ_MULTIPLE_ACCEPT_REQ, u16Offset);

    vWrite2Array_16(au8SendBuff, u16ConnHandle, &u16Offset);
    vWrite2Array_8(au8SendBuff, eStatus, &u16Offset);
    
    vCopyArrayParams(pu8ReadMulHle, au8SendBuff, 0, u16Offset,  2);
    u16Offset += 2;

    /* Send command */
    eResult = eSendData(au8SendBuff, u16Offset);

    return  eResult;
};

/******************************************************************************/
le_func_status_e eGetServerGattReadMultiAccept_Resp(uint8_t* pu8Data, le_srv_multi_acc_event_st* pstEvntData)
{
    le_func_status_e eResult;
    uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_LE_GATT_SER_READ_MULTIPLE_ACCEPT_RESP);

    if(LE_FUNC_SUCCCESS == eResult)
    {
      pstEvntData->u16ConnHandle = GET_SHORT(pu8Data[u32Offset], pu8Data[u32Offset+1]);
      u32Offset+=2;
      pstEvntData->eStatus = (gatt_status_code_e) pu8Data[u32Offset];
    }

    return eResult;
}

/******************************************************************************/
#if 0
le_func_status_e eSetServerGattValNotify_Req(uint16_t u16ConnHandle, uint16_t u16CharValHandle,  uint8_t* pu8CharValData, uint16_t u16ValDataLen)
{
    le_func_status_e eResult;
    uint16_t u16Offset = UART_PACKET_OFFSET;
    //uint8_t au8SendBuff[64];

   // u16Offset = u16AutoSetCmdHeader(au8SendBuff, );

    /* TO DO: insert data to array */

    /* Send command */
    eResult = eSendData(au8SendBuff, u16Offset);

    return  eResult;
};
#endif
/******************************************************************************/
le_func_status_e eGetServerGattValNotify_Event(uint8_t* pu8Data, uint16_t* pu16ConnHandle)
{
    le_func_status_e eResult;
    uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_LE_GATT_SER_CHAR_VAL_NOTIFICATION_EVENT);

    if(LE_FUNC_SUCCCESS == eResult)
    {
       *pu16ConnHandle = GET_SHORT(pu8Data[u32Offset], pu8Data[u32Offset+1]);
    }

    return eResult;
}

/******************************************************************************/
le_func_status_e eGetServerGattWriteWithoutRespCmd_Event(uint8_t* pu8Data, le_srv_wrt_wo_evt_st* pstEvtData)
{
    le_func_status_e eResult;
    uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_LE_GATT_SER_WRITE_WITHOUT_RESPONSE_CMD_EVENT);

    if(LE_FUNC_SUCCCESS == eResult)
    {
      pstEvtData->u16ValDataLen = PARSE_CMD_PARAM_LENGTH(pu8Data) - 4;
      pstEvtData->u16ConnHandle = GET_SHORT(pu8Data[u32Offset], pu8Data[u32Offset+1]);
      u32Offset+=2;
      pstEvtData->u16CharValHandle = GET_SHORT(pu8Data[u32Offset], pu8Data[u32Offset+1]);
      u32Offset+=2;

      vCopyArrayParams(pu8Data, pstEvtData->pu8CharValData, u32Offset, 0,  pstEvtData->u16ValDataLen);
    }

    return eResult;
}

/******************************************************************************/
le_func_status_e eSetServerGattCharValNotification_Req(uint16_t u16ConnHandle, uint16_t u16CharValHandle, uint16_t u16CharValLen, uint8_t* pu8UCharVal)
{
    le_func_status_e eResult;
    uint16_t u16Offset = UART_PACKET_OFFSET;
    uint16_t u16ParamLen;

    u16ParamLen = 4 + u16CharValLen;
    u16Offset = u16SetCmdHeaderUserLen(au8SendBuff, TCU_LE_GATT_SER_CHAR_VAL_NOTIFICATION_REQ, u16ParamLen, u16Offset);
    vWrite2Array_16(au8SendBuff, u16ConnHandle, &u16Offset);
    vWrite2Array_16(au8SendBuff, u16CharValHandle, &u16Offset);

    vCopyArrayParams(pu8UCharVal, au8SendBuff, 0, u16Offset, u16CharValLen);
    u16Offset += (uint16_t)u16CharValLen;

    /* Send command */
    eResult = eSendData(au8SendBuff, u16Offset);

    return  eResult;
};

/******************************************************************************/
le_func_status_e eSetServerGattCharValIndication_Req(uint16_t u16ConnHandle, uint16_t u16CharValHandle, uint16_t u16CharValLen, uint8_t* pu8UCharVal)
{
    le_func_status_e eResult;
    uint16_t u16Offset = UART_PACKET_OFFSET;
    uint16_t u16ParamLen;

    u16ParamLen = 4 + u16CharValLen;
    u16Offset = u16SetCmdHeaderUserLen(au8SendBuff, TCU_LE_GATT_SER_CHAR_VAL_INDICATION_REQ, u16ParamLen, u16Offset);
    vWrite2Array_16(au8SendBuff, u16ConnHandle, &u16Offset);
    vWrite2Array_16(au8SendBuff, u16CharValHandle, &u16Offset);

    vCopyArrayParams(pu8UCharVal, au8SendBuff, 0, u16Offset, u16CharValLen);
    u16Offset += (uint16_t)u16CharValLen;

    /* Send command */
    eResult = eSendData(au8SendBuff, u16Offset);

    return  eResult;
};

/******************************************************************************/
le_func_status_e eGetServerGattValIndication_Event(uint8_t* pu8Data, le_srv_char_cal_ind_st* pstEvtData)
{
    le_func_status_e eResult;
    uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_LE_GATT_SER_CHAR_VAL_INDICATION_EVENT);

    if(LE_FUNC_SUCCCESS == eResult)
    {
       pstEvtData->u16ConnHandle =GET_SHORT(pu8Data[u32Offset], pu8Data[u32Offset+1]);
       pstEvtData->eStatus       =(gatt_status_code_e) pu8Data[u32Offset];
    }

    return eResult;
}

/******************************************************************************/
le_func_status_e eGetServerGattReadCharDescriptor_Event(uint8_t* pu8Data, le_srv_read_char_val_event_st* pstEvntData)
{
    le_func_status_e eResult;
    uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_LE_GATT_SER_READ_CHAR_DESP_EVENT);

    if(LE_FUNC_SUCCCESS == eResult)
    {
       pstEvntData->u16ConnHandle     = GET_SHORT(pu8Data[u32Offset],pu8Data[u32Offset+1]);
       u32Offset+=2;
       pstEvntData->u16CharDescHandle = GET_SHORT(pu8Data[u32Offset],pu8Data[u32Offset+1]);
    }

    return eResult;
}

/******************************************************************************/
le_func_status_e eSetServerGattReadCharDescriptorAccept_Req(uint16_t u16ConnHandle,  uint8_t u8Status, uint16_t u16DescHle)
{
    le_func_status_e eResult;
    uint16_t u16Offset = UART_PACKET_OFFSET;
    
    u16Offset = u16AutoSetCmdHeader(au8SendBuff, TCU_LE_GATT_SER_READ_CHAR_DESP_ACCEPT_REQ, u16Offset);
    vWrite2Array_16(au8SendBuff, u16ConnHandle, &u16Offset);
    vWrite2Array_8(au8SendBuff, u8Status, &u16Offset);
    vWrite2Array_16(au8SendBuff, u16DescHle, &u16Offset);

    /* Send command */
    eResult = eSendData(au8SendBuff, u16Offset);

    return  eResult;
};

/******************************************************************************/
le_func_status_e eGetServerGattReadCharDescriptorAccept_Resp(uint8_t* pu8Data, le_srv_read_char_acc_event_st* pstEvntData)
{
    le_func_status_e eResult;
    uint32_t u32Offset = CMD_ARRAY_PARAM_OFFS;

    /* Check if received command is matching */
    eResult = eIsCmdMatching(pu8Data, TCU_LE_GATT_SER_READ_CHAR_DESP_ACCEPT_RESP);

    if(LE_FUNC_SUCCCESS == eResult)
    {
       pstEvntData->u16ConnHandle = GET_SHORT(pu8Data[u32Offset], pu8Data[u32Offset+1]);
       u32Offset+=2;
       pstEvntData->eStatus = (gatt_status_code_e) pu8Data[u32Offset];
    }

    return eResult;
}

/************************* BEGIN of DISCLAIMER   *****************************

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


****************************  END of DISCLAIMER *****************************/
/********************************* BEGIN OF LOG *****************************
*
* $Log: $
*
*********************************** END OF LOG *****************************/

