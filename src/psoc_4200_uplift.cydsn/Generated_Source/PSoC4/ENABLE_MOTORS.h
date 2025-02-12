/*******************************************************************************
* File Name: ENABLE_MOTORS.h  
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

#if !defined(CY_PINS_ENABLE_MOTORS_H) /* Pins ENABLE_MOTORS_H */
#define CY_PINS_ENABLE_MOTORS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ENABLE_MOTORS_aliases.h"


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
} ENABLE_MOTORS_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   ENABLE_MOTORS_Read(void);
void    ENABLE_MOTORS_Write(uint8 value);
uint8   ENABLE_MOTORS_ReadDataReg(void);
#if defined(ENABLE_MOTORS__PC) || (CY_PSOC4_4200L) 
    void    ENABLE_MOTORS_SetDriveMode(uint8 mode);
#endif
void    ENABLE_MOTORS_SetInterruptMode(uint16 position, uint16 mode);
uint8   ENABLE_MOTORS_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void ENABLE_MOTORS_Sleep(void); 
void ENABLE_MOTORS_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(ENABLE_MOTORS__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define ENABLE_MOTORS_DRIVE_MODE_BITS        (3)
    #define ENABLE_MOTORS_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ENABLE_MOTORS_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the ENABLE_MOTORS_SetDriveMode() function.
         *  @{
         */
        #define ENABLE_MOTORS_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define ENABLE_MOTORS_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define ENABLE_MOTORS_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define ENABLE_MOTORS_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define ENABLE_MOTORS_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define ENABLE_MOTORS_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define ENABLE_MOTORS_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define ENABLE_MOTORS_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define ENABLE_MOTORS_MASK               ENABLE_MOTORS__MASK
#define ENABLE_MOTORS_SHIFT              ENABLE_MOTORS__SHIFT
#define ENABLE_MOTORS_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ENABLE_MOTORS_SetInterruptMode() function.
     *  @{
     */
        #define ENABLE_MOTORS_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define ENABLE_MOTORS_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define ENABLE_MOTORS_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define ENABLE_MOTORS_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(ENABLE_MOTORS__SIO)
    #define ENABLE_MOTORS_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(ENABLE_MOTORS__PC) && (CY_PSOC4_4200L)
    #define ENABLE_MOTORS_USBIO_ENABLE               ((uint32)0x80000000u)
    #define ENABLE_MOTORS_USBIO_DISABLE              ((uint32)(~ENABLE_MOTORS_USBIO_ENABLE))
    #define ENABLE_MOTORS_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define ENABLE_MOTORS_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define ENABLE_MOTORS_USBIO_ENTER_SLEEP          ((uint32)((1u << ENABLE_MOTORS_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << ENABLE_MOTORS_USBIO_SUSPEND_DEL_SHIFT)))
    #define ENABLE_MOTORS_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << ENABLE_MOTORS_USBIO_SUSPEND_SHIFT)))
    #define ENABLE_MOTORS_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << ENABLE_MOTORS_USBIO_SUSPEND_DEL_SHIFT)))
    #define ENABLE_MOTORS_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(ENABLE_MOTORS__PC)
    /* Port Configuration */
    #define ENABLE_MOTORS_PC                 (* (reg32 *) ENABLE_MOTORS__PC)
#endif
/* Pin State */
#define ENABLE_MOTORS_PS                     (* (reg32 *) ENABLE_MOTORS__PS)
/* Data Register */
#define ENABLE_MOTORS_DR                     (* (reg32 *) ENABLE_MOTORS__DR)
/* Input Buffer Disable Override */
#define ENABLE_MOTORS_INP_DIS                (* (reg32 *) ENABLE_MOTORS__PC2)

/* Interrupt configuration Registers */
#define ENABLE_MOTORS_INTCFG                 (* (reg32 *) ENABLE_MOTORS__INTCFG)
#define ENABLE_MOTORS_INTSTAT                (* (reg32 *) ENABLE_MOTORS__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define ENABLE_MOTORS_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(ENABLE_MOTORS__SIO)
    #define ENABLE_MOTORS_SIO_REG            (* (reg32 *) ENABLE_MOTORS__SIO)
#endif /* (ENABLE_MOTORS__SIO_CFG) */

/* USBIO registers */
#if !defined(ENABLE_MOTORS__PC) && (CY_PSOC4_4200L)
    #define ENABLE_MOTORS_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define ENABLE_MOTORS_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define ENABLE_MOTORS_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define ENABLE_MOTORS_DRIVE_MODE_SHIFT       (0x00u)
#define ENABLE_MOTORS_DRIVE_MODE_MASK        (0x07u << ENABLE_MOTORS_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins ENABLE_MOTORS_H */


/* [] END OF FILE */
