/*
@************************ CYC_SYS_I2C.h ******************************************

$MODULE IDENT		:  	I2C $
$DESCRIPTION		:	This is the header file for I2C functionality

<BEGIN REVISION>

    $Copyright: CRATUS TECHNOLOGY INC, 2013-14 $
    $Project: CYCLOPS Remote $
    $Revision: 0.1 $
    $Author: Sudhi $
    $Log:  $
    
	Revision 0.1  2014/3/6 
    Creation of the template
    
@********************** <File Name>*****************************************
*/

 /*
NOTES:

*/



/* INCLUDE FILES: */


/* EXPORTED CONSTANT DEFINITIONS            *ccccccccc*/

/* EXPORTED MACRO DEFINITIONS               *mmmmmmmmm*/

/* EXPORTED TYPE DEFINITIONS                *ttttttttt*/

/* EXPORTED FUNCTIONS                       *ggggggggg*/
STATUS CYC_SYS_I2CB1_Enable(void);
STATUS CYC_SYS_I2CB0_Enable(void);
STATUS CYC_SYS_I2CB0_Disable(void);

STATUS CYC_SYS_I2C_Write(	UINT8 ru8SlaveAddress,
							UINT8 ru8RegisterAddress,
							UINT8 ru8Length,
							UINT8 *rpu8Data);

STATUS CYC_SYS_I2C_Read(	UINT8 ru8SlaveAddress,
							UINT8 ru8RegisterAddress,
							UINT8 ru8Length,
							UINT8 *rpu8Data);


/* EXPORTED DATA DEFINITIONS/DECLARATIONS   ddddddd*/

/*-----------------------------EOF-------------------------------------------*/
