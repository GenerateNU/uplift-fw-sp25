/*******************************************************************************
* File Name: CURRENT_SENSE_2_INT.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_CURRENT_SENSE_2_INT_H)
#define CY_ISR_CURRENT_SENSE_2_INT_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void CURRENT_SENSE_2_INT_Start(void);
void CURRENT_SENSE_2_INT_StartEx(cyisraddress address);
void CURRENT_SENSE_2_INT_Stop(void);

CY_ISR_PROTO(CURRENT_SENSE_2_INT_Interrupt);

void CURRENT_SENSE_2_INT_SetVector(cyisraddress address);
cyisraddress CURRENT_SENSE_2_INT_GetVector(void);

void CURRENT_SENSE_2_INT_SetPriority(uint8 priority);
uint8 CURRENT_SENSE_2_INT_GetPriority(void);

void CURRENT_SENSE_2_INT_Enable(void);
uint8 CURRENT_SENSE_2_INT_GetState(void);
void CURRENT_SENSE_2_INT_Disable(void);

void CURRENT_SENSE_2_INT_SetPending(void);
void CURRENT_SENSE_2_INT_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the CURRENT_SENSE_2_INT ISR. */
#define CURRENT_SENSE_2_INT_INTC_VECTOR            ((reg32 *) CURRENT_SENSE_2_INT__INTC_VECT)

/* Address of the CURRENT_SENSE_2_INT ISR priority. */
#define CURRENT_SENSE_2_INT_INTC_PRIOR             ((reg32 *) CURRENT_SENSE_2_INT__INTC_PRIOR_REG)

/* Priority of the CURRENT_SENSE_2_INT interrupt. */
#define CURRENT_SENSE_2_INT_INTC_PRIOR_NUMBER      CURRENT_SENSE_2_INT__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable CURRENT_SENSE_2_INT interrupt. */
#define CURRENT_SENSE_2_INT_INTC_SET_EN            ((reg32 *) CURRENT_SENSE_2_INT__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the CURRENT_SENSE_2_INT interrupt. */
#define CURRENT_SENSE_2_INT_INTC_CLR_EN            ((reg32 *) CURRENT_SENSE_2_INT__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the CURRENT_SENSE_2_INT interrupt state to pending. */
#define CURRENT_SENSE_2_INT_INTC_SET_PD            ((reg32 *) CURRENT_SENSE_2_INT__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the CURRENT_SENSE_2_INT interrupt. */
#define CURRENT_SENSE_2_INT_INTC_CLR_PD            ((reg32 *) CURRENT_SENSE_2_INT__INTC_CLR_PD_REG)



#endif /* CY_ISR_CURRENT_SENSE_2_INT_H */


/* [] END OF FILE */
