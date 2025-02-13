/*******************************************************************************
* File Name: DIR_BACK_LEFT.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_DIR_BACK_LEFT_ALIASES_H) /* Pins DIR_BACK_LEFT_ALIASES_H */
#define CY_PINS_DIR_BACK_LEFT_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define DIR_BACK_LEFT_0			(DIR_BACK_LEFT__0__PC)
#define DIR_BACK_LEFT_0_PS		(DIR_BACK_LEFT__0__PS)
#define DIR_BACK_LEFT_0_PC		(DIR_BACK_LEFT__0__PC)
#define DIR_BACK_LEFT_0_DR		(DIR_BACK_LEFT__0__DR)
#define DIR_BACK_LEFT_0_SHIFT	(DIR_BACK_LEFT__0__SHIFT)
#define DIR_BACK_LEFT_0_INTR	((uint16)((uint16)0x0003u << (DIR_BACK_LEFT__0__SHIFT*2u)))

#define DIR_BACK_LEFT_INTR_ALL	 ((uint16)(DIR_BACK_LEFT_0_INTR))


#endif /* End Pins DIR_BACK_LEFT_ALIASES_H */


/* [] END OF FILE */
