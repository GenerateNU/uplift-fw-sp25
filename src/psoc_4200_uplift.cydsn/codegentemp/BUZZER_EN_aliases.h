/*******************************************************************************
* File Name: BUZZER_EN.h  
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

#if !defined(CY_PINS_BUZZER_EN_ALIASES_H) /* Pins BUZZER_EN_ALIASES_H */
#define CY_PINS_BUZZER_EN_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define BUZZER_EN_0			(BUZZER_EN__0__PC)
#define BUZZER_EN_0_PS		(BUZZER_EN__0__PS)
#define BUZZER_EN_0_PC		(BUZZER_EN__0__PC)
#define BUZZER_EN_0_DR		(BUZZER_EN__0__DR)
#define BUZZER_EN_0_SHIFT	(BUZZER_EN__0__SHIFT)
#define BUZZER_EN_0_INTR	((uint16)((uint16)0x0003u << (BUZZER_EN__0__SHIFT*2u)))

#define BUZZER_EN_INTR_ALL	 ((uint16)(BUZZER_EN_0_INTR))


#endif /* End Pins BUZZER_EN_ALIASES_H */


/* [] END OF FILE */
