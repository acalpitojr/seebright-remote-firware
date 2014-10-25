/*
@************************ CYC_IO_MOTS.h	 ******************************************

$MODULE IDENT		:  	MOTION SENSOR	$
$DESCRIPTION		: 	This file contains the header file relevant to Motion Sensor functionality

<BEGIN REVISION>

    $Copyright: CRATUS TECHNOLOGY INC, 2013-14 $
    $Project: CYCLOPS Remote $
    $Revision: 0.1 $
    $Author: Sudhi $
    $Log:  $
    
	Revision 0.1  2014/3/6 
    Creation of the template
    
@*******************************************************************************
*/



 /*
NOTES:

*/

/* INCLUDE FILES */

/* EXPORTED CONSTANT DEFINITIONS            *ccccccccc*/
#define		MPU9250							//	Motion sensor that is being used

/* EXPORTED MACRO DEFINITIONS               *mmmmmmmmm*/

/* EXPORTED TYPE DEFINITIONS                *ttttttttt*/
typedef struct{
                    uint8_t accel_data[3];
                    uint8_t gyro_data[3];
                    uint8_t mag_data[3];
                    uint32_t quat_data[4];
}mpu_data_STRUCT;
/* EXPORTED FUNCTIONS                       *ggggggggg*/
STATUS CYC_IO_MOTS_Init();
STATUS CYC_IO_MOTS_GetQuaternionData(INT32 *rpu32QuatData);

uint8_t get_accel_data(uint8_t* data_buf);
uint8_t get_gyro_data(uint8_t* data_buf);
uint8_t get_quat_data(uint8_t* data_buf);

mpu_data_STRUCT   get_mpu_data(void);


/* EXPORTED DATA DEFINITIONS/DECLARATIONS   ddddddd*/

/*-----------------------------EOF-------------------------------------------*/






    
    
