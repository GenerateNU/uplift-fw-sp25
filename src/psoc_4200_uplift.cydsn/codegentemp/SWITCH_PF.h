/*******************************************************************************
* File Name: SWITCH_PF.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_SWITCH_PF_H) /* Pins SWITCH_PF_H */
#define CY_PINS_SWITCH_PF_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SWITCH_PF_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} SWITCH_PF_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   SWITCH_PF_Read(void);
void    SWITCH_PF_Write(uint8 value);
uint8   SWITCH_PF_ReadDataReg(void);
#if defined(SWITCH_PF__PC) || (CY_PSOC4_4200L) 
    void    SWITCH_PF_SetDriveMode(uint8 mode);
#endif
void    SWITCH_PF_SetInterruptMode(uint16 position, uint16 mode);
uint8   SWITCH_PF_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void SWITCH_PF_Sleep(void); 
void SWITCH_PF_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(SWITCH_PF__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define SWITCH_PF_DRIVE_MODE_BITS        (3)
    #define SWITCH_PF_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SWITCH_PF_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the SWITCH_PF_SetDriveMode() function.
         *  @{
         */
        #define SWITCH_PF_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define SWITCH_PF_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define SWITCH_PF_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define SWITCH_PF_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define SWITCH_PF_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define SWITCH_PF_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define SWITCH_PF_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define SWITCH_PF_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define SWITCH_PF_MASK               SWITCH_PF__MASK
#define SWITCH_PF_SHIFT              SWITCH_PF__SHIFT
#define SWITCH_PF_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SWITCH_PF_SetInterruptMode() function.
     *  @{
     */
        #define SWITCH_PF_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define SWITCH_PF_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define SWITCH_PF_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define SWITCH_PF_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(SWITCH_PF__SIO)
    #define SWITCH_PF_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(SWITCH_PF__PC) && (CY_PSOC4_4200L)
    #define SWITCH_PF_USBIO_ENABLE               ((uint32)0x80000000u)
    #define SWITCH_PF_USBIO_DISABLE              ((uint32)(~SWITCH_PF_USBIO_ENABLE))
    #define SWITCH_PF_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define SWITCH_PF_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define SWITCH_PF_USBIO_ENTER_SLEEP          ((uint32)((1u << SWITCH_PF_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << SWITCH_PF_USBIO_SUSPEND_DEL_SHIFT)))
    #define SWITCH_PF_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << SWITCH_PF_USBIO_SUSPEND_SHIFT)))
    #define SWITCH_PF_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << SWITCH_PF_USBIO_SUSPEND_DEL_SHIFT)))
    #define SWITCH_PF_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(SWITCH_PF__PC)
    /* Port Configuration */
    #define SWITCH_PF_PC                 (* (reg32 *) SWITCH_PF__PC)
#endif
/* Pin State */
#define SWITCH_PF_PS                     (* (reg32 *) SWITCH_PF__PS)
/* Data Register */
#define SWITCH_PF_DR                     (* (reg32 *) SWITCH_PF__DR)
/* Input Buffer Disable Override */
#define SWITCH_PF_INP_DIS                (* (reg32 *) SWITCH_PF__PC2)

/* Interrupt configuration Registers */
#define SWITCH_PF_INTCFG                 (* (reg32 *) SWITCH_PF__INTCFG)
#define SWITCH_PF_INTSTAT                (* (reg32 *) SWITCH_PF__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define SWITCH_PF_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(SWITCH_PF__SIO)
    #define SWITCH_PF_SIO_REG            (* (reg32 *) SWITCH_PF__SIO)
#endif /* (SWITCH_PF__SIO_CFG) */

/* USBIO registers */
#if !defined(SWITCH_PF__PC) && (CY_PSOC4_4200L)
    #define SWITCH_PF_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define SWITCH_PF_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define SWITCH_PF_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define SWITCH_PF_DRIVE_MODE_SHIFT       (0x00u)
#define SWITCH_PF_DRIVE_MODE_MASK        (0x07u << SWITCH_PF_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins SWITCH_PF_H */


/* [] END OF FILE */
