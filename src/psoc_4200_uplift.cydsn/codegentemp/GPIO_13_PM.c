/*******************************************************************************
* File Name: GPIO_13.c  
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
#include "GPIO_13.h"

static GPIO_13_BACKUP_STRUCT  GPIO_13_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: GPIO_13_Sleep
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
*  \snippet GPIO_13_SUT.c usage_GPIO_13_Sleep_Wakeup
*******************************************************************************/
void GPIO_13_Sleep(void)
{
    #if defined(GPIO_13__PC)
        GPIO_13_backup.pcState = GPIO_13_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            GPIO_13_backup.usbState = GPIO_13_CR1_REG;
            GPIO_13_USB_POWER_REG |= GPIO_13_USBIO_ENTER_SLEEP;
            GPIO_13_CR1_REG &= GPIO_13_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(GPIO_13__SIO)
        GPIO_13_backup.sioState = GPIO_13_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        GPIO_13_SIO_REG &= (uint32)(~GPIO_13_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: GPIO_13_Wakeup
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
*  Refer to GPIO_13_Sleep() for an example usage.
*******************************************************************************/
void GPIO_13_Wakeup(void)
{
    #if defined(GPIO_13__PC)
        GPIO_13_PC = GPIO_13_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            GPIO_13_USB_POWER_REG &= GPIO_13_USBIO_EXIT_SLEEP_PH1;
            GPIO_13_CR1_REG = GPIO_13_backup.usbState;
            GPIO_13_USB_POWER_REG &= GPIO_13_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(GPIO_13__SIO)
        GPIO_13_SIO_REG = GPIO_13_backup.sioState;
    #endif
}


/* [] END OF FILE */
