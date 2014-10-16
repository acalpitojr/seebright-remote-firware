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
*   VERSION     : 1.01
*   DATE        : 2.05.2012
*****************************************************************************/

/*****************************************************************************
DEMO description:
In this sample TC35661 is connection initiator.
It searches for inquiring devices (PartyB).
TC35661 starts connection procedure if PartyB supports SPP.
If connection succeeds the demo sample transmits string "! HELLO !" 
and sends back all received data.
*****************************************************************************/

/**********************************************
*                Include files                *
**********************************************/
#include "bt_common.h"
#include "bt_spp_api.h"

/**********************************************
*         Variables and forward declarations  *
**********************************************/
extern uint8_t DATA_FROM_BLUETOOTH_UART;
/**********************************************
*             Constants & Macros              *
**********************************************/
//#define tskIDLE_PRIORITY			            ( ( unsigned uint32_t ) 0U )
//#define tskLED1_PRIORITY                        ( ( unsigned uint32_t ) 1U )
//#define tskLED2_PRIORITY                        ( ( unsigned uint32_t ) 2U )
//#define mainQUEUE_RECEIVE_TASK_PRIORITY         ( ( unsigned uint32_t ) 3U )


/**********************************************
*  Static variables and forward declarations  *
**********************************************/
/* The rate at which data is sent to the queue, specified in milliseconds. */
//#define mainQUEUE_SEND_FREQUENCY_MS			( 10 / portTICK_RATE_MS )

/**************************************
**************************************/
//void vApplicationStackOverflowHook (xTaskHandle *pxTask, signed portCHAR *pcTaskName)
//{
	/* This function will get called if a task overflows its stack. */
//  (void)pxTask;
//  (void)pcTaskName;
//  while(1);
//}

/**************************************
**************************************/
void error(void){
  while(1);
}
/**************************************
**************************************/
#if 0
int main(void)
{
  //unsigned portSHORT stackSize = 800;
  //pdTASK_CODE pvTask;
  
 // #ifdef  RUN_IN_RAM
 // /* Set the Vector Table base location at 0x02000000 */
 //   SCB->VTOR = ((uint32_t)0x20000000);
 // #else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x00000000 */
 //   SCB->VTOR = 0x0 ;
 // #endif
    
  SystemInit();
     
  /*ENABLE AND SET UP THE BLUETOOTH UART WITH RX INTERRUPT ON*/
    //#if defined(BOARD_TOPASM369)
      //  SIO_Configuration(UART_BT_SSP);
      //SIO_ChInit(UART_BT_SSP);
      //NVIC_ClearPendingIRQ(UART_BT_SSP_TXINT);
      //NVIC_ClearPendingIRQ(UART_BT_SSP_RXINT);
      //#elif defined(BOARD_TOPASM369_BT)
      //FUART_GPIOConfig();         /* Congigure GPIO for FUART4 */
      //FUART_ChInit();             /* Initialize FUART4 */
      //FUART_Enable(FUART4);
      //FUART_DisableFIFO(FUART4);
      //NVIC_EnableIRQ(INTUART4_IRQn);
      //FUART_SetINTMask(FUART4, 0x10);//enable receive interrupt mask
      //#endif
  
  //pvTask = app_BT_SPP_Initiator_DEMO;

  //if(pdPASS != xTaskCreate(pvTask, NULL, stackSize, (void*)0, 0, NULL)){
   // while(1){};//endless loop
  //}
  //vTaskStartScheduler();

 // while(1);

  /*NOW START THE BLUETOOTH TASK*/

}
#endif
volatile uint8_t deviceNo; //No. of remote device to be connected to.
volatile uint8_t max_Number_of_Reports;//  specifies maximum number of remote devices to be found  
uint8_t remoteDevCount;//contains number of found remote  devices
static uint32_t err;//error code
/********************************************************************************
 Function		app_BT_SPP_DEMO(void* pvParameters)
 Argumets		:pvParameters
 Returns		:non
 Explanation	:
*********************************************************************************/
void app_BT_SPP_Initiator_DEMO(void)
{  
  uint32_t queueRETURN;
  uint32_t loop;

  /*THIS IS JUST RESETTING THE BLUETOOTH MODULE WITH THE RESET PIN*/
      // #if defined(BOARD_TOPASM369_BT)
        /*RESET Chiron*/
      // GPIO_SetOpenDrain(GPIO_PD, GPIO_BIT_7, ENABLE);//set PD7 to Open-drain
      // GPIO_WriteDataBit(GPIO_PD, GPIO_BIT_7, 0);//set to low
      //// GPIO_SetOutputEnableReg(GPIO_PD, GPIO_BIT_7, ENABLE);//
      //GPIO_SetInputEnableReg(GPIO_PD, GPIO_BIT_7, DISABLE);//
      //for(loop=0; loop< 40000;loop++){
      //// }
      //GPIO_WriteDataBit(GPIO_PD, GPIO_BIT_7, 1);//set to high
      // for(loop=0; loop< 40000;loop++){
      // }
        /*RESET Chiron*/
      //#endif
  
  /*THIS STARTS THE QUEUE FOR BLUETOOTH*/
      /*Initiate OS resources for BT SPP driver*/
      //if(BT_os_init() != API_SUCCESS){
        //  while(1){};//endless loop
     // }
 

  init_bluetooth();  /*inits the uart, and reset line for the bluetooth*/



  /*Switch Chiron to TCU Compete mode*/
  err = BT_hci_init((uint8_t *)(&BD_ADDR), (uint8_t *)&Device_Name);
  if(err != API_SUCCESS){
    while(1){};//endless loop
    }
     
  deviceNo = 0;
  max_Number_of_Reports = 10;
  /*Search for inquiring devices */
  err = BT_spp_discover_remote_device(max_Number_of_Reports, &bt_remote_device[0] ,&remoteDevCount);
  if(err != API_SUCCESS){
    while(1){};//endless loop
  }     

  /*Discover services of device indicated by deviceNo*/
  /*deviceNo is used to select one of devices dicovered by routine "BT_spp_discover_remote_device()"*/
  err = BT_spp_discover_remote_service(&bt_remote_device[deviceNo], &bt_service_information);
  if(err != API_SUCCESS){
    //while(1){};//endless loop
  } 
  if(bt_service_information.Service_Type != PROFILE_INDICATOR_SPP_B_PARTY){
    //while(1){};//endless loop
  }
  
  /*Initiate SPP connection*/
  err = BT_spp_connect_remote_device(&bt_remote_device[deviceNo], &bt_service_information);
  if(err != API_SUCCESS){
    while(1){};//endless loop
  }          

  /*Send string "! HELLO !"*/
  if (tcu_event.eventType == TCU_SPP_CONNECT_EVENT){
    BT_spp_send("! HELLO !", 9);
  }
  
  /*run demo application*/
  while(1)
  {
   // queueRETURN = ReceiveEvent( btQueueEVENT, &ul_BT_SPP_rcvValue, (portMAX_DELAY) );
    while(DATA_FROM_BLUETOOTH_UART == 0)  /*we wait for data from uart to process*/
    {
    }



   // if(queueRETURN != pdPASS)
    //{
     // queueRETURN = errQUEUE_EMPTY;
      //write code for error
    //}

  if(TCU_BT_SPP == tcu_event.Service_ID){
    if(TCU_NO_EVENT != tcu_event.eventType){
      /*Process tcu_event*/
      switch (tcu_event.eventType){
        
        /*SPP RECEIVED EVENT*/ 
        case TCU_SPP_DATA_RECEIVE_EVENT:
          BT_spp_send((uint8_t*)&cSPP_DATA_RECEIVE_buff[0], tcu_spp_data_receive_event.Length_of_Data);          
          break;
          
        /*SPP DISCONNECT EVENT*/          
        case TCU_SPP_DISCONNECT_EVENT:        
          err = BT_spp_connect_remote_device(&bt_remote_device[deviceNo], &bt_service_information);
          if(err != API_SUCCESS){
            while(1){};//endless loop 
          }           
          break;
          
        /*SPP CONNECT EVENT*/ 
        case TCU_SPP_CONNECT_EVENT:          
          break;
          
        /*SPP SEND EVENT*/           
        case TCU_SPP_DATA_SEND_EVENT:
          break;
          
        default:
        break;      
      }            
    }
    tcu_event.eventType = TCU_NO_EVENT;//clear event
    }
    
  }      
}    
/****************************************************************************/


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
/*eof*/
