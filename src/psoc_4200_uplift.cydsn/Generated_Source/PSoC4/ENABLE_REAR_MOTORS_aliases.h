/*******************************************************************************
* File Name: ENABLE_REAR_MOTORS.h  
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

#if !defined(CY_PINS_ENABLE_REAR_MOTORS_ALIASES_H) /* Pins ENABLE_REAR_MOTORS_ALIASES_H */
#define CY_PINS_ENABLE_REAR_MOTORS_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define ENABLE_REAR_MOTORS_0			(ENABLE_REAR_MOTORS__0__PC)
#define ENABLE_REAR_MOTORS_0_PS		(ENABLE_REAR_MOTORS__0__PS)
#define ENABLE_REAR_MOTORS_0_PC		(ENABLE_REAR_MOTORS__0__PC)
#define ENABLE_REAR_MOTORS_0_DR		(ENABLE_REAR_MOTORS__0__DR)
#define ENABLE_REAR_MOTORS_0_SHIFT	(ENABLE_REAR_MOTORS__0__SHIFT)
#define ENABLE_REAR_MOTORS_0_INTR	((uint16)((uint16)0x0003u << (ENABLE_REAR_MOTORS__0__SHIFT*2u)))

#define ENABLE_REAR_MOTORS_INTR_ALL	 ((uint16)(ENABLE_REAR_MOTORS_0_INTR))


#endif /* End Pins ENABLE_REAR_MOTORS_ALIASES_H */


/* [] END OF FILE */
