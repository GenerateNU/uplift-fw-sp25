/*******************************************************************************
* File Name: BUTTON_DIR_DOWN.h  
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

#if !defined(CY_PINS_BUTTON_DIR_DOWN_ALIASES_H) /* Pins BUTTON_DIR_DOWN_ALIASES_H */
#define CY_PINS_BUTTON_DIR_DOWN_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define BUTTON_DIR_DOWN_0			(BUTTON_DIR_DOWN__0__PC)
#define BUTTON_DIR_DOWN_0_PS		(BUTTON_DIR_DOWN__0__PS)
#define BUTTON_DIR_DOWN_0_PC		(BUTTON_DIR_DOWN__0__PC)
#define BUTTON_DIR_DOWN_0_DR		(BUTTON_DIR_DOWN__0__DR)
#define BUTTON_DIR_DOWN_0_SHIFT	(BUTTON_DIR_DOWN__0__SHIFT)
#define BUTTON_DIR_DOWN_0_INTR	((uint16)((uint16)0x0003u << (BUTTON_DIR_DOWN__0__SHIFT*2u)))

#define BUTTON_DIR_DOWN_INTR_ALL	 ((uint16)(BUTTON_DIR_DOWN_0_INTR))


#endif /* End Pins BUTTON_DIR_DOWN_ALIASES_H */


/* [] END OF FILE */
