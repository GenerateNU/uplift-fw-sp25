/*******************************************************************************
* File Name: BUZZER_PWM_0_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "BUZZER_PWM_0.h"

static BUZZER_PWM_0_backupStruct BUZZER_PWM_0_backup;


/*******************************************************************************
* Function Name: BUZZER_PWM_0_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  BUZZER_PWM_0_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void BUZZER_PWM_0_SaveConfig(void) 
{

    #if(!BUZZER_PWM_0_UsingFixedFunction)
        #if(!BUZZER_PWM_0_PWMModeIsCenterAligned)
            BUZZER_PWM_0_backup.PWMPeriod = BUZZER_PWM_0_ReadPeriod();
        #endif /* (!BUZZER_PWM_0_PWMModeIsCenterAligned) */
        BUZZER_PWM_0_backup.PWMUdb = BUZZER_PWM_0_ReadCounter();
        #if (BUZZER_PWM_0_UseStatus)
            BUZZER_PWM_0_backup.InterruptMaskValue = BUZZER_PWM_0_STATUS_MASK;
        #endif /* (BUZZER_PWM_0_UseStatus) */

        #if(BUZZER_PWM_0_DeadBandMode == BUZZER_PWM_0__B_PWM__DBM_256_CLOCKS || \
            BUZZER_PWM_0_DeadBandMode == BUZZER_PWM_0__B_PWM__DBM_2_4_CLOCKS)
            BUZZER_PWM_0_backup.PWMdeadBandValue = BUZZER_PWM_0_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(BUZZER_PWM_0_KillModeMinTime)
             BUZZER_PWM_0_backup.PWMKillCounterPeriod = BUZZER_PWM_0_ReadKillTime();
        #endif /* (BUZZER_PWM_0_KillModeMinTime) */

        #if(BUZZER_PWM_0_UseControl)
            BUZZER_PWM_0_backup.PWMControlRegister = BUZZER_PWM_0_ReadControlRegister();
        #endif /* (BUZZER_PWM_0_UseControl) */
    #endif  /* (!BUZZER_PWM_0_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: BUZZER_PWM_0_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  BUZZER_PWM_0_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void BUZZER_PWM_0_RestoreConfig(void) 
{
        #if(!BUZZER_PWM_0_UsingFixedFunction)
            #if(!BUZZER_PWM_0_PWMModeIsCenterAligned)
                BUZZER_PWM_0_WritePeriod(BUZZER_PWM_0_backup.PWMPeriod);
            #endif /* (!BUZZER_PWM_0_PWMModeIsCenterAligned) */

            BUZZER_PWM_0_WriteCounter(BUZZER_PWM_0_backup.PWMUdb);

            #if (BUZZER_PWM_0_UseStatus)
                BUZZER_PWM_0_STATUS_MASK = BUZZER_PWM_0_backup.InterruptMaskValue;
            #endif /* (BUZZER_PWM_0_UseStatus) */

            #if(BUZZER_PWM_0_DeadBandMode == BUZZER_PWM_0__B_PWM__DBM_256_CLOCKS || \
                BUZZER_PWM_0_DeadBandMode == BUZZER_PWM_0__B_PWM__DBM_2_4_CLOCKS)
                BUZZER_PWM_0_WriteDeadTime(BUZZER_PWM_0_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(BUZZER_PWM_0_KillModeMinTime)
                BUZZER_PWM_0_WriteKillTime(BUZZER_PWM_0_backup.PWMKillCounterPeriod);
            #endif /* (BUZZER_PWM_0_KillModeMinTime) */

            #if(BUZZER_PWM_0_UseControl)
                BUZZER_PWM_0_WriteControlRegister(BUZZER_PWM_0_backup.PWMControlRegister);
            #endif /* (BUZZER_PWM_0_UseControl) */
        #endif  /* (!BUZZER_PWM_0_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: BUZZER_PWM_0_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  BUZZER_PWM_0_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void BUZZER_PWM_0_Sleep(void) 
{
    #if(BUZZER_PWM_0_UseControl)
        if(BUZZER_PWM_0_CTRL_ENABLE == (BUZZER_PWM_0_CONTROL & BUZZER_PWM_0_CTRL_ENABLE))
        {
            /*Component is enabled */
            BUZZER_PWM_0_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            BUZZER_PWM_0_backup.PWMEnableState = 0u;
        }
    #endif /* (BUZZER_PWM_0_UseControl) */

    /* Stop component */
    BUZZER_PWM_0_Stop();

    /* Save registers configuration */
    BUZZER_PWM_0_SaveConfig();
}


/*******************************************************************************
* Function Name: BUZZER_PWM_0_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  BUZZER_PWM_0_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void BUZZER_PWM_0_Wakeup(void) 
{
     /* Restore registers values */
    BUZZER_PWM_0_RestoreConfig();

    if(BUZZER_PWM_0_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        BUZZER_PWM_0_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
