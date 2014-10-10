/*
@************************ CYC_IO_MOTS_Config.c ******************************************

$MODULE IDENT		:  IO / MOTS	$
$DESCRIPTION		: 	This file contains the functions to configure the motion sensor MPU-9250

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
#include "CYC_Config.h"
#include "..\SYS\CYC_SYS_Common.h"
#include "..\SYS\CYC_SYS_TargetConfig.h"
#include "CYC_ERROR_CODES.h"
#include "CYC_IO_MOTS.h"
#include "..\SYS\msp430_interrupt.h"
#include "eMPL\inv_mpu.h"
#include "eMPL\inv_mpu_dmp_motion_driver.h"
#include <string.h>

/* MODULE EXTERNAL DATA DEFINITIONS        *ddddddd*/

/* MODULE INTERNAL CONSTANT DEFINITIONS    *ccccccc*/

/* MODULE INTERNAL TYPE DEFINITIONS        *ttttttt*/
struct hal_s {
    unsigned char sensors;
    unsigned char dmp_on;
    unsigned char wait_for_tap;
    volatile unsigned char new_gyro;
    unsigned short report;
    unsigned short dmp_features;
    unsigned char motion_int_mode;
};



/* MODULE INTERNAL MACRO DEFINITIONS       *mmmmmmm*/
/* Data requested by client. */
#define PRINT_ACCEL     (0x01)
#define PRINT_GYRO      (0x02)
#define PRINT_QUAT      (0x04)

#define ACCEL_ON        (0x01)
#define GYRO_ON         (0x02)

#define MOTION          (0)
#define NO_MOTION       (1)

/* Starting sampling rate. */
#define DEFAULT_MPU_HZ  (100)

#define FLASH_SIZE      (512)
#define FLASH_MEM_START ((void*)0x1800)

/* MODULE INTERNAL FUNCTION PROTOTYPES     *fffffff*/
static inline unsigned short inv_row_2_scale(const signed char *row);
static inline unsigned short inv_orientation_matrix_to_scalar(const signed char *mtx);
//static void setup_gyro(void);
static void tap_cb(unsigned char direction, unsigned char count);
static void android_orient_cb(unsigned char orientation);
static void gyro_data_ready_cb(void);

/* MODULE INTERNAL DATA DEFINITIONS        *ddddddd*/
static struct hal_s hal = {0};

/* The sensors can be mounted onto the board in any orientation. The mounting
 * matrix seen below tells the MPL how to rotate the raw data from thei
 * driver(s).
 * TODO: The following matrices refer to the configuration on an internal test
 * board at Invensense. If needed, please modify the matrices to match the
 * chip-to-body matrix for your particular set up.
 */
static signed char gyro_orientation[9] = {-1, 0, 0,
                                           0,-1, 0,
                                           0, 0, 1};

/* EXPORTED (GLOBAL or External) FUNCTIONS *ggggggg*/

/*
@@********************* CYC_IO_MOTS_Init ***************************************
 *  Function	     :
 *  Description 	 :
 *  Input parameters :
 *  Output parameters:
 *  Return      	 :
 *  Note         	 :
 ******************************************************************************
 */
STATUS CYC_IO_MOTS_Init()
{
	STATUS	lu32Status=SUCCESS;
    unsigned char accel_fsr;
    unsigned short gyro_rate, gyro_fsr;
    struct int_param_s int_param;

    //	Enable the interrupt pin from MPU-9250
    msp430_int_init();

    /* Set up gyro.
     * Every function preceded by mpu_ is a driver function and can be found
     * in inv_mpu.h.
     */
    int_param.cb = gyro_data_ready_cb;


#if defined TARGET_CYCLOPS_GAME | defined REMOTE_V1_2
    //	PORT 2, pin number 7 is where interrupt signal is connected. INT_PIN_P27
    int_param.pin = INT_PIN_P17;
#endif

    //int_param.lp_exit = INT_EXIT_LPM0;
    int_param.lp_exit = INT_EXIT_NONE;
    int_param.active_low = 1;

	//	Initialize MPU9250 with default settings
	lu32Status = mpu_init(&int_param);
	if(lu32Status)
	{
		return CYC_IO_MOTS_ERRORS;
	}

    /* Get/set hardware configuration. Start gyro. */
    //	Wake up all sensors
    mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL);

    //	Push both gyro and accel data into the FIFO
    mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL);

    //	Set default sampling rate
    mpu_set_sample_rate(DEFAULT_MPU_HZ);

    //	Read back configuration in case it was set improperly
    mpu_get_sample_rate(&gyro_rate);
    mpu_get_gyro_fsr(&gyro_fsr);
    mpu_get_accel_fsr(&accel_fsr);

    //	Initialize HAL state variables
    memset(&hal, 0, sizeof(hal));
    hal.sensors = ACCEL_ON | GYRO_ON;
    hal.report = PRINT_QUAT;

    /*------------------------CONFIGURE THE DMP ON CHIP------------------------------------ */
    //	Load the firmware onto DMP the image provided in inv_mpu_dmp_motion_driver.c
    dmp_load_motion_driver_firmware();
    //	Set the orientation
    dmp_set_orientation(
        inv_orientation_matrix_to_scalar(gyro_orientation));
    //	Register for tap call back
    dmp_register_tap_cb(tap_cb);
    //
    dmp_register_android_orient_cb(android_orient_cb);

    /*
     * Known Bug -
     * DMP when enabled will sample sensor data at 200Hz and output to FIFO at the rate
     * specified in the dmp_set_fifo_rate API. The DMP will then sent an interrupt once
     * a sample has been put into the FIFO. Therefore if the dmp_set_fifo_rate is at 25Hz
     * there will be a 25Hz interrupt from the MPU device.
     *
     * There is a known issue in which if you do not enable DMP_FEATURE_TAP
     * then the interrupts will be at 200Hz even if fifo rate
     * is set at a different rate. To avoid this issue include the DMP_FEATURE_TAP
     */
    hal.dmp_features = DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP |
        DMP_FEATURE_ANDROID_ORIENT | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO |
        DMP_FEATURE_GYRO_CAL;

    //	Enable the DMP features
    dmp_enable_feature(hal.dmp_features);
    //	Set FIFO rate
    dmp_set_fifo_rate(DEFAULT_MPU_HZ);
    //	Turn on DMP
    mpu_set_dmp_state(1);
    hal.dmp_on = 1;

    __enable_interrupt();

    return SUCCESS;
}

/*
@@********************* CYC_IO_MOTS_Init ***************************************
 *  Function	     :
 *  Description 	 :
 *  Input parameters :
 *  Output parameters:
 *  Return      	 :
 *  Note         	 :
 ******************************************************************************
 */
STATUS CYC_IO_MOTS_GetQuaternionData(INT32 *rpu32QuatData)
{

	unsigned long sensor_timestamp;

	while(1)
	{

		//	If interrupt mode is desired, wait until the data is ready
        if (hal.motion_int_mode)
        {
            /* Enable motion interrupt. */
			mpu_lp_motion_interrupt(500, 1, 5);
            hal.new_gyro = 0;
            /* Wait for the MPU interrupt. */
            while (!hal.new_gyro)
                __bis_SR_register(LPM0_bits + GIE);
            /* Restore the previous sensor configuration. */
            mpu_lp_motion_interrupt(0, 0, 0);
            hal.motion_int_mode = 0;
        }

        if (!hal.sensors || !hal.new_gyro)
        {
            /* Put the MSP430 to sleep until a timer interrupt or data ready
             * interrupt is detected.
             */
            __bis_SR_register(LPM0_bits + GIE);
            continue;
        }

        //	If data is available and DMP is on, read the values

        if (hal.new_gyro && hal.dmp_on)

        if (hal.dmp_on)
        {
            short gyro[3], accel[3], sensors;
            unsigned char more;
            long quat[4];
            /* This function gets new data from the FIFO when the DMP is in
             * use. The FIFO can contain any combination of gyro, accel,
             * quaternion, and gesture data. The sensors parameter tells the
             * caller which data fields were actually populated with new data.
             * For example, if sensors == (INV_XYZ_GYRO | INV_WXYZ_QUAT), then
             * the FIFO isn't being filled with accel data.
             * The driver parses the gesture data to determine if a gesture
             * event has occurred; on an event, the application will be notified
             * via a callback (assuming that a callback function was properly
             * registered). The more parameter is non-zero if there are
             * leftover packets in the FIFO.
             */
            dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors,&more);
            if (!more)
                hal.new_gyro = 0;
            /* Gyro and accel data are written to the FIFO by the DMP in chip
             * frame and hardware units. This behavior is convenient because it
             * keeps the gyro and accel outputs of dmp_read_fifo and
             * mpu_read_fifo consistent.
             */


            if (sensors & INV_WXYZ_QUAT && hal.report & PRINT_QUAT)
            {
            	//	Copy quaternion data into the passed buffer
            	*(rpu32QuatData) = quat[0];		//	X
            	rpu32QuatData++;
            	*(rpu32QuatData) = quat[1];		//	Y
            	rpu32QuatData++;
            	*(rpu32QuatData) = quat[2];		//	Z
            	rpu32QuatData++;
            	*(rpu32QuatData) = quat[3];		//	W
            	rpu32QuatData++;

            	//	Break out of the while loop
            	break;
            }

#if 0
            if (sensors & INV_XYZ_GYRO && hal.report & PRINT_GYRO)
                send_packet(PACKET_TYPE_GYRO, gyro);
            if (sensors & INV_XYZ_ACCEL && hal.report & PRINT_ACCEL)
                send_packet(PACKET_TYPE_ACCEL, accel);
            /* Unlike gyro and accel, quaternions are written to the FIFO in
             * the body frame, q30. The orientation is set by the scalar passed
             * to dmp_set_orientation during initialization.
             */
            if (sensors & INV_WXYZ_QUAT && hal.report & PRINT_QUAT)
                send_packet(PACKET_TYPE_QUAT, quat);
#endif
        }
        else if (hal.new_gyro)
        {
            short gyro[3], accel[3];
            unsigned char sensors, more;
            /* This function gets new data from the FIFO. The FIFO can contain
             * gyro, accel, both, or neither. The sensors parameter tells the
             * caller which data fields were actually populated with new data.
             * For example, if sensors == INV_XYZ_GYRO, then the FIFO isn't
             * being filled with accel data. The more parameter is non-zero if
             * there are leftover packets in the FIFO.
             */
            mpu_read_fifo(gyro, accel, &sensor_timestamp, &sensors, &more);
            if (!more)
                hal.new_gyro = 0;
#if 0
            if (sensors & INV_XYZ_GYRO && hal.report & PRINT_GYRO)
                send_packet(PACKET_TYPE_GYRO, gyro);
            if (sensors & INV_XYZ_ACCEL && hal.report & PRINT_ACCEL)
                send_packet(PACKET_TYPE_ACCEL, accel);
#endif
        }

	}

	return SUCCESS;
}

/* MODULE INTERNAL FUNCTIONS               *fffffff*/
/* These next two functions converts the orientation matrix (see
 * gyro_orientation) to a scalar representation for use by the DMP.
 * NOTE: These functions are borrowed from Invensense's MPL.
 */
static inline unsigned short inv_row_2_scale(const signed char *row)
{
    unsigned short b;

    if (row[0] > 0)
        b = 0;
    else if (row[0] < 0)
        b = 4;
    else if (row[1] > 0)
        b = 1;
    else if (row[1] < 0)
        b = 5;
    else if (row[2] > 0)
        b = 2;
    else if (row[2] < 0)
        b = 6;
    else
        b = 7;      // error
    return b;
}

static inline unsigned short inv_orientation_matrix_to_scalar(
    const signed char *mtx)
{
    unsigned short scalar;

    /*
       XYZ  010_001_000 Identity Matrix
       XZY  001_010_000
       YXZ  010_000_001
       YZX  000_010_001
       ZXY  001_000_010
       ZYX  000_001_010
     */

    scalar = inv_row_2_scale(mtx);
    scalar |= inv_row_2_scale(mtx + 3) << 3;
    scalar |= inv_row_2_scale(mtx + 6) << 6;


    return scalar;
}

/* Handle sensor on/off combinations. */
#if 0
static void setup_gyro(void)
{
    unsigned char mask = 0;
    if (hal.sensors & ACCEL_ON)
        mask |= INV_XYZ_ACCEL;
    if (hal.sensors & GYRO_ON)
        mask |= INV_XYZ_GYRO;
    /* If you need a power transition, this function should be called with a
     * mask of the sensors still enabled. The driver turns off any sensors
     * excluded from this mask.
     */
    mpu_set_sensors(mask);
    if (!hal.dmp_on)
        mpu_configure_fifo(mask);
}
#endif

static void tap_cb(unsigned char direction, unsigned char count)
{
    __IO char data[2];
    data[0] = (char)direction;
    data[1] = (char)count;
    //send_packet(PACKET_TYPE_TAP, data);
}

static void android_orient_cb(unsigned char orientation)
{
    //send_packet(PACKET_TYPE_ANDROID_ORIENT, &orientation);
}

/* Every time new gyro data is available, this function is called in an
 * ISR context. In this example, it sets a flag protecting the FIFO read
 * function.
 */
static void gyro_data_ready_cb(void)
{
    hal.new_gyro = 1;
}


/*-----------------------------EOF-------------------------------------------*/





    
    
