/*******************************************************************************
* File Name: PWM_REAR.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "PWM_REAR.h"

static PWM_REAR_BACKUP_STRUCT  PWM_REAR_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: PWM_REAR_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet PWM_REAR_SUT.c usage_PWM_REAR_Sleep_Wakeup
*******************************************************************************/
void PWM_REAR_Sleep(void)
{
    #if defined(PWM_REAR__PC)
        PWM_REAR_backup.pcState = PWM_REAR_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            PWM_REAR_backup.usbState = PWM_REAR_CR1_REG;
            PWM_REAR_USB_POWER_REG |= PWM_REAR_USBIO_ENTER_SLEEP;
            PWM_REAR_CR1_REG &= PWM_REAR_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PWM_REAR__SIO)
        PWM_REAR_backup.sioState = PWM_REAR_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        PWM_REAR_SIO_REG &= (uint32)(~PWM_REAR_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: PWM_REAR_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to PWM_REAR_Sleep() for an example usage.
*******************************************************************************/
void PWM_REAR_Wakeup(void)
{
    #if defined(PWM_REAR__PC)
        PWM_REAR_PC = PWM_REAR_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            PWM_REAR_USB_POWER_REG &= PWM_REAR_USBIO_EXIT_SLEEP_PH1;
            PWM_REAR_CR1_REG = PWM_REAR_backup.usbState;
            PWM_REAR_USB_POWER_REG &= PWM_REAR_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PWM_REAR__SIO)
        PWM_REAR_SIO_REG = PWM_REAR_backup.sioState;
    #endif
}


/* [] END OF FILE */
