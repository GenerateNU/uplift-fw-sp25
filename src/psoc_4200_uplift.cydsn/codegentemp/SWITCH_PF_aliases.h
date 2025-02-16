/*******************************************************************************
* File Name: SWITCH_PF.h  
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

#if !defined(CY_PINS_SWITCH_PF_ALIASES_H) /* Pins SWITCH_PF_ALIASES_H */
#define CY_PINS_SWITCH_PF_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SWITCH_PF_0			(SWITCH_PF__0__PC)
#define SWITCH_PF_0_PS		(SWITCH_PF__0__PS)
#define SWITCH_PF_0_PC		(SWITCH_PF__0__PC)
#define SWITCH_PF_0_DR		(SWITCH_PF__0__DR)
#define SWITCH_PF_0_SHIFT	(SWITCH_PF__0__SHIFT)
#define SWITCH_PF_0_INTR	((uint16)((uint16)0x0003u << (SWITCH_PF__0__SHIFT*2u)))

#define SWITCH_PF_INTR_ALL	 ((uint16)(SWITCH_PF_0_INTR))


#endif /* End Pins SWITCH_PF_ALIASES_H */


/* [] END OF FILE */
