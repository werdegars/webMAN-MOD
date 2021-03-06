/***********************************************************************/
/*                                                                     */
/*  FILE        :resetprg.c                                            */
/*  DATE        :Tue, Nov 08, 2016                                     */
/*  DESCRIPTION :Reset Program                                         */
/*  CPU TYPE    :RX220                                                 */
/*                                                                     */
/*  This file is generated by Renesas Project Generator (Ver.4.53).    */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
/*********************************************************************
*
* Device     : RX/RX200
*
* File Name  : resetprg.c
*
* Abstract   : Reset Program.
*
* History    : 1.00  (2010-12-17)
*            : 1.10  (2011-02-21)
*            : 1.11  (2011-06-20)
*
* NOTE       : THIS IS A TYPICAL EXAMPLE.
*
* Copyright (C) 2010 (2011) Renesas Electronics Corporation.
* and Renesas Solutions Corp.
*
*********************************************************************/

#include	<machine.h>
#include	<_h_c_lib.h>
//#include	<stddef.h>					// Remove the comment when you use errno
//#include 	<stdlib.h>					// Remove the comment when you use rand()
#include	"typedefine.h"		// Define Types
#include	"iodefine.h"
#include	"stacksct.h"		// Stack Sizes (Interrupt and User)

#ifdef __cplusplus
extern "C" {
#endif
void PowerON_Reset_PC(void);
void main(void);
#ifdef __cplusplus
}
#endif

//#ifdef __cplusplus				// Use SIM I/O
//extern "C" {
//#endif
//extern void _INIT_IOLIB(void);
//extern void _CLOSEALL(void);
//#ifdef __cplusplus
//}
//#endif

//extern void srand(_UINT);		// Remove the comment when you use rand()
//extern _SBYTE *_s1ptr;				// Remove the comment when you use strtok()
		
//#ifdef __cplusplus				// Use Hardware Setup
//extern "C" {
//#endif
//extern void HardwareSetup(void);
//#ifdef __cplusplus
//}
//#endif
	
//#ifdef __cplusplus			// Remove the comment when you use global class object
//extern "C" {					// Sections C$INIT and C$END will be generated
//#endif
//extern void _CALL_INIT(void);
//extern void _CALL_END(void);
//#ifdef __cplusplus
//}
//#endif

#pragma section ResetPRG		// output PowerON_Reset to PResetPRG section

#pragma entry PowerON_Reset_PC

void PowerON_Reset_PC(void)
{ 
	int n;


	set_intb(__sectop("C$VECT"));

	/* Initialize clock system */

	SYSTEM.PRCR.WORD = 0xA503;	/* Unlock clock control / module stop registers */

	SYSTEM.SCKCR3.WORD = 0x0000;	/* Select LOCO (CKSEL=0) */
	SYSTEM.HOCOCR.BYTE = 0x01;		/* Stop HOCO (HCSTP=1) */
	SYSTEM.HOCOCR2.BYTE = 0x00;		/* Set HOCO freq. 32MHz (HCFREQ=0) */
	SYSTEM.HOCOCR.BYTE = 0x00;		/* Start HOCO (HCSTP=0) */
	for (n = 0; n < 10; n++) SYSTEM.HOCOCR.BYTE;	/* Delay */
	SYSTEM.SCKCR3.WORD = 0x0100;	/* Select HOCO (CKSEL=1) */

	SYSTEM.SCKCR.LONG = 0x00000000;	/* Set system clock dividers (FCK=0, ICK=0, BCK=0, PCLKB=0, PCKD=0) */

	SYSTEM.PRCR.WORD = 0xA500;	/* Lock clock contrl / module stop registers */


	_INITSCT();						// Initialize RAM sections

//	_INIT_IOLIB();					// Use SIM I/O

//	errno=0;						// Remove the comment when you use errno
//	srand((_UINT)1);					// Remove the comment when you use rand()
//	_s1ptr=NULL;					// Remove the comment when you use strtok()

//	HardwareSetup();				// Use Hardware Setup
    nop();

//	_CALL_INIT();					// Remove the comment when you use global class object

	set_psw(0x00010000);			// Initialize PSW (U=0, I=1)
//	chg_pmusr();					// Change PSW PMbit (SuperVisor->User, ISP->USP)

	main();

//	_CLOSEALL();					// Use SIM I/O
	
//	_CALL_END();					// Remove the comment when you use global class object

	brk();
}
