/*******************************************************************************
* File Name: BUTTON_TILT_EN.h  
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

#if !defined(CY_PINS_BUTTON_TILT_EN_ALIASES_H) /* Pins BUTTON_TILT_EN_ALIASES_H */
#define CY_PINS_BUTTON_TILT_EN_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define BUTTON_TILT_EN_0			(BUTTON_TILT_EN__0__PC)
#define BUTTON_TILT_EN_0_PS		(BUTTON_TILT_EN__0__PS)
#define BUTTON_TILT_EN_0_PC		(BUTTON_TILT_EN__0__PC)
#define BUTTON_TILT_EN_0_DR		(BUTTON_TILT_EN__0__DR)
#define BUTTON_TILT_EN_0_SHIFT	(BUTTON_TILT_EN__0__SHIFT)
#define BUTTON_TILT_EN_0_INTR	((uint16)((uint16)0x0003u << (BUTTON_TILT_EN__0__SHIFT*2u)))

#define BUTTON_TILT_EN_INTR_ALL	 ((uint16)(BUTTON_TILT_EN_0_INTR))


#endif /* End Pins BUTTON_TILT_EN_ALIASES_H */


/* [] END OF FILE */
