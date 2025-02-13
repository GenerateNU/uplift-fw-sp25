/*******************************************************************************
* File Name: BUTTON_DIR_UP.h  
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

#if !defined(CY_PINS_BUTTON_DIR_UP_H) /* Pins BUTTON_DIR_UP_H */
#define CY_PINS_BUTTON_DIR_UP_H

#include "cytypes.h"
#include "cyfitter.h"
#include "BUTTON_DIR_UP_aliases.h"


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
} BUTTON_DIR_UP_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   BUTTON_DIR_UP_Read(void);
void    BUTTON_DIR_UP_Write(uint8 value);
uint8   BUTTON_DIR_UP_ReadDataReg(void);
#if defined(BUTTON_DIR_UP__PC) || (CY_PSOC4_4200L) 
    void    BUTTON_DIR_UP_SetDriveMode(uint8 mode);
#endif
void    BUTTON_DIR_UP_SetInterruptMode(uint16 position, uint16 mode);
uint8   BUTTON_DIR_UP_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void BUTTON_DIR_UP_Sleep(void); 
void BUTTON_DIR_UP_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(BUTTON_DIR_UP__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define BUTTON_DIR_UP_DRIVE_MODE_BITS        (3)
    #define BUTTON_DIR_UP_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - BUTTON_DIR_UP_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the BUTTON_DIR_UP_SetDriveMode() function.
         *  @{
         */
        #define BUTTON_DIR_UP_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define BUTTON_DIR_UP_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define BUTTON_DIR_UP_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define BUTTON_DIR_UP_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define BUTTON_DIR_UP_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define BUTTON_DIR_UP_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define BUTTON_DIR_UP_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define BUTTON_DIR_UP_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define BUTTON_DIR_UP_MASK               BUTTON_DIR_UP__MASK
#define BUTTON_DIR_UP_SHIFT              BUTTON_DIR_UP__SHIFT
#define BUTTON_DIR_UP_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BUTTON_DIR_UP_SetInterruptMode() function.
     *  @{
     */
        #define BUTTON_DIR_UP_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define BUTTON_DIR_UP_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define BUTTON_DIR_UP_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define BUTTON_DIR_UP_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(BUTTON_DIR_UP__SIO)
    #define BUTTON_DIR_UP_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(BUTTON_DIR_UP__PC) && (CY_PSOC4_4200L)
    #define BUTTON_DIR_UP_USBIO_ENABLE               ((uint32)0x80000000u)
    #define BUTTON_DIR_UP_USBIO_DISABLE              ((uint32)(~BUTTON_DIR_UP_USBIO_ENABLE))
    #define BUTTON_DIR_UP_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define BUTTON_DIR_UP_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define BUTTON_DIR_UP_USBIO_ENTER_SLEEP          ((uint32)((1u << BUTTON_DIR_UP_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << BUTTON_DIR_UP_USBIO_SUSPEND_DEL_SHIFT)))
    #define BUTTON_DIR_UP_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << BUTTON_DIR_UP_USBIO_SUSPEND_SHIFT)))
    #define BUTTON_DIR_UP_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << BUTTON_DIR_UP_USBIO_SUSPEND_DEL_SHIFT)))
    #define BUTTON_DIR_UP_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(BUTTON_DIR_UP__PC)
    /* Port Configuration */
    #define BUTTON_DIR_UP_PC                 (* (reg32 *) BUTTON_DIR_UP__PC)
#endif
/* Pin State */
#define BUTTON_DIR_UP_PS                     (* (reg32 *) BUTTON_DIR_UP__PS)
/* Data Register */
#define BUTTON_DIR_UP_DR                     (* (reg32 *) BUTTON_DIR_UP__DR)
/* Input Buffer Disable Override */
#define BUTTON_DIR_UP_INP_DIS                (* (reg32 *) BUTTON_DIR_UP__PC2)

/* Interrupt configuration Registers */
#define BUTTON_DIR_UP_INTCFG                 (* (reg32 *) BUTTON_DIR_UP__INTCFG)
#define BUTTON_DIR_UP_INTSTAT                (* (reg32 *) BUTTON_DIR_UP__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define BUTTON_DIR_UP_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(BUTTON_DIR_UP__SIO)
    #define BUTTON_DIR_UP_SIO_REG            (* (reg32 *) BUTTON_DIR_UP__SIO)
#endif /* (BUTTON_DIR_UP__SIO_CFG) */

/* USBIO registers */
#if !defined(BUTTON_DIR_UP__PC) && (CY_PSOC4_4200L)
    #define BUTTON_DIR_UP_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define BUTTON_DIR_UP_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define BUTTON_DIR_UP_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define BUTTON_DIR_UP_DRIVE_MODE_SHIFT       (0x00u)
#define BUTTON_DIR_UP_DRIVE_MODE_MASK        (0x07u << BUTTON_DIR_UP_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins BUTTON_DIR_UP_H */


/* [] END OF FILE */
