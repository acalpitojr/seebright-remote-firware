/*
@************************ CYC_DataTypes.h ******************************************

$MODULE IDENT		:  	COMMON	$
$DESCRIPTION		: 	This file contains the definition of data types used across the
						project.

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

/* EXPORTED TYPE DEFINITIONS                *ttttttttt*/
/*
 * Standard Definitions:
 * These defines allow for easier porting to other compilers. if porting change
 * these defines to the required values for the chosen compiler.
 */

typedef unsigned char   UINT8;      /*unsigned 8 bit definition */
typedef unsigned short  UINT16;     /*unsigned 16 bit definition*/
typedef unsigned long   UINT32;     /*unsigned 32 bit definition*/
typedef signed char     INT8;       /*signed 8 bit definition */
typedef short           INT16;      /*signed 16 bit definition*/
typedef long int        INT32;      /*signed 32 bit definition*/
typedef void		    VOID;
typedef unsigned long   STATUS;
#define	__IO			volatile

/* EXPORTED CONSTANT DEFINITIONS            *ccccccccc*/

/* EXPORTED MACRO DEFINITIONS               *mmmmmmmmm*/
#define TRUE    		                    1
#define FALSE   	                    	0
#define SUCCESS                             0

/* Macros to access bytes within words and words within longs */
#define LOW_BYTE(x)     ((unsigned char)((x)&0xFF))
#define HIGH_BYTE(x)    ((unsigned char)(((x)>>8)&0xFF))
#define LOW_WORD(x)     ((unsigned short)((x)&0xFFFF))
#define HIGH_WORD(x)    ((unsigned short)(((x)>>16)&0xFFFF))


/* EXPORTED FUNCTIONS                       *ggggggggg*/


/* EXPORTED DATA DEFINITIONS/DECLARATIONS   ddddddd*/

/*-----------------------------EOF-------------------------------------------*/
