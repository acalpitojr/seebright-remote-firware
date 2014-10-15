/****************************************************************************
*   COPYRIGHT 2006-2009 All rights reserved
*   Toshiba Electronics Europe GmbH
*   European LSI Design and Engineering Center (ELDEC)
*****************************************************************************
*   File Name   : $RCSfile: booting.h,v $
*   Description : Contains global booting definitions
*****************************************************************************
*   PROJECT     : Bluetooth BLE
*   MODULE      :
*               : $Name:  $
*   LIBRARIES   : None
*   AUTHOR      : $Author: arelic $
*****************************************************************************
*   VERSION     : $$
*   RELEASE     : Preliminary & Confidential
*   DATE        : $Date: $
*   SOURCE MOD. : $Source:$
*   LOG:        : please have a look at the end of the file
****************************************************************************/
#ifndef _HEARTRATE_H
#define _HEARTRATE_H


/**********************************************
*                Include files                *
**********************************************/
#include "stdint.h"
#include "le_gatt_command.h"

/**********************************************
*               Defs                          *
**********************************************/
/* APPEARANCE value for H/R sensor */
#define HR_APPEARANCE 833


/**********************************************
*               Enums                         *
**********************************************/
/* GAP UUID */
typedef enum tag_gap_uuid_e
{
    GAP_SERVICE                        = 0x1800,
    GAP_DEV_NAME                       = 0x2A00,
    APPEARANCE                         = 0x2A01
} gap_uuid_e;

/* GATT UUID */
typedef enum tag_gatt_uuid_e
{
    GATT_DEV_INFO                      = 0x180A, /* Device Information Service */
    GATT_CHAR_MANUF_NAME_STRING        = 0x2A29, /* Manufacturer String Characteristic */
    GATT_HEART_RATE                    = 0x180D, /* Heart Rate Service */
    GATT_HEART_RATE_MEASUREMENT        = 0x2A37, /* Heart Rate Measurement Characteristic */
    GATT_CLI_CHARACT_CONFIGURATION     = 0x2902  /* Client characteristic configuration */

} gatt_uuid_e;

/**********************************************
*               Structs                       *
**********************************************/
/* Heart Rate initialisation structure */
typedef struct tag_hr_init_st
{
  uint8_t*  pu8DevName;                                 /* Device Name of the Heart Rate Sensor */
  uint8_t   u8DevNameLen;                               /* Length of the Devace Name */
  uint8_t*  pu8ManufName;                               /* Manufacturer Name of the Heart Rate Sensor */
  uint8_t   pu8ManufNameLen;                            /* Length of the Manufacturer Name */
  uint16_t  u16ConnHandle;                              /* Connection Handle */

  uint16_t* pu16RetDevNameSvcHndl;                      /* GAP Device Name Service Return Handle */

  uint16_t* pu16RetDISvcHndl;                           /* GATT Device Identification Service Return Handle */
  uint16_t* pu16RetDICharDeclHndl;                      /* GATT Device Identification Characteristic Declaration Return Handle */
  uint16_t* pu16RetDICharValDeclHndl;                   /* GATT Device Identification Characteristic VALUE Declaration Return Handle */

  uint16_t* pu16RetHRSvcHndl;                           /* GATT Heart Rate Service Return Handle */
  uint16_t* pu16RetHRCharDeclHndl;                      /* GATT Heart Rate Measurement Characteristic Declaration Return Handle */
  uint16_t* pu16RetHRCharValDeclHndl;                   /* GATT Heart Rate Measurement Characteristic VALUE Declaration Return Handle */
  le_conn_evt_st* pstConnectInfo;                       /* Connection information */
  le_mtu_exchg_st* pstMtuEvtData;                       /* MTU Event Data */
  le_mtu_exchg_acc_resp_st* pstMtuAccResp;              /* MTU Accept Response */

} hr_init_st;

/**********************************************
*                Functions                    *
**********************************************/
/**
 * @brief     Initializes Peripheral device, GATT Server and registers
 *            following services:
 *              1) GAP Device Name,
 *              2) GATT Device Identification,
 *              3) Heart-Rate Services.
 *            On the end configures and starts Advertizing.
 *            After successfully completing this function,  the device
 *            is discoverable by the Client during SCAN procedure.
 *
 * @param[in]  qHandle OS Message-Queue Handle
 * @param[in]  stInit Pointer to initialization structure
 *
 */
le_api_result_e eHRInitialise(xQueueHandle qHandle,
                               hr_init_st* stInit);

/**
 * @brief     Main Heart Rate Profil Routine is an event driven routine, which
 *            processes events comming from the local Chiron chip or from a remote
 *            BT Client.
 *
 * @param[in]  qHandle OS Message-Queue Handle
 * @param[in]  stInit Pointer to initialization structure
 *
 */
void HRMainRoutine(xQueueHandle qHandle, hr_init_st* stInit);

/**
 * @brief     Configures and starts advertizing. After this function is executed,
 *            the device is visible to all central devices performing the scan
 *            procedure
 *
 * @param[in]  qHandle OS Message-Queue Handle
 *
 */
le_api_result_e eHRStartAdvertising(xQueueHandle qHandle);

/**
 * @brief     Registers GAP services (Device Name & Appearance)
 *
 * @param[in]  qHandle OS Message-Queue Handle
 * @param[in]  stInit Pointer to initialization structure
 *
 */
le_api_result_e eHRAddGAPDevName_Appearance_Service(xQueueHandle qHandle,
                                                   uint16_t* pu16SvcHandle,
                                                   uint16_t u16DevNameLen,
                                                   uint8_t* pu8DevName);

/**
 * @brief     Registers GATT Device Identification  Service to the GATT data-base
 *
 * @param[in]  qHandle OS Message-Queue Handle
 * @param[in]  stInit Pointer to initialization structure
 * @param[in]  pu8ManufName Manufacturer name string in UTF8 format.
 * @param[in]  pu8ManufNameLen Length of the manufacturer name string array.
 * @param[out]  pu16SvcHandle Returned service handle.
 * @param[out]  pu16RetHandleCharDecl Returned character declaration handle
 * @param[out]  pu16RetHandleCharValDecl Returned character value declaration handles.
 *
 */
le_api_result_e eHRAddDevIdentService(xQueueHandle qHandle,
                                       uint8_t* pu8ManufName,
                                       uint8_t pu8ManufNameLen,
                                       uint16_t* pu16SvcHandle,
                                       uint16_t* pu16RetHandleCharDecl,
                                       uint16_t* pu16RetHandleCharValDecl);
/**
 * @brief     Registers GAP services (Device Name & Appearance)
 *
 * @param[out]  pu16RetHandleCharDecl Returned character declaration handle
 * @param[out]  pu16RetHandleCharValDecl Returned character value declaration handles.
 *
 */
le_api_result_e eHRAddHeartRateService(xQueueHandle qHandle, uint16_t* pu16SvcHandle,
                                     uint16_t* pu16RetHandleCharDecl,
                                     uint16_t* pu16RetHandleCharValDecl);


#endif /* _HEARTRATE_H */

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