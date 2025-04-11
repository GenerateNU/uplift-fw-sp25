/*******************************************************************************
* File Name: e_PM.c
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

#include "e.h"

static e_backupStruct e_backup;


/*******************************************************************************
* Function Name: e_SaveConfig
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
*  e_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void e_SaveConfig(void) 
{

    #if(!e_UsingFixedFunction)
        #if(!e_PWMModeIsCenterAligned)
            e_backup.PWMPeriod = e_ReadPeriod();
        #endif /* (!e_PWMModeIsCenterAligned) */
        e_backup.PWMUdb = e_ReadCounter();
        #if (e_UseStatus)
            e_backup.InterruptMaskValue = e_STATUS_MASK;
        #endif /* (e_UseStatus) */

        #if(e_DeadBandMode == e__B_PWM__DBM_256_CLOCKS || \
            e_DeadBandMode == e__B_PWM__DBM_2_4_CLOCKS)
            e_backup.PWMdeadBandValue = e_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(e_KillModeMinTime)
             e_backup.PWMKillCounterPeriod = e_ReadKillTime();
        #endif /* (e_KillModeMinTime) */

        #if(e_UseControl)
            e_backup.PWMControlRegister = e_ReadControlRegister();
        #endif /* (e_UseControl) */
    #endif  /* (!e_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: e_RestoreConfig
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
*  e_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void e_RestoreConfig(void) 
{
        #if(!e_UsingFixedFunction)
            #if(!e_PWMModeIsCenterAligned)
                e_WritePeriod(e_backup.PWMPeriod);
            #endif /* (!e_PWMModeIsCenterAligned) */

            e_WriteCounter(e_backup.PWMUdb);

            #if (e_UseStatus)
                e_STATUS_MASK = e_backup.InterruptMaskValue;
            #endif /* (e_UseStatus) */

            #if(e_DeadBandMode == e__B_PWM__DBM_256_CLOCKS || \
                e_DeadBandMode == e__B_PWM__DBM_2_4_CLOCKS)
                e_WriteDeadTime(e_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(e_KillModeMinTime)
                e_WriteKillTime(e_backup.PWMKillCounterPeriod);
            #endif /* (e_KillModeMinTime) */

            #if(e_UseControl)
                e_WriteControlRegister(e_backup.PWMControlRegister);
            #endif /* (e_UseControl) */
        #endif  /* (!e_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: e_Sleep
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
*  e_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void e_Sleep(void) 
{
    #if(e_UseControl)
        if(e_CTRL_ENABLE == (e_CONTROL & e_CTRL_ENABLE))
        {
            /*Component is enabled */
            e_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            e_backup.PWMEnableState = 0u;
        }
    #endif /* (e_UseControl) */

    /* Stop component */
    e_Stop();

    /* Save registers configuration */
    e_SaveConfig();
}


/*******************************************************************************
* Function Name: e_Wakeup
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
*  e_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void e_Wakeup(void) 
{
     /* Restore registers values */
    e_RestoreConfig();

    if(e_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        e_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
