/*******************************************************************************
* File Name: e.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_e_H)
#define CY_PWM_e_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 e_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define e_Resolution                     (8u)
#define e_UsingFixedFunction             (0u)
#define e_DeadBandMode                   (0u)
#define e_KillModeMinTime                (0u)
#define e_KillMode                       (0u)
#define e_PWMMode                        (0u)
#define e_PWMModeIsCenterAligned         (0u)
#define e_DeadBandUsed                   (0u)
#define e_DeadBand2_4                    (0u)

#if !defined(e_PWMUDB_genblk8_stsreg__REMOVED)
    #define e_UseStatus                  (1u)
#else
    #define e_UseStatus                  (0u)
#endif /* !defined(e_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(e_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define e_UseControl                 (1u)
#else
    #define e_UseControl                 (0u)
#endif /* !defined(e_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define e_UseOneCompareMode              (1u)
#define e_MinimumKillTime                (1u)
#define e_EnableMode                     (0u)

#define e_CompareMode1SW                 (0u)
#define e_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define e__B_PWM__DISABLED 0
#define e__B_PWM__ASYNCHRONOUS 1
#define e__B_PWM__SINGLECYCLE 2
#define e__B_PWM__LATCHED 3
#define e__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define e__B_PWM__DBMDISABLED 0
#define e__B_PWM__DBM_2_4_CLOCKS 1
#define e__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define e__B_PWM__ONE_OUTPUT 0
#define e__B_PWM__TWO_OUTPUTS 1
#define e__B_PWM__DUAL_EDGE 2
#define e__B_PWM__CENTER_ALIGN 3
#define e__B_PWM__DITHER 5
#define e__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define e__B_PWM__LESS_THAN 1
#define e__B_PWM__LESS_THAN_OR_EQUAL 2
#define e__B_PWM__GREATER_THAN 3
#define e__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define e__B_PWM__EQUAL 0
#define e__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!e_UsingFixedFunction)
        uint8 PWMUdb;               /* PWM Current Counter value  */
        #if(!e_PWMModeIsCenterAligned)
            uint8 PWMPeriod;
        #endif /* (!e_PWMModeIsCenterAligned) */
        #if (e_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (e_UseStatus) */

        /* Backup for Deadband parameters */
        #if(e_DeadBandMode == e__B_PWM__DBM_256_CLOCKS || \
            e_DeadBandMode == e__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(e_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (e_KillModeMinTime) */

        /* Backup control register */
        #if(e_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (e_UseControl) */

    #endif /* (!e_UsingFixedFunction) */

}e_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    e_Start(void) ;
void    e_Stop(void) ;

#if (e_UseStatus || e_UsingFixedFunction)
    void  e_SetInterruptMode(uint8 interruptMode) ;
    uint8 e_ReadStatusRegister(void) ;
#endif /* (e_UseStatus || e_UsingFixedFunction) */

#define e_GetInterruptSource() e_ReadStatusRegister()

#if (e_UseControl)
    uint8 e_ReadControlRegister(void) ;
    void  e_WriteControlRegister(uint8 control)
          ;
#endif /* (e_UseControl) */

#if (e_UseOneCompareMode)
   #if (e_CompareMode1SW)
       void    e_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (e_CompareMode1SW) */
#else
    #if (e_CompareMode1SW)
        void    e_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (e_CompareMode1SW) */
    #if (e_CompareMode2SW)
        void    e_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (e_CompareMode2SW) */
#endif /* (e_UseOneCompareMode) */

#if (!e_UsingFixedFunction)
    uint8   e_ReadCounter(void) ;
    uint8 e_ReadCapture(void) ;

    #if (e_UseStatus)
            void e_ClearFIFO(void) ;
    #endif /* (e_UseStatus) */

    void    e_WriteCounter(uint8 counter)
            ;
#endif /* (!e_UsingFixedFunction) */

void    e_WritePeriod(uint8 period)
        ;
uint8 e_ReadPeriod(void) ;

#if (e_UseOneCompareMode)
    void    e_WriteCompare(uint8 compare)
            ;
    uint8 e_ReadCompare(void) ;
#else
    void    e_WriteCompare1(uint8 compare)
            ;
    uint8 e_ReadCompare1(void) ;
    void    e_WriteCompare2(uint8 compare)
            ;
    uint8 e_ReadCompare2(void) ;
#endif /* (e_UseOneCompareMode) */


#if (e_DeadBandUsed)
    void    e_WriteDeadTime(uint8 deadtime) ;
    uint8   e_ReadDeadTime(void) ;
#endif /* (e_DeadBandUsed) */

#if ( e_KillModeMinTime)
    void e_WriteKillTime(uint8 killtime) ;
    uint8 e_ReadKillTime(void) ;
#endif /* ( e_KillModeMinTime) */

void e_Init(void) ;
void e_Enable(void) ;
void e_Sleep(void) ;
void e_Wakeup(void) ;
void e_SaveConfig(void) ;
void e_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define e_INIT_PERIOD_VALUE          (255u)
#define e_INIT_COMPARE_VALUE1        (25u)
#define e_INIT_COMPARE_VALUE2        (63u)
#define e_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    e_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    e_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    e_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    e_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define e_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  e_CTRL_CMPMODE2_SHIFT)
#define e_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  e_CTRL_CMPMODE1_SHIFT)
#define e_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (e_UsingFixedFunction)
   #define e_PERIOD_LSB              (*(reg16 *) e_PWMHW__PER0)
   #define e_PERIOD_LSB_PTR          ( (reg16 *) e_PWMHW__PER0)
   #define e_COMPARE1_LSB            (*(reg16 *) e_PWMHW__CNT_CMP0)
   #define e_COMPARE1_LSB_PTR        ( (reg16 *) e_PWMHW__CNT_CMP0)
   #define e_COMPARE2_LSB            (0x00u)
   #define e_COMPARE2_LSB_PTR        (0x00u)
   #define e_COUNTER_LSB             (*(reg16 *) e_PWMHW__CNT_CMP0)
   #define e_COUNTER_LSB_PTR         ( (reg16 *) e_PWMHW__CNT_CMP0)
   #define e_CAPTURE_LSB             (*(reg16 *) e_PWMHW__CAP0)
   #define e_CAPTURE_LSB_PTR         ( (reg16 *) e_PWMHW__CAP0)
   #define e_RT1                     (*(reg8 *)  e_PWMHW__RT1)
   #define e_RT1_PTR                 ( (reg8 *)  e_PWMHW__RT1)

#else
   #if (e_Resolution == 8u) /* 8bit - PWM */

       #if(e_PWMModeIsCenterAligned)
           #define e_PERIOD_LSB      (*(reg8 *)  e_PWMUDB_sP8_pwmdp_u0__D1_REG)
           #define e_PERIOD_LSB_PTR  ((reg8 *)   e_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #else
           #define e_PERIOD_LSB      (*(reg8 *)  e_PWMUDB_sP8_pwmdp_u0__F0_REG)
           #define e_PERIOD_LSB_PTR  ((reg8 *)   e_PWMUDB_sP8_pwmdp_u0__F0_REG)
       #endif /* (e_PWMModeIsCenterAligned) */

       #define e_COMPARE1_LSB        (*(reg8 *)  e_PWMUDB_sP8_pwmdp_u0__D0_REG)
       #define e_COMPARE1_LSB_PTR    ((reg8 *)   e_PWMUDB_sP8_pwmdp_u0__D0_REG)
       #define e_COMPARE2_LSB        (*(reg8 *)  e_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #define e_COMPARE2_LSB_PTR    ((reg8 *)   e_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #define e_COUNTERCAP_LSB      (*(reg8 *)  e_PWMUDB_sP8_pwmdp_u0__A1_REG)
       #define e_COUNTERCAP_LSB_PTR  ((reg8 *)   e_PWMUDB_sP8_pwmdp_u0__A1_REG)
       #define e_COUNTER_LSB         (*(reg8 *)  e_PWMUDB_sP8_pwmdp_u0__A0_REG)
       #define e_COUNTER_LSB_PTR     ((reg8 *)   e_PWMUDB_sP8_pwmdp_u0__A0_REG)
       #define e_CAPTURE_LSB         (*(reg8 *)  e_PWMUDB_sP8_pwmdp_u0__F1_REG)
       #define e_CAPTURE_LSB_PTR     ((reg8 *)   e_PWMUDB_sP8_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(e_PWMModeIsCenterAligned)
               #define e_PERIOD_LSB      (*(reg16 *) e_PWMUDB_sP8_pwmdp_u0__D1_REG)
               #define e_PERIOD_LSB_PTR  ((reg16 *)  e_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #else
               #define e_PERIOD_LSB      (*(reg16 *) e_PWMUDB_sP8_pwmdp_u0__F0_REG)
               #define e_PERIOD_LSB_PTR  ((reg16 *)  e_PWMUDB_sP8_pwmdp_u0__F0_REG)
            #endif /* (e_PWMModeIsCenterAligned) */

            #define e_COMPARE1_LSB       (*(reg16 *) e_PWMUDB_sP8_pwmdp_u0__D0_REG)
            #define e_COMPARE1_LSB_PTR   ((reg16 *)  e_PWMUDB_sP8_pwmdp_u0__D0_REG)
            #define e_COMPARE2_LSB       (*(reg16 *) e_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #define e_COMPARE2_LSB_PTR   ((reg16 *)  e_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #define e_COUNTERCAP_LSB     (*(reg16 *) e_PWMUDB_sP8_pwmdp_u0__A1_REG)
            #define e_COUNTERCAP_LSB_PTR ((reg16 *)  e_PWMUDB_sP8_pwmdp_u0__A1_REG)
            #define e_COUNTER_LSB        (*(reg16 *) e_PWMUDB_sP8_pwmdp_u0__A0_REG)
            #define e_COUNTER_LSB_PTR    ((reg16 *)  e_PWMUDB_sP8_pwmdp_u0__A0_REG)
            #define e_CAPTURE_LSB        (*(reg16 *) e_PWMUDB_sP8_pwmdp_u0__F1_REG)
            #define e_CAPTURE_LSB_PTR    ((reg16 *)  e_PWMUDB_sP8_pwmdp_u0__F1_REG)
        #else
            #if(e_PWMModeIsCenterAligned)
               #define e_PERIOD_LSB      (*(reg16 *) e_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
               #define e_PERIOD_LSB_PTR  ((reg16 *)  e_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #else
               #define e_PERIOD_LSB      (*(reg16 *) e_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
               #define e_PERIOD_LSB_PTR  ((reg16 *)  e_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
            #endif /* (e_PWMModeIsCenterAligned) */

            #define e_COMPARE1_LSB       (*(reg16 *) e_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
            #define e_COMPARE1_LSB_PTR   ((reg16 *)  e_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
            #define e_COMPARE2_LSB       (*(reg16 *) e_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #define e_COMPARE2_LSB_PTR   ((reg16 *)  e_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #define e_COUNTERCAP_LSB     (*(reg16 *) e_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
            #define e_COUNTERCAP_LSB_PTR ((reg16 *)  e_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
            #define e_COUNTER_LSB        (*(reg16 *) e_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
            #define e_COUNTER_LSB_PTR    ((reg16 *)  e_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
            #define e_CAPTURE_LSB        (*(reg16 *) e_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
            #define e_CAPTURE_LSB_PTR    ((reg16 *)  e_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define e_AUX_CONTROLDP1          (*(reg8 *)  e_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)
       #define e_AUX_CONTROLDP1_PTR      ((reg8 *)   e_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (e_Resolution == 8) */

   #define e_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  e_PWMUDB_sP8_pwmdp_u0__A1_REG)
   #define e_AUX_CONTROLDP0          (*(reg8 *)  e_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)
   #define e_AUX_CONTROLDP0_PTR      ((reg8 *)   e_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (e_UsingFixedFunction) */

#if(e_KillModeMinTime )
    #define e_KILLMODEMINTIME        (*(reg8 *)  e_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define e_KILLMODEMINTIME_PTR    ((reg8 *)   e_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (e_KillModeMinTime ) */

#if(e_DeadBandMode == e__B_PWM__DBM_256_CLOCKS)
    #define e_DEADBAND_COUNT         (*(reg8 *)  e_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define e_DEADBAND_COUNT_PTR     ((reg8 *)   e_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define e_DEADBAND_LSB_PTR       ((reg8 *)   e_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define e_DEADBAND_LSB           (*(reg8 *)  e_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(e_DeadBandMode == e__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (e_UsingFixedFunction)
        #define e_DEADBAND_COUNT         (*(reg8 *)  e_PWMHW__CFG0)
        #define e_DEADBAND_COUNT_PTR     ((reg8 *)   e_PWMHW__CFG0)
        #define e_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << e_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define e_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define e_DEADBAND_COUNT         (*(reg8 *)  e_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define e_DEADBAND_COUNT_PTR     ((reg8 *)   e_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define e_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << e_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define e_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (e_UsingFixedFunction) */
#endif /* (e_DeadBandMode == e__B_PWM__DBM_256_CLOCKS) */



#if (e_UsingFixedFunction)
    #define e_STATUS                 (*(reg8 *) e_PWMHW__SR0)
    #define e_STATUS_PTR             ((reg8 *) e_PWMHW__SR0)
    #define e_STATUS_MASK            (*(reg8 *) e_PWMHW__SR0)
    #define e_STATUS_MASK_PTR        ((reg8 *) e_PWMHW__SR0)
    #define e_CONTROL                (*(reg8 *) e_PWMHW__CFG0)
    #define e_CONTROL_PTR            ((reg8 *) e_PWMHW__CFG0)
    #define e_CONTROL2               (*(reg8 *) e_PWMHW__CFG1)
    #define e_CONTROL3               (*(reg8 *) e_PWMHW__CFG2)
    #define e_GLOBAL_ENABLE          (*(reg8 *) e_PWMHW__PM_ACT_CFG)
    #define e_GLOBAL_ENABLE_PTR      ( (reg8 *) e_PWMHW__PM_ACT_CFG)
    #define e_GLOBAL_STBY_ENABLE     (*(reg8 *) e_PWMHW__PM_STBY_CFG)
    #define e_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) e_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define e_BLOCK_EN_MASK          (e_PWMHW__PM_ACT_MSK)
    #define e_BLOCK_STBY_EN_MASK     (e_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define e_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define e_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define e_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define e_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define e_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define e_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define e_CTRL_ENABLE            (uint8)((uint8)0x01u << e_CTRL_ENABLE_SHIFT)
    #define e_CTRL_RESET             (uint8)((uint8)0x01u << e_CTRL_RESET_SHIFT)
    #define e_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << e_CTRL_CMPMODE2_SHIFT)
    #define e_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << e_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define e_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define e_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << e_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define e_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define e_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define e_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define e_STATUS_TC_INT_EN_MASK_SHIFT            (e_STATUS_TC_SHIFT - 4u)
    #define e_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define e_STATUS_CMP1_INT_EN_MASK_SHIFT          (e_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define e_STATUS_TC              (uint8)((uint8)0x01u << e_STATUS_TC_SHIFT)
    #define e_STATUS_CMP1            (uint8)((uint8)0x01u << e_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define e_STATUS_TC_INT_EN_MASK              (uint8)((uint8)e_STATUS_TC >> 4u)
    #define e_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)e_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define e_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define e_RT1_MASK              (uint8)((uint8)0x03u << e_RT1_SHIFT)
    #define e_SYNC                  (uint8)((uint8)0x03u << e_RT1_SHIFT)
    #define e_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define e_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << e_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define e_SYNCDSI_EN            (uint8)((uint8)0x0Fu << e_SYNCDSI_SHIFT)


#else
    #define e_STATUS                (*(reg8 *)   e_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define e_STATUS_PTR            ((reg8 *)    e_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define e_STATUS_MASK           (*(reg8 *)   e_PWMUDB_genblk8_stsreg__MASK_REG)
    #define e_STATUS_MASK_PTR       ((reg8 *)    e_PWMUDB_genblk8_stsreg__MASK_REG)
    #define e_STATUS_AUX_CTRL       (*(reg8 *)   e_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define e_CONTROL               (*(reg8 *)   e_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define e_CONTROL_PTR           ((reg8 *)    e_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define e_CTRL_ENABLE_SHIFT      (0x07u)
    #define e_CTRL_RESET_SHIFT       (0x06u)
    #define e_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define e_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define e_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define e_CTRL_ENABLE            (uint8)((uint8)0x01u << e_CTRL_ENABLE_SHIFT)
    #define e_CTRL_RESET             (uint8)((uint8)0x01u << e_CTRL_RESET_SHIFT)
    #define e_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << e_CTRL_CMPMODE2_SHIFT)
    #define e_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << e_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define e_STATUS_KILL_SHIFT          (0x05u)
    #define e_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define e_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define e_STATUS_TC_SHIFT            (0x02u)
    #define e_STATUS_CMP2_SHIFT          (0x01u)
    #define e_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define e_STATUS_KILL_INT_EN_MASK_SHIFT          (e_STATUS_KILL_SHIFT)
    #define e_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (e_STATUS_FIFONEMPTY_SHIFT)
    #define e_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (e_STATUS_FIFOFULL_SHIFT)
    #define e_STATUS_TC_INT_EN_MASK_SHIFT            (e_STATUS_TC_SHIFT)
    #define e_STATUS_CMP2_INT_EN_MASK_SHIFT          (e_STATUS_CMP2_SHIFT)
    #define e_STATUS_CMP1_INT_EN_MASK_SHIFT          (e_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define e_STATUS_KILL            (uint8)((uint8)0x00u << e_STATUS_KILL_SHIFT )
    #define e_STATUS_FIFOFULL        (uint8)((uint8)0x01u << e_STATUS_FIFOFULL_SHIFT)
    #define e_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << e_STATUS_FIFONEMPTY_SHIFT)
    #define e_STATUS_TC              (uint8)((uint8)0x01u << e_STATUS_TC_SHIFT)
    #define e_STATUS_CMP2            (uint8)((uint8)0x01u << e_STATUS_CMP2_SHIFT)
    #define e_STATUS_CMP1            (uint8)((uint8)0x01u << e_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define e_STATUS_KILL_INT_EN_MASK            (e_STATUS_KILL)
    #define e_STATUS_FIFOFULL_INT_EN_MASK        (e_STATUS_FIFOFULL)
    #define e_STATUS_FIFONEMPTY_INT_EN_MASK      (e_STATUS_FIFONEMPTY)
    #define e_STATUS_TC_INT_EN_MASK              (e_STATUS_TC)
    #define e_STATUS_CMP2_INT_EN_MASK            (e_STATUS_CMP2)
    #define e_STATUS_CMP1_INT_EN_MASK            (e_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define e_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define e_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define e_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define e_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define e_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* e_UsingFixedFunction */

#endif  /* CY_PWM_e_H */


/* [] END OF FILE */
